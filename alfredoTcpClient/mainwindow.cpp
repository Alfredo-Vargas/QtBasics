#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_socket = new QTcpSocket(this);

  ui->home->setHidden(false);
  ui->navigation->setHidden(true);

  // Here the Tcp Connections
  connect(ui->pbConnect, &QPushButton::clicked, this, &MainWindow::tryConnection);
  connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::processConnection);
  connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::getSelectedImage);

  // Here the Ui connections
  connect(ui->actionSetings, &QAction::triggered, this, &MainWindow::setServerSettings);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

void MainWindow::tryConnection(void) {
  m_socket->connectToHost(m_serverAddress, m_serverPort);
  if (m_socket->waitForConnected(3000)) {
    QD << "connection successfull";
    m_socket->write("get list");
/*
    m_socket->write("GET /index.html HTTP/1.1 Host: 127.0.0.1:6400"
                     "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,/*;q=0.8"
                     "Accept-Language: en-us,en;q=0.5"
                     "Connection: keep-alive\r\n\r\n\r\n\r\n");
*/
    ui->home->setHidden(true);
    ui->navigation->setHidden(false);
  }

}

void MainWindow::processConnection(void) {
  QD << "readyRead() was called";
  QByteArray serverResponse = m_socket->readAll();
  QD << serverResponse;

  if (!m_isClientConnected) {
    QList<QByteArray> figureList = serverResponse.split('\n');
    foreach (const QByteArray &figure, figureList) {
      ui->listWidget->addItem(figure);
    }
    m_isClientConnected = true;
  }
  else {
    QList<QByteArray> imageDataResponse = serverResponse.split('\n');
    /* QD << imageDataResponse[0];
    QD << imageDataResponse[1]; */
    int imageByteSize = imageDataResponse[0].toInt();
    QD << imageByteSize;
    QImage rawImage;
    if (rawImage.loadFromData(imageDataResponse[1])) {
      QD << "rawImage loaded";
    }
  }
}

void MainWindow::getSelectedImage(void) {

  QListWidgetItem* current_item = ui->listWidget->currentItem();
  QString imageRequest = "get " + current_item->text();
  QD << imageRequest.toLatin1();
  m_socket->write(imageRequest.toLatin1());
}

void MainWindow::setServerSettings(void) {
  QD << "server settings was called";
/*
  QHBoxLayout dialog_vlayout = new QHVBoxLayout(this);
  QHVBoxLayout dialog_hlayout = new QHVBoxLayout(this);
  QDialog *mySettings = new QDialog(this);
  QLabel *myLabel = new QLabel("Host:");
  QLineEdit *myLineEdit = new QLineEdit();
  QSpinBox *mySpinBox = new QAbstractSpinBox();
  QPushButton *okButton = new QPushButton("OK");
  QPushButton *cancelButton = new QPushButton("Cancel");
  mySettings->setLayout(dialog_vlayout);
*/
}

MainWindow::~MainWindow()
{
  delete ui;
}

