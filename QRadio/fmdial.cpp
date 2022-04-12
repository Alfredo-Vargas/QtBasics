#include "fmdial.h"

FmDial::FmDial(QWidget *parent)
    : QWidget{parent}
{
  // m_layout = new QHBoxLayout(this);
  // initially we have 400 pixels width and we need to split it into 70 ticks
  // therefore we use to 50 pixels on left and right margins to split every tick by 5 pixels
  // m_layout->setContentsMargins(25, 0, 25, 0);  

  // m_position = new int(875);


  // this->setLayout(m_layout);
}

FmDial::~FmDial() {

}

int FmDial::value() {
  return m_position;
}

QSize FmDial::sizeHint() const {
  return QSize(400, 50);  // according to the suggested minimum size
}

void FmDial::setValue(int current_position) {
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

  // Horizontal position must be relative to the parent width
  int parent_width = width();
  int x0 = 0.1 * parent_width;
  // tick step equal to the effective width (80% of parent) divided by number of ticks
  int tick_step = 0.8 * parent_width / 70;

  // Vertical position must be relative to the parent height
  int parent_height = height();
  // to vertical in the middle and give room to display the current position 
  int y0 = parent_height / 2;  
  int normal_tick_length = 10;
  int large_tick_length = 20;

  // relative position for the tick text indicators
  int deltay = 25;
  int deltax = -10;

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

void FmDial::paintIndicator(QPainter* painter) {

  QPolygon indicator;

  // we create the polygon that respresents the indicator
  int indicator_width =  4 * 0.8 * width() / 210;
  int indicator_height = 15;
  int relative_xpos = (1080 - m_position) * width() / 210;
  int relative_ypos = height() / 2 - 5;
  QPoint p0(relative_xpos , relative_ypos);
  QPoint p1(relative_xpos + indicator_width, relative_ypos);
  QPoint p2(relative_xpos + indicator_width, relative_ypos + indicator_height);
  QPoint p3(relative_xpos + indicator_width / 2, relative_ypos + 1.5 * indicator_height);
  QPoint p4(relative_xpos, relative_ypos + indicator_height);
  indicator << p0 << p1 << p2 << p3 << p4;

  // we color the polygon (indicator)
  QPen pen;
  QColor color(255, 0, 0, 125);
  pen.setColor(Qt::black);
  painter->setPen(pen);
  painter->setBrush(color);
  painter->drawPolygon(indicator);
}

// TODO:
// Relative position not working properly for the indicator (specially when resizing)
// Maybe use QPointF instead of QPoint?
