#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  ui->setupUi(this);
  m_dialogTimer = new QTimer(this);
  Worker *worker = new Worker;
  worker->moveToThread(&workerThread);
  // To delete Worker once thread is finished
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  // To start the worker thread whenever the start button is clicked
  connect(ui->pushButtonStart, &QPushButton::clicked, this, [=]() {
            m_dialogTimer->start(50);
            workerThread.start();
            qDebug() << "Worker started working";
            for(int i = 0; i < 1000; i++){
              qDebug() << i;
              worker->mutex.lock();
              sharedData = 0xFFFFFFFF;
              QThread::msleep(90);
              sharedData = i;
              worker->mutex.unlock();
              QThread::msleep(10);
              if(this->stop) break; 
            }
            qDebug() << "Worker work done";
            QThread::currentThread()->quit();
            emit worker->resultReady(sharedData);
          });
  connect(ui->pushButtonStop, &QPushButton::clicked, this, &Dialog::onWorkerStop);
  // To update the label after the work of the worker is ready
  connect(m_dialogTimer, &QTimer::timeout, this, &Dialog::updateLabelCounter);

}

Dialog::~Dialog()
{
  workerThread.quit();
  workerThread.wait();
  delete ui;
}

/* void Dialog::onWorkerStart(void) {

} */

void Dialog::onWorkerStop(void) {
  stop = true;
  m_dialogTimer->stop();
}

void Dialog::updateLabelCounter(void) {
  ui->labelCounter->setText(QString::number(sharedData));
}


