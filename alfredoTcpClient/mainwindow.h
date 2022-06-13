#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QHostAddress>
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
  void tryConnection(void);
  void processConnection(void);
  void getSelectedImage(void);
  void setServerSettings(void);

private:
  Ui::MainWindow *ui;
  QTcpSocket *m_socket;
  bool m_isClientConnected = false;

  // Here specify the address and port of the server that the client with try to connect to
  QHostAddress m_serverAddress = QHostAddress::LocalHostIPv6;
  quint16 m_serverPort = 64000; // this uint16 has the range of available ports
};
#endif // MAINWINDOW_H
