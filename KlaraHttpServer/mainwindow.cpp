#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(serverConnected()));
    m_tcpServer->listen(QHostAddress::Any,64000);
    ui->severSts->setText("The (mini) HTTP server is running");

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    ui->addressDtl->setText(tr("surf to http://%1:%2\n\n").arg(ipAddress).arg(m_tcpServer->serverPort()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverConnected()
{

    QTcpSocket *connection= m_tcpServer->nextPendingConnection();

    connect(connection,SIGNAL(disconnected()),connection,SLOT(deleteLater()));
    connect(connection,&QTcpSocket::readyRead,this,[=](){parseReq(connection);});

    QByteArray buffer;

    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    //connection->write(buffer);
   // connection->disconnectFromHost();

}
void MainWindow::parseReq(QTcpSocket* m_client)
{
    QString req=m_client->readAll();
    QByteArray answerHeader="HTTP/1.1 200 OK\r\n";
    QByteArray answerBody;
    QRegExp rx("GET (.*) HTTP");
    QByteArray line;

    ui->connectionsDetails->appendPlainText("New connection from: "+m_client->localAddress().toString());

    rx.setMinimal(true);
    int found=rx.indexIn(req);

    if(found != -1)
    {QString uri= rx.cap(1);
        ui->connectionsDetails->appendPlainText("Request for file: "+uri);
        if(uri == ";" || uri=="/index.html")
        {

            answerBody="Cache-Control: no-cache\r\n"
                       "Cache-Control: private\r\n"
                       "Pragma: no-cache\r\n"
                       "Content-type: text/html\r\n\r\n";

            QFile file("C:/Users/klara/OneDrive/Desktop/CPP/Advanced LAb/miniHTTPserver/in.txt.txt");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

            while (!file.atEnd()) {
               line = file.readLine();
            }
            qDebug()<<answerHeader<<answerBody<<line;
            m_client->write(answerHeader);
            m_client->write(answerBody);
            m_client->write(line);
        }
    }
    else
    {
        m_client->write("HTTP/1.1 400 Bad Request\r\n\r\n" );
    }


    qDebug()<<req;

}
