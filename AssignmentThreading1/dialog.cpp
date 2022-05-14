#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  ui->setupUi(this);

  // We create the sharedData and a pointer to it:
  // Reference cannot be modified and we need to modify it in the worker thread!
  // int sharedData = 0;
  int *shareDataPtr = &sharedData;
/*
  // Memory allocation for QTimer
  m_dialogTimer = new QTimer(this);
  m_dialogTimer->start(50);
*/
  // Memory allocation for Worker
  worker = new Worker;

  // connect(m_dialogTimer, &QTimer::timeout, this, [=]{updateLabelCounter();});
  // connect(m_dialogTimer, &QTimer::timeout, this, [=]{qDebug() << "update!";});

  qDebug() << "The GUI Thread ID is:\t" << QThread::currentThreadId();
  // We move the worker thread initially assigned to the GUI thread to the its own subthread
  worker->moveToThread(&workerThread);
  // CONNECTIONS:
  // To start the worker thread whenever the start button is clicked

  connect(ui->pushButtonStart, &QPushButton::clicked, worker, [=]{
          worker->doWork(shareDataPtr);
          });

  // To stop the worker thread whenever the stop button is clicked
  connect(ui->pushButtonStop, &QPushButton::clicked, this, &Dialog::onWorkerStop);
  // To update the label after work of the worker work is ready or the button stop was pressed


  // connect(m_dialogTimer, &QTimer::timeout, this, &Dialog::updateLabelCounter);
  connect(worker, &Worker::resultReady, this, &Dialog::updateLabelCounter);
  // To delete Worker once thread is finished
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

  // We Start the worker thread at the end of the constructor of dialog
  workerThread.start();
}

Dialog::~Dialog()
{
  workerThread.quit();
  workerThread.wait();
  delete ui;
}

/* void Dialog::onWorkerStart(void) {
  qDebug() << QThread::currentThreadId();
} */

void Dialog::onWorkerStop(void) {
  qDebug() << "The Thread ID onWorkerStop is:\t" << QThread::currentThreadId();
  m_dialogTimer->stop();
  worker->stopWork();
}

void Dialog::updateLabelCounter() {
  // qDebug() << "The Thread ID onUpdateLabel is:\t" << QThread::currentThreadId();
  ui->labelCounter->setText(QString::number(sharedData));
}

