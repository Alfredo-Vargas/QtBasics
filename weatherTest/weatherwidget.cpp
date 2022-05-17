#include "weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget{parent}
{

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
  if (type >= 0 && type <= 8){
    if (type != m_type) {
      emit weatherTypeChanged(type);
    }
  }
  update();
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
      QString pure_weather_type = name.mid(4);
      pure_weather_type.chop(4);
/*
      QD << name;
      QD << pure_weather_type;
*/
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
  // QD << "At QPaintEvent the type is: " << m_type;
  if (m_type != -1) {
    paintFrameOnSelected(&painter);
    m_weather = iconsList.at(m_type).fileName().mid(4);
    m_weather.chop(4);
    // QD << m_weather;
  }
}

QString WeatherWidget::getWeatherString(void) {
  if (m_type != -1) {
    QFileInfoList iconsList = QDir(":/img/").entryInfoList();
    m_weather = iconsList.at(m_type).fileName().mid(4);
    m_weather.chop(4);
  }
  return m_weather;
}

void WeatherWidget::mousePressEvent(QMouseEvent *me) {
  qreal x = me->x();
  qreal y = me->y();

  int x0 = 0;
  int y0 = 0;

  if (x <= 120) {
    x0 = 0;
  } else if (x <= 240) {
    x0 = 1;
  } else {
    x0 = 2;
  }

  if (y <= 120) {
    y0 = 0;
  } else if (y <= 240) {
    y0 = 3;
  } else {
    y0 = 6;
  }

  m_type = x0 + y0;
  emit weatherTypeChanged(m_type);
  // QD << "The type at clicking is: " << m_type;
  update();
}

void WeatherWidget::paintFrameOnSelected(QPainter *painter) {
  // painter->save();

  QPen pen(Qt::red);
  pen.setWidth(2);
  painter->setPen(pen);
  painter->setBrush(Qt::NoBrush);

  int x0 = 0;
  int y0 = 0;

  switch(m_type) {
    case 0: {
      x0 = 0;
      y0 = 0;
      break;
    }
    case 1: {
      x0 = 120;
      y0 = 0;
      break;
    }
    case 2: {
      x0 = 240;
      y0 = 0;
      break;
    }
    case 3: {
      x0 = 0;
      y0 = 120;
      break;
    }
    case 4: {
      x0 = 120;
      y0 = 120;
      break;
    }
    case 5: {
      x0 = 240;
      y0 = 120;
      break;
    }
    case 6: {
      x0 = 0;
      y0 = 240;
      break;
    }
    case 7: {
      x0 = 120;
      y0 = 240;
      break;
    }
    case 8: {
      x0 = 240;
      y0 = 240;
      break;
    }
  }
/*
  QD << "the type just before drawing is: " << m_type;
  QD << "Rectangle starts at: " << x0 << ", " << y0;
*/
  if (m_type != -1) {
    painter->drawRect(x0, y0, 120, 120);
  }
  // painter->restore();
}

