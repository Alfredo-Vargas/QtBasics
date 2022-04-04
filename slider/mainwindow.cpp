#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->groupBoxTestArea->setVisible(false);
  ui->groupBoxButtons->setVisible(false);

  connect(ui->initOkButton, &QPushButton::clicked, this, &MainWindow::showTestAreaButtons);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showTestAreaButtons() {
  ui->groupBoxInit->setVisible(false);
  int n_sliders = ui->spinBox->value();

  SliderArray *sa = new SliderArray(nullptr, n_sliders);
  ui->sliderArray = sa;
  ui->groupBoxTestArea->setVisible(true);
  ui->groupBoxButtons->setVisible(true);
}



// QUESTIONS:
// 1. How to avoid the red lines in the Init GroupBox  (for label and spinbox)?
// 2. It is better to specify qint32 or just use int ?
