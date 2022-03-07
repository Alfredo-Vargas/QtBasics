#ifndef MULTICHOICEWINDOW_H
#define MULTICHOICEWINDOW_H

#include <QWidget>

namespace Ui {
class MultiChoiceWindow;
}

class MultiChoiceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MultiChoiceWindow(QWidget *parent = nullptr);
    ~MultiChoiceWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MultiChoiceWindow *ui;
};

#endif // MULTICHOICEWINDOW_H
