#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  ui->setupUi(this);
  QD << "The GUI Thread ID is:  " << QThread::currentThreadId();

  m_dialogTimerPtr = new QTimer(this);
  m_workerThreadPtr = new QThread(this);
  m_mutexPtr = new QMutex();
  m_sharedDataPtr = new int(0); 
  m_stopPtr = new bool(false);

  m_workerPtr = new Worker();
  m_workerPtr->passQMutex(m_mutexPtr);
  m_workerPtr->passSharedData(m_sharedDataPtr);
  m_workerPtr->passStopBoolean(m_stopPtr);


  // We move the worker thread initially assigned to the GUI thread to the its own subthread
  m_workerPtr->moveToThread(m_workerThreadPtr);
  // CONNECTIONS:
  connect(ui->pushButtonStart, &QPushButton::clicked, this, [=]{
            m_dialogTimerPtr->start(50);
            m_workerThreadPtr->start();
          });
  connect(m_workerThreadPtr, &QThread::started, m_workerPtr, &Worker::doWork);

  connect(ui->pushButtonStop, &QPushButton::pressed, this, [=]{
            *m_stopPtr = true;
            m_dialogTimerPtr->stop();
            ui->labelCounter->setText(QString::number(-1));
          });
  connect(m_dialogTimerPtr, &QTimer::timeout, this, [=]{
            m_mutexPtr->lock();
            ui->labelCounter->setText(QString::number(*m_sharedDataPtr));
            m_mutexPtr->unlock();
          });
}

Dialog::~Dialog()
{
  m_workerThreadPtr->quit();
  m_workerThreadPtr->wait();

  delete m_mutexPtr;
  delete m_sharedDataPtr;
  delete m_stopPtr;
  delete m_workerPtr;

  delete ui;
}

