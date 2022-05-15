#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::doWork(void) {
  QD << "The Worker Thread ID is:  " << QThread::currentThreadId();
  // Here is the expensive or blocking operation 
  QD << "Worker started working";
  *m_stopPtr = false;
   for(int i = 0; i < 100; i++){
     QD << i;
     m_mutexPtr->lock();
     *m_sharedDataPtr = 0xFFFFFFFF;
     QThread::msleep(90);
     *m_sharedDataPtr = i;
     m_mutexPtr->unlock();
     QThread::msleep(10);
     if(*m_stopPtr) break;
  }
  qDebug() << "Worker work done";
  QThread::currentThread()->quit();
}

void Worker::passQMutex(QMutex *mutex) {
  m_mutexPtr = mutex;
}

void Worker::passSharedData(int *data) {
  m_sharedDataPtr = data;
}

void Worker::passStopBoolean(bool *stopPtr) {
  m_stopPtr = stopPtr;
}
