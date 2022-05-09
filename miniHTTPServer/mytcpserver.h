#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit MyTcpServer(QObject *parent = nullptr);

// signals:

private:
  QTcpSocket *m_serverSocket = nullptr;


};

#endif // MYTCPSERVER_H
