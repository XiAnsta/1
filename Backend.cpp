#include "Backend.h"
#include "DatabaseManager.h"
#include <QByteArray>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QRandomGenerator>
#include <QStandardPaths>
#include <QUrl>
#include <QVariantMap>
#include <QVector>

Backend::Backend(QObject *parent)
    : QObject(parent), m_targetIp("192.168.1.100"), m_connectionState(0),
      m_currentProjectName("-"), m_currentDbPath("-"), m_internalTemp(35.0),
      m_signalStrength(-65.0), m_isAcquiring(false), m_progressPercent(0),
      m_currentSampleIndex(0) {
  // Initialize DB
  QString dbPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
      "/tem_data.db";
  QDir().mkpath(
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
  DatabaseManager::instance().initialize(dbPath);

  // Initialize with some default flat data
  for (int i = 0; i < 18; ++i) {
    m_recvWaveform.append(0.0);
    m_sendWaveform.append(0.0);
  }

  m_statusTimer = new QTimer(this);
  connect(m_statusTimer, &QTimer::timeout, this, [this]() {
    if (m_connectionState == TcpClient::Connected) {
      if (m_tcpClient) {
        m_tcpClient->sendData("GET_STATUS\n");
      }
    }
  });
  // Start polling status every 2 seconds
  m_statusTimer->start(2000);

  m_tcpClient = new TcpClient(this);
  connect(m_tcpClient, &TcpClient::stateChanged, this,
          &Backend::onTcpStateChanged);
  connect(m_tcpClient, &TcpClient::dataReceived, this,
          &Backend::onTcpDataReceived);
  connect(m_tcpClient, &TcpClient::errorOccurred, this, &Backend::onTcpError);

  // Load mock data array
  QFile file("DB_js/Data_Sample.json");
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray data = file.readAll();
    m_mockDataArray = QJsonDocument::fromJson(data).array();
  }
}

// Project Expose to QML
bool Backend::createProjectDB(const QString &fileUrl) {
  // QML FileDialog passes a URL like file:///D:/path...
  QString localPath = QUrl(fileUrl).toLocalFile();
  if (localPath.isEmpty()) {
    localPath = fileUrl; // Fallback just in case
  }

  qDebug() << "Creating new project database at:" << localPath;

  if (DatabaseManager::instance().initialize(localPath)) {
    m_currentDbPath = localPath;
    // Extract filename for project name
    QFileInfo fi(localPath);
    m_currentProjectName = fi.baseName();

    // Setup initial project in DB
    QVariantMap pData;
    pData["CreateTime"] = QDateTime::currentSecsSinceEpoch();
    DatabaseManager::instance().createProject(pData);

    // Blank canvas for new project
    m_projectTreeModel.clear();

    emit projectChanged();
    emit projectTreeChanged();
    return true;
  } else {
    qDebug() << "Failed to create Database:" << localPath;
    return false;
  }
}

bool Backend::openProjectDB(const QString &fileUrl) {
  QString localPath = QUrl(fileUrl).toLocalFile();
  if (localPath.isEmpty()) {
    localPath = fileUrl;
  }

  qDebug() << "Opening existing project database at:" << localPath;

  if (DatabaseManager::instance().initialize(localPath)) {
    m_currentDbPath = localPath;
    QFileInfo fi(localPath);
    m_currentProjectName = fi.baseName();

    // TODO: Load existing lines and points from Data_Line and Data_Point
    // into m_projectTreeModel here.
    m_projectTreeModel.clear();

    emit projectChanged();
    emit projectTreeChanged();
    return true;
  } else {
    qDebug() << "Failed to open Database:" << localPath;
    return false;
  }
}

void Backend::setTargetIp(const QString &ip) {
  if (m_targetIp != ip) {
    m_targetIp = ip;
    emit targetIpChanged();
  }
}

void Backend::setCurrentPoint(const QString &point) {
  if (m_currentPoint != point) {
    m_currentPoint = point;
    emit pointChanged();
  }
}

