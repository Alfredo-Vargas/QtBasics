#pragma once

// #include <QHBoxLayout>
#include <QWidget>
#include <QLine>
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <QMouseEvent>

class FmDial : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const int value READ value WRITE setValue NOTIFY dialPositionChanged)
public:
  explicit FmDial(QWidget *parent = nullptr);
  // we let the parent widget manage the destructor of this custom widget
  virtual ~FmDial();

  // this overloads a predefined sizeHint() -> useful for custom rendering
  QSize sizeHint() const;

  qreal value();

public slots:
  void setValue(qreal);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

signals:
  void dialPositionChanged(qreal);
  // void frequencyChanged(qreal);

protected:
  // this overloads a predefined paintEvent() -> useful for custom rendering
  void paintEvent(QPaintEvent*);
  void paintIndicator(QPainter*);
  // int frequencyToPixel(qreal freq);
  // qreal pixelToFrequency(int pixel);

private:
  qreal m_position = 870;
  qreal m_hmp = 0.2;  // horizontal margin percentage
  qreal m_horizontalMargin = 20;
  qreal m_maxFrequency = 108;
  qreal m_minFrequency = 87;
};

// NOTE: Both sizeHint() and paintEvent() go always together!!!
