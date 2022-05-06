#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_localServer = new LocalServer(this);


  // connect(ui->actionSet_Directory, &QAction::triggered, this, &QApplication::quit);
  // connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButtonStart_clicked()
{
  if (!m_localServer->listen(ui->labelServerName->text())) {
    QMessageBox::critical(this, "Error", m_localServer->errorString());
    ui->listWidget->addItem(m_localServer->errorString());
  } else {
    ui->listWidget->addItem("New connection from ::1");
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

