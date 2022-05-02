#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QVBoxLayout>

class WeatherWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(const int weatherType READ weatherType WRITE setWeatherType NOTIFY weatherType)
public:
  explicit WeatherWidget(QWidget *parent = nullptr);
  virtual ~WeatherWidget();

  QSize sizeHint() const;
  int weatherType(void);
  void setWeatherType(int);

signals:
  void weatherTypeChanged(QString wheatherType);

protected:
  void paintEvent(QPaintEvent*);
  void paintImage(QPainter*);

private:
  int m_type;
  QPixmap *m_background;
  // QVBoxLayout *m_layout;

};

#endif // WEATHERWIDGET_H

