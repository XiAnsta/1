import socket
import threading
import time
import random
import base64
import struct
import json

# ==================== 配置参数 ====================
HOST = '0.0.0.0'  # 监听所有IP
PORT = 8888         # 模拟设备端口
CURRENT_POINT_ID = 1
CURRENT_ID = 1

# 采集参数状态
PARAMS = {
    "send_current": 10.0,
    "sample_rate": 51200,
    "stack_count": 16,
    "sample_time": 2048,
    "custom": ""
}

# ==================== 生成模拟数据核心函数 ====================
def generate_sim_binary_data(length=655, data_type="recv"):
    """生成模拟的二进制波形数据（big-endian IEEE 754 doubles）
    匹配真实数据库的格式和值域范围
    recv: -1 ~ 10 V 范围
    send: -40 ~ 40 A 范围
    off:  -80 ~ 40 V 范围
    """
    import math
    data = bytearray()
    for i in range(length):
        t = i / length
        if data_type == "recv":
            # 模拟接收电压：先上升后衰减，范围 -1 ~ 10
            base = 10.0 * math.exp(-3.0 * t) * math.sin(2 * math.pi * 5 * t)
            noise = random.uniform(-0.3, 0.3)
            value = base + noise
        elif data_type == "send":
            # 模拟发射电流：方波 + 噪声，范围 -40 ~ 40
            if t < 0.45:
                value = 38.0 + random.uniform(-1, 1)
            elif t < 0.55:
                value = 38.0 * (1 - (t - 0.45) / 0.1) * 2 - 38.0
                value += random.uniform(-2, 2)
            else:
                value = -38.0 + random.uniform(-1, 1)
        else:  # off
            # 模拟关断响应：快速衰减，范围 -80 ~ 40
            value = 38.0 * math.exp(-8.0 * t) - 77.0 * (1 - math.exp(-2.0 * t)) * math.exp(-5.0 * t)
            value += random.uniform(-2, 2)
        # 打包为 big-endian double (8 bytes)
        data.extend(struct.pack('>d', value))
    return bytes(data)

def encode_base64_safe(binary_data):
    """生成与样本一致的Base64编码（无换行）"""
    return base64.b64encode(binary_data).decode('utf-8').replace('\n', '')

def generate_sim_db_record():
    """生成完整的模拟数据库记录（完全匹配你的样本结构）"""
    global CURRENT_POINT_ID, CURRENT_ID
    
    # 1. 生成各类Base64编码数据（big-endian doubles，匹配真实数据库格式）
    data_recv = encode_base64_safe(generate_sim_binary_data(655, "recv"))
    data_recv_len = encode_base64_safe(generate_sim_binary_data(100, "recv"))
    data_recv_pos = encode_base64_safe(generate_sim_binary_data(100, "recv"))
    data_send = encode_base64_safe(generate_sim_binary_data(500, "send"))
    data_soff = encode_base64_safe(generate_sim_binary_data(500, "off"))
    
    # 2. 生成时间戳（毫秒级）
    start_time = int(time.time() * 1000)
    
    # 3. 组装完整记录
    record = {
        "DATA_RECV": data_recv,
        "DATA_RECV_LEN": data_recv_len,
        "DATA_RECV_POS": data_recv_pos,
        "DATA_SEND": data_send,
        "DATA_SOFF": data_soff,
        "Data_PointID": CURRENT_POINT_ID,
        "DeviceType": 1,
        "ID": CURRENT_ID,
        "NOTE": None,
        "PERIOD": 500,
        "RecvFs": float(PARAMS["sample_rate"]),
        "SampleOffFs": 2000000.0,
        "SampleSendFs": 2000000.0,
        "SendFs": 25.0,
        "SendCurrent": PARAMS["send_current"],
        "StackCount": PARAMS["stack_count"],
        "StartTime": start_time,
        "TYPE": 1,
        "USE": 1
    }
    
    # 4. 更新ID
    CURRENT_ID += 1
    CURRENT_POINT_ID += 5  # 模拟测点编号递增：1, 6, 11...
    
    return record