void Backend::copyPreviousPointParams() {
  // Mock logic to copy previous point. In reality this queries the local SQLite
  // DB. We'll simulate fetching params from the previous point.
  setSendCurrent(12.5);
  setSampleRate(102400);
  setStackCount(32);
  setSampleTimeLength(4096);
  setCustomParams("Copied from P003");
  appendLog("Previous parameters successfully copied.", false);
}

void Backend::connectDevice() {
  if (m_connectionState != TcpClient::Disconnected)
    return;

  // Remove simulator timer since we talk to external python now
  // m_simTimer->start(50);

  m_tcpClient->connectToServer(m_targetIp, 8888);
}

void Backend::disconnectDevice() {
  m_tcpClient->disconnectFromServer();

  if (m_isAcquiring) {
    m_isAcquiring = false;
    emit acquisitionChanged();
  }
}

void Backend::startAcquisition() {
  if (m_connectionState != TcpClient::Connected) {
    appendLog("Error: Device not connected!", true);
    return;
  }
  if (m_isAcquiring)
    return;

  m_isAcquiring = true;
  m_progressPercent = 0;
  m_currentSampleIndex = 0;
  m_tcpBuffer.clear();

  // Send start command to Python Simulator
  m_tcpClient->sendData("START_COLLECT\n");

  emit acquisitionChanged();
  emit progressChanged();
  appendLog("Sent START_COLLECT to simulator for " + m_currentPoint, false);
}

void Backend::stopAcquisition() {
  if (!m_isAcquiring)
    return;
  m_isAcquiring = false;
  emit acquisitionChanged();
  appendLog("Acquisition stopped manually.", true);
}

void Backend::skipPoint() {
  stopAcquisition();
  // Simulate moving to next point (P004 -> P005)
  m_currentPoint = "P005";
  emit pointChanged();
  appendLog("Skipped to next measurement point: P005", false);
}

void Backend::setSendCurrent(double current) {
  if (m_sendCurrent == current)
    return;
  m_sendCurrent = current;
  emit sendCurrentChanged();
  syncParamsToSimulator();
}

void Backend::setSampleRate(int rate) {
  if (m_sampleRate == rate)
    return;
  m_sampleRate = rate;
  emit sampleRateChanged();
  syncParamsToSimulator();
}

void Backend::setStackCount(int count) {
  if (m_stackCount == count)
    return;
  m_stackCount = count;
  emit stackCountChanged();
  syncParamsToSimulator();
}

void Backend::setSampleTimeLength(int length) {
  if (m_sampleTimeLength == length)
    return;
  m_sampleTimeLength = length;
  emit sampleTimeLengthChanged();
  syncParamsToSimulator();
}

void Backend::setCustomParams(const QString &params) {
  if (m_customParams == params)
    return;
  m_customParams = params;
  emit customParamsChanged();
  syncParamsToSimulator();
}

void Backend::syncParamsToSimulator() {
  if (m_connectionState != TcpClient::Connected)
    return;

  QVariantMap params;
  params["send_current"] = m_sendCurrent;
  params["sample_rate"] = m_sampleRate;
  params["stack_count"] = m_stackCount;
  params["sample_time"] = m_sampleTimeLength;
  params["custom"] = m_customParams;

  QByteArray jsonData =
      QJsonDocument::fromVariant(params).toJson(QJsonDocument::Compact);
  m_tcpClient->sendData("SET_PARAMS:" + jsonData + "\n");
}

void Backend::onTcpStateChanged(TcpClient::ConnectionState newState) {
  m_connectionState = static_cast<int>(newState);
  emit connectionStateChanged();

  if (newState == TcpClient::Connected) {
    appendLog("Connected to simulator at " + m_targetIp, false);
    m_tcpClient->sendData("GET_STATUS\n");
  } else if (newState == TcpClient::Disconnected) {
    appendLog("Disconnected from simulator.", true);
  }
}

