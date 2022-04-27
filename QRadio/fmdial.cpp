#include "fmdial.h"

FmDial::FmDial(QWidget *parent)
    : QWidget{parent}
{
}

FmDial::~FmDial() {

}

qreal FmDial::value() {
  return m_position;
}

QSize FmDial::sizeHint() const {
  return QSize(400, 50);  // according to the suggested minimum size
}

void FmDial::setValue(qreal current_position) {
  m_position = current_position;
}

void FmDial::paintEvent(QPaintEvent *) {

  QPainter painter(this);
  // Indicates that the engine should antialias edges of primitives if possible
  painter.setRenderHint(QPainter::Antialiasing);    


  QPen pen(Qt::black);
  pen.setWidth(2);
  painter.setPen(pen);
  // QFont(const QString &family, int pointSize = -1, int weight = -1, bool italic = false)
  painter.setFont(QFont("Helvetica", 7));

  // We draw a rectangle at the margins of the fmdial to have a sense of the spacing:
  QRect outerFrame(0, 0, width(), height());
  painter.drawRect(outerFrame);

  // Horizontal position must be relative to the parent width
  qreal parent_width = width();
  // qreal x0 = m_horizontalMargin * parent_width;
  qreal x0 = parent_width * m_hmp / 2;
  // tick step equal to the effective width (80% of parent) divided by number of ticks
  qreal tick_step = (1 - m_hmp) * parent_width / 70;

  // Vertical position must be relative to the parent height
  qreal parent_height = height();
  // to vertical in the middle and give room to display the current position 
  qreal y0 = parent_height / 2;  
  qreal normal_tick_length = 10;
  qreal large_tick_length = 20;

  // relative position for the tick text indicators
  qreal deltay = 25;
  qreal deltax = -10;

  // to count when to introduce a larger tick indicator
  int step_counter = 0;

  // here we draw the ticks
  for (int i=870; i <= 1080; i=i+3) {
    if (step_counter % 10 != 0) {
      painter.drawLine(x0 + tick_step, y0, x0 + tick_step, y0 + normal_tick_length);
    }
    else {
      painter.drawLine(x0 + tick_step, y0, x0 + tick_step, y0 + large_tick_length);
      QString indicator = QString::number(i / 10);
      painter.drawText(x0 + tick_step + deltax, y0 + deltay,
                       x0 + tick_step + deltax, y0 + large_tick_length + deltay,
                       0, indicator);
    }
    step_counter++;
    x0 += tick_step;
  }

  // here we draw the position indicator
  paintIndicator(&painter);
}

void FmDial::paintIndicator(QPainter *painter) {

  QPolygonF indicator;

  // we create the polygon that represents the indicator
  qreal indicator_width =  (1 - m_hmp) * width() / 70;
  qreal indicator_height = 15;
  // qreal relative_xpos = (1080 - m_position) * width() / 210;
  qreal ymax = (1 - m_hmp / 2) * width();
  qreal ymin = width() * m_hmp / 2;
  qreal xmax = 1080;
  qreal xmin = 870;
  qreal slope = (ymax - ymin) / (xmax - xmin);
  qreal const_term = (ymin * xmax - ymax * xmin) / (xmax - xmin);
  m_position = m_position > 1080 ? 1080 : m_position;
  m_position = m_position < 870 ? 870 : m_position;
  qreal relative_xpos = slope * m_position + const_term + indicator_width / 2;
  // qDebug() << "The total width is: " << width();
  // qDebug() << "The ymax and ymin are: " << ymax << " " << ymin;
  // qDebug() << "The slope and const_term are: " << slope << " " << const_term;
  // qDebug() << "The relative xpos is: " << relative_xpos;
  qreal relative_ypos = 1.0 * height() / 2 - 5;
  QPointF p0(relative_xpos , relative_ypos);
  QPointF p1(relative_xpos + indicator_width, relative_ypos);
  QPointF p2(relative_xpos + indicator_width, relative_ypos + indicator_height);
  QPointF p3(relative_xpos + indicator_width / 2, relative_ypos + 1.5 * indicator_height);
  QPointF p4(relative_xpos, relative_ypos + indicator_height);
  indicator << p0 << p1 << p2 << p3 << p4;
  
  // we color the polygon (indicator)
  QPen pen;
  QColor color(255, 0, 0, 125);
  pen.setColor(Qt::black);
  painter->setPen(pen);
  painter->setBrush(color);
  painter->drawPolygon(indicator);

  // we create the label above the polygon to show the current frequency of the dial indicator
  qreal deltay = -15;
  qreal deltax = -10;


  QString currentFrequency = QString::number(m_position / 10, 'f', 2);
  painter->drawText(relative_xpos + deltax, relative_ypos + deltay,
                    relative_xpos + deltax, relative_ypos, 0, currentFrequency);

  // painter->restore();
}

