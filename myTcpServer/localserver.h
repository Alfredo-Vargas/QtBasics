#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QLocalServer>
#include <QLocalSocket>
#include <QTextStream>

class QLocalSocket;

class LocalServer : public QLocalServer
{
  Q_OBJECT
public:
  explicit LocalServer(QObject *parent = nullptr);
  ~LocalServer();
  void sendMessage(const QString);

private:
  QLocalSocket *m_socket;

};

#endif // LOCALSERVER_H
