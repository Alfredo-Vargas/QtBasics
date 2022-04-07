#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDebug>
#include <QTimer>

// Timer needs to be an instant of QObject because we want to implement a signal from it
class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(QObject *parent = nullptr);

signals:

private slots:
    void addOneSecond();

private:
  int m_secs;
};

#endif // TIMER_H
