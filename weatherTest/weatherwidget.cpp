#include "weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget{parent}
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setBrush(Qt::white);
  painter.drawRect(0, 0, 360, 360);

  int imageCounter = 1;
  qreal x0 = 0;
  qreal y0 = 0;
  qreal dx = 120;
  qreal dy = 120;
  QFileInfoList iconsList = QDir(":/img/").entryInfoList();
  foreach(const QFileInfo &info, iconsList) {
    QString name = info.fileName();
    m_background = new QPixmap();
    m_background->load(name);
    if (m_background->load(":/img/" + name)) {
      qDebug() << name;
      // painter.drawPixmap(0, 0, 10, 10, m_background);
      painter.drawImage(x0, y0, m_background->toImage());
      x0 = x0 + dx;
      if (imageCounter % 3 == 0) {
        y0 = y0 + dy;
        x0 = 0;
      }
    }
  }
}

WeatherWidget::~WeatherWidget() {

}

QSize WeatherWidget::sizeHint() const {
  return QSize(360, 360);
}

int WeatherWidget::weatherType(void) {
  return m_type;
}

void WeatherWidget::setWeatherType(int type) {
  m_type = type;
}

void WeatherWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setBrush(Qt::white);
  painter.drawRect(0, 0, 360, 360);

  int imageCounter = 1;
  qreal x0 = 0;
  qreal y0 = 0;
  qreal dx = 120;
  qreal dy = 120;

  QFileInfoList iconsList = QDir(":/img/").entryInfoList();
  foreach(const QFileInfo &info, iconsList) {
    QString name = info.fileName();
    m_background = new QPixmap();
    if (m_background->load(":/img/" + name)) {
      qDebug() << name;
      // painter.drawPixmap(0, 0, 10, 10, m_background);
      painter.drawImage(x0, y0, m_background->toImage());
     // Update the new positions
      x0 = x0 + dx;
      if (imageCounter % 3 == 0) {
        y0 = y0 + dy;
        x0 = 0;
      }
      imageCounter += 1;
    }
  }
}

//TODO
// (1) Why is painter.drawPixmap(0, 0, 10, 10, m_background) not recognized as member variable?