// int FmDial::frequencyToPixel(qreal freq) {
//
//   int horizontal_margin = m_hmp * width() / 2;
//   int w = width() - horizontal_margin * 2;
//   qreal pixelVal = (w / (m_maxFrequency - m_minFrequency)) * (freq - m_minFrequency) + horizontal_margin;
//   pixelVal = qBound(0, (int)pixelVal, width());
//   return pixelVal;
// }
//
// qreal FmDial::pixelToFrequency(int pixel) {
//   int horizontal_margin = m_hmp * width() / 2;
//   int w = width() - horizontal_margin * 2;
//   qreal freqVal = m_minFrequency + ((m_maxFrequency - m_minFrequency) / w) * (pixel - horizontal_margin);
//   freqVal = qRound(freqVal * 10) / 10.0;
//   return freqVal;
// }

void FmDial::mousePressEvent(QMouseEvent *me) {
  qreal ymax = (1 - m_hmp / 2) * width();
  qreal ymin = width() * m_hmp / 2;
  qreal xmax = 1080;
  qreal xmin = 870;
  qreal slope = (ymax - ymin) / (xmax - xmin);
  qreal const_term = (ymin * xmax - ymax * xmin) / (xmax - xmin);
  // m_position = (me->globalX() - const_term) / slope;  // relative to screen
  m_position = (me->pos().x() - const_term) / slope - 2.5;  // relative to widget
  // the above position have a deviation of 2.5 !! why?? (round error?)

  m_position = m_position > 1080 ? 1080 : m_position;
  m_position = m_position < 870 ? 870 : m_position;
  // qDebug() << "The mouse position is: " << me->pos().x();
  // qDebug() << "The total width is: " << width();
  // qDebug() << "The ymax and ymin are: " << ymax << " " << ymin;
  // qDebug() << "The slope and const_term are: " << slope << " " << const_term;
  // qDebug() << "new indicator frequency should be:  " << m_position;
  update();
  emit dialPositionChanged(m_position);
}

void FmDial::mouseMoveEvent(QMouseEvent *me) {
  qreal ymax = (1 - m_hmp / 2) * width();
  qreal ymin = width() * m_hmp / 2;
  qreal xmax = 1080;
  qreal xmin = 870;
  qreal slope = (ymax - ymin) / (xmax - xmin);
  qreal const_term = (ymin * xmax - ymax * xmin) / (xmax - xmin);
  // m_position = (me->globalX() - const_term) / slope;  // relative to screen
  m_position = (me->pos().x() - const_term) / slope - 2.5;  // relative to widget
  // the above position have a deviation of 2.5 !! why?? (round error?)

  m_position = m_position > 1080 ? 1080 : m_position;
  m_position = m_position < 870 ? 870 : m_position;
  // qDebug() << "The mouse position is: " << me->pos().x();
  // qDebug() << "The total width is: " << width();
  // qDebug() << "The ymax and ymin are: " << ymax << " " << ymin;
  // qDebug() << "The slope and const_term are: " << slope << " " << const_term;
  // qDebug() << "new indicator frequency should be:  " << m_position;
  update();
  emit dialPositionChanged(m_position);
}

void FmDial::mouseReleaseEvent(QMouseEvent *me) {
  qreal ymax = (1 - m_hmp / 2) * width();
  qreal ymin = width() * m_hmp / 2;
  qreal xmax = 1080;
  qreal xmin = 870;
  qreal slope = (ymax - ymin) / (xmax - xmin);
  qreal const_term = (ymin * xmax - ymax * xmin) / (xmax - xmin);
  // m_position = (me->globalX() - const_term) / slope;  // relative to screen
  m_position = (me->pos().x() - const_term) / slope - 2.5;  // relative to widget
  // the above position have a deviation of 2.5 !! why?? (round error?)

  m_position = m_position > 1080 ? 1080 : m_position;
  m_position = m_position < 870 ? 870 : m_position;
  // qDebug() << "The mouse position is: " << me->pos().x();
  // qDebug() << "The total width is: " << width();
  // qDebug() << "The ymax and ymin are: " << ymax << " " << ymin;
  // qDebug() << "The slope and const_term are: " << slope << " " << const_term;
  // qDebug() << "new indicator frequency should be:  " << m_position;
  update();
  emit dialPositionChanged(m_position);
}
