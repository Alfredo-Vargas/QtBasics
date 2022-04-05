#include "mainwindow.h"
#include "sliderarray.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->groupBoxTestArea->setVisible(false);
  ui->groupBoxButtons->setVisible(false);

  connect(ui->initOkButton, &QPushButton::clicked, this, &MainWindow::showTestAreaButtons);
  connect(ui->saveSliders, &QPushButton::clicked, this, &MainWindow::displaySliderStatus);
  connect(ui->slidersStatusList, &QListWidget::itemClicked, this, &MainWindow::getSelectedItem);
  connect(ui->deleteStep, &QPushButton::clicked, this, &MainWindow::deleteStep);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showTestAreaButtons() {
  ui->groupBoxInit->setVisible(false);
  int n_sliders = ui->spinBox->value();

  // We delete the default sliderArray that comes with 10 Sliders!
  SliderArray *default_sa = ui->sliderArray;
  delete default_sa;

  // We create a new sliderArray with the number of the Sliders given by the spinbox
  SliderArray *sa = new SliderArray(ui->groupBoxTestArea, n_sliders);
  sa->setObjectName("runTimeSliderArray");
  QVBoxLayout *testAreaLayout = qobject_cast<QVBoxLayout*>(ui->groupBoxTestArea->layout());
  // insert at the 0 position gives you padding automatically: "layout->insertWdiget(0, sa)"
  testAreaLayout->addWidget(sa);
  ui->groupBoxTestArea->setVisible(true);
  ui->groupBoxButtons->setVisible(true);
}

void MainWindow::displaySliderStatus() {
  SliderArray *sa = this->findChild<SliderArray *>("runTimeSliderArray");
  QList<int> data = sa->value();
  QString sliders_status = "";
  for (int i=0; i < data.count(); ++i){
    sliders_status = sliders_status + QString::number(data[i]) + ",";
  }
  ui->slidersStatusList->addItem(sliders_status);
}

QListWidgetItem* MainWindow::getSelectedItem() {
  QListWidgetItem* current_item = ui->slidersStatusList->currentItem();
  return current_item;
}

void MainWindow::deleteStep() {
  if (ui->slidersStatusList->selectedItems().size() != 0) {
    QListWidgetItem* current = getSelectedItem();
    ui->slidersStatusList->removeItemWidget(current);
  }
}

// QUESTIONS:
// 1. How to avoid the red lines in the Init GroupBox  (for label and spinbox)?
// 2. It is better to specify qint32 or just use int ?
//