# ==================== TCP通信处理 ====================
def handle_client_connection(conn, addr):
    """处理与客户端的单个连接"""
    print(f"[模拟设备] 客户端已连接：{addr}")
    global CURRENT_POINT_ID
    
    try:
        while True:
            # 接收客户端指令
            data = conn.recv(1024).decode('utf-8').strip()
            if not data:
                break
            
            print(f"[模拟设备] 收到指令：{data}")
            
            if data == "START_COLLECT":
                # 模拟采集过程：分3次发送数据（模拟采集次数=3）
                print("[模拟设备] 开始采集...")
                for i in range(3):
                    time.sleep(0.3)  # 模拟采集间隔
                    record = generate_sim_db_record()
                    # 发送JSON格式数据
                    conn.sendall((json.dumps(record) + '\n').encode('utf-8'))
                print("[模拟设备] 采集完成")
            
            elif data == "NEXT_POINT":
                # 切换到下一个测点
                print(f"[模拟设备] 切换到测点：{CURRENT_POINT_ID}")
                response = {"status": "success", "next_point": CURRENT_POINT_ID}
                conn.sendall((json.dumps(response) + '\n').encode('utf-8'))
            
            elif data == "RESET_POINT":
                # 重置测点编号
                CURRENT_POINT_ID = 1
                print("[模拟设备] 测点已重置为1")
                response = {"status": "success", "reset_point": 1}
                conn.sendall((json.dumps(response) + '\n').encode('utf-8'))
            
            elif data == "GET_STATUS":
                # 返回设备状态
                status = {
                    "status": "connected",
                    "current_point": CURRENT_POINT_ID,
                    "battery_voltage": round(random.uniform(11.8, 12.5), 2),
                    "temperature": round(random.uniform(25, 35), 1),
                    "params": PARAMS
                }
                conn.sendall((json.dumps(status) + '\n').encode('utf-8'))
            
            elif data.startswith("SET_PARAMS:"):
                # 更新参数
                try:
                    params_data = json.loads(data.split(":", 1)[1])
                    if "send_current" in params_data: PARAMS["send_current"] = params_data["send_current"]
                    if "sample_rate" in params_data: PARAMS["sample_rate"] = params_data["sample_rate"]
                    if "stack_count" in params_data: PARAMS["stack_count"] = params_data["stack_count"]
                    if "sample_time" in params_data: PARAMS["sample_time"] = params_data["sample_time"]
                    if "custom" in params_data: PARAMS["custom"] = params_data["custom"]
                    print(f"[模拟设备] 参数已更新: {PARAMS}")
                    conn.sendall(b'{"status": "success", "msg": "params_updated"}\n')
                except Exception as e:
                    print(f"[模拟设备] 参数解析失败: {e}")
                    conn.sendall(b'{"error": "parse_failed"}\n')
            
            else:
                # 未知指令
                conn.sendall(b'{"error": "unknown_command"}\n')
    
    except Exception as e:
        print(f"[模拟设备] 连接异常：{e}")
    finally:
        conn.close()
        print(f"[模拟设备] 客户端已断开：{addr}")

# ==================== 启动模拟设备服务端 ====================
def start_sim_device():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        print(f"========================================")
        print(f"  瞬变电磁模拟设备已启动")
        print(f"  监听地址：{HOST}:{PORT}")
        print(f"  支持指令：START_COLLECT, NEXT_POINT, RESET_POINT, GET_STATUS")
        print(f"========================================")
        
        while True:
            conn, addr = s.accept()
            # 每个客户端连接启动一个独立线程
            client_thread = threading.Thread(
                target=handle_client_connection,
                args=(conn, addr),
                daemon=True
            )
            client_thread.start()

if __name__ == "__main__":
    start_sim_device()