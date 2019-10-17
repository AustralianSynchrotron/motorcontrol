#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QToolButton>
#include <QFile>
#include <QComboBox>

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
  QComboBox * presets;
  QToolButton * saveBut;
  QToolButton * loadBut;

  void saveConfiguration(bool params, bool select);
  void loadConfiguration(bool move, bool add, bool select);

private slots:

  void onSave();
  void onSelectiveSave();
  void onConfigSave();
  void onSelectiveConfigSave();
  void onLoad();
  void onListLoad();
  void onMoveLoad();
  void onPresetChanged();

};

#endif // MAINWINDOW_H
