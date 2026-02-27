#include "TcpClient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent), m_state(Disconnected) {
  m_socket = new QTcpSocket(this);
  m_timeoutTimer = new QTimer(this);
  m_timeoutTimer->setSingleShot(true);

  // Map QTcpSocket signals
  connect(m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
  connect(m_socket, &QTcpSocket::disconnected, this,
          &TcpClient::onDisconnected);
  connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
  connect(m_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onError);
#else
  connect(m_socket,
          QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this,
          &TcpClient::onError);
#endif

  connect(m_timeoutTimer, &QTimer::timeout, this,
          &TcpClient::onConnectionTimeout);
}

TcpClient::~TcpClient() {
  if (m_socket->isOpen()) {
    m_socket->disconnectFromHost();
  }
}

void TcpClient::connectToServer(const QString &ip, quint16 port,
                                int timeoutMs) {
  if (m_state != Disconnected) {
    disconnectFromServer();
  }

  qDebug() << "TcpClient connecting to" << ip << ":" << port;
  setState(Connecting);

  m_socket->connectToHost(ip, port);
  m_timeoutTimer->start(timeoutMs);
}

void TcpClient::disconnectFromServer() {
  if (m_socket->state() != QAbstractSocket::UnconnectedState) {
    m_socket->disconnectFromHost();
  } else {
    setState(Disconnected);
  }
}

bool TcpClient::sendData(const QByteArray &data) {
  if (m_state != Connected) {
    return false;
  }
  m_socket->write(data);
  return m_socket->flush();
}

void TcpClient::setState(ConnectionState newState) {
  if (m_state != newState) {
    m_state = newState;
    emit stateChanged(m_state);
  }
}

void TcpClient::onConnected() {
  m_timeoutTimer->stop();
  qDebug() << "TcpClient connected successfully.";
  setState(Connected);
}

void TcpClient::onDisconnected() {
  m_timeoutTimer->stop();
  qDebug() << "TcpClient disconnected.";
  setState(Disconnected);
}

void TcpClient::onReadyRead() {
  QByteArray data = m_socket->readAll();
  emit dataReceived(data);
}

void TcpClient::onError(QAbstractSocket::SocketError socketError) {
  Q_UNUSED(socketError)
  m_timeoutTimer->stop();
  QString errStr = m_socket->errorString();
  qDebug() << "TcpClient Error:" << errStr;
  emit errorOccurred(errStr);

  if (m_state == Connecting) {
    setState(Disconnected);
  }
}

void TcpClient::onConnectionTimeout() {
  qDebug() << "TcpClient Connection Timeout.";
  m_socket->abort();
  emit errorOccurred("Connection timeout");
  setState(Disconnected);
}
