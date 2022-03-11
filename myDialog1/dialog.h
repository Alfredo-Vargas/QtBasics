#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    QHBoxLayout *m_layout;
    QLineEdit *m_label;
    QPushButton *m_button;

};
#endif // DIALOG_H
