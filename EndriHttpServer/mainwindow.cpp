#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup server
    m_server = new QTcpServer(this);
    connect(m_server,&QTcpServer::newConnection,this,&MainWindow::serverConnected);
    m_server->listen(QHostAddress::Any,m_port);

    // add server information to label
    QList<QHostAddress> list = QHostInfo::fromName(QHostInfo::localHostName()).addresses();

    if(m_server->isListening())
    {
        ui->label->setText("The mini http server is running : \n http://" + list[7].toString() + ":" + QString::number(m_port));
    }

}

void MainWindow::serverConnected()
{
    QTcpSocket *connection = m_server->nextPendingConnection();
    connect(connection,&QTcpSocket::disconnected,connection,&QTcpSocket::deleteLater);
    connect(connection,&QTcpSocket::readyRead,this,[=](){parseRequest(connection);});

    QByteArray buffer;
    QDataStream response(&buffer,QIODevice::WriteOnly);
    response.setVersion(QDataStream::Qt_5_4);
}

void MainWindow::parseRequest(QTcpSocket *connection)
{
    QByteArray line;
    QString request = connection->readAll();
    ui->plainTextEdit->appendPlainText("New connection from : [" + connection->localAddress().toString() + "]");
    QStringList url = request.split(" ");
    QString method = url[0];
    QString path = url[1];
    //qDebug() << url;

    if(method != "GET")
    {
        connection->write("HTTP/1.1 400 Bad Request\r\n\r\nBad Request!");
        connection->disconnectFromHost();
    }

    if(path == "/" || path == "/index.html")
    {
        qDebug() << "Method : " << method << "\nPath : " << path;
        connection->write("HTTP/1.1 200 OK\r\n"
                          "Cache-Control: no-cache\r\n"
                          "Cache-Control: private\r\n"
                          "Pragma: no-cache\r\n"
                          "Content-type: text/html\r\n\r\n");
        QFile file("/www/index.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        while (!file.atEnd()) {
            line = file.readLine();
        }
        connection->write(line);
        connection->disconnectFromHost();
    }
    else
    {
        connection->write("HTTP/1.1 404 Not Found\r\n\r\nNot Found!" );
        connection->disconnectFromHost();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

