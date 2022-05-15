#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>

#define QD qDebug() << __FILE__ << __LINE__

class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker(QObject *parent = nullptr);
  void passQMutex(QMutex*);
  void passSharedData(int*);
  void passStopBoolean(bool*);

public slots:
  void doWork(void);

private:
  QMutex *m_mutexPtr;
  int *m_sharedDataPtr;
  bool *m_stopPtr;
    
};

#endif // WORKER_H

