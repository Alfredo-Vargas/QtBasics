#ifndef VALUEOBJECT_H
#define VALUEOBJECT_H

#include <QObject>

class ValueObject : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(qint32 integer READ value WRITE setValue)
public:
    explicit ValueObject(QObject *parent = nullptr);
    virtual ~ValueObject();  // virtual is declared so when the destructor of QObject is called can destroy this class unambiguosly
    void setValue(qint32);
    qint32 value(void);

signals:


private:
    qint32 integer; // can't name this value!!!

};

#endif // VALUEOBJECT_H
