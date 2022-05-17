#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->labelWeatherTypeDynamic->setWordWrap(true);

  // show weather type on a label
  connect(ui->weatherWidget, &WeatherWidget::weatherTypeChanged, [=]{
            QString newWeatherType = ui->weatherWidget->getWeatherString();
            ui->labelWeatherTypeDynamic->setText(newWeatherType);
          });
  // show exit the application and show the help menu
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);
  // to save/load files
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveToFile);
  connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadFromFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile() { 
  QPixmap weatherPixmap(this->size());
  this->render(&weatherPixmap);
  weatherPixmap.save("WeatherState.png");
}


void MainWindow::loadFromFile() { 

}

