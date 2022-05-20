#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFileDialog>
#include <QMessageBox>

#define QD qDebug() << __FILE__ << __LINE__

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void processMessage(void);
  void setRootDirectory(void);
  void sendMessage(void);

private:
  Ui::MainWindow *ui;
  QTcpServer *m_server;
  QTcpSocket *m_socket;

  // Here specify the address and port of your server and Document Root
  QHostAddress m_serverAddress = QHostAddress::LocalHostIPv6;
  quint16 m_serverPort = 8080;
  QString m_documentRoot = "";
};

