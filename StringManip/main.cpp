#include "stringmanip.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StringManip w;
    w.show();
    return a.exec();
}
