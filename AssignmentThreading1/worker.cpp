#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{



  // Memory allocation for QTimer
  workerTimer = new QTimer(this);
  workerTimer->start(50);

  connect(workerTimer, &QTimer::timeout, this, [=]{
          resultReady(2);});
}

void Worker::doWork(int *shareDataPtr) {
  qDebug() << "The Worker Thread ID is:\t" << QThread::currentThreadId();
  int result;
  // Here is the expensive or blocking operation 
   qDebug() << "Worker started working";
   for(int i = 0; i < 10; i++){
     qDebug() << i;
     mutex.lock();
     *shareDataPtr = 0xFFFFFFFF;
     QThread::msleep(90);
     *shareDataPtr = i;
     mutex.unlock();
     QThread::msleep(10);
     if(this->stop) break;
  }
  qDebug() << "Worker work done";
  QThread::currentThread()->quit();
  result = *shareDataPtr;
  emit resultReady(result);
}

void Worker::stopWork(void) {
  stop = true;
}

