#include "qcamotor.h"
#include <limits>

#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QtCore/qmath.h>



using namespace std;

QCaMotor::QCaMotor(QObject *parent) :
  QObject(parent),
  pv(),
  description(),
  precsision(0),
  units(),
  userPosition(0),
  dialPosition(0),
  rawPosition(0),
  userGoal(0),
  dialGoal(0),
  rawGoal(0),
  step(0),
  offset(0),
  direction(POSITIVE),
  loLimitStatus(false),
  hiLimitStatus(false),
  userLoLimit(0),
  userHiLimit(0),
  dialLoLimit(0),
  dialHiLimit(0),
  motorResolution(1.0),
  readbackResolution(1.0),
  encoderResolution(1.0),
  maximumSpeed(1.0),
  normalSpeed(1.0),
  revSpeed(1.0),
  backlashSpeed(1.0),
  jogSpeed(1.0),
  acceleration(1.0),
  backlashAcceleration(1.0),
  jogAcceleration(1.0),
  iAmConnected(false),
  iAmMoving(false), // false is crusial here to distinguish first and further updates in ::updateMoving()
  useEncoder(false),
  useReadback(false),
  backlash(0),
  iAmPowered(true),
  powerIsConnected(false),
  iaAmWired(true),
  lastMotion(0)
{
  init();
}

QCaMotor::QCaMotor(const QString & _pv, QObject *parent) :
  QObject(parent),
  pv(),
  description(),
  precsision(0),
  units(),
  userPosition(0),
  dialPosition(0),
  rawPosition(0),
  userGoal(0),
  dialGoal(0),
  rawGoal(0),
  step(0),
  offset(0),
  direction(POSITIVE),
  loLimitStatus(false),
  hiLimitStatus(false),
  userLoLimit(0),
  userHiLimit(0),
  dialLoLimit(0),
  dialHiLimit(0),
  motorResolution(1.0),
  readbackResolution(1.0),
  encoderResolution(1.0),
  maximumSpeed(1.0),
  normalSpeed(1.0),
  revSpeed(1.0),
  backlashSpeed(1.0),
  jogSpeed(1.0),
  acceleration(1.0),
  backlashAcceleration(1.0),
  jogAcceleration(1.0),
  iAmConnected(false),
  iAmMoving(false), // false is crusial here to distinguish first and further updates in ::updateMoving()
  useEncoder(false),
  useReadback(false),
  backlash(0),
  iAmPowered(true),
  powerIsConnected(false),
  iaAmWired(true),
  lastMotion(0)
{
  init();
  setPv(_pv);
}


