#include "stringmanip.h"
#include "ui_stringmanip.h"

StringManip::StringManip(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StringManip)
{
    ui->setupUi(this);
    // connect(ui->lineEditInput, &QLineEdit::textChanged, ui->lineEditOutput, &QLineEdit::setText());

}

StringManip::~StringManip()
{
    delete ui;
}


void StringManip::on_lineEditInput_textChanged(const QString &arg1)
{
    // FIRST SOLUTION (without using the feedback)
    QStringList words = arg1.split(" ");
    QLineEdit *output = ui->lineEditOutput;
    if (words.size() < 2){
        output->setText(arg1);
    }
    else{
        if (words[1].toInt() && words[0] == "value:"){  // <-- this line excludes the case where the number is equal to zero!!
            qint32 result = words[1].toInt() + 1;
            output->setText(QString::number(result));
        }
        else {
            output->setText("Not a valid value");
        }
    }

    // Solution from the Feedback
    // QString newText = arg1;
    // QLineEdit *output = ui->lineEditOutput;
    // bool ok;
    // if (newText.startsWith("value:", Qt::CaseInsensitive)){
        // newText = newText.mid(6);
        // int value = newText.toInt(&ok);  // <-- this implementation does not exclude the case where the number is equal to zero!!
        // if (ok) {
            // output->setText(QString::number(value + 1));
        // }
        // else {
            // output->setText("Not a valid value");
        // }
    // }
    // else {
        // output->setText(arg1);
    // }
}
























