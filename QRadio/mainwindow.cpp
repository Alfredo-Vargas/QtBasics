#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QFile zendersFile("/home/alfredo/projects/QtBasics/QRadio/zendersGent.dat");
  if (!zendersFile.open(QIODevice::ReadOnly)) {
    qFatal("Could not open the file zendersGent.dat");
  }
  QDataStream outFromFile(&zendersFile);
  outFromFile.setVersion(QDataStream::Qt_5_0);
  // m_zenders = outFromFile.readLine();
  outFromFile >> m_zenders;
  qDebug() << "The value of the first mapping is: " << m_zenders.firstKey();



  // Here begins the connections
  connect(ui->dialVolume, &QDial::valueChanged, this, &MainWindow::displayVolumeLevel);
  connect(ui->dialFrequency, &QDial::valueChanged, this, &MainWindow::changeIndicatorPositionThroughDial);
  connect(ui->fmRule, &FmDial::dialPositionChanged, this, &MainWindow::changeDialPositionThroughIndicator);
  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);
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

void MainWindow::changeIndicatorPositionThroughDial() {
  qreal current_value = ui->dialFrequency->value();
  ui->fmRule->setValue(current_value);
  update();
}

void MainWindow::changeDialPositionThroughIndicator() {
  // int indicator_position = ui->fmRule->value();
  // qDebug() << "The value of the indicator is: " << indicator_position;
  // qDebug() << "The value of the dial is: " << ui->dialFrequency->value();
  ui->dialFrequency->setValue(ui->fmRule->value());
  update();
}
