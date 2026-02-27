#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class TcpClient : public QObject {
  Q_OBJECT
public:
  enum ConnectionState { Disconnected = 0, Connecting, Connected };
  Q_ENUM(ConnectionState)

  explicit TcpClient(QObject *parent = nullptr);
  ~TcpClient();

  void connectToServer(const QString &ip, quint16 port, int timeoutMs = 3000);
  void disconnectFromServer();
  bool sendData(const QByteArray &data);

  ConnectionState state() const { return m_state; }

signals:
  void stateChanged(TcpClient::ConnectionState newState);
  void dataReceived(const QByteArray &data);
  void errorOccurred(const QString &errorMsg);

private slots:
  void onConnected();
  void onDisconnected();
  void onReadyRead();
  void onError(QAbstractSocket::SocketError socketError);
  void onConnectionTimeout();

private:
  void setState(ConnectionState newState);

  QTcpSocket *m_socket;
  QTimer *m_timeoutTimer;
  ConnectionState m_state;
};

#endif // TCPCLIENT_H
