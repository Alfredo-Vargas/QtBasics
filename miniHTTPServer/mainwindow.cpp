#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_tcpServer = new MyTcpServer(this);
  m_nam = new QNetworkAccessManager(this);

  connect(m_nam, &QNetworkAccessManager::connectToHost, this, [=](){
            ui->plainTextEdit->insertPlainText("New connection from ::1");
          });
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
  QHostAddress serverAddress("192.168.0.2");
  if (!m_tcpServer->listen(serverAddress, 64000)) {
    QMessageBox::critical(this, "Error", m_tcpServer->errorString());
  } else {
    QString initFeedback = "";
    initFeedback = "The (mini) HTTP server is running.\n surf to http://" + serverAddress.toString() + ":64000";
    ui->labelStatus->setText(initFeedback);
    // ui->listWidget->addItem("New connection from ::1");
    // ui->listWidget->addItem("Connected to: " + m_localServer->serverAddress().toString());
    // QMessageBox::information(this, "Server", "Server started");
  }
  }

}
