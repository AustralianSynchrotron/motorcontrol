#ifndef QMOTORSTACK_H
#define QMOTORSTACK_H

#include <QWidget>
#include <QFile>

#include "ui_motorstack.h"
#include "qcamotorgui.h"
#include "interbutt.h"

namespace Ui {
  class MotorStack;
}

class QMotorStack : public QWidget
{

  Q_OBJECT;

private:

  /// Pair of the motor GUI and it's controlling button widgets.
  typedef QPair<QCaMotorGUI*, interbutt*> MotBut;

  QList< MotBut > motors;       ///< List of the motors in the GUI.
  QFile motorsFile;             ///< Configuration file with the list of ::motors's PVs

  Ui::MotorStack * ui;

  /// Searches for the button in the motors list.
  /// @param but button to search for.
  /// @return index of the pair in the ::botors list with containig the button.
  ///         -1 if search failed.
  int indexOf(interbutt* but);

  /// Searches for the motor in the motors list.
  /// @param mot motor to search for.
  /// @return index of the pair in the ::botors list with containig the motor.
  ///         -1 if search failed.
  int indexOf(QCaMotorGUI* mot);


private slots:

  /// Removes the motor with the button from the UI.
  /// @param button button assigned to the motor.
  void removeMotor(interbutt* button);

  /// Moves the motor up in the UI.
  /// @param button button assigned to the motor.
  void upMotor(interbutt* button);

  /// Moves the motor down in the UI.
  /// @param button button assigned to the motor.
  void downMotor(interbutt* button);

  /// Updates the motorsFile with the motors from the ::motors.
  void updateMotorsFile();

  /// Rearranges elements in the UI according to the ::motors list.
  void constructLayout();

  /// Initializes the program. Must be called only after the
  /// contractor has returned and therefore implemented as
  /// the separate slot
  void initialize();


public:

  QMotorStack(const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(QWidget *parent);
  ~QMotorStack();

  inline bool isLocked() {return ! ui->add->isVisible();}
  QList < const QCaMotor * > motorList() const;

public slots:

  void lock(bool lck);

  /// Adds new motor into the UI.
  ///
  /// @param presetpv Motor's PV.
  /// @param lock Locks the new motor if true.
  /// @param noFileSave Does not update the motorsFile if true.
  ///
  void addMotor(const QString & presetpv = "", bool lock = false, bool noFileSave = false);

  /// Removes all motors from stack.
  void clear();

};

#endif // QMOTORSTACK_H
