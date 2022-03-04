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
        connect(btnArray[i], &QPushButton::clicked, this, [=] {m_calculator->numEntered(i);});
    }
        connect(ui->buttonAdd, &QPushButton::clicked, this, [=] {m_calculator->additionMode();});
        connect(ui->buttonSubtract, &QPushButton::clicked, this, [=] {m_calculator->subtractionMode();});
        connect(ui->buttonCalculate, &QPushButton::clicked, this, [=] {m_calculator->calculate();});
        connect(ui->buttonClear, &QPushButton::clicked, this, [=] {m_calculator->clear();});
        connect(ui->buttonAllClear, &QPushButton::clicked, this, [=] {m_calculator->allClear();});
        // Labels have some Public Slots, one of them is QLabel::setText(const Qstring &)   <-- CHECK THE HELP ALWAYS !!!
        connect(m_calculator, &Calculator::displayChanged, ui->entryLabel, &QLabel::setText);
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
    default:
        break;
    }
}
