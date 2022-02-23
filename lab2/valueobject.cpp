#include "valueobject.h"
#include <QDebug>

ValueObject::ValueObject(QObject *parent)
    : QObject{parent}
{
    integer = 0;
    qDebug() << "ValueObject consutructed.";
}

ValueObject::~ValueObject()
{
    qDebug() << "ValueObject" << QObject::objectName() << "destructed.";
}

void ValueObject::setValue(qint32 number){
    integer = number;
}

qint32 ValueObject::value(void){
    return integer;
}
