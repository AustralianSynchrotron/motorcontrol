#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QtGui/QWidget>
#include <QValidator>
#include <QAbstractButton>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <QMap>
#include <QMenu>
#include <QDialog>

#include "qcamotor.h"




/// The table model containing the descriptions of all motors
/// PVs known to the program. Used for the "Choose PV" dialog (Ui::PVtable)
///
class KnownPVTable : public QAbstractTableModel {

  Q_OBJECT;

private:

  QList <QEpicsPv*> knownPVs;   ///< List of the motors' description fields.

  /// SAearches for the pv in the ::knownPVs list.
  ///
  /// @param pv PV to search for.
  ///
  /// @return the index of the pv in the ::knownPVs list if found or invalid index if
  /// the pv was not found in the list.
  ///
  QModelIndex indexOf(QEpicsPv* pv) const;

public:

  /// Constructor
  ///
  /// @param list List of known motor PVs.
  /// @param parent Parent of the object.
  ///
  /// @return
  ///
  KnownPVTable(const QStringList &list, QObject *parent=0);

  /// Implements QAbstractTableModel::rowCount()
  /// @param parent unused.
  /// @return number of rows in the table: size of the ::knownPVs.
  int rowCount(const QModelIndex &parent) const;

  /// Implements QAbstractTableModel::columnCount()
  /// @param parent unused.
  /// @return number of columns in the table. Always 2: motor's PV and the description.
  int columnCount(const QModelIndex &parent) const;

  /// Data stored in the table. Implements the QAbstractTableModel::data().
  ///
  /// @param index Index of the cell.
  /// @param role Role of the data.
  ///
  /// @return Data stored in the cell under the role.
  ///
  QVariant data(const QModelIndex &index, int role) const;

  /// Data in the table's (horizontal) header. Implements QAbstractTableModel::headerData().
  ///
  /// @param section table's column.
  /// @param orientation Header's orientation (only Qt::Horizontal will get some data).
  /// @param role Role of the data.
  ///
  /// @return Data for the header.
  ///
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private slots:

  void updateData();            ///< Slot used to catch the data change.

};


/// \brief Event filter to modify the key press behaviour in the "Choose PV" dialog.
///
/// The dialog contains only two widgets: the search field and the table view. The main idea
/// is to redirect any text-editing key stroke into the search field (they have ho effect
/// in the table view) and up/down navigation to the table view (no effect in the search),
/// leaving only the Enter, Home, End key events where it happened.
///
class KeyPressEater : public QObject {
  Q_OBJECT;
public:
  /// Contructor
  /// @param parent object's parent.
  KeyPressEater(QObject * parent) : QObject(parent) {}
protected:
  /// The event filter. Re-implementation of the Object::eventFilter()
  /// @param obj the object.
  /// @param event key press event.
  /// @return same as in Object::eventFilter().
  bool eventFilter(QObject *obj, QEvent *event);
};



namespace Ui {
  class MotorControl;
  class MotorSetup;
  class GoRelative;
  class PVtable;
}


/// Graphical user interface for the motor.
class QCaMotorGUI : public QWidget {
  Q_OBJECT;

public:

  /// Base name of the files containing the list of the known motor PVs.
  static const QString pvListBaseName;

  static const QString configsSearchBaseDir;
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
  Ui::PVtable *pUi;             ///< "Choose PV" GUI.

  QDialog * setupDialog;        ///< "Setup" dialog.
  QDialog * pvDialog;           ///< "Choose PV" dialog.
  QDialog * relativeDialog;     ///< "Move relatively" dialog.

  QAction * pasteCfgAction;

  static QMap<QString,QString> knownConfigs;
  static KnownPVTable * knownPVs; ///< Table model for the table view in the "Choose PV".

  static bool inited;

  /// Constructs the ::knownPVs and ::knownConfigs.
  ///
  /// The function cannot be called before the application has inited
  /// (needs Qt event loop running), and therefore
  /// is called from within the constructor.
  static void static_init();

  void init();


  QSortFilterProxyModel *proxyModel; ///< Sort/filter proxy for the table view in the "Choose PV".

