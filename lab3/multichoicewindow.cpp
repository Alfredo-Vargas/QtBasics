#include "multichoicewindow.h"
#include "ui_multichoicewindow.h"
#include "manualwidget.h"
#include "designerwidget.h"

MultiChoiceWindow::MultiChoiceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiChoiceWindow)
{
    ui->setupUi(this);
}

MultiChoiceWindow::~MultiChoiceWindow()
{
    delete ui;
}

void MultiChoiceWindow::on_pushButton_clicked()
{
    QWidget *w=0;
    if(ui->radioManual->isChecked())
    w = new ManualWidget();
    else
    w = new DesignerWidget();
    if(ui->radioModal->isChecked())
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle(ui->titleEdit->text());
    w->show();
}

