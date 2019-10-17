#include "qcamotorgui.h"
#include "qcamotorgui-additional.h"
#include "ui_qcamotorgui.h"
#include "ui_qcamotorgui-setup.h"
#include "ui_qcamotorgui-pv.h"
#include "ui_qcamotorgui-relative.h"


#include <math.h>
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QStringListModel>
#include <QClipboard>
#include <QMessageBox>


static const QString redStyle =
  "background-color: rgb(128, 0, 0); color: rgb(255, 255, 255);";
static const QString orgStyle =
  "background-color: rgb(128, 64, 0); color: rgb(255, 255, 255);";



static MotorSelection * motSelection = 0;

QStringList selectMotors(bool onemotor, const QStringList & restrictTo, bool selectRestricted) {
  if (!motSelection)
    motSelection = new MotorSelection();
  if (!motSelection) {
    qDebug() << "Failed to create motor selection dialog.";
    return QStringList();
  }
  motSelection->setSingleSelection(onemotor);
  motSelection->limitSelection();
  motSelection->limitSelection(restrictTo, selectRestricted);
  motSelection->open();
  qtWait(motSelection, SIGNAL(finished(int)));
  return ( motSelection->result() == QDialog::Accepted ) ?
           motSelection->selected()  :  QStringList();
}


QString selectMotor(const QStringList & restrictTo) {
  QStringList lst = selectMotors(true, restrictTo);
  return lst.count() == 1 ? lst.at(0) : QString() ;
}









const QString QCaMotorGUI::configsExt="motor.sh";
const QString QCaMotorGUI::pvListBaseName = "listOfKnownMotorPVs.txt";


QCaMotorGUI::QCaMotorGUI(QWidget *parent) :
  QWidget(parent),
  mot(new QCaMotor(parent)),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  setupDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent))
{
  init();
}

QCaMotorGUI::QCaMotorGUI(const QString & pv, QWidget *parent) :
  QWidget(parent),
  mot(new QCaMotor(pv, parent)),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  setupDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent))
{
  init();
}


QCaMotorGUI::QCaMotorGUI(QCaMotor * _mot, QWidget *parent) :
  QWidget(parent),
  mot(_mot),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  setupDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent))
{
  mot->setParent(parent);
  connect(mot, SIGNAL(destroyed()), SLOT(onMotorDestruction()));
  init();
}


QCaMotorGUI::~QCaMotorGUI() {
  delete mUi;
  delete sUi;
  delete rUi;
  delete setupDialog;
  delete relativeDialog;
}



