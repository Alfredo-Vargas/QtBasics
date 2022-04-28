#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpixmap.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QPixmap *m_pix1;
  QPixmap *m_pix2;
};
#endif // MAINWINDOW_H
