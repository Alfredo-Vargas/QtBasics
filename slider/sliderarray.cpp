#include "sliderarray.h"

SliderArray::SliderArray(QWidget *parent, qint32 slider_number)
    : QWidget{parent}
{
    // QWidget *myCentral = new QWidget;
    m_sliderLayout = new QHBoxLayout(this);

    for (int i = 0; i < slider_number; ++i) {
        temp_slider = new QSlider(Qt::Vertical, this);
        m_slidersPointers->push_back(*temp_slider);
        m_sliderLayout->addWidget(temp_slider);
    }
    // setCentralWidget(myCentral);
}

QList<qint32> SliderArray::values() {
    QList<qint32> data;

    for (int i=0; i < m_slidersPointers->count(); ++i) {
        data.push_back(m_slidersPointers->at(i).value());
    }

    return data;
}

void SliderArray::setValues(QList<qint32>* data)
{
   for (int i=0; i < data->count(); ++i) {
       // m_slidersPointers->at(i).setValue(data->at(i));
    }
}
