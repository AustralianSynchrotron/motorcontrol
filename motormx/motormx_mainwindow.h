#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QToolButton>
#include <QFile>
#include <QDir>
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
  QDir configDir;

  QString fileSL();
  void saveConfiguration(bool params, bool select);
  void loadConfiguration(bool move, bool add, bool select);
  bool event(QEvent *ev) override;
  bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

  void onSave();
  void onSelectiveSave();
  void onConfigSave();
  void onSelectiveConfigSave();
  void onLoad();
  void onListLoad();
  void onMoveLoad();
  void onDirectoryLoad(QString dirName = QString());
  void onDirectoryLoad(const QStringList & pths);
  void onPresetChanged();

};

#endif // MAINWINDOW_H
