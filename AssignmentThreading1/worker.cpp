#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::doWork(int sd) {
  qDebug() << QThread::currentThreadId();
  int result;
  // Here is the expensive or blocking operation 
   qDebug() << "Worker started working";
   for(int i = 0; i < 100; i++){
     qDebug() << i;
     mutex.lock();
     sd = 0xFFFFFFFF;
     QThread::msleep(90);
     sd = i;
     mutex.unlock();
     QThread::msleep(10);
     if(this->stop) break;
  }
  qDebug() << "Worker work done";
  QThread::currentThread()->quit();
  result = sd;
  emit resultReady(result);
}

void Worker::stopWork(void) {
  stop = true;
}

