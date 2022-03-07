#include "manualwidget.h"
#include "designerwidget.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    // ManualWidget mw;
    // mw.show();
    DesignerWidget dw;
    dw.show();
    return a.exec();
}
