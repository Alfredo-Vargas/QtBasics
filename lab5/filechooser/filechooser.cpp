#include "filechooser.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

FileChooser::FileChooser(QWidget *parent)
    : QWidget(parent)
{
    lineEdit = new QLineEdit(this);
    button = new QPushButton(tr("..."), this);
    
    lineEdit->setGeometry(5, 5, 200, 20);
    button->setGeometry(210, 5, 20, 20);

    // enter your code here
    // create a layout, set it on the widget and add the two child widgets to it
    layout = new QHBoxLayout(this);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    // make a signal-slot connection between the two widgets
    connect(this->button, &QPushButton::clicked, this, [=]{this->chooseFile();});
    // connection after getter and setter
    // connect(this->button, &QPushButton::clicked, this->lineEdit, [=]{this->file();});
}

void FileChooser::chooseFile() {
    // enter your code here
    // ask the user for a file name and set its path as text of lineEdit

    QString chosenFile = QFileDialog::getOpenFileName();
    chosenFile != "" ? this->lineEdit->setText(chosenFile) : this->lineEdit->setText("");
}

QString FileChooser::file() const {
    QString chosenFile = this->lineEdit->text();
    return chosenFile;
}

void FileChooser::setFile(const QString &f) {
    f != "" ? this->lineEdit->setText(f) : this->lineEdit->setText("");
}
