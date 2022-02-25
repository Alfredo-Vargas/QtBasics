#include "valueobject.h"
#include <QDebug>

ValueObject::ValueObject(QObject *parent)
    : QObject{parent}
{
    m_value = 0;
    qDebug() << "ValueObject consutructed.";
}

ValueObject::~ValueObject()
{
    qDebug() << "ValueObject" << QObject::objectName() << "destructed.";
}

void ValueObject::setValue(qint32 number){
    if (number != m_value){
        m_value = number;
        qDebug() << "The integer value is: " << m_value;
        emit valueChanged(m_value);
    }
}

qint32 ValueObject::value(void){
    return m_value;
}
