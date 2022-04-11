#include "fmdial.h"

FmDial::FmDial(QWidget *parent)
    : QWidget{parent}
{
  m_layout = new QHBoxLayout(this);
  // initially we have 400 pixels width and we need to split it into 70 ticks
  // therefore we use to 50 pixels on left and right margins to split every tick by 5 pixels
  m_layout->setContentsMargins(25, 0, 25, 0);  

  m_position = new int(875);

  int counter = 0;
  int pixel_step = 0;
  for (int i=870; i <= 1080; i=i+3) {
    if (counter % 10 != 0) {
      QLine *line = new QLine(counter + pixel_step, counter, counter + pixel_step, counter + 10);
    } 
    else {
      QLine *line = new QLine(counter + pixel_step, counter, counter + pixel_step, counter + 20);
    }
    counter++;
    pixel_step += 5;
  }
  this->setLayout(m_layout);
}

int FmDial::value() {

}

void FmDial::setValue(int current_position) {

}

