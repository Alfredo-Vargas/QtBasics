#include "localserver.h"

LocalServer::LocalServer(QObject *parent)
    : QTcpServer{parent}
{
  m_socket = nullptr;

  connect(this, &LocalServer::newConnection, this, [=] {
            m_socket = nextPendingConnection();
          });

}

LocalServer::~LocalServer()
{

}

void:: LocalServer::sendMessage(const QString message) {
  if (m_socket) {
    QTextStream T(m_socket);
    T << message;
    m_socket->flush();
  }
}
