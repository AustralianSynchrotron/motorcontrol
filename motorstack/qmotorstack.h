#ifndef QMOTORSTACK_H
#define QMOTORSTACK_H

#include <QWidget>
#include <QFile>

#include "ui_motorstack.h"
#include "qcamotorgui.h"
//#include "interbutt.h"

namespace Ui {
  class MotorStack;
}

class QMotorStack : public QWidget
{

  Q_OBJECT;

private:

  QHash< QPushButton*, QCaMotorGUI* > motors;       ///< List of the motors in the GUI.
  QFile motorsFile;             ///< Configuration file with the list of ::motors's PVs

  Ui::MotorStack * ui;

private slots:

  /// Removes the motor with the button from the UI.
  /// @param button button assigned to the motor.
  void removeRow(int idx);

  /// Updates the motorsFile with the motors from the ::motors.
  void updateMotorsFile();

  /// Initializes the program. Must be called only after the
  /// contractor has returned and therefore implemented as
  /// the separate slot
  void initialize();

  void stopAll();

  void powerOnAll();

  void powerOffAll();

  void updatePowerConnections(bool pwr=false);

public:

  QMotorStack(const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(QWidget *parent);
  ~QMotorStack();

  inline bool isLocked() {return ! ui->add->isVisible();}
  QList < QCaMotorGUI * > motorList() const;

public slots:

  void lock(bool lck);

  /// Adds new motor into the UI.
  ///
  /// @param presetpv Motor's PV.
  /// @param lock Locks the new motor if true.
  /// @param noFileSave Does not update the motorsFile if true.
  ///
  QCaMotorGUI * addMotor(const QString & presetpv = "", bool lock = false, bool noFileSave = false);

  /// Removes the motor with the button from the UI.
  /// @param button button assigned to the motor.
  void removeMotor(QCaMotorGUI * motor);


  /// Removes all motors from stack.
  void clear();


  void resetHeader();

  void saveConfiguration(const QString & fileName);

  void loadConfiguration(const QString & fileName);



};

#endif // QMOTORSTACK_H
