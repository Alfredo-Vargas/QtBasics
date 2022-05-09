#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include "mytcpserver.h"
#include <QDebug>
#include <QMessageBox>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void chooseRootDirectory(void);
  void logHostConnection(void);


private:
  Ui::MainWindow *ui;
  QString m_rootDir = "";
  MyTcpServer *m_tcpServer;
  QNetworkAccessManager *m_nam;

};
#endif // MAINWINDOW_H
