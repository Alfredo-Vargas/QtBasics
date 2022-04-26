﻿#include "mainwindow.h"
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
  connect(ui->dialVolume, &QDial::valueChanged, this, &MainWindow::displayVolumeLevel);
  connect(ui->dialFrequency, &QDial::valueChanged, this, &MainWindow::changeDialPositionThroughDial);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayVolumeLevel() {
  ui->lineEditStatus->setText("");
  QString volumeFeedback = "Volume at " + QString::number(ui->dialVolume->value());
  volumeFeedback = volumeFeedback + ui->lineEditStatus->text() + "% Listening to QMusic";
  ui->lineEditStatus->setText(volumeFeedback);
}

void MainWindow::changeDialPositionThroughDial() {
  qreal current_value = ui->dialFrequency->value();
  emit ui->fmRule->setValue(current_value);
  update();
}
