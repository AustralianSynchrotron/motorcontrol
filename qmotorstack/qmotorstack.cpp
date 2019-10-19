#include "ui_qcamotorgui.h"
#include "ui_qmotorstack.h"
#include "qmotorstack.h"
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>

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

  ui->table->verticalHeader()->setSectionsMovable(true);
  ui->table->verticalHeader()->setSectionsClickable(true);
  ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  connect(ui->add, SIGNAL(clicked()), SLOT(addMotor()));
  connect(ui->viewModeAll, SIGNAL(currentIndexChanged(int)), SLOT(viewModeAll()));
  connect(ui->stopAll, SIGNAL(clicked()), SLOT(stopAll()));
  connect(ui->clear, SIGNAL(clicked()), SLOT(clear()));
  connect(ui->table->verticalHeader(), SIGNAL(sectionDoubleClicked(int)),SLOT(removeRow(int)));
  ui->table->verticalScrollBar()->installEventFilter(this);

  if ( motorsFile.open(QIODevice::ReadWrite | QIODevice::Text) &&
    motorsFile.isReadable() )
    while ( !motorsFile.atEnd() ) {
      QByteArray line = motorsFile.readLine();
      addMotor(line.trimmed(), false, true);
    }
    if ( ! motorsFile.isWritable() )
      motorsFile.close();

}

bool QMotorStack::eventFilter(QObject* obj, QEvent* event) {
  if (    event->type() == QEvent::Paint
      ||  event->type() == QEvent::Show
      ||  event->type() == QEvent::Hide) {
    ui->table->resizeColumnsToContents();
    QScrollBar * sbar = ui->table->verticalScrollBar();
    setFixedWidth(  ui->table->verticalHeader()->size().width()
                  + ui->table->horizontalHeader()->length()
                  + ( sbar->isVisible() ? sbar->width() : 0 ) );
  }
  return QObject::eventFilter(obj, event);
}


void QMotorStack::addMotor(const QList<QCaMotor*> & motorList, bool lock, bool noFileSave) {
  foreach(QCaMotor * mot, motorList)
    addMotor(mot, lock, noFileSave);
}


void QMotorStack::addMotor(const QList<QCaMotorGUI*> & motorList, bool noFileSave) {
  foreach(QCaMotorGUI * mot, motorList)
    addMotor(mot, noFileSave);
}

void QMotorStack::addMotor() {
  QStringList motorPvList = selectMotors(false);
  foreach(QString pv, motorPvList)
    addMotor(pv);
}

QCaMotorGUI * QMotorStack::addMotor(const QString & presetpv, bool lock, bool noFileSave) {
  QCaMotorGUI * motor = new QCaMotorGUI;
  motor->motor()->setPv(presetpv);
  motor->lock(lock);
  addMotor(motor, noFileSave);
  return motor;
}

QCaMotorGUI * QMotorStack::addMotor(QCaMotor *motor, bool lock, bool noFileSave) {
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

  motor->basicUI()->setup->installEventFilter(this);
  //motor->basicUI()->userPosition->installEventFilter(this);
  //motor->basicUI()->step->installEventFilter(this);

  connect(motor->motor(), SIGNAL(changedPv()), SLOT(updateMotorsFile()));

  motors[motor->basicUI()->setup] = motor;

  QTableWidgetItem * itm = new QTableWidgetItem("-");
  itm->setToolTip("Drag to reorganize, double-click to remove.");
  ui->table->setVerticalHeaderItem( idx, itm );

  if ( ! ui->all->isEnabled() )
    ui->all->setEnabled(true);

  if ( ui->viewModeAll->currentText() == "Show" ) {
    motor->showSetup();
    if ( motor->motor()->getPv().isEmpty() )
      motor->motor()->setPv(selectMotor());
  } else if ( ui->viewModeAll->currentText() != "Hide" ) {
    motor->setViewMode( ui->viewModeAll->currentIndex() - 1 );
  }

  emit listChanged();
  if ( ! noFileSave )
    updateMotorsFile();

}

void QMotorStack::removeRow(int idx) {

  if (idx<0)
    return;

  QPushButton * mbtn = (QPushButton*) ui->table->cellWidget(idx, 0);
  ui->table->removeRow( idx );
  delete motors.take(mbtn);

  if (motors.isEmpty())
    ui->all->setEnabled(false);

  emit listChanged();
  updateMotorsFile();

}

void QMotorStack::removeMotor(QCaMotorGUI * motor) {

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


void QMotorStack::clear() {
  for (int crow = ui->table->rowCount() - 1 ;  crow >= 0 ; --crow )
    removeRow(crow);
}

void QMotorStack::showGeneral(bool showall) {
  ui->all->setVisible(showall);
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

QStringList QMotorStack::nameList() const {
  QStringList ret;
  foreach(QCaMotorGUI * mtr, motorList())
    ret << mtr->motor()->getPv();
  return ret;
}


void QMotorStack::updateMotorsFile() {
  if ( ! motorsFile.isOpen() )
    return;
  motorsFile.reset();
  motorsFile.resize(0);
  foreach (QCaMotorGUI * motor, motorList() )
    motorsFile.write( ( motor->motor()->getPv() + "\n" ).toLatin1());
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
        motor->motor()->setPv(selectMotor());
    }
    else if ( ui->viewModeAll->currentText() == "Hide" )
      foreach(QCaMotorGUI * motor, motors)
        motor->showSetup(false);
      else
        foreach(QCaMotorGUI * motor, motors)
          motor->setViewMode( ui->viewModeAll->currentIndex() - 1 );
}

void QMotorStack::stopAll() {
  foreach(QCaMotorGUI * motor, motors)
    motor->motor()->stop();
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
      sett.setValue("offset",mot->getOffset());
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
