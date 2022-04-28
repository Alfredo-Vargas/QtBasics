#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QString chosenFile = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "/home/alfredo/projects/QtBasics/testTemplate/extra/",
      tr("Image Files (*.png *.jpg *.bmp)"));
  qDebug() << "Chosen file is: " << chosenFile;
  m_pix1 = new QPixmap();
  m_pix1->load(chosenFile);
  qDebug() << "pix1 was loaded";
  ui->needle1->setPixmap(*m_pix1);
  qDebug() << "pix1 was added to ui";
  m_pix2 = new QPixmap(":/extra/clock_needle.png");
  qDebug() << "pix2 was loaded";
  ui->needle2->setPixmap(*m_pix2);
  qDebug() << "pix2 was added to ui";
}

MainWindow::~MainWindow()
{
  delete m_pix1;
  delete m_pix2;
  delete ui;
}

