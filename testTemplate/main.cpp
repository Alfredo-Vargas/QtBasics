#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// TODO:
// 1) Add Load, Save and Exit buttons to the main window
// 2) Generate the compile_commands.json
// 3) How to draw on Top of QLabel that became a QPixmap?
