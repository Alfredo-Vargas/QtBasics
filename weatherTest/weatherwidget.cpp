#include "weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget{parent}
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setBrush(Qt::white);
  painter.drawRect(0, 0, 360, 360);


  // m_layout = new QVBoxLayout(this);
  QFileInfoList iconsList = QDir(":/img/").entryInfoList();
  foreach(const QFileInfo &info, iconsList) {
    QString name = info.fileName();
    m_background = new QPixmap();
    m_background->load(name);
    qDebug() << name;
    // We need to paint here the image
    // painter.drawImage(name);

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

  // We need to paint here the image
  // painter.drawImage(name);
}

