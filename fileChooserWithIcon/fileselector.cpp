#include "fileselector.h"

// First we create the dir button to be used in our custom fileselector

namespace FileSelectorHelper {
class SimpleButton : public QToolButton
{
  Q_OBJECT

public:
    explicit SimpleButton(QWidget *parent)
      : QToolButton(parent)
    {
      // the mouse will assume a shape when is over this item
      setCursor(Qt::ArrowCursor);   
    }

protected:
  void paintEvent(QPaintEvent *) override
  {
    QPainter painter(this);
    int size = height() - 4;
    painter.drawImage(2, 2, QImage("folder.svg").scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  }
};
}

using namespace FileSelectorHelper;

FileSelector::FileSelector(Mode mode, QWidget *parent)
    : QLineEdit(parent)
{
  m_dirButton = new SimpleButton(this);
  m_dirButton->hide();
  setMode(mode);
  connect(m_dirButton, &SimpleButton::clicked, this, &FileSelector::chooseFile);

}

FileSelector::~FileSelector()
{
}

void FileSelector::resizeEvent(QResizeEvent *event) 
{
  const int size = event->size().height();
  m_dirButton->resize(size, size);
  m_dirButton->move(event->size().width() - size, 0);   // so it is always at the end
  auto margins = textMargins();
  margins.setRight(size);   // so the lineEdit will not be on top of the dir icon!!
  setTextMargins(margins);  // we apply the right margin

  // whenever you override by an event, make sure to always call the super class to update
  QLineEdit::resizeEvent(event);
}

void FileSelector::chooseFile()
{
  const QString fileChosen = [this] {
    switch (mode()) {
      case FileOpen:
        return QFileDialog::getOpenFileName(this, QString(), text());
      case FileSave:
        return QFileDialog::getOpenFileName(this, QString(), text());
      case Directory:
        return QFileDialog::getExistingDirectory(this, QString(), text());
    }
    // this tells the compiler that this point cannot be reached in any possible situation
    // therefore optimization can be viable
    Q_UNREACHABLE();
  }();

  if (!fileChosen.isEmpty()) {
    setText(fileChosen);
    emit editingFinished();   // call similar to signal when enter is pressed
  }
}

void FileSelector::setMode(Mode mode)
{
  const QString text = [mode] {
    switch (mode) {
      case Mode::FileOpen:
      return "Choose file to open";
      case Mode::FileSave:
      return "Choose file to save to";
      case Mode::Directory:
      return "Choose Directory";
    }
    Q_UNREACHABLE();
  }();
  
  // here text is shown when no valid index is set
  setPlaceholderText(text);

  if (mode != m_mode) {
    m_mode = mode;
    emit modeChanged(mode);
  }
}

FileSelector::Mode FileSelector::mode() const 
{
  return m_mode;
}

void FileSelector::focusInEvent(QFocusEvent *event)
{
  m_dirButton->show();
  QLineEdit::focusInEvent(event);
}

void FileSelector::focusOutEvent(QFocusEvent *event)
{
  m_dirButton->hide();
  QLineEdit::focusOutEvent(event);
}
