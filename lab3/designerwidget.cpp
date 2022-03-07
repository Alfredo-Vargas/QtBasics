#include "designerwidget.h"
#include "ui_designerwidget.h"
#include <QMessageBox>

DesignerWidget::DesignerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignerWidget)
{
    ui->setupUi(this);
    // Solution similar to the Manual Widget
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, [=] {DesignerWidget::on_pushButton_clicked();});
}

DesignerWidget::~DesignerWidget()
{
    delete ui;
}

void DesignerWidget::on_pushButton_clicked()
{
    QMessageBox::information(this, "Message", "The text entered in the designer widget window is:\n" + ui->lineEdit->text());
}

// This extra slot function can be omitted if a new connection is made
// However the drawback will be that the reaction of Button clicked or
// press return key will be identical
void DesignerWidget::on_lineEdit_returnPressed()
{
    QMessageBox::information(this, "Message", "The text entered in the designer widget window is:\n" + ui->lineEdit->text());
}

