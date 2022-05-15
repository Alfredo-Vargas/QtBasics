#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "worker.h"
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

  private:
  Ui::Dialog *ui;
  QTimer *m_dialogTimerPtr;
  QThread *m_workerThreadPtr;
  QMutex *m_mutexPtr;
  int *m_sharedDataPtr;
  bool *m_stopPtr;
  Worker *m_workerPtr;

};
#endif // DIALOG_H

