#include "ui_qcamotorgui.h"
#include "ui_motorstack.h"
#include "qmotorstack.h"
#include <QSettings>
#include <QFileDialog>

QMotorStack::QMotorStack(const QString & _motorsFile, QWidget *parent) :
    QWidget(parent),
    motorsFile(_motorsFile),
    ui(new Ui::MotorStack)
{
  initialize();
}

QMotorStack::QMotorStack(const QStringList & _motorsList, const QString & _motorsFile, QWidget *parent) :
  QWidget(parent),
  motorsFile(_motorsFile),
  ui(new Ui::MotorStack)
{
  initialize();
  foreach (QString mPV, _motorsList)
    addMotor(mPV,true,true);
}

QMotorStack::QMotorStack(const QStringList & _motorsList, QWidget *parent) :
  QWidget(parent),
  motorsFile(),
  ui(new Ui::MotorStack)
{
  initialize();
  foreach (QString mPV, _motorsList)
    addMotor(mPV,true,true);
}


QMotorStack::QMotorStack(QWidget *parent) :
    QWidget(parent),
    motorsFile(),
    ui(new Ui::MotorStack)
{
  initialize();
}


QMotorStack::~QMotorStack() {
  motorsFile.close();
  clear();
  delete ui;
}


void QMotorStack::initialize() {

  ui->setupUi(this);

  ui->table->verticalHeader()->setMovable(true);
  ui->table->verticalHeader()->setClickable(true);
  ui->table->verticalHeader()->setResizeMode(QHeaderView::Fixed);

  ui->table->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
  ui->table->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
  ui->table->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
  ui->table->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
  ui->table->horizontalHeader()->setResizeMode(4, QHeaderView::ResizeToContents);
  ui->table->horizontalHeader()->setResizeMode(5, QHeaderView::ResizeToContents);
  ui->table->horizontalHeader()->setResizeMode(6, QHeaderView::ResizeToContents);

  connect(ui->add, SIGNAL(clicked()), SLOT(addMotor()));
  connect(ui->viewModeAll, SIGNAL(currentIndexChanged(int)), SLOT(viewModeAll()));
  connect(ui->stopAll, SIGNAL(clicked()), SLOT(stopAll()));
  connect(ui->onAll, SIGNAL(clicked()), SLOT(powerOnAll()));
  connect(ui->offAll, SIGNAL(clicked()), SLOT(powerOffAll()));
  connect(ui->clear, SIGNAL(clicked()), SLOT(clear()));
  connect(ui->table->verticalHeader(), SIGNAL(sectionDoubleClicked(int)),
          SLOT(removeRow(int)));

  if ( motorsFile.open(QIODevice::ReadWrite | QIODevice::Text) &&
       motorsFile.isReadable() )
    while ( !motorsFile.atEnd() ) {
      QByteArray line = motorsFile.readLine();
      addMotor(line.trimmed(), false, true);
  }
  if ( ! motorsFile.isWritable() )
    motorsFile.close();

  updatePowerConnections();

}


QCaMotorGUI * QMotorStack::addMotor(const QString & presetpv, bool lock, bool noFileSave){
  QCaMotorGUI * motor = new QCaMotorGUI;
  motor->motor()->setPv(presetpv);
  motor->lock(lock);
  addMotor(motor, noFileSave);
  return motor;
}

QCaMotorGUI * QMotorStack::addMotor(QCaMotor *motor, bool lock, bool noFileSave){
  QCaMotorGUI * motorUi = new QCaMotorGUI(motor);
  motorUi->lock(lock);
  addMotor(motorUi, noFileSave);
  return motorUi;
}

void QMotorStack::addMotor(QCaMotorGUI * motor, bool noFileSave) {

  int idx = ui->table->rowCount();
  ui->table->insertRow(idx);
  ui->table->setCellWidget(idx,0,motor->basicUI()->setup);
  ui->table->setCellWidget(idx,1,motor->basicUI()->userPosition);
  ui->table->setCellWidget(idx,2,motor->basicUI()->mButtons);
  ui->table->setCellWidget(idx,3,motor->basicUI()->step);
  ui->table->setCellWidget(idx,4,motor->basicUI()->pButtons);
  ui->table->setCellWidget(idx,5,motor->basicUI()->stop);
  ui->table->setCellWidget(idx,6,motor->basicUI()->powerW);

  connect(motor->motor(), SIGNAL(changedPowerConnection(bool)),
          SLOT(updatePowerConnections(bool)));
  connect(motor->motor(), SIGNAL(changedPower(bool)),
          SLOT(resetHeader()));
  connect(motor->motor(), SIGNAL(changedDescription(QString)),
          SLOT(resetHeader()));
  connect(motor->motor(), SIGNAL(changedPv()),
          SLOT(resetHeader()));
  connect(motor->motor(), SIGNAL(changedPv()),
          SLOT(updateMotorsFile()));

  motors[motor->basicUI()->setup] = motor;

  QTableWidgetItem * itm = new QTableWidgetItem("-");
  itm->setToolTip("Drag to reorganize, double-click to remove.");
  ui->table->setVerticalHeaderItem( idx, itm );

  if ( ! ui->all->isEnabled() )
    ui->all->setEnabled(true);

  if ( ui->viewModeAll->currentText() == "Show" ) {
    motor->showSetup();
    if ( motor->motor()->getPv().isEmpty() )
      motor->showPvSetup();
  } else if ( ui->viewModeAll->currentText() != "Hide" ) {
      motor->setViewMode( ui->viewModeAll->currentIndex() - 1 );
  }

  emit listChanged();
  if ( ! noFileSave )
    updateMotorsFile();

}

