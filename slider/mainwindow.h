#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
  void startCycle();
  void cycleToNext();


private:
  Ui::MainWindow *ui;
  QTimer *m_cycleTimer;
  int m_cycleStepCounter = 0;
  bool m_isCycleRunning = false;

};
#endif // MAINWINDOW_H
