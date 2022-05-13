#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_tcpServer = new MyTcpServer(this);
  m_nam = new QNetworkAccessManager();

  connect(m_tcpServer, &MyTcpServer::newConnection, this, &MainWindow::logNewConnection);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionSet_Directory, &QAction::triggered, this, &MainWindow::chooseRootDirectory);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::chooseRootDirectory(void) {
  QFileDialog myFD;
  myFD.setFileMode(QFileDialog::DirectoryOnly);
  m_rootDir = QFileDialog::getExistingDirectory();
  // m_rootDir = "file://" + m_rootDir;
  if (m_rootDir != "") {

    // Change this with the the IP of the interface which will act as a Server
    QHostAddress serverAddress("10.67.45.209");
    if (!m_tcpServer->listen(serverAddress, 64000)) {
      QMessageBox::critical(this, "Error", m_tcpServer->errorString());
    } 
    else {
      QString initFeedback = "";
      initFeedback = "The (mini) HTTP server is running.\n surf to http://" + serverAddress.toString() + ":64000";
      ui->labelStatus->setText(initFeedback);

    }
    // m_nam->get(QNetworkRequest(QUrl("http://192.168.0.2:64000")));
  }

}

void MainWindow::logNewConnection() {
  QString clientAddress = m_tcpServer->getServerSocket()->peerAddress().toString();
  int clientPort = m_tcpServer->getServerSocket()->peerPort();
  QString clientID = clientAddress + ":" + QString::number(clientPort) +"\n";
  QString feedback = "New connection from " + clientID;
  ui->plainTextEdit->insertPlainText(feedback);
  if (m_tcpServer->getFileRequested() != "") {
    QString fileRequested = m_tcpServer->getFileRequested();
    ui->plainTextEdit->insertPlainText("Requested for file: \"" + fileRequested + "\"\n");
  }
  QString fileToTransfer = m_rootDir + m_tcpServer->getFileRequested();
  qDebug() << fileToTransfer;
  if (QFileInfo::exists(fileToTransfer)) {
    QString feedbackFile = "Sending Data from file: ";
    ui->plainTextEdit->insertPlainText(feedbackFile + fileToTransfer + "...\n");
  }
  else {
  m_tcpServer->getServerSocket()->write("HTTP/1.1 404 Not Found\r\n\r\n" );
  }
}
