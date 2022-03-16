#include "calculatorwidget.h"

#include <QHBoxLayout>
#include <QFont>
#include <QDebug>

CalculatorWidget::CalculatorWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget( m_firstValue = new QLineEdit() );
    layout->addWidget( new QLabel("+") );
    layout->addWidget( m_secondValue = new QLineEdit() );
    layout->addWidget( new QLabel("=") );
    layout->addWidget( m_result = new QLabel() );

    QFont font = m_result->font();
    font.setBold(true);
    m_result->setFont(font);

    // String based connection
    // connect(m_firstValue, SIGNAL(textChanged(QString)), this, SLOT(valueChanged()));
    // connect(m_secondValue, SIGNAL(textChanged(QString)), this, SLOT(valueChanged()));

    // Functor based connection
    connect(this->m_firstValue, &QLineEdit::textChanged, this->m_result ,[=]{valueChanged(m_firstValue->text(), m_secondValue->text());});
    connect(this->m_secondValue, &QLineEdit::textChanged, this->m_result, [=]{valueChanged(m_firstValue->text(), m_secondValue->text());});

    m_firstValue->setText("0");
    m_secondValue->setText("0");
    m_result->setText("0");
}

void CalculatorWidget::valueChanged(QString s1, QString s2)
{
    bool ok = true;
    if (s1.toInt(&ok) && s2.toInt(&ok)){
        m_result->setText(QString::number(s1.toInt() + s2.toInt()));
    }
    else if (s1.toInt(&ok) && s2 == "0") {
        m_result->setText(s1);
    }
    else if (s2.toInt(&ok) && s1 == "0") {
        m_result->setText(s2);
    }
    else {
        m_result->setText("no result");
    }
}
