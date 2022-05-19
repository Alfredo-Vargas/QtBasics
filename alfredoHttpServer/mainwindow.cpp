#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // We create the tcp server
  m_server = new QTcpServer(this);
  if (m_server->listen(m_serverAddress, m_serverPort)) {
    QString welcomePhrase = "The (mini) HTTP server is running.\n";
    welcomePhrase += "Surf to " + m_serverAddress.toString() +":" + QString::number(m_serverPort);
    ui->serverInfo->setText(welcomePhrase);
  }
  else {
    QString welcomePhrase = "An error occured with the server ip and or port.\n";
    welcomePhrase += "Please verify those values and try again";
    ui->serverInfo->setText(welcomePhrase);
  }

  // Here we handle the TcpSever connections:
  connect(m_server, &QTcpServer::newConnection, this, [=](){
            if (m_documentRoot == "") {
              QMessageBox chooseRDmsg;
              chooseRDmsg.setText("Please choose the root directory");
              chooseRDmsg.exec();
              m_documentRoot = QFileDialog::getExistingDirectory();
            }
            m_socket = m_server->nextPendingConnection();
            ui->serverLog->insertPlainText("New connection from " + m_socket->peerAddress().toString() + "\n");
            connect(m_socket, &QTcpSocket::disconnected, m_socket, &QTcpSocket::deleteLater);
            connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::processMessage);
          });

  // Ui connections
  connect(ui->actionSet_Directory, &QAction::triggered, this, &MainWindow::setRootDirectory);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);
}

void MainWindow::processMessage(void) {
  // Consecutive calls of m_socket->readAll() look for next request!!!
  // Do not repeat readAll() !!!;
  QString clientRequest = m_socket->readAll();
  QString filenameRequested = clientRequest.split(' ')[1];
  QString method = clientRequest.split(' ')[0];

  if (filenameRequested == "/" or filenameRequested == "") {
      filenameRequested = "/index.html";
  }

  if (method != "GET") {
    ui->serverLog->insertPlainText("400: Bad request (" + method + ")");
    m_socket->write("HTTP/1.1 400 Bad Request\r\n\r\n");
  }

  if (m_documentRoot == "") {
    QMessageBox chooseRDmsg;
    chooseRDmsg.setText("Please choose the root directory");
    chooseRDmsg.exec();
    m_documentRoot = QFileDialog::getExistingDirectory();
  }

  QString fullFileNameRequest = m_documentRoot + filenameRequested;

  QFile *file = new QFile(fullFileNameRequest);
  // file.setFileName(fullFileNameRequest);
  // QD << fullFileNameRequest;

  if (file->exists())
  {
    file->open(QIODevice::ReadOnly);
    ui->serverLog->insertPlainText("Sending Data from file " + file->fileName() + "\n");

    m_socket->write(QString("HTTP/1.1 200 OK\r\n"
    "Cache-Control: no-cache\r\n"
    "Cache-Control: private\r\n"
    "Content-Length: %1\r\n"
    "Pragma: no-cache\r\n"
    "Content-type: text/html\r\n\r\n").arg(file->bytesAvailable()).toLatin1());
    m_socket->write(file->readAll());
    file->close();
  }
  else
  {
    ui->serverLog->insertPlainText("404: Not found (" + file->fileName() + ")\n");
    m_socket->write("HTTP/1.1 404 Not Found\r\n\r\n" );
  }
  m_socket->close();
  ui->serverLog->insertPlainText("Connection closed\n");
}

void MainWindow::setRootDirectory(void) {
  m_documentRoot = QFileDialog::getExistingDirectory();
}

MainWindow::~MainWindow()
{
  delete ui;
}

