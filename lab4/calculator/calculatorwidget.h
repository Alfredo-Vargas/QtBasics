#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QLabel>

class CalculatorWidget : public QWidget
{
Q_OBJECT
public:
    explicit CalculatorWidget(QWidget *parent = 0);

private slots:
    void valueChanged(const QString, const QString);

private:
    QLineEdit *m_firstValue;
    QLineEdit *m_secondValue;
    QLabel *m_result;
};

#endif // CALCULATORWIDGET_H
