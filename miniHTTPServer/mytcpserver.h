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

QTcpSocket* getServerSocket(void);
QString getFileRequested(void);
void parseRequest(void);

// signals:

private:
  QTcpSocket *m_serverSocket = nullptr;
  QString m_fileRequested = "";
};

#endif // MYTCPSERVER_H
