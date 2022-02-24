#include "calculatorinterface.h"
#include "ui_calculatorinterface.h"

#include "calculator.h"

CalculatorInterface::CalculatorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorInterface),
    m_calculator(new Calculator(this))
{
    ui->setupUi(this);

    // Add code here (Qt5 way)
}

CalculatorInterface::~CalculatorInterface()
{
    delete ui;
}

void CalculatorInterface::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
