#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QFile zendersFile("/home/pacha/projects/QtBasics/QRadio/zendersGent.dat");
  if (!zendersFile.open(QIODevice::ReadWrite)) {
    qFatal("Could not open the file zendersGent.dat");
  }
  QDataStream fromToFile(&zendersFile);
  fromToFile.setVersion(QDataStream::Qt_5_0);

  QStringList frequencies;
  QStringList radioNames;
  while (!fromToFile.atEnd()) {
    QString tempFrequency;
    QString tempRadioName;
    fromToFile >> tempFrequency;
    fromToFile >> tempRadioName;
    m_zenders.insert(tempFrequency, tempRadioName);
  }
  zendersFile.close();

  // qDebug() << "Testing the QMap m_zenders[88.60]=QMusic: " << m_zenders["88.60"];

  // We define the layout of the groupBoxPresets
  QHBoxLayout *groupBoxPresetsLayout = new QHBoxLayout();
  ui->groupBoxPresets->setLayout(groupBoxPresetsLayout);

  // We activate the StatusLine
  displayVolumeLevel();

  // Here begins the connections
  connect(ui->dialVolume, &QDial::valueChanged, this, &MainWindow::displayVolumeLevel);
  connect(ui->dialFrequency, &QDial::valueChanged, this, &MainWindow::changeIndicatorPositionThroughDial);
  connect(ui->fmRule, &FmDial::dialPositionChanged, this, &MainWindow::changeDialPositionThroughIndicator);
  connect(ui->pushButtonAddPreset, &QPushButton::clicked, this, &MainWindow::addButtonToPresets);
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
  volumeFeedback = volumeFeedback + ui->lineEditStatus->text() + "% Listening to ";

  qreal current_frequency = ui->fmRule->value() / 10;
  QString radioKey = QString::number(current_frequency, 'f', 2);

  if (m_zenders.contains(radioKey)) {
    volumeFeedback = volumeFeedback + m_zenders[radioKey];
  }
  else {
    volumeFeedback = volumeFeedback + radioKey + " FM";
  }

  ui->lineEditStatus->setText(volumeFeedback);
}

void MainWindow::changeIndicatorPositionThroughDial() {
  qreal current_value = ui->dialFrequency->value();
  ui->fmRule->setValue(current_value);
  update();
  displayVolumeLevel();
}

void MainWindow::changeDialPositionThroughIndicator() {
  // int indicator_position = ui->fmRule->value();
  // qDebug() << "The value of the indicator is: " << indicator_position;
  // qDebug() << "The value of the dial is: " << ui->dialFrequency->value();
  ui->dialFrequency->setValue(ui->fmRule->value());
  update();
  displayVolumeLevel();
}

void MainWindow::addButtonToPresets() {
  QPushButton *newPreset = new QPushButton();
  qreal current_frequency = ui->fmRule->value() / 10;
  QString radioKey = QString::number(current_frequency, 'f', 2);

  if (m_zenders.contains(radioKey)) {
    newPreset->setText(m_zenders[radioKey]);
  }
  else {
    newPreset->setText(radioKey + " FM");
  }
  ui->groupBoxPresets->layout()->addWidget(newPreset);
  connect(newPreset, &QPushButton::clicked, this, [=]
          {
            qreal buttonFrequency = radioKey.toDouble();
            ui->fmRule->setValue(buttonFrequency * 10);
            emit ui->fmRule->dialPositionChanged(buttonFrequency);
          }
        );
}

