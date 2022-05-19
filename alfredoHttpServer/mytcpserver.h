#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

signals:

};

#endif // MYTCPSERVER_H
