#ifndef MANUALWIDGET_H
#define MANUALWIDGET_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class ManualWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManualWidget(QWidget *parent = nullptr);

signals:

private slots:
    void showMessage(void);

private:
    QLabel *m_label;
    QHBoxLayout *m_layout;
    QLineEdit *m_lineEdit;
    QPushButton *m_pushButton;
};

#endif // MANUALWIDGET_H
