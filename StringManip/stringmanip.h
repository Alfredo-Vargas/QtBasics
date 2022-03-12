#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <QDialog>
#include <QLineEdit>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class StringManip; }
QT_END_NAMESPACE

class StringManip : public QDialog
{
    Q_OBJECT

public:
    StringManip(QWidget *parent = nullptr);
    ~StringManip();

private slots:
    void on_lineEditInput_textChanged(const QString &arg1);

private:
    Ui::StringManip *ui;
};
#endif // STRINGMANIP_H
