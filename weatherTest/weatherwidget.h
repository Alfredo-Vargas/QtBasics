#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QMouseEvent>

#define QD qDebug()

class WeatherWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const int weatherType READ weatherType WRITE setWeatherType NOTIFY weatherType)
public:
  explicit WeatherWidget(QWidget *parent = nullptr);
  virtual ~WeatherWidget();

  QSize sizeHint() const;
  int weatherType(void);
  QString getWeatherString(void);

public slots:
  void setWeatherType(int);

signals:
  void weatherTypeChanged(int wheatherType);

protected:
  void paintEvent(QPaintEvent*);
  void paintImage(QPainter*);
  void mousePressEvent(QMouseEvent*);
  void paintFrameOnSelected(QPainter*);
  void showWeatherType(void);

private:
  int m_type = -1;
  QPixmap *m_background;
  QString m_weather = " ";
};

#endif // WEATHERWIDGET_H

