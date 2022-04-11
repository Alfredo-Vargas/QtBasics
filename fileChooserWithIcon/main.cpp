#include "fileselector.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  auto top = new QWidget;
  auto layout = new QGridLayout(top);
  int row = -1;

  auto *checkLabel = new QLabel;

  // Lambda expression to add items:
  auto addItem = [&](const QString &text, FileSelector::Mode mode) {
    layout->addWidget(new QLabel(text), ++row, 0);
    auto selector = new FileSelector(mode);
    layout->addWidget(selector, row, 1);
    QObject::connect(selector, &FileSelector::editingFinished, checkLabel, 
                     [selector, checkLabel, text] {
                       checkLabel->setText(QString("%1, %2").arg(text, selector->text()));
                     });
  };

  addItem("Load a File", FileSelector::FileOpen);
  addItem("Save File", FileSelector::FileSave);
  addItem("Choose a Directory", FileSelector::Directory);

  layout->addWidget(new QLabel("File to load:"), ++row, 0);
  layout->addWidget(checkLabel, row, 1);

  top->resize(600, top->sizeHint().height());
  top->show();
  return QApplication::exec();
}