void Backend::appendLog(const QString &msg, bool isWarning) {
  QString timeStr = QTime::currentTime().toString("HH:mm:ss.zzz");
  QString formattedMsg = QString("%1  %2").arg(timeStr, msg);

  if (isWarning) {
    formattedMsg = "<font color=\"#F9A825\">" + formattedMsg + "</font>";
  }

  m_logMessages.prepend(formattedMsg);
  if (m_logMessages.size() > 50) {
    m_logMessages.removeLast();
  }

  emit logMessagesChanged();
  emit logMessage(msg, isWarning); // Keep emitting the old signal just in case
}

void Backend::onTcpDataReceived(const QByteArray &data) {
  m_tcpBuffer.append(data);

  int newlineIdx;
  while ((newlineIdx = m_tcpBuffer.indexOf('\n')) != -1) {
    QByteArray frame = m_tcpBuffer.left(newlineIdx).trimmed();
    m_tcpBuffer.remove(0, newlineIdx + 1);

    if (frame.isEmpty())
      continue;

    // Parse JSON frame from Python Simulator
    QJsonDocument doc = QJsonDocument::fromJson(frame);
    if (!doc.isObject())
      continue;

    QJsonObject obj = doc.object();

    // Check if it's a GET_STATUS response
    if (obj.contains("status") && obj["status"].toString() == "connected") {
      m_batteryVoltage = obj["battery_voltage"].toDouble();
      m_internalTemp = obj["temperature"].toDouble();
      // The simulator changes point ID, we could sync it, but usually we drive
      // it
      emit monitorDataChanged();
      continue;
    }

    // Otherwise it is an Acquisition Sample (has DATA_RECV)
    if (obj.contains("DATA_RECV")) {
      QString recvB64 = obj["DATA_RECV"].toString();
      QString sendB64 = obj["DATA_SEND"].toString();
      QString offB64 = obj["DATA_SOFF"].toString();

      QByteArray recvRaw = QByteArray::fromBase64(recvB64.toUtf8());
      QByteArray sendRaw = QByteArray::fromBase64(sendB64.toUtf8());
      QByteArray offRaw = QByteArray::fromBase64(offB64.toUtf8());

      // Data format: big-endian IEEE 754 doubles (8 bytes per value)
      // This matches the DB_js/Data_Sample.json format
      QVector<double> recvData;
      for (int i = 0; i + 7 < recvRaw.size(); i += 8) {
        quint64 bits = 0;
        for (int b = 0; b < 8; ++b)
          bits = (bits << 8) | static_cast<quint8>(recvRaw[i + b]);
        double val;
        memcpy(&val, &bits, sizeof(double));
        recvData.append(val);
      }

      QVector<double> sendData;
      for (int i = 0; i + 7 < sendRaw.size(); i += 8) {
        quint64 bits = 0;
        for (int b = 0; b < 8; ++b)
          bits = (bits << 8) | static_cast<quint8>(sendRaw[i + b]);
        double val;
        memcpy(&val, &bits, sizeof(double));
        sendData.append(val);
      }

      QVector<double> offData;
      for (int i = 0; i + 7 < offRaw.size(); i += 8) {
        quint64 bits = 0;
        for (int b = 0; b < 8; ++b)
          bits = (bits << 8) | static_cast<quint8>(offRaw[i + b]);
        double val;
        memcpy(&val, &bits, sizeof(double));
        offData.append(val);
      }

      m_latestSample.pointId = obj["Data_PointID"].toInt();
      m_latestSample.recvData = recvData;
      m_latestSample.sendData = sendData;
      m_latestSample.offData = offData;

      // Update device monitor from sample metadata
      if (obj.contains("RecvFs")) {
        m_signalStrength =
            obj["RecvFs"].toDouble() / 10000.0; // Scale to percentage-like
      }
      m_sampleRate = obj.value("RecvFs").toInt(m_sampleRate);
      m_sendFs = qMax(1, obj.value("SendFs").toInt(25));
      m_offFs = qMax(1, obj.value("SampleOffFs").toInt(2000000));
      emit monitorDataChanged();

      // Update QML charts safely (Subsample if necessary)
      QVariantList newRecv;
      QVariantList newSend;
      int rStep = qMax(1, recvData.size() / 1500);
      for (int i = 0; i < recvData.size(); i += rStep)
        newRecv.append(recvData[i]);
      int sStep = qMax(1, sendData.size() / 1500);
      for (int i = 0; i < sendData.size(); i += sStep)
        newSend.append(sendData[i]);

      m_recvWaveform = newRecv;
      m_sendWaveform = newSend;

      emit waveformChanged();

      m_currentSampleIndex++;
      m_progressPercent =
          qMin(100, m_currentSampleIndex * 33); // Simulator sends 3 frames
      emit progressChanged();

      appendLog(QString("Received Frame #%1 (%2 bytes)")
                    .arg(m_currentSampleIndex)
                    .arg(recvRaw.size()),
                false);

      if (m_progressPercent >= 99) {
        m_progressPercent = 100;
        emit progressChanged();
        appendLog("Acquisition Complete", false);
        stopAcquisition();
      }
    }
  }
}

