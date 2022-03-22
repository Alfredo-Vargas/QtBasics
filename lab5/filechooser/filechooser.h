#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QFileDialog>
#include <QWidget>
#include <QHBoxLayout>


class QLineEdit;
class QPushButton;
// class QHBoxLayout;
class FileChooser : public QWidget
{
    Q_OBJECT

public:
    FileChooser(QWidget *parent = 0);
    QString file() const;
    void setFile(const QString &file);
public slots:
    void chooseFile();
private:
    QLineEdit *lineEdit;
    QPushButton *button;
    QHBoxLayout *layout;
};

#endif // FILECHOOSER_H
