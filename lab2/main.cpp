#include  "valueobject.h"
#include <QFile>
#include <QDebug>
#include <QVariant>

int main (int argc, char **argv) {
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "-------------------------EXPLORING INHERITANCE------------------------";
    // qDebug() << "----------------------------------------------------------------------";

    // ValueObject o;
    // QFile file;

    // qDebug() << "Inheritance Info of ValueObject:";
    // qDebug() << "Does the object \"ValueObject\" inherits from QObject?:" << o.inherits("QObject");
    // qDebug() << "Does the object \"ValueObject\" inherits from ValueObject?:" << o.inherits("ValueObject");
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "Inheritance Info of QFile:";
    // qDebug() << "Does the object \"QFile\" inherits from QIODevice?:" << file.inherits("QIODevice");
    // qDebug() << "Does the object \"QFile\" inherits from QDataStream?:" << file.inherits("QDataStream");
    // qDebug() << "Does the object \"QFile\" inherits from QObject?:" << file.inherits("QObject");
    // qDebug() << "Does the object \"QFile\" inherits from QTemporaryFile?:" << file.inherits("QTemporaryFile");
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "The initial value of ValueObject is: " << o.value();
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "----------------------------------------------------------------------";
    // qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());
    // o.setValue(42);
    // qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());  // Not able to read through property without Q_PROPERTY(qint32 integer READ value)
    // o.setProperty("integer", 11);       // Not able to write through property without Q_PROPERTY(qint32 integer WRITE setValue)
    // qDebug("Value: %d = %d", o.value(), o.property("integer").toInt());

    // qDebug() << "----------------------------------------------------------------------";
    // qDebug() << "-------------------------MEMORY MANAGEMENT----------------------------";
    // qDebug() << "----------------------------------------------------------------------";
    // o.setObjectName("root");

    // ValueObject *c1 = new ValueObject();
    // c1->setObjectName("child 1");
    // ValueObject *c2 = new ValueObject();
    // c2->setObjectName("child 2");
    // ValueObject *c1c1 = new ValueObject();
    // c1c1->setObjectName("child 1 of child 1");
    // ValueObject *c2c1 = new ValueObject();
    // c2c1->setObjectName("child 2 of child 1");
    // ValueObject *c = new ValueObject();
    // c->setObjectName("child");

    // // Only root was destructed until this point (why not the others?)
    // // The pointers to Value objects c1, c2, c1c1, c2c1 and c are destructed
    // // but the memory of the new ValueObjects() that they pointed to are never deallocated?
    // // Is the above a signal of memory leaking?

    // c1->setParent(&o);
    // c2->setParent(&o);
    // c1c1->setParent(c1);
    // c2c1->setParent(c1);
    // c->setParent(c2);

    // From the above we see that the order of destruction follows a stack structure.
    // The setParent() enables pointers in both directions, every object is now linked to
    // the root and follow a STACK structure, the objects themselves are ALWAYS on the HEAP.
    // This avoids dangling pointers

    qDebug() << "----------------------------------------------------------------------";
    qDebug() << "-------------------------SIGNALS AND SLOTS----------------------------";
    qDebug() << "----------------------------------------------------------------------";
    ValueObject o1;
    ValueObject o2;
    // The following line connects o2 to o1
    QObject::connect(&o1, SIGNAL(valueChanged(qint32)), &o2, SLOT(setValue(qint32)));
    // The following line completes the connection of the circle o2 follows o1 and o1 follows o2 (THIS CRASHES THE PROGRAM)
    QObject::connect(&o2, SIGNAL(valueChanged(qint32)), &o1, SLOT(setValue(qint32)));
    o1.setValue(1);
    o2.setValue(2);
    // Connect here
    qDebug("o1: %d, o2: %d", o1.value(), o2.value());
    o1.setValue(42);
    qDebug("o1: %d, o2: %d", o1.value(), o2.value());
    o2.setValue(11);
    qDebug("o1: %d, o2: %d", o1.value(), o2.value());


    // From the above everything is consistent and self explanatory, with o1 and o2 independent
    // Why the emit then? -- ANSWER: Emit (in ValueObject::setValue) makes the connection codewise!

    // Because o2 follows o1 then whenever we change the value of o1 then o2 also executes the
    // function of o1

    // Two objects following each other can be useful whenever you want to change an attribute in
    // two different ways

  return 0;
}








