#include "myrunnable.h"

MyRunnable::MyRunnable()
{
}

void MyRunnable::run()
{
    if(!SocketDescriptor) return;

    QTcpSocket socket;
    socket.setSocketDescriptor(SocketDescriptor);

    socket.write("hello world");
    socket.flush();
    socket.waitForBytesWritten();
    socket.close();
}
