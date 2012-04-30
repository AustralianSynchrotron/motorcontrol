#ifndef QMOTORSTACK_H
#define QMOTORSTACK_H

#include <QWidget>
#include <QFile>

#include "qcamotorgui.h"

namespace Ui {
  class MotorStack;
}

class QMotorStack : public QWidget {
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

  void viewModeAll();
  void stopAll();
  void powerOnAll();
  void powerOffAll();
  void updatePowerConnections(bool pwr=false);
  void showGeneral(bool showall=true);

public:

  QMotorStack(const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(const QStringList & _motorsList, const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(const QStringList & _motorsList, QWidget *parent);
  QMotorStack(QWidget *parent);
  ~QMotorStack();

  bool isLocked();
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

  /// Adds existing motor into the UI.
  ///
  /// @param motor existing motor.
  /// @param noFileSave Does not update the motorsFile if true.
  ///
  void addMotor(QCaMotorGUI * motor, bool noFileSave = false);

  /// Adds existing motor into the UI.
  ///
  /// @param motor existing motor.
  /// @param noFileSave Does not update the motorsFile if true.
  ///
   QCaMotorGUI * addMotor(QCaMotor * motor, bool lock = false, bool noFileSave = false);

   /// Adds existing motors into the UI.
   ///
   /// @param motors existing motors.
   /// @param noFileSave Does not update the motorsFile if true.
   ///
   void addMotor(const QList<QCaMotor*> & motorList, bool lock = false, bool noFileSave = false);

   /// Adds existing motors into the UI.
   ///
   /// @param motorList existing motors.
   /// @param noFileSave Does not update the motorsFile if true.
   ///
   void addMotor(const QList<QCaMotorGUI*> & motorList, bool noFileSave = false);


  /// Removes the motor with the button from the UI.
  /// @param button button assigned to the motor.
  void removeMotor(QCaMotorGUI * motor);


  /// Removes all motors from stack.
  void clear();

  void saveConfiguration(const QString & fileName);

  void loadConfiguration(const QString & fileName);

private slots:

  // To address a bug (is it a bug?) in Qt which does not resizes the
  // column widths when the context of the column elements is changed.
  void resetHeader();

signals:

  void listChanged();


};

#endif // QMOTORSTACK_H
