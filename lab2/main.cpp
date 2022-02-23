#include  "valueobject.h"
#include <QFile>
#include <QDebug>
#include <QVariant>

int main (int argc, char **argv) {
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "-------------------------EXPLORING INHERITANCE------------------------";
    qDebug() << "----------------------------------------------------------------------";

    ValueObject o;
    QFile file;

    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "-------------------------EXPLORING INHERITANCE------------------------";
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "Inheritance Info of ValueObject:";
    qDebug() << "Does the object \"ValueObject\" inherits from QObject?:" << o.inherits("QObject");
    qDebug() << "Does the object \"ValueObject\" inherits from ValueObject?:" << o.inherits("ValueObject");
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "Inheritance Info of QFile:";
    qDebug() << "Does the object \"QFile\" inherits from QIODevice?:" << file.inherits("QIODevice");
    qDebug() << "Does the object \"QFile\" inherits from QDataStream?:" << file.inherits("QDataStream");
    qDebug() << "Does the object \"QFile\" inherits from QObject?:" << file.inherits("QObject");
    qDebug() << "Does the object \"QFile\" inherits from QTemporaryFile?:" << file.inherits("QTemporaryFile");
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "The initial value of ValueObject is: " << o.value();
    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "----------------------------------------------------------------------";
    qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());
    o.setValue(42);
    qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());  // Not able to read through property without Q_PROPERTY(qint32 integer READ value)
    o.setProperty("integer", 11);       // Not able to write through property without Q_PROPERTY(qint32 integer WRITE setValue)
    qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());

    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "-------------------------MEMORY MANAGEMENT----------------------------";
    qDebug() << "----------------------------------------------------------------------";
    o.setObjectName("root");

    ValueObject *c1 = new ValueObject();
    c1->setObjectName("child 1");
    ValueObject *c2 = new ValueObject();
    c2->setObjectName("child 2");
    ValueObject *c1c1 = new ValueObject();
    c1c1->setObjectName("child 1 of child 1");
    ValueObject *c2c1 = new ValueObject();
    c2c1->setObjectName("child 2 of child 1");
    ValueObject *c = new ValueObject();
    c->setObjectName("child");

    // Only root was destructed until this point (why not the others?)
    // The pointers to Value objects c1, c2, c1c1, c2c1 and c are destructed
    // but the memory of the new ValueObjects() that they pointed to are never deallocated?
    // Is the above a signal of memory leaking?

    c1->setParent(&o);
    c2->setParent(&o);
    c1c1->setParent(c1);
    c2c1->setParent(c1);
    c->setParent(c2);

    // From the above we see that the order of destruction follows a stack structure.
    // Does this avoids dangling pointers?


    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "-------------------------SIGNALS AND SLOTS----------------------------";
    qDebug() << "----------------------------------------------------------------------";

  return 0;
}








