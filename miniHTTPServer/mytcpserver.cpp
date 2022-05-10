#include "mytcpserver.h"
#include "qnetworkaccessmanager.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{
  connect(this, &MyTcpServer::newConnection, this, [=] {
            m_serverSocket = nextPendingConnection();
          });
}
