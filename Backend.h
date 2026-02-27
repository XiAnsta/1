#ifndef BACKEND_H
#define BACKEND_H

#include "TcpClient.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QVariantList>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

class Backend : public QObject {
  Q_OBJECT

  // Network & Connection
  Q_PROPERTY(
      QString targetIp READ targetIp WRITE setTargetIp NOTIFY targetIpChanged)
  Q_PROPERTY(
      int connectionState READ connectionState NOTIFY connectionStateChanged)

  // Project Management
  Q_PROPERTY(
      QString currentProjectName READ currentProjectName NOTIFY projectChanged)
  Q_PROPERTY(QString currentDbPath READ currentDbPath NOTIFY projectChanged)
  Q_PROPERTY(QVariantList projectTreeModel READ projectTreeModel NOTIFY
                 projectTreeChanged)

  // Acquisition Status
  Q_PROPERTY(bool isAcquiring READ isAcquiring NOTIFY acquisitionChanged)
  Q_PROPERTY(QString currentPoint READ currentPoint WRITE setCurrentPoint NOTIFY
                 pointChanged)
  Q_PROPERTY(int progressPercent READ progressPercent NOTIFY progressChanged)

  // Device Monitor Data
  Q_PROPERTY(
      double batteryVoltage READ batteryVoltage NOTIFY monitorDataChanged)
  Q_PROPERTY(double internalTemp READ internalTemp NOTIFY monitorDataChanged)
  Q_PROPERTY(
      double signalStrength READ signalStrength NOTIFY monitorDataChanged)

  // Waveform Data (Mock arrays for UI binding)
  Q_PROPERTY(QVariantList recvWaveform READ recvWaveform NOTIFY waveformChanged)
  Q_PROPERTY(QVariantList sendWaveform READ sendWaveform NOTIFY waveformChanged)

  // Acquisition Parameters
  Q_PROPERTY(double sendCurrent READ sendCurrent WRITE setSendCurrent NOTIFY
                 sendCurrentChanged)
  Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate NOTIFY
                 sampleRateChanged)
  Q_PROPERTY(int stackCount READ stackCount WRITE setStackCount NOTIFY
                 stackCountChanged)
  Q_PROPERTY(int sampleTimeLength READ sampleTimeLength WRITE
                 setSampleTimeLength NOTIFY sampleTimeLengthChanged)
  Q_PROPERTY(QString customParams READ customParams WRITE setCustomParams NOTIFY
                 customParamsChanged)

public:
  explicit Backend(QObject *parent = nullptr);

  // Getters
  QString targetIp() const { return m_targetIp; }
  int connectionState() const { return m_connectionState; }
  bool isAcquiring() const { return m_isAcquiring; }
  QString currentPoint() const { return m_currentPoint; }
  int progressPercent() const { return m_progressPercent; }

  QString currentProjectName() const { return m_currentProjectName; }
  QString currentDbPath() const { return m_currentDbPath; }
  QVariantList projectTreeModel() const { return m_projectTreeModel; }

  double batteryVoltage() const { return m_batteryVoltage; }
  double internalTemp() const { return m_internalTemp; }
  double signalStrength() const { return m_signalStrength; }

  QVariantList recvWaveform() const { return m_recvWaveform; }
  QVariantList sendWaveform() const { return m_sendWaveform; }

  double sendCurrent() const { return m_sendCurrent; }
  int sampleRate() const { return m_sampleRate; }
  int stackCount() const { return m_stackCount; }
  int sampleTimeLength() const { return m_sampleTimeLength; }
  QString customParams() const { return m_customParams; }
  QStringList logMessages() const { return m_logMessages; }

  // Setters
  void setTargetIp(const QString &ip);
  void setCurrentPoint(const QString &point);
  Q_INVOKABLE void setSendCurrent(double current);
  Q_INVOKABLE void setSampleRate(int rate);
  Q_INVOKABLE void setStackCount(int count);
  Q_INVOKABLE void setSampleTimeLength(int length);
  Q_INVOKABLE void setCustomParams(const QString &params);

  // Project Expose to QML
  Q_INVOKABLE bool createProjectDB(const QString &fileUrl);
  Q_INVOKABLE bool openProjectDB(const QString &fileUrl);

  // Expose methods to QML
  // Read-only properties for UI display
  Q_PROPERTY(QStringList logMessages READ logMessages NOTIFY logMessagesChanged)

  Q_INVOKABLE void connectDevice();
  Q_INVOKABLE void disconnectDevice();
  Q_INVOKABLE void startAcquisition();
  Q_INVOKABLE void stopAcquisition();
  Q_INVOKABLE void skipPoint();
  Q_INVOKABLE void copyPreviousPointParams();
  Q_INVOKABLE void savePointData(bool isQualified, const QString &remark);

  // Waveform Series Updaters
  Q_INVOKABLE void updateRecvSeries(QAbstractSeries *series);
  Q_INVOKABLE void updateSendSeries(QAbstractSeries *series);
  Q_INVOKABLE void updateOffSeries(QAbstractSeries *series);

signals:
  void targetIpChanged();
  void connectionStateChanged();
  void acquisitionChanged();
  void pointChanged();
  void progressChanged();
  void monitorDataChanged();
  void waveformChanged();
  void projectChanged();
  void projectTreeChanged();
  void logMessagesChanged();

  void sendCurrentChanged();
  void sampleRateChanged();
  void stackCountChanged();
  void sampleTimeLengthChanged();
  void customParamsChanged();

  // Signal to push log messages to QML
  void logMessage(const QString &msg, bool isWarning = false);

public slots:
  void appendLog(const QString &msg, bool isWarning = false);

private slots:
  void onTcpStateChanged(TcpClient::ConnectionState newState);
  void onTcpDataReceived(const QByteArray &data);
  void onTcpError(const QString &errorMsg);

private:
  void syncParamsToSimulator();

private:
  QString m_currentProjectName = "新建工程";
  QString m_currentDbPath = "";
  QVariantList m_projectTreeModel;

  QString m_targetIp = "192.168.1.100";
  int m_connectionState = 0; // 0: Disconnected, 1: Connecting, 2: Connected
  bool m_isAcquiring = false;
  QString m_currentPoint = "P004";
  int m_progressPercent = 0;

  double m_batteryVoltage = 12.4;
  double m_internalTemp = 42.8;
  double m_signalStrength = 0.0;

  QVariantList m_recvWaveform;
  QVariantList m_sendWaveform;

  // Acquisition Parameters
  double m_sendCurrent = 10.0;
  int m_sampleRate = 51200;
  int m_stackCount = 16;
  int m_sampleTimeLength = 2048;
  QString m_customParams = "";
  QStringList m_logMessages;

  QTimer *m_statusTimer; // Poll device status
  QJsonArray m_mockDataArray;
  // TCP & Data Parsing
  TcpClient *m_tcpClient;
  QByteArray m_tcpBuffer;
  int m_currentSampleIndex;
  int m_sendFs = 25;     // Send sample rate (Hz)
  int m_offFs = 2000000; // Off sample rate (Hz)

  // Temporary storage for latest parsed structural data
  struct ParsedSample {
    int pointId;
    QVector<double> recvData;
    QVector<double> sendData;
    QVector<double> offData;
  };
  ParsedSample m_latestSample;
};

#endif // BACKEND_H
