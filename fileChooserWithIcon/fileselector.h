#pragma once

// #include <QWidget> we will replace these header by using simply the QLineEdit class
#include <QLineEdit>
#include <QToolButton>  // QToolButton has no text but an icon instead!
#include <QPainter>
#include <QImage>
#include <QResizeEvent>
#include <QFileDialog>

// We need to create a class to have the button folder inside the fileselector class
// This is needed to have full portability of custom widget fileselector

// first we declare only the class to be used as button 
// we will make a distinction from the FileSelector class by using a namespace!

// Declarations of the constructor has to be done on the implementation of the 
// fileselector class !!!
namespace FileSelectorHelper {
class SimpleButton;
}

class FileSelector : public QLineEdit
{
  Q_OBJECT
  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)

public:
  enum Mode { FileOpen, FileSave, Directory};
  // The constructor will not imply conversion types (open, save, directory) 
  // needed when you tailor customize your widget
  explicit FileSelector(Mode mode, QWidget *parent = nullptr);   // customize constructor
  ~FileSelector();  // default destructor

  Mode mode() const;    // to get the current mode
  void setMode(Mode);   // to set the mode to a chosen one
  void chooseFile();    // to call the QFile

signals:
  void modeChanged(FileSelector::Mode);

protected:
  // These calls do not need to interact with I/O user, therefore only requires
  // visibility among the connected classes ==> protected attribute is enough
  void resizeEvent(QResizeEvent *event) override;   // to make layout flexible
  void focusInEvent(QFocusEvent *event) override;   // to show Icon on focus in
  void focusOutEvent(QFocusEvent *event) override;  // to hide Icon on focus out

private:
  Mode m_mode = FileSave;   // By initialization will have this mode by default
  FileSelectorHelper::SimpleButton *m_dirButton = nullptr;   // By default is null
};
