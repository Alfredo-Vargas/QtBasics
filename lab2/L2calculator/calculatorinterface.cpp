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
        connect(btnArray[i], &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonAdd->text());});
    }
        connect(ui->buttonAdd, &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonAdd->text());});
        connect(ui->buttonSubtract, &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonSubtract->text());});
        connect(ui->buttonCalculate, &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonCalculate->text());});
        connect(ui->buttonClear, &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonClear->text());});
        connect(ui->buttonAllClear, &QPushButton::clicked, this, [=] {updateDisplay(ui->buttonAllClear->text());});

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

void CalculatorInterface::updateDisplay(QString m_btnvalue)
{
    QRegExp rx("\\d");
    if (rx.exactMatch(m_btnvalue)) {
        if (m_calculator->getCurrentNumber() != 0 && m_calculator->getOperator()) {
            m_calculator->numEntered(m_btnvalue.toInt());
        }
        else if (m_calculator->getLastResult() != 0 && m_calculator->getOperator()){

    }

    }
    else if (m_btnvalue == "C") {
       m_calculator->clear();
    }
    else if (m_btnvalue == "AC") {
        m_calculator->allClear();
    }
    else if (m_btnvalue == "+") {
        m_calculator->setOperator(m_btnvalue[0]);
    }
    ui->entryLabel->setText(QString::number(m_calculator->getCurrentNumber()));
    emit m_calculator->displayChanged(ui->entryLabel->text());
}
