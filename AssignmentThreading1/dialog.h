#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "worker.h"
#include <QThread>
#include <QTimer>

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
  void updateLabelCounter(void);

  private:
  Ui::Dialog *ui;
  int sharedData = 0;
  bool stop = false;
  QTimer *m_dialogTimer;
};
#endif // DIALOG_H

// QUESTIONS:
// In what scope is the QThread workerThread declared?? (global??)
