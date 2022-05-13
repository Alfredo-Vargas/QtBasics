#include "dialog.h"
#include "ui_dialog.h"

// Shared data is globally defined
int sharedData = 0;

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  ui->setupUi(this);

  // Memory allocation for QTimer and Worker
  m_dialogTimer = new QTimer(this);
  worker = new Worker;

  // We move the worker thread initially assigned to the GUI thread to the its own subthread
  worker->moveToThread(&workerThread);

  // CONNECTIONS:
  // To start the worker thread whenever the start button is clicked
  connect(ui->pushButtonStart, &QPushButton::clicked, worker, &Worker::doWork);
  // To stop the worker thread whenever the stop button is clicked
  connect(ui->pushButtonStop, &QPushButton::clicked, this, &Dialog::onWorkerStop);
  // To update the label after the work of the worker is ready
  connect(m_dialogTimer, &QTimer::timeout, this, &Dialog::updateLabelCounter);
  // To delete Worker once thread is finished
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
}

Dialog::~Dialog()
{
  workerThread.quit();
  workerThread.wait();
  delete ui;
}

void Dialog::onWorkerStart(void) {
  qDebug() << QThread::currentThreadId();
  worker->doWork(sharedData);
}

void Dialog::onWorkerStop(void) {
  m_dialogTimer->stop();
  worker->stopWork();
}

void Dialog::updateLabelCounter(void) {
  ui->labelCounter->setText(QString::number(sharedData));
}

