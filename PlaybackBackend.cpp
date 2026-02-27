#include "PlaybackBackend.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QTimer>
#include <QUrl>

PlaybackBackend::PlaybackBackend(QObject *parent)
    : QObject(parent), m_totalPoints(0), m_currentPointIndex(0),
      m_batteryVoltage(12.5), m_internalTemp(35.0), m_signalStrength(80.0),
      m_isPlaying(false), m_playbackProgress(0.0), m_sampleRate(1) {

  m_playbackTimer = new QTimer(this);
  m_playbackTimer->setInterval(100); // 10 FPS
  connect(m_playbackTimer, &QTimer::timeout, this,
          &PlaybackBackend::onPlaybackTick);

  m_playbackConnectionName =
      QString("playbackDB_%1").arg(reinterpret_cast<quintptr>(this));
}

PlaybackBackend::~PlaybackBackend() {
  if (QSqlDatabase::contains(m_playbackConnectionName)) {
    QSqlDatabase::removeDatabase(m_playbackConnectionName);
  }
}

bool PlaybackBackend::openPlaybackDB(const QString &fileUrl) {
  QString localPath = QUrl(fileUrl).toLocalFile();
  if (localPath.isEmpty()) {
    localPath = fileUrl; // fallback if plain path
  }

  QFileInfo fi(localPath);
  if (!fi.exists()) {
    emit logMessage("Playback DB does not exist.", true);
    return false;
  }

  if (QSqlDatabase::contains(m_playbackConnectionName)) {
    QSqlDatabase::removeDatabase(m_playbackConnectionName);
  }

  QSqlDatabase db =
      QSqlDatabase::addDatabase("QSQLITE", m_playbackConnectionName);
  db.setDatabaseName(localPath);

  if (!db.open()) {
    emit logMessage("Failed to open Playback DB: " + db.lastError().text(),
                    true);
    return false;
  }

  m_currentDbPath = localPath;
  m_currentProjectName = fi.baseName();
  emit projectChanged();
  emit logMessage("Playback database loaded: " + m_currentProjectName, false);
  return true;
}

QVariantList PlaybackBackend::getProjectTree() {
  QVariantList tree;
  QSqlDatabase db = QSqlDatabase::database(m_playbackConnectionName);
  if (!db.isValid() || !db.isOpen())
    return tree;

  QSqlQuery qLine("SELECT * FROM Data_Line", db);
  while (qLine.next()) {
    int lineId = qLine.value("ID").toInt();
    QString lineName = qLine.value("NAME").toString();

    QVariantList pointsList;
    QSqlQuery qPoint(db);
    qPoint.prepare("SELECT * FROM Data_Point WHERE Data_LineID = ?");
    qPoint.addBindValue(lineId);
    qPoint.exec();

    while (qPoint.next()) {
      QVariantMap pt;
      pt["id"] = qPoint.value("ID").toInt();
      pt["name"] = qPoint.value("NAME").toString();
      pointsList.append(pt);
    }

    QVariantMap lineMap;
    lineMap["id"] = lineId;
    lineMap["name"] = lineName;
    lineMap["points"] = pointsList;
    tree.append(lineMap);
  }
  return tree;
}

bool PlaybackBackend::loadPointData(int pointId) {
  QSqlDatabase db = QSqlDatabase::database(m_playbackConnectionName);
  if (!db.isValid() || !db.isOpen())
    return false;

  QSqlQuery q(db);
  q.prepare("SELECT * FROM Data_Sample WHERE Data_PointID = ? ORDER BY ID DESC "
            "LIMIT 1");
  q.addBindValue(pointId);

  if (!q.exec() || !q.next()) {
    emit logMessage("No sample data found for this point.", true);
    return false;
  }

  m_sampleRate =
      q.value("SendFs").toInt(); // Assuming SendFs stores sample rate
  if (m_sampleRate <= 0)
    m_sampleRate = 51200;

  // Retrieve Base64 BLOBs directly as Strings
  QString recvStr = q.value("DATA_RECV").toString();
  QString sendStr = q.value("DATA_SEND").toString();

  QByteArray rBytes = QByteArray::fromBase64(recvStr.toUtf8());
  QByteArray sBytes = QByteArray::fromBase64(sendStr.toUtf8());

  int rFloats = rBytes.size() / sizeof(float);
  int sFloats = sBytes.size() / sizeof(float);

  const float *rFloatPtr = reinterpret_cast<const float *>(rBytes.constData());
  const float *sFloatPtr = reinterpret_cast<const float *>(sBytes.constData());

  m_fullRecvData.clear();
  m_fullSendData.clear();
  m_fullOffData.clear();

  for (int i = 0; i < rFloats; i++)
    m_fullRecvData.append(rFloatPtr[i]);
  for (int i = 0; i < sFloats; i++)
    m_fullSendData.append(sFloatPtr[i]);

  // Mock metadata
  m_batteryVoltage =
      12.0 + (QRandomGenerator::global()->generate() % 10) / 10.0;
  m_internalTemp = 36.0 + (QRandomGenerator::global()->generate() % 50) / 10.0;

  // Also get the name of the point
  QSqlQuery qp(db);
  qp.prepare("SELECT NAME FROM Data_Point WHERE ID = ?");
  qp.addBindValue(pointId);
  if (qp.exec() && qp.next()) {
    m_currentPointName = qp.value(0).toString();
  } else {
    m_currentPointName = QString("Point %1").arg(pointId);
  }

  m_playbackProgress = 0.0;
  seek(0.0); // Reset render arrays
  emit loadedPointChanged();
  emit logMessage("Loaded point " + m_currentPointName +
                      QString(" (%1 bytes)").arg(rBytes.size()),
                  false);
  return true;
}