  /// Lock status of the motor. If the motor is locked, then the PV cannot be changed.
  bool locked;

  ViewMode currentView;         ///< Current view mode of the "Setup" GUI.



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

  inline void showSetup(bool shown=true) { setupDialog->setShown(shown); }

  inline void showPvSetup(bool shown=true) { pvDialog->setShown(shown); }


private slots:

  void onMotorDestruction();

  /// \brief Copies motor's PV into clipboard.
  void copyPV();

  /// \brief Copies motor's description into clipboard.
  void copyDescription();

  /// \brief Copies motor's user position into clipboard.
  void copyPosition();

  /// \brief Copies motor's configuration into clipboard.
  void copyConfiguration();

  /// \brief Pastes motor's configuration from clipboard and loads it.
  void pasteConfiguration();


  /*
  void showContextMenu(const QPoint& pos);
  */

  /// \brief Apply filter to the table view in the "Choose PV" GUI.
  /// Used to catch the text changes from the search line in the GUI.
  /// @param _text new filter.
  void filterPV(const QString & _text="");

  /// Sets new PV when it is activated in the table view from the "Choose PV" GUI.
  /// @param index Index of the cell activated in the table view.
  void choosePV(const QModelIndex & index);

  /// Sets new PV when it is activated from the search field in the "Choose PV" GUI.
  void pvFromSearch();

  /// Reacts on clicking the Setup button of the main GUI.
  void onSetupClicked();

  /// Updates all GUIs when the motor PV has changed.
  /// @param newpv new PV.
  void updatePv(const QString & newpv = "");

  void onSave() ;

  void onLoad(const QString & text) ;

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

  /// \brief Sets the units-per-rev resolution and direction.
  ///
  /// Needed to address the bug described in QCaMotor::setResolution().
  /// In fact it always sets the units-per-rev
  /// to the absolute value of ::res and the direction
  /// to the sign of ::res
  /// @param res new resolution.
  void setUnitsPerRevAndDirection(double res);


  /// Catches the go-backward-by-step commands from GUIs.
  inline void goStepM(){ mot->goStep(-1); }

  /// Catches the go-forward-by-step commands from GUIs.
  inline void goStepP(){ mot->goStep(1);  }

  /// Catches the go-to-negative-limit commands from GUIs.
  inline void goLimitM(){ mot->goLimit(-1); }

  /// Catches the go-to-positive-limit commands from GUIs.
  inline void goLimitP(){ mot->goLimit(1);  }

  /// Catches the start-negative-jog commands from GUIs.
  inline void jogMstart(){ mot->jog(true, -1); }

  /// Catches the stop-negative-jog commands from GUIs.
  inline void jogMstop(){ mot->jog(false, -1); }

  /// Catches the start-positive-jog commands from GUIs.
  inline void jogPstart(){ mot->jog(true, 1); }

  /// Catches the stop-positive-jog commands from GUIs.
  inline void jogPstop(){ mot->jog(false, 1); }

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

  void updateStep(double stp);

  void updateUserHiLimit(double hiL);

  void updateUserLoLimit(double loL);

  void updateDialHiLimit(double hiL);

  void updateDialLoLimit(double loL);

  void updateUnitsPerRev(double vRes);

  void updateMaximumSpeed(double maxSpeed);

  void updateNormalSpeed(double spd);

  void updateBacklashSpeed(double spd);

  void updateJogSpeed(double spd);

  void updateAcceleration(double acc);

  void updateBacklashAcceleration(double acc);

  void updateJogAcceleration(double acc);

  void updateBacklash(double blsh);

  void updateSuMode(QCaMotor::SuMode mode);

  void updateOffsetMode(QCaMotor::OffMode mode);

  void updateDirection(QCaMotor::Direction dir);

  void updateSpmgMode(QCaMotor::SpmgMode mode);

  void updateConnection(bool suc);

  void updateMoving(bool mov);

  void updatePower(bool pwr);

  void updateWired(bool wr);


};

#endif // MOTORCONTROL_H
