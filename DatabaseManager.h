#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QVariantList>
#include <QVariantMap>

class DatabaseManager : public QObject {
  Q_OBJECT
public:
  static DatabaseManager &instance();

  bool initialize(const QString &dbPath);
  bool createTablesIfNotExist();

  // Insertion methods mapping to JSON schema
  int createProject(const QVariantMap &projectData);
  int createLine(int projectId, const QString &lineName, int type = 0,
                 int use = 1);
  int createPoint(int lineId, const QString &pointName, int type = 0,
                  int use = 1);

  // Save sample - returns true if queued or saved successfully
  bool saveSample(int pointId, const QVariantMap &sampleData,
                  const QString &recvBase64, const QString &sendBase64,
                  const QString &soffBase64);

  // Retrieve full hierarchical tree for the UI (Lines -> Points)
  QVariantList getProjectTree();

  // Retrieve unsynced records
  QVariantList getUnsyncedSamples();

signals:
  void databaseError(const QString &errorStr);
  void dataSaved(int sampleId);

private:
  explicit DatabaseManager(QObject *parent = nullptr);
  ~DatabaseManager();

  QSqlDatabase m_db;
  QString m_dbPath;
};

#endif // DATABASEMANAGER_H
