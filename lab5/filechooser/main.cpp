#include <QApplication>
#include "filechooser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileChooser w;
    w.show();


    return a.exec();
}


// QUESTION 1:
// Why not include the needed files in the header files
// class call? instead of include? any difference?
// Best practice?
