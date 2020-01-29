#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QWidget>
#include <QValidator>
#include <QAbstractButton>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <QDoubleSpinBox>
#include <QMap>
#include <QMenu>
#include <QDialog>

#include "qcamotor.h"


namespace Ui {
  class MotorControl;
  class MotorSetup;
  class GoRelative;
}


QStringList selectMotors(bool onemotor=true,
                         const QStringList & restrictTo = QStringList(), bool selectRestricted=false);
QString selectMotor(const QStringList & restrictTo = QStringList());

/// Graphical user interface for the motor.
class QCaMotorGUI : public QWidget {
  Q_OBJECT;

public:

  static const QString configsExt;

  /// Enumeration with the view modes of the setup dialog.
  /// The values of each element in the enumeration must
  /// coincide with the index of the corresponding item in the
  /// viewMode QCombobox in the "Setup" GUI.
  enum ViewMode {
    SETPV=0,
    MINI=1,
    COMFO=2,
    CONFIG=3,
    EPICS=4
  };

private:

  QCaMotor * mot;          ///< Motor.

  Ui::MotorControl *mUi;        ///< GUI of the main widget.
  Ui::MotorSetup *sUi;          ///< "Setup" (advanced control) GUI.
  Ui::GoRelative *rUi;          ///< "Move relatively" GUI.

  QDialog * setupDialog;        ///< "Setup" dialog.
  QDialog * relativeDialog;     ///< "Move relatively" dialog.

  void init();
  bool locked;

  ViewMode currentView;         ///< Current view mode of the "Setup" GUI.

  QHash<QWidget*,bool> states;
  void updateState(QWidget * wdg, bool good,  QString goodMsg=QString(), QString badMsg=QString() );



public:

  /// Constructor.
  /// @param parent parent widget.
  QCaMotorGUI(QWidget *parent=0);

  QCaMotorGUI(const QString & pv, QWidget *parent=0);

  QCaMotorGUI(QCaMotor * _mot, QWidget *parent=0);

  inline QCaMotor * motor() {return mot;}


  /// Destructor.
  ~QCaMotorGUI();

  /// Lock/unlock the motor (see ::locked).
  /// @param lck new lock status
  void lock(bool lck);

  /// Gives an external application access to the setup button.
  QPushButton * setupButton();
  QDoubleSpinBox * currentPosition(bool readOnly);

  /// Gives an external application access to the widgets of the
  /// basic control UI.
  /// To be used within the QMotorStack.
  Ui::MotorControl * basicUI();

signals:

  /// Emitted whenever the value in the userPosition widget of the main GUI is changed.
  /// @param QString new value.
  void ioPositionChanged(QString);

public slots:

  /// Sets new view mode of the "Setup" GUI.
  /// @param mode new view mode.
  void setViewMode(ViewMode mode);

  /// Same the view mode of the "Setup" GUI.
  /// @param mode view mode (must be the integer from the ::ViewMode enumeration).
  inline void setViewMode(int mode){ setViewMode( (ViewMode) mode ); }

  inline void showSetup(bool shown=true) { setupDialog->setVisible(shown); }


private slots:

  inline void updateName() { setObjectName("GUI for " + motor()->objectName()); }

  void onMotorDestruction();

  /// \brief Copies motor's PV into clipboard.
  void setPv();

  /// \brief Copies motor's PV into clipboard.
  void copyPv();

  /// \brief Copies motor's description into clipboard.
  void copyDescription();

  /// \brief Copies motor's user position into clipboard.
  void copyPosition();

  /// \brief Copies motor's configuration into clipboard.
  void copyConfiguration();

  /// \brief Pastes motor's configuration from clipboard and loads it.
  void pasteConfiguration();

  void pastePv();


  /// Reacts on clicking the Setup button of the main GUI.
  void onSetupClicked();

  /// Updates all GUIs when the motor PV has changed.
  /// @param newpv new PV.
  void updatePv(const QString & newpv = "");

  void onSave() ;

  void onLoad();

  /// \brief Updates main GUIs when a new text in the ::step widget is activated/edited.
  ///
  /// The ::step widget is multifunctional: it can be either the step or one of the
  /// driving modes: jog/relative/limit.
  ///
  /// @param _text new text in the widget.
  ///
  void setStep(const QString & _text="");

  void setSpeedS(double spd=0);
  void setAccelerationS(double acc=0);

  /// \brief Sets the resolution and direction.
  ///
  /// to the absolute value of ::res and the direction
  /// to the sign of ::res
  /// @param res new resolution.
  void setResolutionAndDirection(double res);

  void setUserPosition(double pos); // depending on view mode may or may not alter the offMode.

  void recordCurrent();

  /// Catches the go-backward-by-step commands from GUIs.
  inline void goStepM(){ recordCurrent(); mot->goStep(QCaMotor::NEGATIVE); }

