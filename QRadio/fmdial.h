#pragma once

// #include <QHBoxLayout>
#include <QWidget>
#include <QLine>
#include <QPainter>
#include <QDebug>

class FmDial : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const int value READ value WRITE setValue NOTIFY frequencyChanged)
public:
  explicit FmDial(QWidget *parent = nullptr);
  // we let the parent widget manage the destructor of this custom widget
  virtual ~FmDial();

  // this overloads a predefined sizeHint() -> useful for custom rendering
  QSize sizeHint() const;

  int value();

public slots:
  void setValue(int);

signals:
  void frequencyChanged();

protected:
  // this overloads a predefined paintEvent() -> useful for custom rendering
  void paintEvent(QPaintEvent*);
  void paintIndicator(QPainter*);

private:
  // QHBoxLayout *m_layout;
  int m_position = 975;
};

// NOTE: Both sizeHint() and paintEvent() go always together!!!
