#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
  void tryConnection(void);
  void logMessage(void);

private:
  Ui::MainWindow *ui;
  QTcpSocket *m_socket;
};
#endif // MAINWINDOW_H
