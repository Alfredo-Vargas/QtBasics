#pragma once

#include <QHBoxLayout>
#include <QWidget>
#include <QLine>

class FmDial : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const int value READ value WRITE setValue NOTIFY valuesChanged)
public:
  explicit FmDial(QWidget *parent = nullptr);
  virtual ~FmDial();

  int value();

public slots:
  void setValue(int);

signals:
  void valuesChanged();

private:
  QHBoxLayout *m_layout;
  int *m_position;
};

