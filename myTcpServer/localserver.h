#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

class QTcpSocket;

class LocalServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit LocalServer(QObject *parent = nullptr);
  ~LocalServer();
  void sendMessage(const QString);

private:
  QTcpSocket *m_socket;

};

#endif // LOCALSERVER_H
