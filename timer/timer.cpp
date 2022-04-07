#include "timer.h"

//
Timer::Timer(QObject *parent)
    : QObject{parent}
{
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Timer::addOneSecond);
  
  timer->start(1000);
}


void Timer::addOneSecond() {
  m_secs += 1;

  const QString str = QString::asprintf("%d:%02d", m_secs / 60, m_secs % 60);

  qDebug() << str;
}
