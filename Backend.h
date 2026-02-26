#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT

    // Network & Connection
    Q_PROPERTY(QString targetIp READ targetIp WRITE setTargetIp NOTIFY targetIpChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)
    
    // Acquisition Status
    Q_PROPERTY(bool isAcquiring READ isAcquiring NOTIFY acquisitionChanged)
    Q_PROPERTY(QString currentPoint READ currentPoint NOTIFY pointChanged)
    Q_PROPERTY(int progressPercent READ progressPercent NOTIFY progressChanged)

    // Device Monitor Data
    Q_PROPERTY(double batteryVoltage READ batteryVoltage NOTIFY monitorDataChanged)
    Q_PROPERTY(double internalTemp READ internalTemp NOTIFY monitorDataChanged)
    Q_PROPERTY(double signalStrength READ signalStrength NOTIFY monitorDataChanged)

    // Waveform Data (Mock arrays for UI binding)
    Q_PROPERTY(QVariantList recvWaveform READ recvWaveform NOTIFY waveformChanged)
    Q_PROPERTY(QVariantList sendWaveform READ sendWaveform NOTIFY waveformChanged)

public:
    explicit Backend(QObject *parent = nullptr);

    // Getters
    QString targetIp() const { return m_targetIp; }
    bool isConnected() const { return m_isConnected; }
    bool isAcquiring() const { return m_isAcquiring; }
    QString currentPoint() const { return m_currentPoint; }
    int progressPercent() const { return m_progressPercent; }
    
    double batteryVoltage() const { return m_batteryVoltage; }
    double internalTemp() const { return m_internalTemp; }
    double signalStrength() const { return m_signalStrength; }

    QVariantList recvWaveform() const { return m_recvWaveform; }
    QVariantList sendWaveform() const { return m_sendWaveform; }

    // Setters
    void setTargetIp(const QString &ip);

    // Expose methods to QML
    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void startAcquisition();
    Q_INVOKABLE void stopAcquisition();
    Q_INVOKABLE void skipPoint();

signals:
    void targetIpChanged();
    void connectionChanged();
    void acquisitionChanged();
    void pointChanged();
    void progressChanged();
    void monitorDataChanged();
    void waveformChanged();
    
    // Signal to push log messages to QML
    void logMessage(const QString &msg, bool isWarning = false);

private slots:
    void simulateDataStream();

private:
    QString m_targetIp = "192.168.1.100";
    bool m_isConnected = false;
    bool m_isAcquiring = false;
    QString m_currentPoint = "P004";
    int m_progressPercent = 0;

    double m_batteryVoltage = 12.4;
    double m_internalTemp = 42.8;
    double m_signalStrength = -68.0;

    QVariantList m_recvWaveform;
    QVariantList m_sendWaveform;

    QTimer *m_simTimer;
};

#endif // BACKEND_H
