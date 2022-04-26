#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QFile zendersFile("/home/alfredo/projects/QtBasics/QRadio/zendersGent.dat");
  zendersFile.open(QIODevice::ReadOnly);
  QDataStream in(&zendersFile);
  in.setVersion(QDataStream::Qt_5_0);
  connect(ui->dialVolume, &QDial::objectNameChanged, ui->lineEditStatus, [=]
          {
            ui->lineEditStatus->setText("30");
          });
}

MainWindow::~MainWindow()
{
    delete ui;
}