void QMotorStack::removeRow(int idx){

  if (idx<0)
    return;

  QPushButton * mbtn = (QPushButton*) ui->table->cellWidget(idx, 0);
  ui->table->removeRow( idx );
  delete motors[mbtn];
  motors.remove(mbtn);

  if (motors.isEmpty())
    ui->all->setEnabled(false);

  emit listChanged();
  updatePowerConnections();
  updateMotorsFile();

}

void QMotorStack::removeMotor(QCaMotorGUI * motor){

  if (!motor)
    return;

  const QPushButton * mbtn = motor->basicUI()->setup;
  const int rowCount = ui->table->rowCount();
  int idx=0;
  while ( idx < rowCount )
    if (ui->table->cellWidget(idx,0) == mbtn)
      break;
    else
      idx++;

  if (idx < rowCount )
    removeRow(idx);

}


void QMotorStack::clear(){
  for (int crow = ui->table->rowCount() - 1 ;  crow >= 0 ; --crow )
    removeRow(crow);
}


QList < QCaMotorGUI * > QMotorStack::motorList() const {
  QList<QCaMotorGUI*> list;
  for (int vidx = 0 ;  vidx < ui->table->rowCount() ; ++vidx ) {
    int lidx = ui->table->verticalHeader()->logicalIndex(vidx);
    QWidget * mbtn = ui->table->cellWidget(lidx, 0);
    list << motors[ (QPushButton*) mbtn ];
  }
  return list;
}


void QMotorStack::updateMotorsFile() {
  if ( ! motorsFile.isOpen() )
    return;
  motorsFile.reset();
  motorsFile.resize(0);
  foreach (QCaMotorGUI * motor, motorList() )
    motorsFile.write( ( motor->motor()->getPv() + "\n" ).toAscii());
  motorsFile.flush();
}


void QMotorStack::lock(bool lck) {
  ui->table->verticalHeader()->setVisible(!lck);
  ui->manipulate->setVisible(!lck);
}

bool QMotorStack::isLocked() {
  return ! ui->manipulate->isVisible();
}



void QMotorStack::viewModeAll() {
  if ( ui->viewModeAll->currentText() == "Show" )
    foreach(QCaMotorGUI * motor, motors) {
      motor->showSetup();
      if ( motor->motor()->getPv().isEmpty() )
        motor->showPvSetup();
    }
  else if ( ui->viewModeAll->currentText() == "Hide" )
    foreach(QCaMotorGUI * motor, motors) {
      motor->showSetup(false);
      motor->showPvSetup(false);
    }
  else
    foreach(QCaMotorGUI * motor, motors)
      motor->setViewMode( ui->viewModeAll->currentIndex() - 1 );
}

void QMotorStack::stopAll() {
  foreach(QCaMotorGUI * motor, motors)
    motor->motor()->stop();
}

void QMotorStack::powerOnAll(){
  foreach(QCaMotorGUI * motor, motors)
    motor->motor()->setPower(true);
}

void QMotorStack::powerOffAll(){
  foreach(QCaMotorGUI * motor, motors)
    motor->motor()->setPower(false);
}

void QMotorStack::updatePowerConnections(bool pwr) {

  if (pwr) {
    ui->table->setColumnHidden(6,false);
    ui->powerW->setVisible(true);
    return;
  }

  bool powerCon = false;
  foreach(QCaMotorGUI * motor, motors)
    powerCon |= motor->motor()->getPowerConnection();
  ui->table->setColumnHidden(6, ! powerCon );
  ui->powerW->setVisible(powerCon);

}

void QMotorStack::resetHeader() {
  // Here the delay of 100 msec is set to allow the setup button's text be
  // updated before resetting the header.
  QTimer::singleShot(100, ui->table->horizontalHeader(), SLOT(reset()));
}

void QMotorStack::saveConfiguration(const QString & fileName) {
  QSettings sett(fileName, QSettings::IniFormat);
  sett.clear();
  foreach (QCaMotorGUI * motor, motorList() ) {
    QCaMotor * mot = motor->motor();
    if ( ! mot->getPv().isEmpty() ) {
      sett.beginGroup(mot->getPv());
      sett.setValue("description", mot->getDescription());
      sett.setValue("units", mot->getUnits());
      sett.setValue("position",mot->getUserPosition());
      sett.setValue("speed",mot->getNormalSpeed());
      sett.setValue("lo_limit",mot->getUserLoLimit());
      sett.setValue("hi_limit",mot->getUserHiLimit());
      sett.setValue("steps_per_revol",mot->getStepsPerRev());
      sett.setValue("units_per_revol",mot->getUnitsPerRev());
      sett.endGroup();
    }
  }
}

void QMotorStack::loadConfiguration(const QString & fileName) {
  QSettings sett(fileName, QSettings::IniFormat);
  foreach (QString motPv, sett.childGroups())
    addMotor(motPv);
}
