#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QTimer>
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "sliderarray.h"
#include <QFileDialog>

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
  void showTestAreaButtons(int);
  void displaySliderStatus();
  void deleteStep();
  QListWidgetItem* getSelectedItem();
  void startCycle();
  void cycleToNext();
  void saveToFile();
  void loadFromFile();

private:
  Ui::MainWindow *ui;
  QTimer *m_cycleTimer;
  int m_cycleStepCounter = 0;
  bool m_isCycleRunning = false;

};
#endif // MAINWINDOW_H
