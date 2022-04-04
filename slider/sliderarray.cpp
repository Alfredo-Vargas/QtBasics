#include "sliderarray.h"

SliderArray::SliderArray(QWidget *parent, qint32 slider_number)
    : QWidget{parent}
{
    m_sliderLayout = new QHBoxLayout(this);
    m_sliderLayout->setContentsMargins(0, 0, 0, 0);
    
    m_slidersPointers = new QList<QSlider>;

    for (int i = 0; i < slider_number; ++i) {
        QSlider *slider;
        slider = new QSlider(Qt::Vertical, this);
        m_sliderLayout->addWidget(slider);
    }

}

QList<int> SliderArray::value() {
    QList<int> data;

    for (int i=0; i < m_slidersPointers->count(); ++i) {
        data.push_back(m_slidersPointers->at(i).value());
    }

    return data;
}

void SliderArray::setValue(QList<int> data)
{
    m_slidersPointers = new QList<QSlider>;
   for (int i=0; i < data.count(); ++i) {
      QSlider *slider;
      slider = new QSlider(Qt::Vertical, this);
      slider->setValue(data.at(i));
      // m_slidersPointers->value(i).setValue(data->at(i));
    }
}
