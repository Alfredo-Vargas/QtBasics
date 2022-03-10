#include "dialog.h"
#include <QWidget>

Dialog::Dialog(QWidget *parent)
    : QDialog{parent},
    m_label(new QLineEdit)
{
    this->setWindowTitle("myDialog1");

}

Dialog::~Dialog()
{
}

