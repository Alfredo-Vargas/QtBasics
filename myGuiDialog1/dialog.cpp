#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_print = ui->buttonBox->button(QDialogButtonBox::Yes);
    m_print->setText("Print");

}

Dialog::~Dialog()
{
    delete ui;
}

