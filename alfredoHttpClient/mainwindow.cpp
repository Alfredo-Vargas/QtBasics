#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_socket = new QTcpSocket(this);

  connect(ui->pb_connectToServer, &QPushButton::clicked, this, &MainWindow::tryConnection);
  connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::logMessage);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

void MainWindow::tryConnection(void) {
  m_socket->connectToHost(ui->lineEditServerIP->text(), ui->spinBoxServerPort->value());
  if (m_socket->waitForConnected(3000)) {
    ui->labelClientStatus->setText("Http Client Status: Connected\n");
  m_socket->write("GET /index.html HTTP/1.1 Host: 127.0.0.1:8080"
                   "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,/*;q=0.8"
                   "Accept-Language: en-us,en;q=0.5"
                   "Connection: keep-alive\r\n\r\n\r\n\r\n");

  }
}

void MainWindow::logMessage(void) {
  QD << "readyRead() was called";
  QString serverResponse = m_socket->readAll();
  ui->clientLog->appendPlainText(serverResponse);
  // QByteArray clientLog = m_socket->readAll();
  // ui->clientLog->insertPlainText(clientLog);
}

MainWindow::~MainWindow()
{
  delete ui;
}

