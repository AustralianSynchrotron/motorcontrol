#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QHash>
#include <QPushButton>
#include <QFile>

#include "qmotorstack.h"

namespace Ui
{
  class MainWindow;
}


/// The main window.
class MainWindow : public QMainWindow {
  Q_OBJECT;

public:

  /// Constructor.
  /// @param parent Parent.
  MainWindow(QWidget *parent = 0);

  /// Destructor.
  ~MainWindow();

private:
  Ui::MainWindow *ui;           ///< UI.
  QMotorStack * ms;
};

#endif // MAINWINDOW_H
