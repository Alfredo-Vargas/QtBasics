#ifndef VALUEOBJECT_H
#define VALUEOBJECT_H

#include <QObject>

class ValueObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 integer READ value WRITE setValue)
public:
    explicit ValueObject(QObject *parent = nullptr);
    virtual ~ValueObject();  // virtual is declared so when the destructor of QObject is called can destroy this class unambiguosly
    qint32 value(void);
    // void setValue(qint32); // move to signals to solve the part of slot and signals exercise

public slots:
    void setValue(qint32);

// A signal must NOT be implemented. The meta object compiler (moc) PROVIDES an implementation.
signals:
    void valueChanged(qint32);

private:
    qint32 m_value; // always give the same name of the getter with a "m_" prefix
};

#endif // VALUEOBJECT_H
