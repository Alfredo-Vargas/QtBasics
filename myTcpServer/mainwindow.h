#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "localserver.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class LocalServer;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  private slots:
  void on_pushButtonStart_clicked();

  void on_pushButtonSend_clicked();

  void on_pushButtonQuit_clicked();

  private:
  Ui::MainWindow *ui;
  LocalServer *m_localServer;
};
#endif // MAINWINDOW_H