void PlaybackBackend::play() {
  if (m_fullRecvData.isEmpty())
    return;
  if (m_playbackProgress >= 1.0)
    seek(0.0); // Restart if finished
  m_isPlaying = true;
  m_playbackTimer->start();
  emit playbackStateChanged();
}

void PlaybackBackend::pause() {
  m_isPlaying = false;
  m_playbackTimer->stop();
  emit playbackStateChanged();
}

void PlaybackBackend::seek(double progressRatio) {
  if (progressRatio < 0.0)
    progressRatio = 0.0;
  if (progressRatio > 1.0)
    progressRatio = 1.0;
  m_playbackProgress = progressRatio;

  int limitR = m_fullRecvData.size() * m_playbackProgress;
  int limitS = m_fullSendData.size() * m_playbackProgress;

  m_renderRecvData = m_fullRecvData.mid(0, qMax(1, limitR));
  m_renderSendData = m_fullSendData.mid(0, qMax(1, limitS));

  emit playbackProgressChanged();
  emit waveformChanged();
}

void PlaybackBackend::onPlaybackTick() {
  double increment = 0.02; // Scrub 2% per tick
  double nextProgress = m_playbackProgress + increment;
  if (nextProgress >= 1.0) {
    seek(1.0);
    pause(); // Auto stop at end
  } else {
    seek(nextProgress);
  }
}

void PlaybackBackend::exportCsv(const QString &destFolderUrl) {
  QString localFolder = QUrl(destFolderUrl).toLocalFile();
  if (localFolder.isEmpty())
    localFolder = destFolderUrl;

  if (m_fullRecvData.isEmpty()) {
    emit logMessage("No point loaded to export.", true);
    return;
  }

  QString filePath =
      QDir(localFolder).filePath(m_currentPointName + "_export.csv");
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << "Time(us),Recv(V),Send(A)\n";
    for (int i = 0; i < m_fullRecvData.size(); i++) {
      double t = i * (1000000.0 / qMax(1, m_sampleRate));
      float r = m_fullRecvData[i];
      float s = (i < m_fullSendData.size()) ? m_fullSendData[i] : 0.0f;
      out << t << "," << r << "," << s << "\n";
    }
    file.close();
    emit logMessage("Successfully exported to: " + filePath, false);
  } else {
    emit logMessage("Failed to write CSV file.", true);
  }
}

// Draw logic exactly like Backend.cpp but reading from m_renderRecvData
void PlaybackBackend::updateRecvSeries(QAbstractSeries *series) {
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int step = qMax(1, m_renderRecvData.size() / 1500); // Decimate
    for (int i = 0; i < m_renderRecvData.size(); i += step) {
      points.append(QPointF(i * (1000000.0 / qMax(1, m_sampleRate)),
                            qMax(0.001f, qAbs(m_renderRecvData[i]))));
    }
    xySeries->replace(points);
  }
}

void PlaybackBackend::updateSendSeries(QAbstractSeries *series) {
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int step = qMax(1, m_renderSendData.size() / 1500);
    for (int i = 0; i < m_renderSendData.size(); i += step) {
      points.append(QPointF(i * (1000000.0 / qMax(1, m_sampleRate)),
                            m_renderSendData[i]));
    }
    xySeries->replace(points);
  }
}

void PlaybackBackend::updateOffSeries(QAbstractSeries *series) {
  // Mock off series out of the last half of Recv for playback
  if (auto *xySeries = qobject_cast<QXYSeries *>(series)) {
    QList<QPointF> points;
    int startIdx = m_renderRecvData.size() / 2;
    int maxP = qMax(1, m_renderRecvData.size() - startIdx);
    int step = qMax(1, maxP / 1000);
    for (int i = startIdx; i < m_renderRecvData.size(); i += step) {
      points.append(
          QPointF((i - startIdx) * (1000000.0 / qMax(1, m_sampleRate)),
                  qMax(0.001f, qAbs(m_renderRecvData[i]))));
    }
    xySeries->replace(points);
  }
}
