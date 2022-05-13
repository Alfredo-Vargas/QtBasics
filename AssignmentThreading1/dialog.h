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

public:
  Dialog(QWidget *parent = nullptr);
  ~Dialog();

  private slots:

  void onWorkerStart(void);
  void onWorkerStop(void);
  void updateLabelCounter(void);

  private:
  Ui::Dialog *ui;
  QTimer *m_dialogTimer;
  QThread workerThread;
  Worker *worker;
};
#endif // DIALOG_H

