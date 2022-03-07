#include "manualwidget.h"
#include <QMessageBox>

ManualWidget::ManualWidget(QWidget *parent)
    : QWidget{parent},
    m_label(new QLabel("Enter text")),
    m_layout(new QHBoxLayout),
    m_lineEdit(new QLineEdit),
    m_pushButton(new QPushButton("Ok"))
{
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_lineEdit);
    m_layout->addWidget(m_pushButton);
    this->setLayout(m_layout);

    // This only works with byclicking the button (No Return key triggers the message)
    // connect(m_pushButton, &QPushButton::clicked, this, [=] {this->showMessage();});
    connect(m_pushButton, &QPushButton::clicked, this, [=] {this->showMessage();});
    connect(m_lineEdit, &QLineEdit::returnPressed, this, [=] {this->showMessage();});
}

void ManualWidget::showMessage(void){
    QMessageBox::information(this, "Message", "The text entered in the manual widget window is:\n" + m_lineEdit->text());
}
