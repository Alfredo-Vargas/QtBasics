#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>

class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker(QObject *parent = nullptr);
  QMutex mutex;

public slots:
  // void doWork(int);
    
signals:
  void resultReady(int);

};

#endif // WORKER_H
