#pragma once
#include <QMainWindow>
#include <QFile>
#include <QMap>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void displayVolumeLevel(void);
  void changeIndicatorPositionThroughDial(void);
  void changeDialPositionThroughIndicator(void);

protected:
  void addButtonToPresets(void);

private:
  Ui::MainWindow *ui;
  QMap<QString, QString> m_zenders;
};
