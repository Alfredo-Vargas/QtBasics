#ifndef SLIDERARRAY_H
#define SLIDERARRAY_H

#include <QHBoxLayout>
#include <QSlider>
#include <QWidget>

class SliderArray : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(const QList<qint32> values READ value WRITE setValues)

public:
    explicit SliderArray(QWidget *parent = nullptr, qint32 slider_number = 3);
    QList<qint32> values() ;

public slots:
    void setValues(QList<qint32>*);


signals:

private:

    QHBoxLayout *m_sliderLayout;
    QList<QSlider> *m_slidersPointers;
    QSlider *temp_slider;
};

Q_DECLARE_METATYPE(SliderArray)

#endif // SLIDERARRAY_H
