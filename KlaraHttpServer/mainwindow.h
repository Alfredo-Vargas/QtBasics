#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void serverConnected(void);
    void parseReq(QTcpSocket *);

private:
    Ui::MainWindow *ui;
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_socket =nullptr;
};
#endif // MAINWINDOW_H
