#include "mytcpserver.h"
#include "qnetworkaccessmanager.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

  m_nam = new QNetworkAccessManager(this);
  connect(this, &MyTcpServer::newConnection, this, [=] {
            m_serverSocket = nextPendingConnection();
          });
}
