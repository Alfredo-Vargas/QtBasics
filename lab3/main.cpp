#include "manualwidget.h"
#include "designerwidget.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ManualWidget mw;
    QLabel *mlabel = new QLabel("Enter text: ");
    QLineEdit *mlineEdit = new QLineEdit;
    QPushButton *mpushButton = new QPushButton("Ok");
    QHBoxLayout *mlayout = new QHBoxLayout;
    mlayout->addWidget(mlabel);
    mlayout->addWidget(mlineEdit);
    mlayout->addWidget(mpushButton);
    mw.setLayout(mlayout);
    mw.show();
    // DesignerWidget dw;
    // dw.show();
    return a.exec();
}
