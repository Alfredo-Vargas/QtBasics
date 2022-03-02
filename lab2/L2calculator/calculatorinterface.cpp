#include "calculatorinterface.h"
#include "ui_calculatorinterface.h"
#include <QDebug>

#include "calculator.h"

CalculatorInterface::CalculatorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorInterface),
    m_calculator(new Calculator(this))
{
    ui->setupUi(this);
    // Add code here (Qt5 way)
    QPushButton *btnArray[10];
    for(int i=0; i < 10; ++i){
        QString btnName = "button" + QString::number(i);
        btnArray[i] = CalculatorInterface::findChild<QPushButton *>(btnName);
        connect(btnArray[i], &QPushButton::clicked, this, [=] {passButtonValue(btnArray[i]->text());});
    }
        connect(ui->buttonAdd, &QPushButton::clicked, this, [=] {passButtonValue(ui->buttonAdd->text());});
        connect(ui->buttonSubtract, &QPushButton::clicked, this, [=] {passButtonValue(ui->buttonSubtract->text());});
        connect(ui->buttonCalculate, &QPushButton::clicked, this, [=] {passButtonValue(ui->buttonCalculate->text());});
        connect(ui->buttonClear, &QPushButton::clicked, this, [=] {passButtonValue(ui->buttonClear->text());});
        connect(ui->buttonAllClear, &QPushButton::clicked, this, [=] {passButtonValue(ui->buttonAllClear->text());});
    m_calculator->allClear();
}

CalculatorInterface::~CalculatorInterface()
{
    delete ui;
}

void CalculatorInterface::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange: // HELP: The application translation changed.  <-- what does this mean
        ui->retranslateUi(this); // <-- what does this? "Refreshes all binding expressions that use strings marked for translation"
        break;
    // case QEvent::KeyPress:
        // something here
        // break;
    default:
        break;
    }
}

void CalculatorInterface::passButtonValue(QString m_btnvalue)
{
    ui->entryLabel->setText(m_btnvalue);
    m_calculator->numEntered(m_btnvalue.toInt());
    qDebug() << "Integer registeed as current number is" << m_calculator->
}
