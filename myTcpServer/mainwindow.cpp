#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_localServer = new LocalServer(this);

}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButtonStart_clicked()
{
  QHostAddress serverAddress;
  // serverAddress.setAddress("127.0.0.1");
  if (!m_localServer->listen(QHostAddress::Any, ui->spinBox->value())) {
    QMessageBox::critical(this, "Error", m_localServer->errorString());
    ui->listWidget->addItem(m_localServer->errorString());
  } else {
    ui->listWidget->addItem("New connection from ::1");
    ui->listWidget->addItem("Connected to: " + m_localServer->serverAddress().toString());
    QMessageBox::information(this, "Server", "Server started");
  }
}


void MainWindow::on_pushButtonSend_clicked()
{
  m_localServer->sendMessage(ui->lineEditServerMessage->text());
  ui->listWidget->addItem("Message send succesfully");
}


void MainWindow::on_pushButtonQuit_clicked()
{
  close();
}

