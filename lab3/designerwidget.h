#ifndef DESIGNERWIDGET_H
#define DESIGNERWIDGET_H

#include <QWidget>

namespace Ui {
class DesignerWidget;
}

class DesignerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DesignerWidget(QWidget *parent = nullptr);
    ~DesignerWidget();

private slots:

    void on_pushButton_clicked();

private:
    Ui::DesignerWidget *ui;
};

#endif // DESIGNERWIDGET_H
