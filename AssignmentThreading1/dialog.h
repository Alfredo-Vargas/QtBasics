#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "worker.h"
#include <QThread>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
  Q_OBJECT
  QThread workerThread;

public:
  Dialog(QWidget *parent = nullptr);
  ~Dialog();

  private slots:

  // void onWorkerStart(void);
  void onWorkerStop(void);
  void updateLabelCounter();

  private:
  Ui::Dialog *ui;
  QTimer *m_dialogTimer;
  Worker *worker;
  int sharedData = 0;
  // int *sharedDataPtr = &sharedData;

};
#endif // DIALOG_H

