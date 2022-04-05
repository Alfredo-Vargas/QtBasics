#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "sliderarray.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void showTestAreaButtons();
  void displaySliderStatus();
  void deleteStep();
  QListWidgetItem* getSelectedItem();

private:
  Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