void Backend::onTcpError(const QString &errorMsg) {
  appendLog("TCP Exception: " + errorMsg, true);
}

void Backend::updateRecvSeries(QAbstractSeries *series) {
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int step = qMax(1, (int)(m_latestSample.recvData.size() / 1000));
    for (int i = 0; i < m_latestSample.recvData.size(); i += step) {
      // time in microsecons
      points.append(QPointF(i * (1000000.0 / qMax(1, m_sampleRate)),
                            m_latestSample.recvData[i]));
    }
    xySeries->replace(points);
  }
}

void Backend::updateSendSeries(QAbstractSeries *series) {
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int step = qMax(1, (int)(m_latestSample.sendData.size() / 1000));
    for (int i = 0; i < m_latestSample.sendData.size(); i += step) {
      points.append(QPointF(i * (1000000.0 / qMax(1, m_sendFs)),
                            m_latestSample.sendData[i]));
    }
    xySeries->replace(points);
  }
}

void Backend::updateOffSeries(QAbstractSeries *series) {
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int step = qMax(1, (int)(m_latestSample.offData.size() / 1000));
    for (int i = 0; i < m_latestSample.offData.size(); i += step) {
      points.append(QPointF(i * (1000000.0 / qMax(1, m_offFs)),
                            m_latestSample.offData[i]));
    }
    xySeries->replace(points);
  }
}

void Backend::savePointData(bool isQualified, const QString &remark) {
  if (m_latestSample.recvData.isEmpty()) {
    appendLog("WARN No data to save", true);
    return;
  }

  QVector<float> rFloat, sFloat, oFloat;
  for (double d : m_latestSample.recvData)
    rFloat.append(static_cast<float>(d));
  for (double d : m_latestSample.sendData)
    sFloat.append(static_cast<float>(d));
  for (double d : m_latestSample.offData)
    oFloat.append(static_cast<float>(d));

  QByteArray rB64 =
      QByteArray(reinterpret_cast<const char *>(rFloat.constData()),
                 rFloat.size() * sizeof(float))
          .toBase64();
  QByteArray sB64 =
      QByteArray(reinterpret_cast<const char *>(sFloat.constData()),
                 sFloat.size() * sizeof(float))
          .toBase64();
  QByteArray oB64 =
      QByteArray(reinterpret_cast<const char *>(oFloat.constData()),
                 oFloat.size() * sizeof(float))
          .toBase64();

  QVariantMap sampleMeta;
  sampleMeta["isQualified"] = isQualified;
  sampleMeta["remark"] = remark;
  sampleMeta["sendCurrent"] = m_sendCurrent;
  sampleMeta["sampleRate"] = m_sampleRate;
  sampleMeta["stackCount"] = m_stackCount;

  bool ok = DatabaseManager::instance().saveSample(
      m_latestSample.pointId, sampleMeta, rB64, sB64, oB64);
  if (ok) {
    appendLog(QString("Saved data for %1 (Qualified: %2)")
                  .arg(m_currentPoint)
                  .arg(isQualified ? "Yes" : "No"),
              false);
  } else {
    appendLog("Failed to save data. No active project DB?", true);
  }
}
