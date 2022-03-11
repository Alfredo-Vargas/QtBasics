#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog{parent}
{
    m_layout = new QHBoxLayout;
    m_label = new QLineEdit;
    m_button = new QPushButton("zoek");
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_button);
    this->setWindowTitle("myDialog1");
    this->setLayout(m_layout);
}

Dialog::~Dialog()
{
}