void QCaMotor::init() {

  installEventFilter(this);

  connect(this, SIGNAL(error(QString)), this, SLOT(printError(QString)));

  fields.insert(".PROC", new QEpicsPv(this));

  fields.insert(".DESC", new QEpicsPv(this));
  connect(fields[".DESC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDescription(QVariant)));

  fields.insert(".PREC", new QEpicsPv(this));
  connect(fields[".PREC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updatePrecision(QVariant)));
  fields.insert(".EGU",  new QEpicsPv(this));
  connect(fields[".EGU"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUnits(QVariant)));

  fields.insert(".RBV",  new QEpicsPv(this));
  connect(fields[".RBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserPosition(QVariant)));
  fields.insert(".DRBV", new QEpicsPv(this));
  connect(fields[".DRBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialPosition(QVariant)));
  fields.insert(".RRBV", new QEpicsPv(this));
  connect(fields[".RRBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRawPosition(QVariant)));
  fields.insert(".VAL",  new QEpicsPv(this));
  connect(fields[".VAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserGoal(QVariant)));
  fields.insert(".DVAL", new QEpicsPv(this));
  connect(fields[".DVAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialGoal(QVariant)));
  fields.insert(".RVAL", new QEpicsPv(this));
  connect(fields[".RVAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRawGoal(QVariant)));
  fields.insert(".TWV",  new QEpicsPv(this));
  connect(fields[".TWV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateStep(QVariant)));
  fields.insert(".RDBD",  new QEpicsPv(this));
  connect(fields[".RDBD"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDeadBand(QVariant)));


  fields.insert(".TWR",  new QEpicsPv(this));
  fields.insert(".TWF",  new QEpicsPv(this));
  fields.insert(".HOMR", new QEpicsPv(this));
  fields.insert(".HOMF", new QEpicsPv(this));
  fields.insert(".JOGR", new QEpicsPv(this));
  fields.insert(".JOGF", new QEpicsPv(this));
  fields.insert(".RLV",  new QEpicsPv(this));
  fields.insert(".STOP", new QEpicsPv(this));

  fields.insert(".HLS",  new QEpicsPv(this));
  connect(fields[".HLS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateHiLimitStatus(QVariant)));
  fields.insert(".LLS",  new QEpicsPv(this));
  connect(fields[".LLS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateLoLimitStatus(QVariant)));
  fields.insert(".HLM",  new QEpicsPv(this));
  connect(fields[".HLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserHiLimit(QVariant)));
  fields.insert(".LLM",  new QEpicsPv(this));
  connect(fields[".LLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserLoLimit(QVariant)));
  fields.insert(".DHLM", new QEpicsPv(this));
  connect(fields[".DHLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialHiLimit(QVariant)));
  fields.insert(".DLLM", new QEpicsPv(this));
  connect(fields[".DLLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialLoLimit(QVariant)));

  fields.insert(".MRES", new QEpicsPv(this));
  connect(fields[".MRES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMotorResolution(QVariant)));
  fields.insert(".RRES", new QEpicsPv(this));
  connect(fields[".RRES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateReadbackResolution(QVariant)));
  fields.insert(".ERES", new QEpicsPv(this));
  connect(fields[".ERES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateEncoderResolution(QVariant)));
  fields.insert(".UREV", new QEpicsPv(this));
  connect(fields[".UREV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUnitsPerRev(QVariant)));
  fields.insert(".SREV", new QEpicsPv(this));
  connect(fields[".SREV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateStepsPerRev(QVariant)));

  fields.insert(".VMAX", new QEpicsPv(this));
  connect(fields[".VMAX"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMaximumSpeed(QVariant)));
  fields.insert(".VELO", new QEpicsPv(this));
  connect(fields[".VELO"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateNormalSpeed(QVariant)));
  fields.insert(".S", new QEpicsPv(this));
  connect(fields[".S"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRevSpeed(QVariant)));
  fields.insert(".BVEL", new QEpicsPv(this));
  connect(fields[".BVEL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklashSpeed(QVariant)));
  fields.insert(".JVEL", new QEpicsPv(this));
  connect(fields[".JVEL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateJogSpeed(QVariant)));

  fields.insert(".ACCL", new QEpicsPv(this));
  connect(fields[".ACCL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateAcceleration(QVariant)));
  fields.insert(".BACC", new QEpicsPv(this));
  connect(fields[".BACC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklashAcceleration(QVariant)));
  fields.insert(".JAR",  new QEpicsPv(this));
  connect(fields[".JAR"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateJogAcceleration(QVariant)));

  fields.insert(".BDST", new QEpicsPv(this));
  connect(fields[".BDST"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklash(QVariant)));

  fields.insert(".DMOV", new QEpicsPv(this));
  connect(fields[".DMOV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMoving(QVariant)));
  fields.insert(".UEIP", new QEpicsPv(this));
  connect(fields[".UEIP"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUseEncoder(QVariant)));
  fields.insert(".URIP", new QEpicsPv(this));
  connect(fields[".URIP"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUseReadback(QVariant)));

  fields.insert(".OFF",  new QEpicsPv(this));
  connect(fields[".OFF"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateOffset(QVariant)));
  fields.insert(".FOFF", new QEpicsPv(this));
  connect(fields[".FOFF"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateOffsetMode(QVariant)));
  fields.insert(".DIR",  new QEpicsPv(this));
  connect(fields[".DIR"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDirection(QVariant)));
  fields.insert(".SET",  new QEpicsPv(this));
  connect(fields[".SET"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateSuMode(QVariant)));
  fields.insert(".SPMG", new QEpicsPv(this));
  connect(fields[".SPMG"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateSpmgMode(QVariant)));
  fields.insert("_ON_STATUS", new QEpicsPv(this));
  connect(fields["_ON_STATUS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updatePower(QVariant)));
  fields.insert("_ON_CMD",    new QEpicsPv(this));
  fields.insert("_CONNECTED_STATUS", new QEpicsPv(this));
  connect(fields["_CONNECTED_STATUS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateWired(QVariant)));


  foreach ( QString key, fields.keys() )
    if ( key == "_CONNECTED_STATUS" )
      connect(fields[key], SIGNAL(connectionChanged(bool)),
              this, SLOT(updateWired()));
    else if ( key == "_ON_STATUS"  ||  key == "_ON_CMD")
      connect(fields[key], SIGNAL(connectionChanged(bool)),
              SLOT(updatePowerConnection(bool)));
    else
      connect(fields[key], SIGNAL(connectionChanged(bool)),
              SLOT(updateConnection(bool)));

}


QCaMotor::~QCaMotor() {
  setPv();
  foreach(QEpicsPv * mpv, fields)
    delete mpv;
}


bool QCaMotor::eventFilter(QObject *obj, QEvent *event) {
  if ( event->type() == QEvent::ApplicationActivate )
    preSetPv();
  return QObject::eventFilter(obj, event);
}



void QCaMotor::saveConfiguration(QTextStream & stream) const {

  if ( ! isConnected() )
    printError("Warning: saving configuration of the disconnected motor." );

  stream
      << "UREV " << getUnitsPerRev() << "\n"
      //<< "SREV " << getStepsPerRev() << "\n"
      //<< "MRES " << getMotorResolution() << "\n"
      // here I prefer the UREV pair over MRES
      // because UREV is the value constant for the stage,
      // while MRES depends on the type of motion.
      << "RRES " << getReadbackResolution() << "\n"
      << "ERES " << getEncoderResolution() << "\n"
      << "PREC " << getPrecision() << "\n"
      << "EGU " << getUnits() << "\n"
      << "DIR " << getDirection() << "\n"
      << "DLLM " << getDialLoLimit() << "\n"
      << "DHLM " << getDialHiLimit() << "\n"
      << "VMAX " << getMaximumSpeed() << "\n"
      << "VELO " << getNormalSpeed() << "\n"
      << "ACCL " << getAcceleration() << "\n"
      << "JVEL " << getJogSpeed() << "\n"
      << "JAR " << getJogAcceleration() << "\n"
      << "BVEL " << getBacklashSpeed() << "\n"
      << "BACC " << getBacklashAcceleration() << "\n"
      << "BDST " << getBacklash() << "\n";

}



void QCaMotor::saveConfiguration(const QString & fileName) const {
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    printError("Cannot open file \"" + fileName + "\" for writing.");
    return;
  }
  QTextStream out(&file);
  saveConfiguration(out);
}

void QCaMotor::loadConfiguration(QTextStream & stream) {
  if ( ! isConnected() ) {
    printError("Cannot load configuration of the motor because it is not connected.");
    return;
  }
  QString line = stream.readLine();
  while ( ! line.isEmpty() ) {
    int idx=line.indexOf(' ');
    if ( idx > 0 ) {
      QString fld = "." + line.left(idx) ;
      QString val = line.mid(idx+1);
      if ( ! fld.isEmpty()  &&  ! val.isEmpty()  &&  fields.contains(fld) )
        fields[fld]->set(val);
    }
    line = stream.readLine();
  }
}


void QCaMotor::loadConfiguration(const QString & fileName) {
  QFile file(fileName);
  if ( ! file.open(QIODevice::ReadOnly) ) {
    printError("Cannot open file \"" + fileName + "\" for reading.");
    return;
  }
  QTextStream in(&file);
  loadConfiguration(in);
}




void QCaMotor::preSetPv(){

  QVariant rtype = QEpicsPv::get(pv+".RTYP");
  if ( ! rtype.isValid() )
    emit error("Can't connect to the \"" + pv + "\" PV.");
  else if ( rtype.toString() != "motor")
    emit error("Unexpected record type \"" + rtype.toString() + "\""
               " of the \"" + pv + "\" PV.");

  foreach ( QString key, fields.keys() )
    fields[key]->setPV(pv+key);

  emit changedPv(pv);

}


void QCaMotor::setPv(const QString & pvName) {

  setObjectName(pvName);

  if (iAmConnected)
    emit changedConnected(iAmConnected=false);
  pv = pvName.trimmed();

  if (pv.isEmpty()) {
    emit changedPv(pv);
    foreach ( QString key, fields.keys() )
      fields[key]->setPV();
  } else if ( QCoreApplication::startingUp() )
    QCoreApplication::postEvent(this, new QEvent(QEvent::ApplicationActivate));
  else
    QTimer::singleShot(0, this, SLOT(preSetPv()));

}


void QCaMotor::updateDouble(const QVariant & data,
                            double & parameter, const QString & parameter_name,
                            void (QCaMotor::* changedDouble)(double) ) {
  bool er;
  double new_val = data.toDouble(&er);
  if (!er)
    emit error("Could not convert \"" + data.toString() + "\" to "
               + parameter_name + " (double).");
  emit (this->*changedDouble)(parameter = new_val);
}



void QCaMotor::updateConnection(bool suc){
  if (suc)
    foreach(QString key, fields.keys()) 
      if ( suc &&
           key != "_ON_STATUS" && key != "_ON_CMD" &&
           key != "_CONNECTED_STATUS" ) // Nonstandard fields
        suc &= fields[key]->isConnected(); 
  if (suc != iAmConnected) {
    emit changedConnected(iAmConnected = suc);
    // below want to set lastMotion to 0;
    qtWait(fields[".DMOV"], SIGNAL(valueUpdated(QVariant)), 200);
    qtWait(100); //needed to let the ::updateMoving() to deal with the lastMotion
    lastMotion = 0;
  }
}

void QCaMotor::updateDescription(const QVariant & data){
  emit changedDescription(description = data.toString());
}

void QCaMotor::updatePrecision(const QVariant & data){
  bool er;
  int new_precsision = data.toInt(&er);
  if (!er)
    emit error("Could not convert \"" + QString::number(new_precsision)
               + "\" to prescision (int).");
  emit changedPrecision(precsision = new_precsision);
}

void QCaMotor::updateUnits(const QVariant & data){
  emit changedUnits(units = data.toString());
}


void QCaMotor::updateUserPosition(const QVariant & data){
  updateDouble(data, userPosition, "user position", &QCaMotor::changedUserPosition);
}

void QCaMotor::updateDialPosition(const QVariant & data){
  updateDouble(data, dialPosition, "dial position", &QCaMotor::changedDialPosition);
}

void QCaMotor::updateRawPosition(const QVariant & data){
  // WARNING! BUG!
  // .toInt() in the nextline is needed because the data's type returned
  // is qlonglong, not int and therefore negative numbers are treated incorrectly
  // f.e. -100 turns to 4294967196
  updateDouble(data.toInt(), rawPosition, "raw position", &QCaMotor::changedRawPosition);
}

void QCaMotor::updateUserGoal(const QVariant & data){
  updateDouble(data, userGoal, "user goal", &QCaMotor::changedUserGoal);
}

void QCaMotor::updateDialGoal(const QVariant & data){
  updateDouble(data, dialGoal, "dial goal", &QCaMotor::changedDialGoal);
}

void QCaMotor::updateRawGoal(const QVariant & data){
  // WARNING! BUG!
  // .toInt() in the nextline is needed because the data's type returned
  // is qlonglong, not int and therefore negative numbers are treated incorrectly
  // f.e. -100 turns to 4294967196
  updateDouble(data.toInt(), rawGoal, "raw goal", &QCaMotor::changedRawGoal);
}

void QCaMotor::updateStep(const QVariant & data){
  updateDouble(data, step, "step", &QCaMotor::changedStep);
}

void QCaMotor::updateDeadBand(const QVariant & data){
  updateDouble(data, deadBand, "dead band", &QCaMotor::changedDeadBand);
}

void QCaMotor::updateHiLimitStatus(const QVariant & data){
  emit changedHiLimitStatus( hiLimitStatus = data.toBool() );
}

void QCaMotor::updateLoLimitStatus(const QVariant & data){
  emit changedLoLimitStatus( loLimitStatus = data.toBool() );
}

void QCaMotor::updateUserHiLimit(const QVariant & data){
  updateDouble(data, userHiLimit, "user hi limit",
               &QCaMotor::changedUserHiLimit);
}

void QCaMotor::updateUserLoLimit(const QVariant & data){
  updateDouble(data, userLoLimit, "user lo limit",
               &QCaMotor::changedUserLoLimit);
}

void QCaMotor::updateDialHiLimit(const QVariant & data){
  updateDouble(data, dialHiLimit, "dial hi limit",
               &QCaMotor::changedDialHiLimit);
}

void QCaMotor::updateDialLoLimit(const QVariant & data){
  updateDouble(data, dialLoLimit, "dial lo limit",
               &QCaMotor::changedDialLoLimit);
}


void QCaMotor::updateMotorResolution(const QVariant & data){
  updateDouble(data, motorResolution, "motor resolution",
               &QCaMotor::changedMotorResolution);

  /// BUG
  // Actually not a bug, but many users called it a bug:
  // When RDBD field is too high.
  double amres = qAbs( getMotorResolution() );
  double ardbd = qAbs( getDeadBand() );
  if ( amres > 0.0  &&  ardbd > amres * 2 )
      setDeadBand(amres*2);
}

void QCaMotor::updateReadbackResolution(const QVariant & data){
  updateDouble(data, readbackResolution, "readback resolution",
               &QCaMotor::changedReadbackResolution);
}

void QCaMotor::updateEncoderResolution(const QVariant & data){
  updateDouble(data, encoderResolution, "encoder resolution",
               &QCaMotor::changedEncoderResolution);
}

void QCaMotor::updateUnitsPerRev(const QVariant & data){
  updateDouble(data, unitsPerRev, "units per revolution",
               &QCaMotor::changedUnitsPerRev);
}

void QCaMotor::updateStepsPerRev(const QVariant & data){
  bool er;
  int new_val = data.toInt(&er);
  if (!er)
    emit error("Could not convert \"" + data.toString() +  "\" to "
               "steps per revolution (int).");
  if (new_val < 0)
    qDebug() << "Warning! New value of the steps per revolution (SREV) field is negative.";
  emit changedStepsPerRev( stepsPerRev = new_val );
}


void QCaMotor::updateMaximumSpeed(const QVariant & data){
  updateDouble(data, maximumSpeed, "maximum speed",
               &QCaMotor::changedMaximumSpeed);
}

void QCaMotor::updateNormalSpeed(const QVariant & data){
  updateDouble(data, normalSpeed, "normal speed",
               &QCaMotor::changedNormalSpeed);
}

void QCaMotor::updateRevSpeed(const QVariant & data){
  updateDouble(data, normalSpeed, "revolving speed",
               &QCaMotor::changedRevSpeed);
}

void QCaMotor::updateBacklashSpeed(const QVariant & data){
  updateDouble(data, backlashSpeed, "backlash speed",
               &QCaMotor::changedBacklashSpeed);
}

void QCaMotor::updateJogSpeed(const QVariant & data){
  updateDouble(data, jogSpeed, "jog speed",
               &QCaMotor::changedJogSpeed);
}


void QCaMotor::updateAcceleration(const QVariant & data){
  updateDouble(data, acceleration, "acceleration",
               &QCaMotor::changedAcceleration);
}

void QCaMotor::updateBacklashAcceleration(const QVariant & data){
  updateDouble(data, backlashAcceleration, "backlash acceleration",
               &QCaMotor::changedBacklashAcceleration);
}

void QCaMotor::updateJogAcceleration(const QVariant & data){
  updateDouble(data, jogAcceleration, "jog acceleration",
               &QCaMotor::changedJogAcceleration);
}


void QCaMotor::updateBacklash(const QVariant & data){
  updateDouble(data, backlash, "backlash", &QCaMotor::changedBacklash);
}


void QCaMotor::updateMoving(const QVariant & data) {

  bool newMov = ! data.toBool();

  if ( newMov == iAmMoving ) lastMotion = 0; // first update
  else if ( newMov )         lastMotion = getRawPosition();
  else                       lastMotion = getRawPosition() - lastMotion;

  iAmMoving = newMov;
  emit changedMoving(iAmMoving);
  if ( ! iAmMoving )
    emit stopped();
  else
    return; // to avoid bug check

  // detect the bug described at the motionAttempt declaration.
  qtWait(500); // to allow update of the raw goal and position
  if ( ! iAmMoving  &&  qAbs(getUserGoal()-getUserPosition()) > qMax( qAbs(getDeadBand()), qPow(-getPrecision(),10) ) ) {
    if (secondMotionAttempt) // it is second time when the bug manifests itself.
      qDebug() << "The undone motion bug happened twice. Something is wrong. Please report to the developers.";
    else
      goRawPosition(getRawGoal()); // do second attempt
    secondMotionAttempt = ! secondMotionAttempt;
  } else if ( ! iAmMoving ) // stopped without the bug
    secondMotionAttempt = false;

}

void QCaMotor::updateUseReadback(const QVariant & data){
  emit changedUseReadback( useReadback = data.toBool() );
}

void QCaMotor::updateUseEncoder(const QVariant & data) {
  emit changedUseEncoder( useEncoder = data.toBool() );
}

void QCaMotor::updateDirection(const QVariant & data) {
  emit changedDirection( direction = (Direction) data.toInt() );
}

void QCaMotor::updateOffsetMode(const QVariant & data){
  emit changedOffsetMode( offsetMode = (OffMode) data.toInt() );
}

void QCaMotor::updateOffset(const QVariant & data){
  updateDouble(data, offset, "offset", &QCaMotor::changedOffset);
}

void QCaMotor::updateSpmgMode(const QVariant & data){
  emit changedSpmgMode( spmgMode = (SpmgMode) data.toInt() );
}

void QCaMotor::updateSuMode(const QVariant & data){
  emit changedSuMode( suMode = (SuMode) data.toInt() );
}

void QCaMotor::updatePowerConnection(bool){
  powerIsConnected =
    fields["_ON_CMD"]->isConnected() && fields["_ON_STATUS"]->isConnected();
  if (!powerIsConnected)
    updatePower(true);
  emit changedPowerConnection(powerIsConnected);
}

void QCaMotor::updatePower(const QVariant & data){
  emit changedPower(iAmPowered = data.toBool());
}


void QCaMotor::updateWired(const QVariant & data) {
  emit changedWired( iaAmWired =
                    ! fields["_CONNECTED_STATUS"]->isConnected()  ||
                    data.toBool() );
}





void QCaMotor::setField(const QString & key, const QVariant & value, bool confirm) {
  if ( ! fields.contains(key) )
    emit error("Unknown field \"" + key + "\".");
  else if ( ! fields[key] )
    emit error("Attempt to operate on uninitialized field \"" + key + "\".");
  else if (confirm)
    fields[key]->set(value, 1.5 * QEpicsPv::expectedResponse);
  else
    fields[key]->set(value);
}


void QCaMotor::setDescription(const QString & desc){
  setField(".DESC", desc);
}

void QCaMotor::setPrecision(int prec){
  setField(".PREC", prec);
}

void QCaMotor::setUnits(const QString & units){
  setField(".EGU", units);
}


void QCaMotor::setUserPosition(double pos){
  SuMode restore_mode = ensureSuMode(SET);
  setField(".VAL", pos);
  if ( getSuMode() != restore_mode )
    setSuMode(restore_mode);
}

void QCaMotor::setDialPosition(double pos){
  SuMode restore_mode = ensureSuMode(SET);
  setField(".DVAL", pos);
  if ( getSuMode() != restore_mode )
    setSuMode(restore_mode);
}

void QCaMotor::setRawPosition(double pos){
  SuMode restore_mode = ensureSuMode(SET);
  setField(".RVAL", pos);
  if ( getSuMode() != restore_mode )
    setSuMode(restore_mode);
}

void QCaMotor::wait_stop(){
  QList<ObjSig> osS;
  osS
      << ObjSig(this, SIGNAL(stopped()))
      << ObjSig(this, SIGNAL(changedConnected(bool)))
      << ObjSig(this, SIGNAL(changedPv(QString)))
      << ObjSig(this, SIGNAL(destroyed()));
  if ( isConnected() && isMoving() )
    qtWait(osS);
}

void QCaMotor::wait_start() {
  QList<ObjSig> osS;
  osS
      << ObjSig(this, SIGNAL(changedMoving(bool)))
      << ObjSig(this, SIGNAL(changedConnected(bool)))
      << ObjSig(this, SIGNAL(changedPv(QString)))
      << ObjSig(this, SIGNAL(destroyed()));
  if ( isConnected() && ! isMoving() )
    qtWait(osS, QEpicsPv::expectedResponse*1.5);
}


void QCaMotor::waitUpdated ( const QString & field, int delay_msec) const {
  if ( ! fields.contains(field) )
    return;
  qtWait(fields[field], SIGNAL(valueUpdated(QVariant)), delay_msec);
}



QCaMotor::SuMode QCaMotor::ensureSuMode(SuMode mode) {
  SuMode store_mode = getSuMode();

  if (store_mode != mode) {

    setSuMode(mode);
    QTimer tmpt;
    tmpt.setInterval(500);
    tmpt.setSingleShot(true);
    tmpt.start();

    while ( getSuMode() != mode  &&  tmpt.isActive() )
      qtWait(this, SIGNAL(changedSuMode(QCaMotor::SuMode)), 100);
    if (getSuMode() != mode) {
      qDebug() << "ERROR! Could not set proper SU mode of the motor." << getPv();
      setSuMode(store_mode);
    }

  }

  return store_mode;

}


QCaMotor::SuMode QCaMotor::prepareMotion(MotionExit ex) {
  SuMode store_mode = ensureSuMode(USE);
  if ( ex > CONFIRMATION )
    fields[".DMOV"]->needUpdated();
  return store_mode;
}


void QCaMotor::finilizeMotion(MotionExit ex, SuMode restore_mode) {

  if ( ex > CONFIRMATION && ! isMoving() ) {
    if ( ! fields[".DMOV"]->getUpdated(200).isValid() )
      return; // did not start within specified time.
  }

  if ( ex == ACCELERATED )
    qtWait( getAcceleration() * 1000 );
  else if ( ex == STOPPED )
    while ( isMoving() )
      qtWait(this, SIGNAL(changedMoving(bool)));

  if ( getSuMode() != restore_mode )
    setSuMode(restore_mode);

}


void QCaMotor::goUserPosition(double pos, MotionExit ex) {

  double res = qAbs(getMotorResolution());
  if ( pos >= numeric_limits<int>::max() * res )
    pos = numeric_limits<int>::max() * res;
  else if ( pos <= numeric_limits<int>::min() * res )
    pos = numeric_limits<int>::min() * res;

  SuMode store_mode = prepareMotion(ex);
  setField(".VAL", pos, (bool) ex );
  finilizeMotion(ex, store_mode);
}

void QCaMotor::goDialPosition(double pos, MotionExit ex) {
  double res = qAbs(getMotorResolution());
  if ( pos >= numeric_limits<int>::max() * res )
    pos = numeric_limits<int>::max() * res;
  else if ( pos <= numeric_limits<int>::min() * res )
    pos = numeric_limits<int>::min() * res;

  SuMode store_mode = prepareMotion(ex);
  setField(".DVAL", pos, (bool) ex );
  finilizeMotion(ex, store_mode);

}

void QCaMotor::goRawPosition(double pos, MotionExit ex) {
  if ( pos >= numeric_limits<int>::max() )
    pos = numeric_limits<int>::max();
  else if ( pos <= numeric_limits<int>::min() )
    pos = numeric_limits<int>::min();

  SuMode store_mode = prepareMotion(ex);
  setField(".RVAL", pos, (bool) ex );
  finilizeMotion(ex, store_mode);

}

void QCaMotor::goLimit(int direction, MotionExit ex) {
  double goal = (direction < 1) ?
                getUserLoLimit() + 2 * qAbs(getBacklash()) :
                getUserHiLimit() - 2 * qAbs(getBacklash()) ;
  goUserPosition(goal, ex);
}

void QCaMotor::goStep(int direction, MotionExit ex) {
  SuMode store_mode = prepareMotion(ex);
  setField( ( direction > 0 ) ? ".TWF" : ".TWR", 1);
  finilizeMotion(ex, store_mode);
}

void QCaMotor::goHome(int direction, MotionExit ex) {
  SuMode store_mode = prepareMotion(ex);
  setField( ( direction > 0 ) ? ".HOMF" : ".HOMR", 1);
  finilizeMotion(ex, store_mode);
}

void QCaMotor::goRelative(double dist, MotionExit ex) {
  SuMode store_mode = prepareMotion(ex);
  setField(".RLV" , dist);
  finilizeMotion(ex, store_mode);
}

void QCaMotor::jog(bool jg, int direction) {
  SuMode store_mode = prepareMotion(IMMIDIATELY);
  setField( ( direction > 0 ) ? ".JOGF" : ".JOGR", jg ? 1 : 0 );
  finilizeMotion(IMMIDIATELY, store_mode);
}

void QCaMotor::undoLastMotion(MotionExit ex) {
  if ( getLastMotion() )
    goRawPosition( getRawPosition() - getLastMotion(), ex );
}

void QCaMotor::stop(MotionExit ex){
  setField(".STOP", 1, (bool) ex );
  if ( ex == STOPPED )
    wait_stop();
}


void QCaMotor::setStep(double step) {
  setField(".TWV", step);
}

void QCaMotor::setDeadBand(double rdbd) {
  setField(".RDBD", rdbd);
}

void QCaMotor::setOffset(double dist) {
  setField(".OFF", dist);
}

void QCaMotor::setOffsetMode(OffMode mode) {
  setField(".FOFF", mode);
}

void QCaMotor::setDirection(Direction direction) {
  setField(".DIR", direction);
}

void QCaMotor::setSuMode(SuMode mode) {
  setField(".SET", mode);
}


void QCaMotor::setUserHiLimit(double limit){
  setField(".HLM", limit);
}


void QCaMotor::setUserLoLimit(double limit){
  setField(".LLM", limit);
}

void QCaMotor::setDialHiLimit(double limit){
  setField(".DHLM", limit);
}

void QCaMotor::setDialLoLimit(double limit){
  setField(".DLLM", limit);
}


void QCaMotor::setMotorResolution(double res){
  setField(".MRES", res);
}

void QCaMotor::setReadbackResolution(double res){
  setField(".RRES", res);
}

void QCaMotor::setEncoderResolution(double res){
  setField(".ERES", res);
}

void QCaMotor::setUnitsPerRev(double units){
  setField(".UREV", units);
}

void QCaMotor::setStepsPerRev(int st) {
  if ( st <= 0 ) {
    qDebug() << "Error! Steps per revolution must be strictly positive. Ignoring request to set it to" << st << ".";
    emit changedStepsPerRev(getStepsPerRev());
    return;
  }
  setField(".SREV", (qlonglong) st);
}


void QCaMotor::setMaximumSpeed(double speed){
  setField(".VMAX", speed);
}

void QCaMotor::setNormalSpeed(double speed){
  setField(".VELO", speed);
}

void QCaMotor::setRevSpeed(double speed){
  setField(".S", speed);
}

void QCaMotor::setBacklashSpeed(double speed){
  setField(".BVEL", speed);
}

void QCaMotor::setJogSpeed(double speed){
  setField(".JVEL", speed);
}


void QCaMotor::setAcceleration(double acc){
  setField(".ACCL", acc);
}

void QCaMotor::setBacklashAcceleration(double acc){
  setField(".BACC", acc);
}

void QCaMotor::setJogAcceleration(double acc){
  setField(".JAR", acc);
}

void QCaMotor::setUseReadback(bool use){
  setField(".URIP", use);
}

void QCaMotor::setUseEncoder(bool use){
  setField(".UEIP", use);
}

void QCaMotor::setBacklash(double dist){
  setField(".BDST", dist);
}

void QCaMotor::setSpmgMode(SpmgMode mode){
  setField(".SPMG", mode);
}

void QCaMotor::setPower(bool pwr){
  if (powerIsConnected)
    setField("_ON_CMD", pwr);
}



