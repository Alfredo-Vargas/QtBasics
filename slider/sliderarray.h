#pragma once

#ifndef SLIDERARRAY_H
#define SLIDERARRAY_H

#include <QHBoxLayout>
#include <QSlider>
#include <QWidget>
#include <QDebug>

class SliderArray : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const QList<int> value READ value WRITE setValue NOTIFY valuesChanged)

public:
  explicit SliderArray(QWidget *parent = nullptr, qint32 slider_number = 10);
  virtual ~SliderArray();
  QList<int> value() ;

public slots:
  void setValue(QList<int>);

signals:
  void valuesChanged();

private:

  QHBoxLayout *m_sliderLayout;
  QList<QSlider*> *m_slidersPointers;
  QList<int> data;
};

#endif // SLIDERARRAY_H
