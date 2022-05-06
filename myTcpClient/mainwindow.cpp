#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);

   connect(m_socket, &QTcpSocket::readyRead, [=]() {
          QTextStream T(m_socket);
          ui->listWidget->addItem(T.readAll());
           });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnect_clicked()
{
  m_socket->connectToHost("localhost", ui->spinBoxPort->value());
  if (m_socket->waitForConnected(1000)){
    ui->listWidget->addItem("Connected to server successfull");
  } else {
    ui->listWidget->addItem(m_socket->errorString());
  }
}

void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

