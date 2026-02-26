#include "Backend.h"
#include <QDateTime>
#include <QRandomGenerator>


Backend::Backend(QObject *parent) : QObject(parent) {
  // Initialize with some default flat data
  for (int i = 0; i < 18; ++i) {
    m_recvWaveform.append(0.0);
    m_sendWaveform.append(0.0);
  }

  m_simTimer = new QTimer(this);
  connect(m_simTimer, &QTimer::timeout, this, &Backend::simulateDataStream);
}

void Backend::setTargetIp(const QString &ip) {
  if (m_targetIp != ip) {
    m_targetIp = ip;
    emit targetIpChanged();
  }
}

void Backend::connectDevice() {
  if (m_isConnected)
    return;

  emit logMessage("Attempting to connect to TCP " + m_targetIp + ":8080...",
                  false);

  // Simulate network delay
  QTimer::singleShot(1000, this, [this]() {
    m_isConnected = true;
    m_batteryVoltage = 12.5;
    m_internalTemp = 38.0;
    emit connectionChanged();
    emit monitorDataChanged();
    emit logMessage("Connected successfully. HW: TEM-A400 FW: 2.3.1", false);
  });
}

void Backend::disconnectDevice() {
  m_isConnected = false;
  m_isAcquiring = false;
  m_simTimer->stop();
  emit connectionChanged();
  emit acquisitionChanged();
  emit logMessage("Disconnected from device.", true);
}

void Backend::startAcquisition() {
  if (!m_isConnected) {
    emit logMessage("Error: Device not connected!", true);
    return;
  }
  if (m_isAcquiring)
    return;

  m_isAcquiring = true;
  m_progressPercent = 0;
  emit acquisitionChanged();
  emit progressChanged();
  emit logMessage("Started TEM acquisition on " + m_currentPoint, false);

  // Start generating fake waveform data at 20fps
  m_simTimer->start(50);
}

void Backend::stopAcquisition() {
  if (!m_isAcquiring)
    return;
  m_isAcquiring = false;
  m_simTimer->stop();
  emit acquisitionChanged();
  emit logMessage("Acquisition stopped manually.", true);
}

void Backend::skipPoint() {
  stopAcquisition();
  // Simulate moving to next point (P004 -> P005)
  m_currentPoint = "P005";
  emit pointChanged();
  emit logMessage("Skipped to next measurement point: P005", false);
}

void Backend::simulateDataStream() {
  // Update progress
  m_progressPercent += 1;
  if (m_progressPercent >= 100) {
    m_progressPercent = 100;
    stopAcquisition();
    emit logMessage("Acquisition completed for " + m_currentPoint, false);
  }
  emit progressChanged();

  // Randomize sensor telemetry slightly
  m_batteryVoltage -= 0.001;
  m_internalTemp += 0.05;
  emit monitorDataChanged();

  // Generate changing waveform data
  QVariantList newRecv;
  QVariantList newSend;
  for (int i = 0; i < 18; ++i) {
    double noise = QRandomGenerator::global()->generateDouble() * 0.1;

    // Mock Send pulse
    if (i > 2 && i < 13)
      newSend.append(0.5 - noise * 0.2);
    else
      newSend.append(noise * 0.1);

    // Mock Recv decay
    double decay = 0.5 * qExp(-i / 5.0) + noise;
    newRecv.append(qMin(1.0, decay));
  }

  m_recvWaveform = newRecv;
  m_sendWaveform = newSend;
  emit waveformChanged();

  // Periodically throw a frame log
  if (m_progressPercent % 10 == 0) {
    emit logMessage(
        QString("FRAME#%1  OK  [51200 Sa]").arg(1000 + m_progressPercent),
        false);
  }
}
