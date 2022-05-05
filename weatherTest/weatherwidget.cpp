#include "weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget{parent}
{
  QPainter painter(this);
  // painter.setRenderHint(QPainter::Antialiasing);
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
      // qDebug() << name;
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
      // qDebug() << name;
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
  paintFrameOnSelected(&painter);
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
  qDebug() << "The type is: " << m_type;
  update();
}

void WeatherWidget::paintFrameOnSelected(QPainter *painter) {
  painter->save();

  QPen pen(Qt::red);
  pen.setWidth(2);
  painter->setPen(pen);
  painter->setBrush(Qt::white);

  int x0 = 0;
  int y0 = 0;

  switch(m_type) {
    case 0: {
      x0 = 0;
      y0 = 0;
      return;
    }
    case 1: {
      x0 = 120;
      y0 = 0;
      return;
    }
    case 2: {
      x0 = 240;
      y0 = 0;
      return;
    }
    case 3: {
      x0 = 0;
      y0 = 120;
      return;
    }
    case 4: {
      x0 = 120;
      y0 = 120;
      return;
    }
    case 5: {
      x0 = 240;
      y0 = 120;
      return;
    }
    case 6: {
      x0 = 0;
      y0 = 240;
      return;
    }
    case 7: {
      x0 = 120;
      y0 = 240;
      return;
    }
    case 8: {
      x0 = 240;
      y0 = 240;
      return;
    }
  }

  if (m_type >= 0) {
    painter->drawRect(x0, y0, 120, 120);
  }
  update();
  qDebug() << "Rectangle starts at: " << x0 << ", " << y0;
}

//TODO
// (1) Why is painter.drawPixmap(0, 0, 10, 10, m_background) not recognized as member variable?
