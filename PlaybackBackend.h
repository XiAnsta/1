#ifndef PLAYBACKBACKEND_H
#define PLAYBACKBACKEND_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QVariantMap>
#include <QVector>
#include <QtCharts/QXYSeries>


class PlaybackBackend : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      QString currentProjectName READ currentProjectName NOTIFY projectChanged)
  Q_PROPERTY(QString currentDbPath READ currentDbPath NOTIFY projectChanged)

  Q_PROPERTY(int totalPoints READ totalPoints NOTIFY loadedPointChanged)
  Q_PROPERTY(
      int currentPointIndex READ currentPointIndex NOTIFY loadedPointChanged)
  Q_PROPERTY(
      QString currentPointName READ currentPointName NOTIFY loadedPointChanged)

  // Device Info from history
  Q_PROPERTY(
      double batteryVoltage READ batteryVoltage NOTIFY loadedPointChanged)
  Q_PROPERTY(double internalTemp READ internalTemp NOTIFY loadedPointChanged)
  Q_PROPERTY(
      double signalStrength READ signalStrength NOTIFY loadedPointChanged)

  // Playback state
  Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY playbackStateChanged)
  Q_PROPERTY(double playbackProgress READ playbackProgress NOTIFY
                 playbackProgressChanged) // 0.0 to 1.0

public:
  explicit PlaybackBackend(QObject *parent = nullptr);
  ~PlaybackBackend();

  // Load an existing SQLite database file independent of the main
  // DatabaseManager
  Q_INVOKABLE bool openPlaybackDB(const QString &fileUrl);

  // Return the Line/Point tree for the playback database
  Q_INVOKABLE QVariantList getProjectTree();

  // Load a specific point completely into memory
  Q_INVOKABLE bool loadPointData(int pointId);

  // Playback Control
  Q_INVOKABLE void play();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void seek(double progressRatio); // 0.0 - 1.0
  Q_INVOKABLE void exportCsv(const QString &destFolderUrl);

  // Bind Series
  Q_INVOKABLE void updateRecvSeries(QAbstractSeries *series);
  Q_INVOKABLE void updateSendSeries(QAbstractSeries *series);
  Q_INVOKABLE void updateOffSeries(QAbstractSeries *series);

signals:
  void projectChanged();
  void loadedPointChanged();
  void playbackStateChanged();
  void playbackProgressChanged();
  void logMessage(const QString &msg, bool isWarning);
  void waveformChanged();

private slots:
  void onPlaybackTick();

private:
  QString m_currentProjectName;
  QString m_currentDbPath;

  int m_totalPoints;
  int m_currentPointIndex;
  QString m_currentPointName;

  double m_batteryVoltage;
  double m_internalTemp;
  double m_signalStrength;

  bool m_isPlaying;
  double m_playbackProgress; // Ratio
  QTimer *m_playbackTimer;

  int m_sampleRate;

  // Full loaded cache from DB
  QVector<float> m_fullRecvData;
  QVector<float> m_fullSendData;
  QVector<float> m_fullOffData;

  // The subset currently permitted to be rendered by playbackProgress
  QVector<float> m_renderRecvData;
  QVector<float> m_renderSendData;
  QVector<float> m_renderOffData;

  QString m_playbackConnectionName;

  QString currentProjectName() const { return m_currentProjectName; }
  QString currentDbPath() const { return m_currentDbPath; }
  int totalPoints() const { return m_totalPoints; }
  int currentPointIndex() const { return m_currentPointIndex; }
  QString currentPointName() const { return m_currentPointName; }
  double batteryVoltage() const { return m_batteryVoltage; }
  double internalTemp() const { return m_internalTemp; }
  double signalStrength() const { return m_signalStrength; }
  bool isPlaying() const { return m_isPlaying; }
  double playbackProgress() const { return m_playbackProgress; }
};

#endif // PLAYBACKBACKEND_H
