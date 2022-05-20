#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::StartServer()
{
    if(listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server: started";
    }
    else
    {
        qDebug() << "Server: not started!";
    }
}

void MyServer::incomingConnection(int handle)
{
    // at the incoming connection, make a client
    MyClient *client = new MyClient(this);
    client->SetSocket(handle);
}