void QCaMotorGUI::init() {

  locked=false;

  mUi->setupUi(this);
  sUi->setupUi(setupDialog);
  rUi->setupUi(relativeDialog);

  foreach (QWidget * wdg, QList<QWidget*>()
    << sUi->backlash
    << sUi->description
    << sUi->dialPosition
    << sUi->dirNeg
    << sUi->dirPos
    << sUi->driveCurrent
    << sUi->encoderResolution
    << sUi->goHome
    << sUi->goHomeM
    << sUi->goHomeP
    << sUi->holdPerCent
    << sUi->limitHi
    << sUi->limitHiDial
    << sUi->limitLo
    << sUi->limitLoDial
    << sUi->loadConfig
    << sUi->maximumSpeed
    << sUi->resolution
    << sUi->offset
    << sUi->offsetFrz
    << sUi->offsetVar
    << sUi->precision
    << sUi->rawPosition
    << sUi->readbackResolution
    << sUi->spmG
    << sUi->spMg
    << sUi->sPmg
    << sUi->Spmg
    << sUi->stepsPerRev
    << sUi->units
    << sUi->unitsPerRev
    << sUi->unitsPerStep
    << sUi->useEncoder
    << sUi->useReadback
    << sUi->userPosition
  )
    protect(wdg);

  setupDialog->setWindowTitle("MotorMx, setup");
  relativeDialog->setWindowTitle("Move relatively");

  sUi->hidden->hide();
  sUi->description->setText(mUi->setup->text());

  sUi->spmgGroup->setId(sUi->Spmg, QCaMotor::STOP);
  sUi->spmgGroup->setId(sUi->sPmg, QCaMotor::PAUSE);
  sUi->spmgGroup->setId(sUi->spMg, QCaMotor::MOVE);
  sUi->spmgGroup->setId(sUi->spmG, QCaMotor::GO);

  sUi->offGroup->setId(sUi->offsetVar, QCaMotor::VARIABLE);
  sUi->offGroup->setId(sUi->offsetFrz, QCaMotor::FROZEN);

  sUi->dirGroup->setId(sUi->dirPos, QCaMotor::POSITIVE);
  sUi->dirGroup->setId(sUi->dirNeg, QCaMotor::NEGATIVE);

  connect(motor(), SIGNAL(changedPv(QString)), SLOT(updateName()));

  //
  // Connect GUI Actions
  //

  connect(mUi->userPosition, SIGNAL(valueChanged(QString)),
          SIGNAL(ioPositionChanged(QString)));
  connect(mUi->setup, SIGNAL(clicked()),
          SLOT(onSetupClicked()) );

  QAction * action;
  #define setupNewAction(L, S) \
          action= new QAction(L, mUi->setup); \
          mUi->setup->addAction(action); \
          connect(action, SIGNAL(triggered()), SLOT(S()));
  setupNewAction("Set PV",              setPv);
  setupNewAction("Copy PV",             copyPv);
  setupNewAction("Paste PV",            pastePv);
  setupNewAction("Copy description",    copyDescription);
  setupNewAction("Copy position",       copyPosition);
  setupNewAction("Copy configuration",  copyConfiguration);
  setupNewAction("Paste configuration", pasteConfiguration);
  mUi->setup->setContextMenuPolicy(Qt::ActionsContextMenu);
  #undef setupNewAction

  mUi->step->setCompleter(0);

  connect(rUi->goRelative, SIGNAL(valueEdited(double)), SLOT(goRelative(double)));

  connect(mUi->userPosition, SIGNAL(valueEdited(double)), SLOT(goUserPosition(double)));
  connect(mUi->step, SIGNAL(textEdited(QString)), SLOT(setStep(QString)));
  connect(mUi->step, SIGNAL(activated(QString)), SLOT(setStep(QString)));
  connect(mUi->step, SIGNAL(escaped()), SLOT(updateStep()));
  connect(mUi->stop, SIGNAL(clicked()), SLOT(pressStop()));
  connect(mUi->jogM, SIGNAL(pressed()), SLOT(jogMstart()));
  connect(mUi->jogM, SIGNAL(released()), SLOT(jogMstop()));
  connect(mUi->jogP, SIGNAL(pressed()), SLOT(jogPstart()));
  connect(mUi->jogP, SIGNAL(released()), SLOT(jogPstop()));
  connect(mUi->goM, SIGNAL(clicked()), SLOT(goStepM()));
  connect(mUi->goP, SIGNAL(clicked()), SLOT(goStepP()));

  connect(sUi->pv, SIGNAL(clicked()), SLOT(copyPv()));
  connect(sUi->viewMode, SIGNAL(activated(int)), SLOT(setViewMode(int)));
  connect(sUi->loadConfig, SIGNAL(clicked()), SLOT(onLoad()));
  connect(sUi->saveConfig, SIGNAL(clicked()),SLOT(onSave()));

  connect(sUi->description, SIGNAL(editingFinished(QString)), mot, SLOT(setDescription(QString)));
  connect(sUi->precision, SIGNAL(valueEdited(int)), mot, SLOT(setPrecision(int)));
  connect(sUi->units, SIGNAL(textEdited(QString)), mot, SLOT(setUnits(QString)));

  connect(sUi->spmgGroup, SIGNAL(buttonClicked(int)), SLOT(setSpmgMode(int)));

  connect(sUi->goHomeM, SIGNAL(clicked()), SLOT(goHomeM()));
  connect(sUi->goHomeP, SIGNAL(clicked()), SLOT(goHomeP()));
  connect(sUi->goHome, SIGNAL(clicked()), mot, SLOT(executeHomeRoutine()));
  connect(sUi->goLimitM, SIGNAL(clicked()), SLOT(goLimitM()));
  connect(sUi->goLimitP, SIGNAL(clicked()), SLOT(goLimitP()));
  connect(sUi->goM, SIGNAL(clicked()), SLOT(goStepM()));
  connect(sUi->goP, SIGNAL(clicked()), SLOT(goStepP()));
  connect(sUi->stepD10, SIGNAL(clicked()), SLOT(stepD10()));
  connect(sUi->stepD2, SIGNAL(clicked()), SLOT(stepD2()));
  connect(sUi->stepM2, SIGNAL(clicked()), SLOT(stepM2()));
  connect(sUi->stepM10, SIGNAL(clicked()), SLOT(stepM10()));
  connect(sUi->step, SIGNAL(valueEdited(double)), mot, SLOT(setStep(double)));
  connect(sUi->jogM, SIGNAL(pressed()), SLOT(jogMstart()));
  connect(sUi->jogM, SIGNAL(released()), SLOT(jogMstop()));
  connect(sUi->jogP, SIGNAL(pressed()), SLOT(jogPstart()));
  connect(sUi->jogP, SIGNAL(released()), SLOT(jogPstop()));
  connect(sUi->stop, SIGNAL(clicked()), SLOT(pressStop()));

  connect(sUi->dialPosition, SIGNAL(valueEdited(double)), mot, SLOT(setDialPosition(double)));
  connect(sUi->dialGoal, SIGNAL(valueEdited(double)), SLOT(goDialPosition(double)));
  connect(sUi->limitLoDial, SIGNAL(valueEdited(double)), mot, SLOT(setDialLoLimit(double)));
  connect(sUi->limitHiDial, SIGNAL(valueEdited(double)), mot, SLOT(setDialHiLimit(double)));

  connect(sUi->readbackResolution, SIGNAL(valueEdited(double)), mot, SLOT(setReadbackResolution(double)));
  connect(sUi->encoderResolution, SIGNAL(valueEdited(double)), mot, SLOT(setEncoderResolution(double)));
  connect(sUi->stepsPerRev, SIGNAL(valueEdited(int)), mot, SLOT(setStepsPerRev(int)));
  connect(sUi->unitsPerStep, SIGNAL(valueEdited(double)), mot, SLOT(setMotorResolution(double)));
  connect(sUi->unitsPerRev, SIGNAL(valueEdited(double)), mot, SLOT(setUnitsPerRev(double)));
  connect(sUi->resolution, SIGNAL(valueEdited(double)), SLOT(setResolutionAndDirection(double)));

  connect(sUi->useEncoder, SIGNAL(clicked(bool)), mot, SLOT(setUseEncoder(bool)));
  connect(sUi->useReadback, SIGNAL(clicked(bool)), mot, SLOT(setUseReadback(bool)));

  connect(sUi->offGroup, SIGNAL(buttonClicked(int)), SLOT(setOffsetMode(int)));
  connect(sUi->dirGroup, SIGNAL(buttonClicked(int)), SLOT(setDirection(int)));

  connect(sUi->maximumSpeed, SIGNAL(valueEdited(double)), mot, SLOT(setMaximumSpeed(double)));
  connect(sUi->speed, SIGNAL(valueEdited(double)), mot, SLOT(setNormalSpeed(double)));
  connect(sUi->backlashSpeed, SIGNAL(valueEdited(double)), mot, SLOT(setBacklashSpeed(double)));
  connect(sUi->acceleration, SIGNAL(valueEdited(double)), mot, SLOT(setAcceleration(double)));
  connect(sUi->backlashAcceleration, SIGNAL(valueEdited(double)), mot, SLOT(setBacklashAcceleration(double)));
  connect(sUi->accelerationS, SIGNAL(valueEdited(double)), SLOT(setAccelerationS(double)));
  connect(sUi->speedS, SIGNAL(valueEdited(double)), SLOT(setSpeedS(double)));
  connect(sUi->equalizeSpeeds, SIGNAL(clicked()), SLOT(setSpeedS()));
  connect(sUi->equalizeAccelerations, SIGNAL(clicked()), SLOT(setAccelerationS()));
  connect(sUi->equalizeSpeeds_2, SIGNAL(clicked()), SLOT(setSpeedS()));
  connect(sUi->equalizeAccelerations_2, SIGNAL(clicked()), SLOT(setAccelerationS()));

  connect(sUi->backlash, SIGNAL(valueEdited(double)), mot, SLOT(setBacklash(double)));

  connect(sUi->userPosition, SIGNAL(valueEdited(double)), mot, SLOT(setUserPosition(double)));
  connect(sUi->rawPosition, SIGNAL(valueEdited(double)), mot, SLOT(setRawPosition(double)));
  connect(sUi->userVarGoal, SIGNAL(valueEdited(double)), SLOT(goUserPosition(double)));
  connect(sUi->userGoal, SIGNAL(valueEdited(double)), SLOT(goUserPosition(double)));
  connect(sUi->rawGoal, SIGNAL(valueEdited(double)), SLOT(goRawPosition(double)));
  connect(sUi->callRelative, SIGNAL(clicked()), relativeDialog, SLOT(show()) );
  connect(sUi->offset, SIGNAL(valueEdited(double)), mot, SLOT(setOffset(double)));
  connect(sUi->limitLo, SIGNAL(valueEdited(double)), mot, SLOT(setUserLoLimit(double)));
  connect(sUi->limitHi, SIGNAL(valueEdited(double)), mot, SLOT(setUserHiLimit(double)));

  connect(sUi->ampFault, SIGNAL(clicked()), mot, SLOT(resetAmpFault()));
  connect(sUi->eloss, SIGNAL(clicked()), mot, SLOT(resetEncoderLoss()));
  connect(sUi->badLimit, SIGNAL(clicked()), mot, SLOT(resetWrongLimits()));
  connect(sUi->initialized, SIGNAL(clicked()), mot, SLOT(initializeMortor()));

  connect(sUi->driveCurrent, SIGNAL(valueEdited(double)), mot, SLOT(setDriveCurrent(double)));
  connect(sUi->holdPerCent, SIGNAL(valueEdited(double)), mot, SLOT(setHoldPerCent(double)));

  //
  // Connect Motor Signals
  //

  #define ConnectMot(NAME, TYPE) connect(mot, \
                           SIGNAL(changed ## NAME (TYPE) ), \
                           SLOT(update ## NAME (TYPE)));

  #define ConnectMotUi(SIG, OBJ, TYPE) connect(mot, \
                         SIGNAL(changed ## SIG (TYPE) ), \
                         OBJ, SLOT(setValue(TYPE)));

  ConnectMot(Pv, QString);
  ConnectMotUi(Out, sUi->out, QString);
  ConnectMot(Description, QString);
  ConnectMot(Precision, int)
  ConnectMot(Units, QString)
  ConnectMot(SlipStall, bool)
  ConnectMot(Problems, bool);
  ConnectMot(CommErr, bool);
  ConnectMot(AmplifierFault, bool);
  ConnectMot(Initialized, bool);
  ConnectMot(WrongLimits, bool);
  ConnectMot(EncoderLoss, bool);
  ConnectMot(UserPosition, double);
  ConnectMot(DialPosition, double);
  ConnectMotUi(RawPosition, sUi->userGoal, double);
  ConnectMotUi(UserGoal, sUi->userGoal, double);
  ConnectMotUi(DialGoal, sUi->dialGoal, double);
  ConnectMotUi(RawGoal, sUi->rawGoal, double);
  ConnectMot(Step, double);
  ConnectMotUi(Offset, sUi->offset, double);
  ConnectMot(OffsetMode, QCaMotor::OffMode);
  ConnectMot(SuMode, QCaMotor::SuMode);
  ConnectMot(Direction, QCaMotor::Direction);
  ConnectMot(SpmgMode, QCaMotor::SpmgMode);
  ConnectMot(HomeRef, QCaMotor::HomeReference);
  ConnectMot(DialHiLimit, double);
  ConnectMot(DialLoLimit, double);
  ConnectMot(UserHiLimit, double);
  ConnectMot(UserLoLimit, double);
  ConnectMotUi(MotorResolution, sUi->unitsPerStep, double);
  ConnectMotUi(ReadbackResolution, sUi->readbackResolution, double);
  ConnectMotUi(EncoderResolution, sUi->encoderResolution, double);
  ConnectMotUi(StepsPerRev, sUi->stepsPerRev, int);
  ConnectMot(MaximumSpeed, double);
  ConnectMot(NormalSpeed, double);
  ConnectMot(BacklashSpeed, double);
  ConnectMot(Acceleration, double);
  ConnectMot(BacklashAcceleration, double);
  ConnectMot(Connected, bool);
  ConnectMot(Moving, bool);
  ConnectMot(Status, bool);
  ConnectMot(Backlash, double);
  ConnectMotUi(DriveCurrent, sUi->driveCurrent, double);
  ConnectMotUi(HoldPerCent, sUi->holdPerCent, double);
  connect(mot, SIGNAL(changedUseReadback(bool)),
          sUi->useReadback, SLOT(setChecked(bool)));
  connect(mot, SIGNAL(changedUseEncoder(bool)),
          sUi->useEncoder, SLOT(setChecked(bool)));
  connect(mot, SIGNAL(changedHiLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));
  connect(mot, SIGNAL(changedLoLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));

  connect(mot, SIGNAL(changedMotorResolution(double)), SLOT(updateResolutionAndDirection()));
  connect(mot, SIGNAL(changedDirection(QCaMotor::Direction)), SLOT(updateResolutionAndDirection()));

  #undef ConnectMot
  #undef ConnectMotUi

  setViewMode(COMFO);
  setupDialog->update();
  setStep();
  updatePv();

}

void QCaMotorGUI::onMotorDestruction() {
  QString pv = mot->getPv();
  mot = new QCaMotor(pv, parent());
  init();
}


void QCaMotorGUI::setPv() {
  mot->setPv(selectMotor());
}

void QCaMotorGUI::copyPv() {
  if ( ! mot->getPv().isEmpty() )
    QApplication::clipboard()->setText(
          mot->getPv());
}

void QCaMotorGUI::copyDescription() {
  if ( ! mot->getDescription().isEmpty() )
    QApplication::clipboard()->setText(
          mot->getDescription());
}

void QCaMotorGUI::copyPosition() {
  if ( mot->isConnected() )
    QApplication::clipboard()->setText(
          QString::number(mot->getUserPosition()) );
}

void QCaMotorGUI::copyConfiguration() {
  if ( ! mot->isConnected() )
    QMessageBox::warning(0, "Warning!",
                         "Copying configuration of the disconnected motor.");
  QString cfg;
  QTextStream stream(&cfg);
  mot->saveConfiguration(stream);
  QApplication::clipboard()->setText(cfg);
}

void QCaMotorGUI::pasteConfiguration() {
  if ( ! mot->isConnected() ) {
    QMessageBox::warning(0, "Error",
                         "Cannot paste configuration because the motor is not connected.");
    return;
  }
  QString cfg = QApplication::clipboard()->text();
  QTextStream stream(&cfg);
  mot->loadConfiguration(stream);
}


void QCaMotorGUI::pastePv() {
  mot->setPv(QApplication::clipboard()->text());
}


void QCaMotorGUI::updatePv(const QString & newpv){
  sUi->pv->setText(newpv);
  updateDescription( newpv.isEmpty() ? "SETUP" : newpv);
  foreach(QAction* act, mUi->setup->findChildren<QAction*>())
      if (!act->text().contains("Paste Pv"))
        act->setEnabled(!newpv.isEmpty());
}

QPushButton * QCaMotorGUI::setupButton() {
  return mUi->setup;
}


QDoubleSpinBox * QCaMotorGUI::currentPosition(bool readOnly) {
  mUi->userPosition->setButtonSymbols( readOnly ? QAbstractSpinBox::NoButtons : QAbstractSpinBox::UpDownArrows );
  mUi->userPosition->setReadOnly(readOnly);
  mUi->userPosition->setFrame(!readOnly);
  return mUi->userPosition;
}


Ui::MotorControl * QCaMotorGUI::basicUI() {
  return mUi;
}


void QCaMotorGUI::lock(bool lck){
  locked = lck;
  foreach ( QAction * action, mUi->setup->actions() )
    if ( action->text() == "Set PV" || action->text() == "Paste PV" )
      action->setDisabled(lck);
}




void QCaMotorGUI::onSetupClicked() {
  if (mot->getPv().isEmpty()) {
    setPv();
  } else {
    setupDialog->show();
    setupDialog->activateWindow();
    setupDialog->raise();
  }
}

void QCaMotorGUI::onSave() {
  const QString fileName = QFileDialog::getSaveFileName(0, "Save configuration",
                           QDir::currentPath() + "/" + mot->getDescription() + "." + configsExt,
                           "Motor configuration files (*." + configsExt + ");;All files (*)");
  mot->saveConfiguration(fileName);
}

void QCaMotorGUI::onLoad() {
  const QString fileName = QFileDialog::getOpenFileName(0, "Load configuration", "",
            "Motor configuration files (*." + configsExt + ");;All files (*)");
  mot->loadConfiguration(fileName);
}

void QCaMotorGUI::setStep(const QString & _text){
  QString text = _text.toLower();
  bool ok;
  double val = text.toDouble(&ok);
  if (text == "jog") {
    mUi->goM->setVisible(false);
    mUi->goP->setVisible(false);
    mUi->jogM->setVisible(true);
    mUi->jogP->setVisible(true);
  } else if (text == "relative") {
    relativeDialog->show();
  } else if (text == "limit -") {
    mot->goLimit(QCaMotor::NEGATIVE);
    mUi->step->fixup();
  } else if (text == "limit +") {
    mot->goLimit(QCaMotor::POSITIVE);
    mUi->step->fixup();
  } else {
    if ( ok && val != mot->getStep() )
      mot->setStep(val);
    mUi->goM->setVisible(true);
    mUi->goP->setVisible(true);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
  }
}


void QCaMotorGUI::setResolutionAndDirection(double res) {
  mot->setMotorResolution(qAbs(res));
  mot->setReadbackResolution(qAbs(res));
  mot->setEncoderResolution(qAbs(res));
  mot->setDirection( res < 0 ? QCaMotor::NEGATIVE : QCaMotor::POSITIVE );
}

void QCaMotorGUI::setSpeedS(double spd) {
  if (spd<=0.0)
    return;
  if ( ! sUi->lockMaximumSpeed->isChecked() ) {
    mot->setMaximumSpeed(spd);
    qtWait(200); // let the maximum speed to be updated.
  }
  if ( spd <= motor()->getMaximumSpeed() ) {
    mot->setJogSpeed(spd);
    mot->setBacklashSpeed(spd);
    mot->setNormalSpeed(spd);
  }
}

void QCaMotorGUI::setAccelerationS(double acc) {
  if (acc<=0.0)
    acc = sUi->accelerationS->value();
  mot->setBacklashAcceleration(acc);
  mot->setAcceleration(acc);
  if (acc)
    mot->setJogAcceleration( motor()->getNormalSpeed() / acc );
}






void QCaMotorGUI::setViewMode(ViewMode mode){

  if ( mode == SETPV ) {
    if (!locked)
      setPv();
    sUi->viewMode->setCurrentIndex(currentView);
    return;
  }

  sUi->viewMode->blockSignals(true);
  currentView = mode;
  sUi->viewMode->setCurrentIndex(currentView);
  sUi->viewMode->blockSignals(false);

  sUi->layHide->insertWidget(0,sUi->rawGoal);
  sUi->layHide->insertWidget(0,sUi->rawPosition);
  sUi->layHide->insertWidget(0,sUi->userGoal);
  sUi->layHide->insertWidget(0,sUi->userPosition);
  sUi->layHide->insertWidget(0,sUi->userVarGoal);
  sUi->layHide->insertWidget(0,sUi->limitHi);
  sUi->layHide->insertWidget(0,sUi->limitLo);
  sUi->layHide->insertWidget(0,sUi->callRelative);
  sUi->layHide->insertWidget(0,sUi->absLabel);
  sUi->layHide->insertWidget(0,sUi->offset);
  sUi->layHide->insertWidget(0,sUi->driveCurrent);
  sUi->layHide->insertWidget(0,sUi->backlash);

  switch (mode) {

  case SETPV:

    // Does not do anything because returns above.

    break;

  case MINI:

    if (mot->isConnected())
      mot->setSpmgMode(QCaMotor::GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->spmgSetup->setVisible(false);
    sUi->goHome ->setVisible(false);
    sUi->goHomeM->setVisible(false);
    sUi->goHomeP->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->placeControlUser->setVisible(false);
    sUi->placeControlRaw->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->userVarGoal);
    sUi->stepD2->setVisible(false);
    sUi->stepD10->setVisible(false);
    sUi->stepM2->setVisible(false);
    sUi->stepM10->setVisible(false);
    sUi->configure->setVisible(false);
    sUi->epics->setVisible(false);

    break;


  case COMFO:

    if (mot->isConnected())
      mot->setSpmgMode(QCaMotor::GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->spmgSetup->setVisible(false);
    sUi->goHome ->setVisible(false);
    sUi->goHomeM->setVisible(false);
    sUi->goHomeP->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlUser->insertWidget(0, sUi->absLabel);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->userVarGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->configure->setVisible(false);
    sUi->epics->setVisible(false);

    break;


  case CONFIG:

    if (mot->isConnected()) {
      mot->setOffsetMode(QCaMotor::FROZEN);
      mot->setSpmgMode(QCaMotor::GO);
    }

    sUi->pv->setVisible(true);
    sUi->label_2->setVisible(true);
    sUi->label_20->setVisible(true);

    sUi->generalSetup->setVisible(true);
    sUi->spmgSetup->setVisible(false);
    sUi->goHome ->setVisible(true);
    sUi->goHomeM->setVisible(true);
    sUi->goHomeP->setVisible(true);

    sUi->label_3->setVisible(true);
    sUi->label_7->setVisible(true);
    sUi->label_21->setVisible(true);
    sUi->layControlUser->insertWidget(0, sUi->userGoal);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->rawGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);

    sUi->layCfgUser->insertWidget(0, sUi->userPosition);
    sUi->layCfgRaw->insertWidget(0, sUi->rawPosition);
    sUi->layCfgLo->insertWidget(0, sUi->limitLo);
    sUi->layCfgHi->insertWidget(0, sUi->limitHi);
    sUi->layCfgOffset->insertWidget(0,sUi->offset);
    sUi->layCfgBlash->insertWidget(0,sUi->backlash);
    sUi->layCfgCurrent->insertWidget(0,sUi->driveCurrent);
    sUi->configure->setVisible(true);
    sUi->epics->setVisible(false);

    break;


  case EPICS:

    sUi->pv->setVisible(true);
    sUi->label_2->setVisible(true);
    sUi->label_20->setVisible(true);

    sUi->generalSetup->setVisible(true);
    sUi->spmgSetup->setVisible(true);
    sUi->goHome ->setVisible(true);
    sUi->goHomeM->setVisible(true);
    sUi->goHomeP->setVisible(true);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->configure->setVisible(false);

    sUi->layEpicsUserMove->insertWidget(0, sUi->userGoal);
    sUi->layEpicsRawMove->insertWidget(0, sUi->rawGoal);
    sUi->layEpicsUserSet->insertWidget(0, sUi->userPosition);
    sUi->layEpicsRawSet->insertWidget(0, sUi->rawPosition);
    sUi->layEpicsHi->insertWidget(0, sUi->limitHi);
    sUi->layEpicsLo->insertWidget(0, sUi->limitLo);
    sUi->layEpicsOffset->insertWidget(0,sUi->offset);
    sUi->layEpicsBlash->insertWidget(0,sUi->backlash);
    sUi->layEpicsCurrent->insertWidget(0,sUi->driveCurrent);
    sUi->epics->setVisible(true);

    break;

  }

}

void QCaMotorGUI::pressStop(){
  if ( ! mot->isMoving() )
    mot->undoLastMotion();
  else if ( dynamic_cast<QAbstractButton*>(sender()) &&
            dynamic_cast<QAbstractButton*>(sender())->text().contains("kill",Qt::CaseInsensitive) )
    mot->kill();
  else {
    mUi->stop->setText("KILL");
    sUi->stop->setText("KILL");
    mot->stop();
  }
}


void QCaMotorGUI::updateConnected(bool suc) {
  updateStopButtonStyle();
  updateAllElements();
  if ( suc &&
       sUi->viewMode->currentIndex() != EPICS &&
       mot->getOffsetMode() != QCaMotor::FROZEN )
    mot->setOffsetMode(QCaMotor::FROZEN);
}


void QCaMotorGUI::updateUserPosition(double ps) {
  mUi->userPosition->setValue(ps);
  sUi->userPosition->setValue(ps);
  sUi->userVarGoal->setValue(ps);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialPosition(double ps) {
  sUi->dialPosition->setValue(ps);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateStep(double stp) {
  sUi->step->setValue(stp);
  sUi->step->QDoubleSpinBox::setValue(stp); // needed to update it even if it has focus
  QString textStep = QString::number(stp);
  mUi->step->setItemText(4, textStep);
  int knownIndex = mUi->step->findText(textStep);
  if (knownIndex == -1)
    mUi->step->insertItem(knownIndex = 4, textStep);
  if ( mUi->step->currentText() == "jog" || mUi->jogM->isHidden() )
    mUi->step->setCurrentIndex(knownIndex);
}

void QCaMotorGUI::updateStep() {
  updateStep(mot->getStep());
}


void QCaMotorGUI::updateDescription(const QString & dsc){
  mUi->setup->setText(dsc);
  setupDialog->setWindowTitle(dsc);
  relativeDialog->setWindowTitle(dsc);
  sUi->description->setText(dsc);
}


void QCaMotorGUI::recordCurrent() {
    if ( ! mot->isConnected() )
        return;
    mUi->userPosition->rememberInHistory();
    sUi->userGoal->rememberInHistory();
    sUi->userVarGoal->rememberInHistory();
    sUi->rawGoal->rememberInHistory();
}


void QCaMotorGUI::updateMoving(bool mov){

  updateAllElements();

  if ( mov )
    mUi->userPosition->setFocus();
  else {
    sUi->jogM->setDown(false);
    sUi->jogP->setDown(false);
    if ( mUi->goM->isDown() )
      mUi->goM->setDown(false);
    if ( mUi->goP->isDown() )
      mUi->goP->setDown(false);
  }

  updateStopButtonStyle();

}


void QCaMotorGUI::updateHomeRef(QCaMotor::HomeReference hr) {

  QFont font;

  font = sUi->goHomeP->font();
  font.setUnderline( hr == QCaMotor::HOMLS || hr == QCaMotor::NEGLS);
  sUi->goHomeP->setFont(font);

  font = sUi->goHomeM->font();
  font.setUnderline( hr == QCaMotor::HOMLS || hr == QCaMotor::POSLS);
  sUi->goHomeM->setFont(font);

  sUi->goHome->setEnabled( hr != QCaMotor::NOHOM );

}


void QCaMotorGUI::updateResolutionAndDirection() {
  sUi->resolution->setValue( mot->getMotorResolution() *
      (mot->getDirection() == QCaMotor::NEGATIVE ? -1.0 : 1.0) );
}

void QCaMotorGUI::updateUnits(const QString & egu){
  rUi->goRelative->setSuffix(egu);
  mUi->userPosition->setSuffix(egu);
  sUi->speed->setSuffix(egu+"/s");
  sUi->speedS->setSuffix(egu+"/s");
  sUi->step->setSuffix(egu);
  sUi->units->setText(egu);
  sUi->limitHiDial->setSuffix(egu);
  sUi->userPosition->setSuffix(egu);
  sUi->dialPosition->setSuffix(egu);
  sUi->limitLoDial->setSuffix(egu);
  sUi->limitLo->setSuffix(egu);
  sUi->limitHi->setSuffix(egu);
  sUi->maximumSpeed->setSuffix(egu+"/s");
  sUi->backlash->setSuffix(egu);
  sUi->unitsPerStep->setSuffix(egu+"/step");
  sUi->unitsPerRev->setSuffix(egu+"/rev");
  sUi->readbackResolution->setSuffix(egu+"/step");
  sUi->encoderResolution->setSuffix(egu+"/step");
  sUi->resolution->setSuffix(egu+"/step");
  sUi->userGoal->setSuffix(egu);
  sUi->userVarGoal->setSuffix(egu);
  sUi->dialGoal->setSuffix(egu);
  sUi->offset->setSuffix(egu);
  sUi->backlashSpeed->setSuffix(egu+"/s");
}

void QCaMotorGUI::updatePrecision(int prec){
  sUi->precision->setValue(prec);
  rUi->goRelative->setDecimals(prec);
  mUi->userPosition->setDecimals(prec);
  sUi->speed->setDecimals(prec);
  sUi->speedS->setDecimals(prec);
  sUi->step->setDecimals(prec);
  sUi->userPosition->setDecimals(prec);
  sUi->dialPosition->setDecimals(prec);
  sUi->limitLo->setDecimals(prec);
  sUi->limitHi->setDecimals(prec);
  sUi->limitLoDial->setDecimals(prec);
  sUi->limitHiDial->setDecimals(prec);
  sUi->acceleration->setDecimals(prec);
  sUi->accelerationS->setDecimals(prec);
  sUi->maximumSpeed->setDecimals(prec);
  sUi->backlash->setDecimals(prec);
  sUi->unitsPerStep->setDecimals(qMax(prec,7));
  sUi->unitsPerRev->setDecimals(qMax(prec,7));
  sUi->readbackResolution->setDecimals(qMax(prec,7));
  sUi->encoderResolution->setDecimals(qMax(prec,7));
  sUi->resolution->setDecimals(qMax(prec,7));
  sUi->userGoal->setDecimals(prec);
  sUi->userVarGoal->setDecimals(prec);
  sUi->offset->setDecimals(prec);
  sUi->dialGoal->setDecimals(prec);
  sUi->backlashSpeed->setDecimals(prec);
  sUi->backlashAcceleration->setDecimals(prec);
}

void QCaMotorGUI::updateMaximumSpeed(double maxSpeed) {
  sUi->speed->setMaximum(maxSpeed);
  sUi->backlashSpeed->setMaximum(maxSpeed);
  sUi->maximumSpeed->setValue(maxSpeed);
  updateSpeeds();
}

void QCaMotorGUI::updateNormalSpeed(double spd) {
  sUi->speed->setValue(spd);
  sUi->speedS->setValue(spd);
  updateSpeeds();
}

void QCaMotorGUI::updateBacklashSpeed(double spd) {
  sUi->backlashSpeed->setValue(spd);
  updateSpeeds();
}


void QCaMotorGUI::updateAcceleration(double acc) {
  sUi->acceleration->setValue(acc);
  sUi->accelerationS->setValue(acc);
  updateAccelerations();
}

void QCaMotorGUI::updateBacklashAcceleration(double acc) {
  sUi->backlashAcceleration->setValue(acc);
  updateAccelerations();
}


void QCaMotorGUI::updateBacklash(double blsh) {
  sUi->backlash->setValue(blsh);
  if (blsh != 0.0 && mot->getBacklashSpeed() == 0.0)
    mot->setBacklashSpeed(mot->getNormalSpeed());
}


void QCaMotorGUI::updateUserHiLimit(double hiL) {
  double loL=mot->getUserLoLimit();
  mUi->userPosition->setMaximum(hiL);
  sUi->userPosition->setMaximum(hiL);
  sUi->userGoal->setMaximum(hiL);
  sUi->userVarGoal->setMaximum(hiL);
  sUi->limitHi->setValue(hiL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateUserLoLimit(double loL) {
  double hiL=mot->getUserHiLimit();
  mUi->userPosition->setMinimum(loL);
  sUi->userPosition->setMinimum(loL);
  sUi->userGoal->setMinimum(loL);
  sUi->userVarGoal->setMinimum(loL);
  sUi->limitLo->setValue(loL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialHiLimit(double hiL){
  sUi->dialPosition->setMaximum(hiL);
  sUi->dialGoal->setMaximum(hiL);
  sUi->limitHiDial->setValue(hiL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialLoLimit(double loL){
  sUi->dialPosition->setMinimum(loL);
  sUi->dialGoal->setMinimum(loL);
  sUi->limitLoDial->setValue(loL);
  updateGoButtonStyle();
}



void QCaMotorGUI::updateState(QWidget * wdg, bool good, QString goodMsg, QString badMsg) {
  if (!wdg)
    return;
  wdg->setStyleSheet( good ? "" : redStyle);
  wdg->setEnabled(!good);
  if ( dynamic_cast<QAbstractButton*>(wdg) ) {
    protect(wdg, !good);
    if ( good && ! goodMsg.isEmpty() )
      dynamic_cast<QAbstractButton*>(wdg)->setText(goodMsg);
    if ( ! good && ! badMsg.isEmpty() )
      dynamic_cast<QAbstractButton*>(wdg)->setText(badMsg);
  }
  if ( dynamic_cast<QPushButton*>(wdg) )
    dynamic_cast<QPushButton*>(wdg)->setFlat(good);
  if ( dynamic_cast<QToolButton*>(wdg) )
    dynamic_cast<QToolButton*>(wdg)->setAutoRaise(!good);
  if ( dynamic_cast<QLabel*>(wdg) ) {
    if ( good && ! goodMsg.isEmpty() )
      dynamic_cast<QLabel*>(wdg)->setText(goodMsg);
    if ( ! good && ! badMsg.isEmpty() )
      dynamic_cast<QLabel*>(wdg)->setText(badMsg);
  }

  states[wdg] = good;
  bool fine = true;
  foreach(bool state, states)
    fine &= state;
  sUi->viewMode->setStyleSheet( fine ? "" : redStyle);
  mUi->setup->setStyleSheet( fine ? "" : redStyle);

}


void QCaMotorGUI::updateSlipStall(bool slst) {
  updateState(sUi->slst, !slst);
}

void QCaMotorGUI::updateProblems(bool probs) {
  updateState(sUi->problems, !probs, "Hardware OK", "HW Problem");
}

void QCaMotorGUI::updateCommErr(bool commerr) {
  updateState(sUi->comErr, !commerr, "Controller OK", "Comm Err");
}

void QCaMotorGUI::updateStatus(bool sts) {
  updateState(sUi->status, sts, "Status OK", "Status Err");
}

void QCaMotorGUI::updateAmplifierFault(bool ampFlt) {
  updateState(sUi->ampFault, !ampFlt, "Amp OK", "Amp Fault");
}

void QCaMotorGUI::updateInitialized(bool inited) {
  sUi->initialized->setText(inited ? "Initialized" : "UnInitialized");
  updateState(sUi->initialized, inited);
}

void QCaMotorGUI::updateWrongLimits(bool badLs) {
  updateState(sUi->badLimit, !badLs, "Limits OK", "Wrong LS's");
}

void QCaMotorGUI::updateEncoderLoss(bool eloss) {
  updateState(sUi->eloss, !eloss, "Encoder OK", "Enc Loss");
}


void QCaMotorGUI::updateSuMode(QCaMotor::SuMode mode) {
  // needed to revert to the original values in the GUI.
  updateUserPosition(mot->getUserPosition());
  updateDialPosition(mot->getDialPosition());
  sUi->rawPosition->setValue(mot->getRawPosition());
  sUi->userGoal->setValue(mot->getUserGoal());
  sUi->dialGoal->setValue(mot->getDialGoal());
  sUi->rawGoal->setValue(mot->getRawGoal());
}

void QCaMotorGUI::updateOffsetMode(QCaMotor::OffMode mode) {
  sUi->offGroup->button(mode)->setChecked(true);
}

void QCaMotorGUI::updateDirection(QCaMotor::Direction dir) {
  sUi->dirGroup->button(dir)->setChecked(true);
}

void QCaMotorGUI::updateSpmgMode(QCaMotor::SpmgMode mode) {
  sUi->spmgGroup->button(mode)->setChecked(true);
}


void QCaMotorGUI::updateSpeeds() {
  double spd = mot->getNormalSpeed();
  sUi->equalizeSpeeds->setVisible( spd != mot->getMaximumSpeed() ||
                                   spd != mot->getBacklashSpeed()||
                                   spd != mot->getJogSpeed() );
}

void QCaMotorGUI::updateAccelerations() {
  double acc = mot->getAcceleration();
  sUi->equalizeAccelerations->setVisible (
        acc != mot->getBacklashAcceleration() ||
      mot->getJogAcceleration() != 0.0 ||
      acc != mot->getNormalSpeed() / mot->getJogAcceleration() ) ;
}

void QCaMotorGUI::updateGoButtonStyle(){

  QString style;

  if (mot->getLoLimitStatus())
    style = redStyle;
  else if ( mot->getUserPosition() <= mot->getUserLoLimit() ||
            mot->getDialPosition() <= mot->getDialLoLimit() )
    style = orgStyle;
  else
    style = "";
  mUi->goM->setStyleSheet(style);
  mUi->jogM->setStyleSheet(style);
  sUi->goM->setStyleSheet(style);
  sUi->goLimitM->setStyleSheet(style);
  sUi->goHomeM->setStyleSheet(style);
  sUi->jogM->setStyleSheet(style);

  if (mot->getHiLimitStatus())
    style = redStyle;
  else if ( mot->getUserPosition() >= mot->getUserHiLimit() ||
            mot->getDialPosition() >= mot->getDialHiLimit() )
    style = orgStyle;
  else
    style = "";
  mUi->goP->setStyleSheet(style);
  mUi->jogP->setStyleSheet(style);
  sUi->goP->setStyleSheet(style);
  sUi->goLimitP->setStyleSheet(style);
  sUi->goHomeP->setStyleSheet(style);
  sUi->jogP->setStyleSheet(style);


}

void QCaMotorGUI::updateStopButtonStyle() {

  if ( ! mot->isConnected() ) {
    mUi->stop->setStyleSheet("");
    sUi->stop->setStyleSheet("");
    mUi->stop->setText("No link");
    sUi->stop->setText("No link");
  } else if (mot->isMoving()) {
    mUi->stop->setStyleSheet(redStyle);
    sUi->stop->setStyleSheet(redStyle);
    mUi->stop->setText("STOP");
    sUi->stop->setText("STOP");
    mUi->stop->setToolTip("Stop motion");
    sUi->stop->setToolTip("Stop motion");
  } else {
    mUi->stop->setStyleSheet("");
    sUi->stop->setStyleSheet("");
    mUi->stop->setText("UNDO");
    sUi->stop->setText("UNDO");
    double undo = - ( mot->getDirection() == QCaMotor::NEGATIVE ? -1.0 : 1.0) *
        mot->getMotorResolution() * mot->getLastMotion();
    const QString txt("Undo last motion ("
                      + QString::number(undo) + mot->getUnits() + ")");
    mUi->stop->setToolTip(txt);
    sUi->stop->setToolTip(txt);
  }

}

void QCaMotorGUI::updateAllElements(){

  const bool
    mv  = mot->isMoving(),
    cn  = mot->isConnected(),
    std = cn && !mv;

  rUi->goRelative    ->setEnabled(std);

  mUi->goM           ->setEnabled(std);
  mUi->goP           ->setEnabled(std);
  mUi->jogM          ->setEnabled(cn && ( ! mv || mUi->jogM->isDown()));
  mUi->jogP          ->setEnabled(cn && ( ! mv || mUi->jogP->isDown()));
  mUi->userPosition  ->setEnabled(std);
  mUi->step          ->setEnabled(std);
  mUi->stop          ->setEnabled(cn);

  sUi->goLimitM      ->setEnabled(std);
  sUi->goLimitP      ->setEnabled(std);
  sUi->goHomeM       ->setEnabled(std);
  sUi->goHomeP       ->setEnabled(std);
  sUi->goM           ->setEnabled(std);
  sUi->goP           ->setEnabled(std);
  sUi->jogM          ->setEnabled(cn && ( ! mv || sUi->jogM->isDown()) );
  sUi->jogP          ->setEnabled(cn && ( ! mv || sUi->jogP->isDown()) );
  sUi->stop          ->setEnabled(cn);
  sUi->spmgSetup     ->setEnabled(cn);
  sUi->rawGoal       ->setEnabled(std);
  sUi->userGoal      ->setEnabled(std);
  sUi->dialGoal      ->setEnabled(std);
  sUi->userVarGoal   ->setEnabled(std);
  sUi->callRelative  ->setEnabled(std);

  sUi->states        ->setEnabled(cn);
  sUi->control       ->setEnabled(cn);
  sUi->loadConfig    ->setEnabled(std);
  sUi->configure     ->setEnabled(std);
  sUi->epics         ->setEnabled(std);
  sUi->generalSetup  ->setEnabled(std);

}
