#include "mytcpserver.h"
#include <QNetworkAccessManager>
#include <QRegularExpression>

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{
  connect(this, &MyTcpServer::newConnection, this, [=] {
            m_serverSocket = nextPendingConnection();
            QByteArray request = m_serverSocket->readAll();
            // qDebug() << request;
            QRegularExpression re("\/[a-z]*[.][a-z]*");
            QRegularExpressionMatch matchedFile = re.match(request);
            // qDebug() << matchedFile;
            if (matchedFile.hasMatch()) {
              // qDebug() << matchedFile.captured();
              m_fileRequested = matchedFile.captured();
            }
            connect(m_serverSocket, &QTcpSocket::readyRead, this, &MyTcpServer::parseRequest);
          });

}

QTcpSocket* MyTcpServer::getServerSocket(void) {
  return m_serverSocket;
}

QString MyTcpServer::getFileRequested(void) {
  return m_fileRequested;
}

void MyTcpServer::parseRequest(void) {
  QByteArray request = m_serverSocket->readAll();
  // qDebug() << request;
  QRegularExpression re("\/[a-z]*[.][a-z]*");
  QRegularExpressionMatch matchedFile = re.match(request);
  // qDebug() << matchedFile;
  if (matchedFile.hasMatch()) {
    // qDebug() << matchedFile.captured();
    m_fileRequested = matchedFile.captured();
  }
}
