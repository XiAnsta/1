#include "DatabaseManager.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>


DatabaseManager &DatabaseManager::instance() {
  static DatabaseManager _instance;
  return _instance;
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {}

DatabaseManager::~DatabaseManager() {
  if (m_db.isOpen()) {
    m_db.close();
  }
}

bool DatabaseManager::initialize(const QString &dbPath) {
  m_dbPath = dbPath;
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(dbPath);

  if (!m_db.open()) {
    qDebug() << "Error: connection with database failed" << m_db.lastError();
    emit databaseError("Connection failed: " + m_db.lastError().text());
    return false;
  }

  qDebug() << "Database: connection ok";
  return createTablesIfNotExist();
}

bool DatabaseManager::createTablesIfNotExist() {
  QSqlQuery query(m_db);

  // 1. Data_Project
  if (!query.exec("CREATE TABLE IF NOT EXISTS Data_Project ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "CalibrateNo TEXT, "
                  "CreateTime REAL, "
                  "LineNoSetp REAL, "
                  "LineNoStart REAL, "
                  "NOTE TEXT, "
                  "OffTime REAL, "
                  "PointLen_D REAL, "
                  "PointLen_R REAL, "
                  "PointNoStart REAL, "
                  "PointNoStep REAL, "
                  "RecvCoil_Gain REAL, "
                  "RecvCoil_Size REAL, "
                  "SSID TEXT, "
                  "SendCoil_Len REAL, "
                  "SendCoil_Turns REAL, "
                  "SendCoil_Width REAL, "
                  "WorkConfig INTEGER"
                  ")")) {
    qDebug() << "Data_Project table error:" << query.lastError();
    return false;
  }

  // 2. Data_Line
  if (!query.exec("CREATE TABLE IF NOT EXISTS Data_Line ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "NAME REAL, "
                  "NOTE TEXT, "
                  "TYPE INTEGER, "
                  "USE INTEGER"
                  ")")) {
    qDebug() << "Data_Line table error:" << query.lastError();
    return false;
  }

  // 3. Data_Point
  if (!query.exec("CREATE TABLE IF NOT EXISTS Data_Point ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "Data_LineID INTEGER, "
                  "NAME REAL, "
                  "NOTE TEXT, "
                  "TYPE INTEGER, "
                  "USE INTEGER"
                  ")")) {
    qDebug() << "Data_Point table error:" << query.lastError();
    return false;
  }

  // 4. Data_Sample
  // Heavy table with base64 strings
  if (!query.exec("CREATE TABLE IF NOT EXISTS Data_Sample ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "DATA_RECV TEXT, "
                  "DATA_RECV_LEN TEXT, "
                  "DATA_RECV_POS TEXT, "
                  "DATA_SEND TEXT, "
                  "DATA_SOFF TEXT, "
                  "Data_PointID INTEGER, "
                  "DeviceType INTEGER, "
                  "NOTE TEXT, "
                  "PERIOD INTEGER, "
                  "RecvFs REAL, "
                  "SampleOffFs REAL, "
                  "SampleSendFs REAL, "
                  "SendFs REAL, "
                  "StartTime INTEGER, "
                  "TYPE INTEGER, "
                  "USE INTEGER"
                  ")")) {
    qDebug() << "Data_Sample table error:" << query.lastError();
    return false;
  }

  // 5. Data_WorkSet
  if (!query.exec("CREATE TABLE IF NOT EXISTS Data_WorkSet ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "RecvCoil_Gain REAL, "
                  "RecvCoil_Size REAL, "
                  "SendCoil_Len REAL, "
                  "SendCoil_Turns REAL, "
                  "SendCoil_Width REAL, "
                  "WorkConfig INTEGER"
                  ")")) {
    qDebug() << "Data_WorkSet table error:" << query.lastError();
    return false;
  }

  qDebug() << "All tables verified/created.";
  return true;
}

int DatabaseManager::createProject(const QVariantMap &p) {
  QSqlQuery q(m_db);
  q.prepare("INSERT INTO Data_Project (CreateTime, LineNoStart, PointNoStart, "
            "PointNoStep, SSID, SendCoil_Len, SendCoil_Turns) "
            "VALUES (:ct, :ls, :ps, :pst, :ssid, :sl, :st)");
  q.bindValue(":ct", p.value("CreateTime", QDateTime::currentSecsSinceEpoch()));
  q.bindValue(":ls", p.value("LineNoStart", 0.0));
  q.bindValue(":ps", p.value("PointNoStart", 0.0));
  q.bindValue(":pst", p.value("PointNoStep", 2.0));
  q.bindValue(":ssid", p.value("SSID", "Android"));
  q.bindValue(":sl", p.value("SendCoil_Len", 0.88));
  q.bindValue(":st", p.value("SendCoil_Turns", 32.0));

  if (q.exec()) {
    return q.lastInsertId().toInt();
  }
  emit databaseError("Insert Project failed: " + q.lastError().text());
  return -1;
}

int DatabaseManager::createLine(int projectId, const QString &lineName,
                                int type, int use) {
  (void)projectId; // As per JS schema, Line doesn't explicitly link to project,
                   // or maybe implicitly globally.
  QSqlQuery q(m_db);
  q.prepare(
      "INSERT INTO Data_Line (NAME, TYPE, USE) VALUES (:name, :type, :use)");
  q.bindValue(":name",
              lineName.toDouble()); // Assuming NAME is float like 1.0 from JS
  q.bindValue(":type", type);
  q.bindValue(":use", use);

  if (q.exec()) {
    return q.lastInsertId().toInt();
  }
  emit databaseError("Insert Line failed: " + q.lastError().text());
  return -1;
}

int DatabaseManager::createPoint(int lineId, const QString &pointName, int type,
                                 int use) {
  QSqlQuery q(m_db);
  q.prepare("INSERT INTO Data_Point (Data_LineID, NAME, TYPE, USE) VALUES "
            "(:lid, :name, :type, :use)");
  q.bindValue(":lid", lineId);
  q.bindValue(":name", pointName.toDouble()); // Assuming NAME is float
  q.bindValue(":type", type);
  q.bindValue(":use", use);

  if (q.exec()) {
    return q.lastInsertId().toInt();
  }
  emit databaseError("Insert Point failed: " + q.lastError().text());
  return -1;
}

bool DatabaseManager::saveSample(int pointId, const QVariantMap &s,
                                 const QString &recvBase64,
                                 const QString &sendBase64,
                                 const QString &soffBase64) {
  QSqlQuery q(m_db);
  q.prepare("INSERT INTO Data_Sample (Data_PointID, DATA_RECV, DATA_SEND, "
            "DATA_SOFF, DeviceType, PERIOD, RecvFs, SendFs, StartTime) "
            "VALUES (:pid, :recv, :send, :soff, :dev, :per, :rfs, :sfs, :st)");

  q.bindValue(":pid", pointId);
  q.bindValue(":recv", recvBase64);
  q.bindValue(":send", sendBase64);
  q.bindValue(":soff", soffBase64);
  q.bindValue(":dev", s.value("DeviceType", 1));
  q.bindValue(":per", s.value("PERIOD", 500));
  q.bindValue(":rfs", s.value("RecvFs", 625000.0));
  q.bindValue(":sfs", s.value("SendFs", 25.0));
  q.bindValue(":st", s.value("StartTime", QDateTime::currentMSecsSinceEpoch()));

  if (q.exec()) {
    int id = q.lastInsertId().toInt();
    emit dataSaved(id);
    return true;
  }

  emit databaseError("Insert Sample failed: " + q.lastError().text());
  return false;
}

QVariantList DatabaseManager::getUnsyncedSamples() {
  QVariantList list;
  // We could return records where USE=1 or something signifying un-synced.
  // For now returning empty list as placeholder.
  return list;
}
