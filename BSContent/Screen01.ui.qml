import QtQuick 6.5
import QtQuick.Controls 6.5
import BS

Rectangle {
    id: root
    width: Constants.width   // 1920
    height: Constants.height // 1080
    color: "#EDF0F3"

    // ── Palette ──────────────────────────────────────────────────────────
    readonly property color cBg:      "#EDF0F3"
    readonly property color cPanel:   "#F4F6F8"
    readonly property color cDark:    "#1E2D3D"
    readonly property color cNavy:    "#1A3A5C"
    readonly property color cBlue:    "#1565C0"
    readonly property color cBlueLt:  "#E3F0FF"
    readonly property color cGreen:   "#2E7D32"
    readonly property color cGreenLt: "#E8F5E9"
    readonly property color cAccent:  "#43A047"
    readonly property color cBorder:  "#C5CBD3"
    readonly property color cText:    "#1C2B3A"
    readonly property color cTextLt:  "#607080"
    readonly property color cRed:     "#C62828"
    readonly property color cRedLt:   "#FFEBEE"
    readonly property color cOrange:  "#E65100"
    readonly property color cYellow:  "#F9A825"
    readonly property color cGrid:    "#D0D8E0"

    // font sizes
    readonly property int f8:  8
    readonly property int f9:  9
    readonly property int f10: 10
    readonly property int f11: 11
    readonly property int f12: 12
    readonly property int f14: 14
    readonly property int f16: 16

    // ════════════════════════════════════════════════════════════════════
    //  TOP NAVIGATION BAR
    // ════════════════════════════════════════════════════════════════════
    Rectangle {
        id: topBar
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
        height: 48
        color: cDark
        z: 20

        // Logo
        Row {
            anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter
            spacing: 8
            Rectangle {
                width: 32; height: 32; radius: 4; color: cAccent
                Column {
                    anchors.centerIn: parent; spacing: 1
                    Text { text: "TEM"; font.pixelSize: f9; font.bold: true; color: "white"; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "采集"; font.pixelSize: f8; color: "#C8E6C9"; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
            Column {
                anchors.verticalCenter: parent.verticalCenter; spacing: 1
                Text { text: "瞬变电磁数据采集系统"; font.pixelSize: f12; font.bold: true; color: "white" }
                Text { text: "Transient EM Acquisition v3.1.0"; font.pixelSize: f8; color: "#78909C"; font.family: "Consolas" }
            }
        }

        // Nav tabs
        Row {
            anchors.left: parent.left; anchors.leftMargin: 280; anchors.verticalCenter: parent.verticalCenter
            spacing: 2
            Repeater {
                model: [
                    { icon: "📁", label: "工程管理", active: true  },
                    { icon: "🔌", label: "设备连接", active: false },
                    { icon: "⚙",  label: "参数配置", active: false },
                    { icon: "☁",  label: "数据同步", active: false },
                    { icon: "↗",  label: "数据导出", active: false },
                    { icon: "▶",  label: "数据回放", active: false }
                ]
                Rectangle {
                    width: 90; height: 36; radius: 3
                    color: modelData.active ? "#2E4A6A" : "transparent"
                    border.color: modelData.active ? "#4A90D9" : "transparent"
                    border.width: 1
                    Column {
                        anchors.centerIn: parent; spacing: 2
                        Text { text: modelData.icon; font.pixelSize: f10; color: modelData.active ? "white" : "#90A4AE"; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: modelData.label; font.pixelSize: f9; color: modelData.active ? "white" : "#78909C"; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                    // active underline
                    Rectangle { visible: modelData.active; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right; height: 2; color: "#4A90D9" }
                }
            }
        }

        // Top-right cluster
        Row {
            anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
            spacing: 16
            // Sync status
            Row { spacing: 4
                Rectangle { width: 8; height: 8; radius: 4; color: cYellow; anchors.verticalCenter: parent.verticalCenter }
                Text { text: "12 条待同步"; font.pixelSize: f9; color: "#90A4AE" }
            }
            // Datetime
            Text { text: "2026-02-26  13:17"; font.pixelSize: f9; color: "#607D8B"; font.family: "Consolas" }
            // User
            Rectangle { width: 28; height: 28; radius: 14; color: cBlue
                Text { anchors.centerIn: parent; text: "张"; font.pixelSize: f10; font.bold: true; color: "white" }
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  MAIN BODY
    // ════════════════════════════════════════════════════════════════════
    Row {
        anchors.top: topBar.bottom; anchors.bottom: statusBar.top; anchors.left: parent.left; anchors.right: parent.right

        // ================================================================
        //  LEFT PANEL — Project Tree  (240px)
        // ================================================================
        Rectangle {
            id: leftPanel
            width: 240; height: parent.height
            color: cPanel
            border.color: cBorder; border.width: 1

            Column {
                anchors.fill: parent; spacing: 0

                // Panel header
                Rectangle {
                    width: parent.width; height: 36
                    color: cNavy
                    Row {
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                        Text { text: "📁"; font.pixelSize: f11; color: "#90CAF9" }
                        Text { text: "工程结构"; font.pixelSize: f11; font.bold: true; color: "white" }
                    }
                    Row {
                        anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                        Repeater {
                            model: ["新建", "打开"]
                            Rectangle {
                                width: 36; height: 22; radius: 3; color: "#2E4A6A"; border.color: "#4A90D9"; border.width: 1
                                Text { anchors.centerIn: parent; text: modelData; font.pixelSize: f9; color: "#90CAF9" }
                            }
                        }
                    }
                }

                // Connection status badge
                Rectangle {
                    width: parent.width; height: 40
                    color: "#E8F5E9"; border.color: cAccent; border.width: 1
                    Row {
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                        Rectangle { width: 12; height: 12; radius: 6; color: cAccent
                            Rectangle { anchors.centerIn: parent; width: 18; height: 18; radius: 9; color: "transparent"; border.color: cAccent; border.width: 1; opacity: 0.5 }
                        }
                        Column { spacing: 1
                            Text { text: "设备已连接"; font.pixelSize: f10; font.bold: true; color: cGreen }
                            Text { text: "192.168.1.100  |  信号 -68 dBm"; font.pixelSize: f8; color: "#4CAF50"; font.family: "Consolas" }
                        }
                    }
                }

                // Search / filter
                Rectangle {
                    width: parent.width; height: 30; color: "#E8ECF0"; border.color: cBorder; border.width: 1
                    Row {
                        anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                        Text { text: "🔍"; font.pixelSize: f10; color: cTextLt }
                        Text { text: "L1_测线西区_2026"; font.pixelSize: f9; color: cText }
                    }
                }

                // Project tree nodes
                Column {
                    width: parent.width; spacing: 0

                    // Project root
                    Rectangle {
                        width: parent.width; height: 32; color: "#DDE3EA"
                        Row {
                            anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                            Text { text: "▾"; font.pixelSize: f10; color: cTextLt }
                            Text { text: "📊"; font.pixelSize: f10 }
                            Text { text: "TEM_项目_2026"; font.pixelSize: f10; font.bold: true; color: cText }
                        }
                        Text { anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter; text: "12线"; font.pixelSize: f8; color: cTextLt }
                    }

                    // Survey lines + points
                    Repeater {
                        model: [
                            { line: "L01  西区测线", pts: 6, depth: 1, open: true },
                            { line: "L02  中区测线", pts: 8, depth: 1, open: false },
                            { line: "L03  东区测线", pts: 6, depth: 1, open: false }
                        ]
                        Column {
                            width: leftPanel.width
                            // Line row
                            Rectangle {
                                width: leftPanel.width; height: 30
                                color: index === 0 ? cBlueLt : (index%2===0 ? "#F0F3F6" : "#E8EBF0")
                                border.color: index === 0 ? "#90CAF9" : "transparent"; border.width: 1
                                Row {
                                    anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter; spacing: 4
                                    Text { text: modelData.open ? "▾" : "▸"; font.pixelSize: f9; color: cTextLt }
                                    Text { text: "📏"; font.pixelSize: f9 }
                                    Text { text: modelData.line; font.pixelSize: f10; color: index===0 ? cBlue : cText; font.bold: index===0 }
                                }
                                Text { anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter; text: modelData.pts + "点"; font.pixelSize: f8; color: cTextLt }
                                Rectangle { visible: index===0; width: 3; height: parent.height; anchors.left: parent.left; color: cBlue }
                            }
                            // Points under L01
                            Column {
                                visible: index === 0
                                width: leftPanel.width
                                Repeater {
                                    model: [
                                        { id: "P001", status: "done",    dist: "0m"   },
                                        { id: "P002", status: "done",    dist: "20m"  },
                                        { id: "P003", status: "done",    dist: "40m"  },
                                        { id: "P004", status: "active",  dist: "60m"  },
                                        { id: "P005", status: "pending", dist: "80m"  },
                                        { id: "P006", status: "pending", dist: "100m" }
                                    ]
                                    Rectangle {
                                        width: leftPanel.width; height: 26
                                        color: modelData.status === "active" ? "#FFF8E1" : "transparent"
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 36; anchors.verticalCenter: parent.verticalCenter; spacing: 5
                                            Rectangle {
                                                width: 8; height: 8; radius: 4; anchors.verticalCenter: parent.verticalCenter
                                                color: modelData.status === "done" ? cAccent : modelData.status === "active" ? cYellow : cBorder
                                            }
                                            Text { text: "📍 " + modelData.id; font.pixelSize: f9; color: modelData.status==="active"?cOrange:cText; font.bold: modelData.status==="active" }
                                            Text { text: modelData.dist; font.pixelSize: f8; color: cTextLt }
                                        }
                                        Rectangle { visible: modelData.status==="active"; width: 3; height: parent.height; anchors.left: parent.left; color: cYellow }
                                    }
                                }
                            }
                        }
                    }
                }

                // Spacer
                Item { width: parent.width; height: 1 }

                // Network diagnostics
                Rectangle {
                    width: parent.width; height: 90; color: "#F0F3F6"; border.color: cBorder; border.width: 1
                    Column {
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 8; spacing: 4
                        Text { text: "网络诊断"; font.pixelSize: f9; font.bold: true; color: cText }
                        Repeater {
                            model: [
                                { lbl: "TCP 延迟",  val: "8 ms",       ok: true  },
                                { lbl: "丢包率",    val: "0.2%",      ok: true  },
                                { lbl: "HTTPS同步", val: "未认证",     ok: false },
                                { lbl: "本地DB",    val: "正常 42MB",  ok: true  }
                            ]
                            Row {
                                spacing: 6
                                Rectangle { width: 6; height: 6; radius: 3; color: modelData.ok?cAccent:cRed; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.lbl + ":"; font.pixelSize: f8; color: cTextLt; width: 56 }
                                Text { text: modelData.val; font.pixelSize: f8; color: modelData.ok?cText:cRed; font.family: "Consolas" }
                            }
                        }
                    }
                }
            }
        }

        // ================================================================
        //  CENTER PANEL
        // ================================================================
        Rectangle {
            id: centerPanel
            width: parent.width - leftPanel.width - rightPanel.width
            height: parent.height
            color: cBg
            border.color: cBorder; border.width: 1

            Column {
                anchors.fill: parent; spacing: 0

                // ──────────────────────────────────────────────────────
                //  UPPER HALF: TCP Config  +  Acquisition Params
                // ──────────────────────────────────────────────────────
                Rectangle {
                    id: upperCenter
                    width: parent.width; height: 310
                    color: cPanel; border.color: cBorder; border.width: 1

                    Column {
                        anchors.fill: parent; spacing: 0

                        // Header
                        Rectangle {
                            width: parent.width; height: 32; color: "#D0D8E4"
                            Row {
                                anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                Text { text: "🔗  TCP 连接配置  &  采集参数"; font.pixelSize: f11; font.bold: true; color: cText }
                                Rectangle {
                                    width: 80; height: 20; radius: 2; color: "#D5F5E3"; border.color: cAccent; border.width: 1
                                    Row { anchors.centerIn: parent; spacing: 4
                                        Rectangle { width: 7; height: 7; radius: 4; color: cAccent; anchors.verticalCenter: parent.verticalCenter }
                                        Text { text: "已连接"; font.pixelSize: f9; color: cGreen }
                                    }
                                }
                            }
                            Row {
                                anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                                Text { text: "当前测点:"; font.pixelSize: f9; color: cTextLt }
                                Text { text: "L01 — P004"; font.pixelSize: f10; font.bold: true; color: cOrange }
                            }
                        }

                        // TCP + Params two-column layout
                        Row {
                            width: parent.width; height: parent.height - 32; spacing: 0

                            // ── TCP Connection column (left, 50%)
                            Rectangle {
                                width: parent.width * 0.48; height: parent.height
                                color: "transparent"; border.color: cBorder; border.width: 1

                                Column {
                                    anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 10; spacing: 8

                                    Text { text: "天线 IP 配置"; font.pixelSize: f10; font.bold: true; color: cText }

                                    // IP input
                                    Row { spacing: 8; width: parent.width
                                        Column { spacing: 3; width: parent.width - 80
                                            Text { text: "目标 IP 地址"; font.pixelSize: f9; color: cTextLt }
                                            Rectangle {
                                                width: parent.width; height: 32; radius: 3; color: "white"
                                                border.color: cBlue; border.width: 2
                                                Row {
                                                    anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                                                    Text { text: "🌐"; font.pixelSize: f10 }
                                                    Text { text: "192.168.1.100"; font.pixelSize: f11; color: cBlue; font.family: "Consolas"; font.bold: true }
                                                }
                                            }
                                        }
                                        Column { spacing: 3
                                            Text { text: "端口"; font.pixelSize: f9; color: cTextLt }
                                            Rectangle {
                                                width: 66; height: 32; radius: 3; color: "white"; border.color: cBorder; border.width: 1
                                                Text { anchors.left: parent.left; anchors.leftMargin: 6; anchors.verticalCenter: parent.verticalCenter; text: "8080"; font.pixelSize: f10; font.family: "Consolas"; color: cText }
                                            }
                                        }
                                    }

                                    // Preset addresses
                                    Text { text: "预设地址"; font.pixelSize: f9; color: cTextLt }
                                    Row { spacing: 5
                                        Repeater {
                                            model: ["192.168.1.100", "192.168.1.101", "192.168.1.102", "10.0.0.50"]
                                            Rectangle {
                                                width: 96; height: 24; radius: 3; color: index===0?"#DDEEFF":"#E8ECF0"
                                                border.color: index===0?cBlue:cBorder; border.width: 1
                                                Text { anchors.centerIn: parent; text: modelData; font.pixelSize: f8; font.family: "Consolas"; color: index===0?cBlue:cText }
                                            }
                                        }
                                    }

                                    // Connect buttons
                                    Row { spacing: 8
                                        Rectangle {
                                            width: 90; height: 30; radius: 4; color: cBlue
                                            Text { anchors.centerIn: parent; text: "🔌  连接"; font.pixelSize: f10; font.bold: true; color: "white" }
                                        }
                                        Rectangle {
                                            width: 90; height: 30; radius: 4; color: "#CFD8DC"; border.color: cBorder; border.width: 1
                                            Text { anchors.centerIn: parent; text: "断开"; font.pixelSize: f10; color: cText }
                                        }
                                        Rectangle {
                                            width: 90; height: 30; radius: 4; color: "#E8ECF0"; border.color: cBorder; border.width: 1
                                            Text { anchors.centerIn: parent; text: "Ping 测试"; font.pixelSize: f10; color: cText }
                                        }
                                    }

                                    // Device info strip
                                    Rectangle {
                                        width: parent.width; height: 54; radius: 3; color: "#F0F4F8"; border.color: cBorder; border.width: 1
                                        Column {
                                            anchors.left: parent.left; anchors.leftMargin: 8; anchors.top: parent.top; anchors.topMargin: 6; spacing: 3
                                            Text { text: "设备信息"; font.pixelSize: f9; font.bold: true; color: cText }
                                            Row { spacing: 16
                                                Repeater {
                                                    model: [
                                                        { k:"型号",   v:"TEM-A400"},
                                                        { k:"固件",   v:"FW 2.3.1"},
                                                        { k:"通道数", v:"3 CH"    },
                                                        { k:"SN",     v:"A4-0072" }
                                                    ]
                                                    Column { spacing: 1
                                                        Text { text: modelData.k; font.pixelSize: f8; color: cTextLt }
                                                        Text { text: modelData.v; font.pixelSize: f9; font.family:"Consolas"; font.bold: true; color: cText }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // ── Acquisition Params column (right, 52%)
                            Rectangle {
                                width: parent.width * 0.52; height: parent.height
                                color: "transparent"; border.color: cBorder; border.width: 1

                                Column {
                                    anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 10; spacing: 6

                                    Row { spacing: 8; width: parent.width
                                        Text { text: "采集参数"; font.pixelSize: f10; font.bold: true; color: cText; anchors.verticalCenter: parent.verticalCenter }
                                        Rectangle {
                                            width: 110; height: 22; radius: 2; color: "#E3F0FF"; border.color: cBlue; border.width: 1
                                            Text { anchors.centerIn: parent; text: "📋 复制上一测点"; font.pixelSize: f9; color: cBlue }
                                        }
                                    }

                                    // Parameter grid (2-column)
                                    Grid { columns: 2; spacing: 6; width: parent.width
                                        Repeater {
                                            model: [
                                                { lbl:"发送电流",   val:"10.0",   unit:"A",  active:false },
                                                { lbl:"采样频率",   val:"51200",  unit:"Hz", active:true  },
                                                { lbl:"采集次数",   val:"16",     unit:"次", active:false },
                                                { lbl:"采样时间",   val:"2048",   unit:"μs", active:false },
                                                { lbl:"极距",       val:"50.0",   unit:"m",  active:false },
                                                { lbl:"关断时间",   val:"500",    unit:"μs", active:false },
                                                { lbl:"叠加次数",   val:"8",      unit:"次", active:false },
                                                { lbl:"增益",       val:"×1",     unit:"",   active:false },
                                                { lbl:"发射方向",   val:"X 轴",   unit:"",   active:false },
                                                { lbl:"基距",       val:"200.0",  unit:"m",  active:false }
                                            ]
                                            Column { spacing: 2; width: 190
                                                Text { text: modelData.lbl; font.pixelSize: f9; color: cTextLt }
                                                Row { spacing: 4
                                                    Rectangle {
                                                        width: 110; height: 28; radius: 3
                                                        color: "white"
                                                        border.color: modelData.active ? cBlue : cBorder
                                                        border.width: modelData.active ? 2 : 1
                                                        Text {
                                                            anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                                            text: modelData.val; font.pixelSize: f11; font.family: "Consolas"
                                                            color: modelData.active ? cBlue : cText; font.bold: modelData.active
                                                        }
                                                    }
                                                    Text { text: modelData.unit; font.pixelSize: f10; color: cTextLt; anchors.verticalCenter: parent.verticalCenter; width: 22 }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // ──────────────────────────────────────────────────────
                //  LOWER HALF: Waveforms  +  Device Monitor
                // ──────────────────────────────────────────────────────
                Rectangle {
                    id: lowerCenter
                    width: parent.width
                    height: parent.height - upperCenter.height
                    color: cPanel; border.color: cBorder; border.width: 1

                    Column {
                        anchors.fill: parent; spacing: 0

                        // Waveform toolbar
                        Rectangle {
                            width: parent.width; height: 32; color: "#D0D8E4"
                            Row {
                                anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                                Text { text: "📈  实时波形监视"; font.pixelSize: f11; font.bold: true; color: cText }
                                Rectangle { width: 60; height: 18; radius: 2; color: cGreenLt; border.color: cAccent; border.width: 1
                                    Text { anchors.centerIn: parent; text: "● 实时"; font.pixelSize: f8; color: cGreen }
                                }
                            }
                            Row {
                                anchors.right: parent.right; anchors.rightMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                                Repeater {
                                    model: ["自适应", "暂停", "清除", "叠加显示"]
                                    Rectangle {
                                        width: 56; height: 22; radius: 3; color: "#E0E6ED"; border.color: cBorder; border.width: 1
                                        Text { anchors.centerIn: parent; text: modelData; font.pixelSize: f9; color: cText }
                                    }
                                }
                            }
                        }

                        // Waveform panels row
                        Row {
                            width: parent.width
                            height: parent.height - 32 - 72; spacing: 0

                            // Waveform panel A — Recv 接收电压
                            Rectangle {
                                width: lowerCenter.width * 0.62 / 3
                                height: lowerCenter.height - 32 - 72
                                color: "#E3F2FD"; border.color: "#1565C0"; border.width: 1

                                Column {
                                    anchors.fill: parent; spacing: 0

                                    Rectangle {
                                        width: parent.width; height: 24; color: "#1565C0"
                                        Text { anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "Recv  接收电压"; font.pixelSize: f9; font.bold: true; color: "white" }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "mV / μs"; font.pixelSize: f8; color: "white"; opacity: 0.8 }
                                    }

                                    Rectangle {
                                        width: parent.width; height: parent.height - 24 - 26; color: "white"
                                        Column {
                                            anchors.left: parent.left; anchors.top: parent.top; anchors.leftMargin: 2
                                            Repeater {
                                                model: ["1.0","0.8","0.6","0.4","0.2","0.0"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; height: 22 }
                                            }
                                        }
                                        // Horizontal grid lines
                                        Repeater {
                                            model: 6
                                            Rectangle { anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right; height: 1; color: "#E0E0E0"; y: index * 22 }
                                        }
                                        // Wave bars — Recv shape: descends then rises
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right
                                            anchors.bottom: parent.bottom; anchors.top: parent.top; spacing: 0
                                            Repeater {
                                                model: [0.50,0.48,0.45,0.40,0.30,0.20,0.16,0.20,0.28,0.35,0.40,0.44,0.46,0.47,0.48,0.49,0.50,0.50]
                                                Item { width: parent.width/18; height: parent.height
                                                    Rectangle { width: parent.width; height: parent.height * modelData; anchors.bottom: parent.bottom; color: "#1565C0"; opacity: 0.3 }
                                                    Rectangle { width: parent.width; height: 2; y: parent.height - parent.height * modelData - 1; color: "#1565C0" }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: parent.width; height: 26; color: "#F5F7F8"; border.color: cBorder; border.width: 1
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                            Repeater {
                                                model: ["0","256","512","768","1024","1280","1536","1792","2048"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; width: parent.width/9 }
                                            }
                                        }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 4; anchors.bottom: parent.bottom; anchors.bottomMargin: 2; text: "μs"; font.pixelSize: f8; color: cTextLt }
                                    }
                                }
                            }

                            // Waveform panel B — Send 发射电流
                            Rectangle {
                                width: lowerCenter.width * 0.62 / 3
                                height: lowerCenter.height - 32 - 72
                                color: "#E8F5E9"; border.color: "#2E7D32"; border.width: 1

                                Column {
                                    anchors.fill: parent; spacing: 0

                                    Rectangle {
                                        width: parent.width; height: 24; color: "#2E7D32"
                                        Text { anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "Send  发射电流"; font.pixelSize: f9; font.bold: true; color: "white" }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "A / μs"; font.pixelSize: f8; color: "white"; opacity: 0.8 }
                                    }

                                    Rectangle {
                                        width: parent.width; height: parent.height - 24 - 26; color: "white"
                                        Column {
                                            anchors.left: parent.left; anchors.top: parent.top; anchors.leftMargin: 2
                                            Repeater {
                                                model: ["1.0","0.8","0.6","0.4","0.2","0.0"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; height: 22 }
                                            }
                                        }
                                        Repeater {
                                            model: 6
                                            Rectangle { anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right; height: 1; color: "#E0E0E0"; y: index * 22 }
                                        }
                                        // Wave bars — Send shape: flat top pulse
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right
                                            anchors.bottom: parent.bottom; anchors.top: parent.top; spacing: 0
                                            Repeater {
                                                model: [0.02,0.02,0.05,0.50,0.50,0.50,0.50,0.50,0.50,0.50,0.50,0.50,0.50,0.48,0.10,0.05,0.02,0.02]
                                                Item { width: parent.width/18; height: parent.height
                                                    Rectangle { width: parent.width; height: parent.height * modelData; anchors.bottom: parent.bottom; color: "#2E7D32"; opacity: 0.3 }
                                                    Rectangle { width: parent.width; height: 2; y: parent.height - parent.height * modelData - 1; color: "#2E7D32" }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: parent.width; height: 26; color: "#F5F7F8"; border.color: cBorder; border.width: 1
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                            Repeater {
                                                model: ["0","256","512","768","1024","1280","1536","1792","2048"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; width: parent.width/9 }
                                            }
                                        }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 4; anchors.bottom: parent.bottom; anchors.bottomMargin: 2; text: "μs"; font.pixelSize: f8; color: cTextLt }
                                    }
                                }
                            }

                            // Waveform panel C — Off 关断响应
                            Rectangle {
                                width: lowerCenter.width * 0.62 / 3
                                height: lowerCenter.height - 32 - 72
                                color: "#FFF3E0"; border.color: "#E65100"; border.width: 1

                                Column {
                                    anchors.fill: parent; spacing: 0

                                    Rectangle {
                                        width: parent.width; height: 24; color: "#E65100"
                                        Text { anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "Off  关断响应"; font.pixelSize: f9; font.bold: true; color: "white" }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 8; anchors.verticalCenter: parent.verticalCenter
                                               text: "mV / μs"; font.pixelSize: f8; color: "white"; opacity: 0.8 }
                                    }

                                    Rectangle {
                                        width: parent.width; height: parent.height - 24 - 26; color: "white"
                                        Column {
                                            anchors.left: parent.left; anchors.top: parent.top; anchors.leftMargin: 2
                                            Repeater {
                                                model: ["1.0","0.8","0.6","0.4","0.2","0.0"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; height: 22 }
                                            }
                                        }
                                        Repeater {
                                            model: 6
                                            Rectangle { anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right; height: 1; color: "#E0E0E0"; y: index * 22 }
                                        }
                                        // Wave bars — Off shape: exponential decay
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 28; anchors.right: parent.right
                                            anchors.bottom: parent.bottom; anchors.top: parent.top; spacing: 0
                                            Repeater {
                                                model: [0.50,0.35,0.22,0.14,0.10,0.09,0.09,0.10,0.12,0.15,0.18,0.22,0.26,0.30,0.34,0.38,0.42,0.46]
                                                Item { width: parent.width/18; height: parent.height
                                                    Rectangle { width: parent.width; height: parent.height * modelData; anchors.bottom: parent.bottom; color: "#E65100"; opacity: 0.3 }
                                                    Rectangle { width: parent.width; height: 2; y: parent.height - parent.height * modelData - 1; color: "#E65100" }
                                                }
                                            }
                                        }
                                    }

                                    Rectangle {
                                        width: parent.width; height: 26; color: "#F5F7F8"; border.color: cBorder; border.width: 1
                                        Row {
                                            anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                            Repeater {
                                                model: ["0","256","512","768","1024","1280","1536","1792","2048"]
                                                Text { text: modelData; font.pixelSize: f8; color: "#9E9E9E"; font.family: "Consolas"; width: parent.width/9 }
                                            }
                                        }
                                        Text { anchors.right: parent.right; anchors.rightMargin: 4; anchors.bottom: parent.bottom; anchors.bottomMargin: 2; text: "μs"; font.pixelSize: f8; color: cTextLt }
                                    }
                                }
                            }

                            // Device Monitor panel (right 38%)
                            Rectangle {
                                width: lowerCenter.width * 0.38
                                height: lowerCenter.height - 32 - 72
                                color: "#F4F6F8"; border.color: cBorder; border.width: 1

                                Column {
                                    anchors.fill: parent; spacing: 0

                                    Rectangle {
                                        width: parent.width; height: 24; color: cNavy
                                        Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: "🖥  设备监控"; font.pixelSize: f10; font.bold: true; color: "white" }
                                    }

                                    // Gauges grid
                                    Grid {
                                        columns: 2; spacing: 1; width: parent.width
                                        Repeater {
                                            model: [
                                                { lbl:"电池电压", val:"12.4",  unit:"V",   icon:"🔋", ok:true,  warn:false },
                                                { lbl:"发射电流", val:"10.02", unit:"A",   icon:"⚡", ok:true,  warn:false },
                                                { lbl:"内部温度", val:"42.8",  unit:"°C",  icon:"🌡", ok:true,  warn:true  },
                                                { lbl:"信号强度", val:"-68",   unit:"dBm", icon:"📶", ok:true,  warn:false },
                                                { lbl:"采样频率", val:"51200", unit:"Hz",  icon:"〜", ok:true,  warn:false },
                                                { lbl:"数据帧率", val:"16",    unit:"fps", icon:"📊", ok:true,  warn:false }
                                            ]
                                            Rectangle {
                                                width: parent.width/2; height: 60
                                                color: modelData.warn ? "#FFF8E1" : "#FAFBFC"
                                                border.color: modelData.warn ? cYellow : cBorder; border.width: 1
                                                Column {
                                                    anchors.left: parent.left; anchors.leftMargin: 10; anchors.top: parent.top; anchors.topMargin: 8; spacing: 3
                                                    Row { spacing: 4
                                                        Text { text: modelData.icon; font.pixelSize: f12 }
                                                        Text { text: modelData.lbl; font.pixelSize: f9; color: cTextLt }
                                                    }
                                                    Row { spacing: 2; anchors.left: parent.left
                                                        Text { text: modelData.val; font.pixelSize: f14; font.bold: true; font.family: "Consolas"; color: modelData.warn ? cOrange : cText }
                                                        Text { text: " " + modelData.unit; font.pixelSize: f9; color: cTextLt; anchors.bottom: parent.bottom }
                                                    }
                                                    Rectangle { width: 60; height: 3; radius: 2; color: modelData.warn?"#FFD54F":cAccent; opacity: 0.7 }
                                                }
                                            }
                                        }
                                    }

                                    // Raw data log
                                    Rectangle {
                                        width: parent.width; height: 1; color: cBorder
                                    }
                                    Rectangle {
                                        width: parent.width
                                        height: parent.height - 24 - 360
                                        color: "#0D1117"
                                        Column {
                                            anchors.left: parent.left; anchors.leftMargin: 8; anchors.top: parent.top; anchors.topMargin: 6; spacing: 2
                                            Text { text: "原始数据流"; font.pixelSize: f9; color: "#58A6FF"; font.bold: true }
                                            Repeater {
                                                model: [
                                                    "13:17:34.221  FRAME#0451  OK  [51200 Sa]",
                                                    "13:17:34.240  FRAME#0452  OK  [51200 Sa]",
                                                    "13:17:34.259  FRAME#0453  OK  [51200 Sa]",
                                                    "13:17:34.278  FRAME#0454  WARN latency 12ms",
                                                    "13:17:34.297  FRAME#0455  OK  [51200 Sa]",
                                                    "13:17:34.316  FRAME#0456  OK  [51200 Sa]"
                                                ]
                                                Text { text: modelData; font.pixelSize: f8; color: index===3?"#F9A825":"#8B949E"; font.family: "Consolas" }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // Acquisition progress + quick actions
                        Rectangle {
                            width: parent.width; height: 72; color: "#E0E7EF"; border.color: cBorder; border.width: 1
                            Row {
                                anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; spacing: 20

                                Column { spacing: 4
                                    Row { spacing: 8
                                        Text { text: "采集进度"; font.pixelSize: f9; font.bold: true; color: cText; anchors.verticalCenter: parent.verticalCenter }
                                        Text { text: "P004  /  L01  (叠加 8/16)"; font.pixelSize: f9; color: cTextLt; anchors.verticalCenter: parent.verticalCenter }
                                    }
                                    Rectangle {
                                        width: 320; height: 10; radius: 5; color: "#C5CBD3"
                                        Rectangle { width: parent.width * 0.5; height: parent.height; radius: 5; color: cAccent }
                                        Rectangle { x: parent.width*0.5 - 5; y:-3; width: 16; height: 16; radius: 8; color: cGreen; border.color: "white"; border.width: 2 }
                                    }
                                    Text { text: "  3 / 6 测点完成   |   预计剩余 04:12"; font.pixelSize: f9; font.family: "Consolas"; color: cTextLt }
                                }

                                // Big acquire button
                                Rectangle {
                                    width: 148; height: 52; radius: 6; color: cGreen
                                    border.color: "#1B5E20"; border.width: 2
                                    Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.leftMargin: 4; anchors.rightMargin: 4; anchors.topMargin: 3; height: 14; radius: 4; color: "#66BB6A"; opacity: 0.4 }
                                    Column { anchors.centerIn: parent; spacing: 2
                                        Text { text: "▶  开始采集"; font.pixelSize: f12; font.bold: true; color: "white"; anchors.horizontalCenter: parent.horizontalCenter }
                                        Text { text: "Start Acquisition"; font.pixelSize: f8; color: "#C8E6C9"; anchors.horizontalCenter: parent.horizontalCenter }
                                    }
                                }

                                Rectangle {
                                    width: 90; height: 52; radius: 5; color: "#CFD8DC"; border.color: "#90A4AE"; border.width: 1
                                    Column { anchors.centerIn: parent; spacing: 2
                                        Text { text: "■  停止"; font.pixelSize: f11; font.bold: true; color: "#455A64"; anchors.horizontalCenter: parent.horizontalCenter }
                                        Text { text: "Stop"; font.pixelSize: f8; color: "#78909C"; anchors.horizontalCenter: parent.horizontalCenter }
                                    }
                                }

                                Rectangle {
                                    width: 90; height: 52; radius: 5; color: "#E3F0FF"; border.color: cBlue; border.width: 1
                                    Column { anchors.centerIn: parent; spacing: 2
                                        Text { text: "⏭  跳过"; font.pixelSize: f11; font.bold: true; color: cBlue; anchors.horizontalCenter: parent.horizontalCenter }
                                        Text { text: "Skip Point"; font.pixelSize: f8; color: "#5C9BD6"; anchors.horizontalCenter: parent.horizontalCenter }
                                    }
                                }

                                Rectangle {
                                    width: 90; height: 52; radius: 5; color: "#FFF3E0"; border.color: cOrange; border.width: 1
                                    Column { anchors.centerIn: parent; spacing: 2
                                        Text { text: "🔄  重采"; font.pixelSize: f11; font.bold: true; color: cOrange; anchors.horizontalCenter: parent.horizontalCenter }
                                        Text { text: "Re-acquire"; font.pixelSize: f8; color: "#EF6C00"; anchors.horizontalCenter: parent.horizontalCenter }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // ================================================================
        //  RIGHT PANEL — Judgment & Sync  (240px)
        // ================================================================
        Rectangle {
            id: rightPanel
            width: 240; height: parent.height
            color: cPanel; border.color: cBorder; border.width: 1

            Column {
                anchors.fill: parent; spacing: 0

                // Header
                Rectangle {
                    width: parent.width; height: 36; color: cNavy
                    Row {
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                        Text { text: "✓"; font.pixelSize: f14; color: "#A5D6A7" }
                        Text { text: "数据判定"; font.pixelSize: f11; font.bold: true; color: "white" }
                    }
                }

                // Current point info
                Rectangle {
                    width: parent.width; height: 50; color: "#FFF8E1"; border.color: cYellow; border.width: 1
                    Column {
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.top: parent.top; anchors.topMargin: 6; spacing: 3
                        Text { text: "当前测点"; font.pixelSize: f9; color: cTextLt }
                        Text { text: "L01 — P004  (60m)"; font.pixelSize: f11; font.bold: true; color: cOrange }
                        Text { text: "2026-02-26  13:17:31  |  叠加完成"; font.pixelSize: f8; color: cTextLt; font.family:"Consolas" }
                    }
                }

                // Data quality indicators
                Rectangle {
                    width: parent.width; height: 100; color: "#F8FAFB"; border.color: cBorder; border.width: 1
                    Column {
                        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 8; spacing: 5
                        Text { text: "信号质量评估"; font.pixelSize: f9; font.bold: true; color: cText }
                        Repeater {
                            model: [
                                { lbl: "SNR",      val: "32.4 dB",  pct: 0.81, ok: true  },
                                { lbl: "噪声基底", val: "0.8 mV",   pct: 0.15, ok: true  },
                                { lbl: "一致性",   val: "97.2%",    pct: 0.97, ok: true  }
                            ]
                            Column { spacing: 2; width: parent.width
                                Row { spacing: 0; width: parent.width
                                    Text { text: modelData.lbl; font.pixelSize: f9; color: cTextLt; width: 56 }
                                    Text { text: modelData.val; font.pixelSize: f9; font.family:"Consolas"; color: modelData.ok?cGreen:cRed; font.bold: true }
                                }
                                Rectangle { width: parent.width; height: 4; radius: 2; color: "#E0E6ED"
                                    Rectangle { width: parent.width*modelData.pct; height: 4; radius: 2; color: modelData.ok?cAccent:cRed }
                                }
                            }
                        }
                    }
                }

                // Manual judgment buttons
                Rectangle {
                    width: parent.width; height: 28; color: "#E0E6ED"; border.color: cBorder; border.width: 1
                    Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: "人工判定"; font.pixelSize: f10; font.bold: true; color: cText }
                }

                Column {
                    width: parent.width; spacing: 6
                    topPadding: 8; leftPadding: 10; rightPadding: 10

                    Row { spacing: 6; width: parent.width - 20
                        Rectangle { width: (parent.width-6)/2; height: 36; radius: 4; color: "#E8F5E9"; border.color: cAccent; border.width: 2
                            Column { anchors.centerIn: parent; spacing: 1
                                Text { text: "✅  合格"; font.pixelSize: f10; font.bold: true; color: cGreen; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: "Pass"; font.pixelSize: f8; color: "#81C784"; anchors.horizontalCenter: parent.horizontalCenter }
                            }
                        }
                        Rectangle { width: (parent.width-6)/2; height: 36; radius: 4; color: cRedLt; border.color: cRed; border.width: 2
                            Column { anchors.centerIn: parent; spacing: 1
                                Text { text: "❌  不合格"; font.pixelSize: f10; font.bold: true; color: cRed; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: "Fail"; font.pixelSize: f8; color: "#EF9A9A"; anchors.horizontalCenter: parent.horizontalCenter }
                            }
                        }
                    }

                    // AI judgment
                    Rectangle {
                        width: parent.width - 20; height: 38; radius: 4; color: "#EDE7F6"; border.color: "#7E57C2"; border.width: 1
                        Row { anchors.centerIn: parent; spacing: 6
                            Text { text: "🤖"; font.pixelSize: f12 }
                            Column { spacing: 1
                                Text { text: "AI 辅助判定"; font.pixelSize: f10; font.bold: true; color: "#512DA8" }
                                Text { text: "置信度 94.2% → 合格"; font.pixelSize: f8; color: "#7E57C2"; font.family:"Consolas" }
                            }
                        }
                    }

                    // Remark input
                    Column { spacing: 3; width: parent.width - 20
                        Text { text: "备注"; font.pixelSize: f9; color: cTextLt }
                        Rectangle { width: parent.width; height: 40; radius: 3; color: "white"; border.color: cBorder; border.width: 1
                            Text { anchors.left: parent.left; anchors.leftMargin: 6; anchors.top: parent.top; anchors.topMargin: 4; text: "地面干扰较低，波形正常"; font.pixelSize: f9; color: "#9E9E9E" }
                        }
                    }

                    // Action buttons
                    Row { spacing: 6; width: parent.width - 20
                        Rectangle { width: (parent.width-12)/3; height: 32; radius: 3; color: cGreen
                            Text { anchors.centerIn: parent; text: "💾 保存"; font.pixelSize: f9; font.bold: true; color: "white" }
                        }
                        Rectangle { width: (parent.width-12)/3; height: 32; radius: 3; color: "#E0E6ED"; border.color: cBorder; border.width: 1
                            Text { anchors.centerIn: parent; text: "⏭ 跳过"; font.pixelSize: f9; color: cText }
                        }
                        Rectangle { width: (parent.width-12)/3; height: 32; radius: 3; color: "#FFF3E0"; border.color: cOrange; border.width: 1
                            Text { anchors.centerIn: parent; text: "🔄 重采"; font.pixelSize: f9; color: cOrange }
                        }
                    }
                }

                Rectangle { width: parent.width; height: 1; color: cBorder }

                // Sync section
                Rectangle {
                    width: parent.width; height: 28; color: cNavy
                    Text { anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: "☁  同步状态"; font.pixelSize: f10; font.bold: true; color: "white" }
                }

                Column {
                    width: parent.width; spacing: 6; topPadding: 8; leftPadding: 10; rightPadding: 10

                    // Sync stats
                    Repeater {
                        model: [
                            { lbl:"已同步",   val:"38 条", color: cGreen  },
                            { lbl:"待同步",   val:"12 条", color: cOrange },
                            { lbl:"同步失败", val:"0 条",  color: cRed    }
                        ]
                        Row { spacing: 8; width: parent.width - 20
                            Rectangle { width: 10; height: 10; radius: 5; color: modelData.color; anchors.verticalCenter: parent.verticalCenter }
                            Text { text: modelData.lbl + ":"; font.pixelSize: f9; color: cTextLt; width: 52 }
                            Text { text: modelData.val; font.pixelSize: f9; font.bold: true; color: modelData.color; font.family:"Consolas" }
                        }
                    }

                    // Last sync time
                    Rectangle { width: parent.width - 20; height: 28; radius: 3; color: "#F0F4F8"; border.color: cBorder; border.width: 1
                        Column { anchors.left: parent.left; anchors.leftMargin: 6; anchors.verticalCenter: parent.verticalCenter; spacing: 1
                            Text { text: "上次同步: 13:15:02"; font.pixelSize: f8; color: cTextLt; font.family: "Consolas"}
                            Text { text: "后台服务: api.geosurv.cn"; font.pixelSize: f8; color: cTextLt; font.family: "Consolas"}
                        }
                    }

                    // Sync button
                    Rectangle { width: parent.width - 20; height: 34; radius: 4; color: cBlue
                        Row { anchors.centerIn: parent; spacing: 6
                            Text { text: "☁"; font.pixelSize: f12; color: "white" }
                            Text { text: "立即同步"; font.pixelSize: f10; font.bold: true; color: "white" }
                        }
                    }

                    // Upload log
                    Rectangle { width: parent.width - 20; height: 26; radius: 3; color: "#E8ECF0"; border.color: cBorder; border.width: 1
                        Text { anchors.centerIn: parent; text: "📋  查看上传日志"; font.pixelSize: f9; color: cTextLt }
                    }

                    Rectangle { width: parent.width; height: 1; color: cBorder }

                    // History records
                    Text { text: "本测线历史"; font.pixelSize: f9; font.bold: true; color: cText }
                    Repeater {
                        model: [
                            { id:"P001", result:"合格", time:"12:48", synced:true  },
                            { id:"P002", result:"合格", time:"13:02", synced:true  },
                            { id:"P003", result:"合格", time:"13:15", synced:false }
                        ]
                        Rectangle { width: parent.width - 20; height: 28; radius: 3; color: "#F5F7F8"; border.color: cBorder; border.width: 1
                            Row { anchors.left: parent.left; anchors.leftMargin: 8; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                                Text { text: modelData.id; font.pixelSize: f9; font.bold: true; color: cText; font.family:"Consolas" }
                                Rectangle { width: 34; height: 16; radius: 2; color: "#E8F5E9"
                                    Text { anchors.centerIn: parent; text: modelData.result; font.pixelSize: f8; color: cGreen }
                                }
                                Text { text: modelData.time; font.pixelSize: f8; color: cTextLt; font.family:"Consolas" }
                                Rectangle { width: 12; height: 12; radius: 6; color: modelData.synced?cAccent:"#CFD8DC"; anchors.verticalCenter: parent.verticalCenter }
                            }
                        }
                    }
                }
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  STATUS BAR
    // ════════════════════════════════════════════════════════════════════
    Rectangle {
        id: statusBar
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        height: 24; color: "#1A2636"

        Row {
            anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter; spacing: 18
            Row { spacing: 4
                Rectangle { width: 7; height: 7; radius: 4; color: cAccent; anchors.verticalCenter: parent.verticalCenter }
                Text { text: "采集中"; font.pixelSize: f9; color: "#78909C" }
            }
            Text { text: "工程: TEM_项目_2026  |  L01-P004  |  TCP: 192.168.1.100:8080  |  SQLite: 42 MB"; font.pixelSize: f9; color: "#607080"; font.family: "Consolas" }
        }
        Row {
            anchors.right: parent.right; anchors.rightMargin: 12; anchors.verticalCenter: parent.verticalCenter; spacing: 14
            Text { text: "MEM 41%  CPU 8%"; font.pixelSize: f9; color: "#546E7A"; font.family: "Consolas" }
            Text { text: "v3.1.0-stable"; font.pixelSize: f9; color: "#37474F" }
        }
    }
}