  /// Catches the go-forward-by-step commands from GUIs.
  inline void goStepP(){ recordCurrent(); mot->goStep(QCaMotor::POSITIVE);  }

  /// Catches the go-to-negative-limit commands from GUIs.
  inline void goLimitM(){ recordCurrent(); mot->goLimit(QCaMotor::NEGATIVE); }

  /// Catches the go-to-positive-limit commands from GUIs.
  inline void goLimitP(){ recordCurrent(); mot->goLimit(QCaMotor::POSITIVE);  }

  /// Catches the go-to-negative-home commands from GUIs.
  inline void goHomeM(){ recordCurrent(); mot->goHome(QCaMotor::NEGATIVE); }

  /// Catches the go-to-positive-home commands from GUIs.
  inline void goHomeP(){ recordCurrent(); mot->goHome(QCaMotor::POSITIVE);  }

  /// Catches the start-negative-jog commands from GUIs.
  inline void jogMstart(){ recordCurrent(); mot->jog(true, QCaMotor::NEGATIVE); }

  /// Catches the stop-negative-jog commands from GUIs.
  inline void jogMstop(){ mot->jog(false, QCaMotor::NEGATIVE); }

  /// Catches the start-positive-jog commands from GUIs.
  inline void jogPstart(){ recordCurrent(); mot->jog(true, QCaMotor::POSITIVE); }

  /// Catches the stop-positive-jog commands from GUIs.
  inline void jogPstop(){ mot->jog(false, QCaMotor::POSITIVE); }

  inline void goRelative(double dist) { recordCurrent(); mot->goRelative(dist);}

  inline void goUserPosition(double pos) { recordCurrent(); mot->goUserPosition(pos);}

  inline void goDialPosition(double pos) { recordCurrent(); mot->goDialPosition(pos);}

  inline void goRawPosition(double pos) { recordCurrent(); mot->goRawPosition(pos);}

  ///
  /// Catches Stop/Undo commands from GUIs.
  ///

  /// Stops the motion if the motor is moving or undos last motion if it does not.
  void pressStop();

  /// Divides current step by 10.
  inline void stepD10() { mot->setStep( 0.1 * mot->getStep() ); }

  /// Divides current step by 2.
  inline void stepD2() { mot->setStep( 0.5 * mot->getStep() ); }

  /// Multiplies current step by 2.
  inline void stepM2() { mot->setStep( 2.0 * mot->getStep() ); }

  /// Multiplies current step by 10.
  inline void stepM10() { mot->setStep( 10.0 * mot->getStep() ); }

  ///
  /// Translates into QCaMotor methods
  ///

  inline void setSpmgMode(int btn) {mot->setSpmgMode( (QCaMotor::SpmgMode) btn );}

  inline void setOffsetMode(int btn) {mot->setOffsetMode( (QCaMotor::OffMode) btn );}

  inline void setDirection(int btn) {mot->setDirection( (QCaMotor::Direction) btn );}

  inline void setSuMode(int btn) {mot->setSuMode( (QCaMotor::SuMode) btn );}


  /// Updates the color of the drive buttons reflecting the limits status.
  void updateGoButtonStyle();

  /// Sets style of the stop buttons reflecting the moving status.
  void updateStopButtonStyle();

  /// Enables / Disables GUIs' elements depending on moving, power, connection and other statuses.
  void updateAllElements();

  void updateSpeeds();

  void updateAccelerations();

  void updateDescription(const QString & dsc);

  void updatePrecision(int prec);

  void updateUnits(const QString & egu);

  void updateUserPosition(double ps);

  void updateDialPosition(double ps);

  void updateRawPosition(double ps);

  void updateStep(double stp);
  void updateStep();

  void updateUserHiLimit(double hiL);

  void updateUserLoLimit(double loL);

  void updateDialHiLimit(double hiL);

  void updateDialLoLimit(double loL);

  void updateMaximumSpeed(double maxSpeed);

  void updateNormalSpeed(double spd);

  void updateBacklashSpeed(double spd);

  void updateAcceleration(double acc);

  void updateBacklashAcceleration(double acc);

  void updateBacklash(double blsh);

  void updateSuMode(QCaMotor::SuMode mode);

  void updateOffsetMode(QCaMotor::OffMode mode);

  void updateDirection(QCaMotor::Direction dir);

  void updateSpmgMode(QCaMotor::SpmgMode mode);

  void updateConnected(bool suc);

  void updateMoving(bool mov);

  void updateSlipStall(bool slst);

  void updateProblems(bool probs);

  void updateCommErr(bool commerr);

  void updateAmplifierFault(bool ampFault);

  void updateInitialized(bool inited);

  void updateWrongLimits(bool wrong);

  void updateEncoderLoss(bool eloss);

  void updateHomeRef(QCaMotor::HomeReference hr);

  void updateStatus(bool sts);

  void updateResolutionAndDirection();

  void correctResFieldsWidth();

};


#endif // MOTORCONTROL_H
