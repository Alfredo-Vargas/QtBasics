#include "manualwidget.h"
#include "designerwidget.h"
#include "multichoicewindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    // ManualWidget mw;
    // mw.show();
    // DesignerWidget dw;
    // dw.show();
    MultiChoiceWindow mcw;
    mcw.show();
    return a.exec();
}
