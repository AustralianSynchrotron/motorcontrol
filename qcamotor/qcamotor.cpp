#include "qcamotor.h"
#include <limits>

#include <QProcess>
#include <QTimer>
#include <QFile>


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

  connect(this, SIGNAL(error(QString)), this, SLOT(printError(QString)));

  motor.insert(".DESC", new QEpicsPv(this));
  connect(motor[".DESC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDescription(QVariant)));

  motor.insert(".PREC", new QEpicsPv(this));
  connect(motor[".PREC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updatePrecision(QVariant)));
  motor.insert(".EGU",  new QEpicsPv(this));
  connect(motor[".EGU"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUnits(QVariant)));

  motor.insert(".RBV",  new QEpicsPv(this));
  connect(motor[".RBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserPosition(QVariant)));
  motor.insert(".DRBV", new QEpicsPv(this));
  connect(motor[".DRBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialPosition(QVariant)));
  motor.insert(".RRBV", new QEpicsPv(this));
  connect(motor[".RRBV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRawPosition(QVariant)));
  motor.insert(".VAL",  new QEpicsPv(this));
  connect(motor[".VAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserGoal(QVariant)));
  motor.insert(".DVAL", new QEpicsPv(this));
  connect(motor[".DVAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialGoal(QVariant)));
  motor.insert(".RVAL", new QEpicsPv(this));
  connect(motor[".RVAL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRawGoal(QVariant)));
  motor.insert(".TWV",  new QEpicsPv(this));
  connect(motor[".TWV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateStep(QVariant)));

  motor.insert(".TWR",  new QEpicsPv(this));
  motor.insert(".TWF",  new QEpicsPv(this));
  motor.insert(".HOMR", new QEpicsPv(this));
  motor.insert(".HOMF", new QEpicsPv(this));
  motor.insert(".JOGR", new QEpicsPv(this));
  motor.insert(".JOGF", new QEpicsPv(this));
  motor.insert(".RLV",  new QEpicsPv(this));
  motor.insert(".STOP", new QEpicsPv(this));

  motor.insert(".HLS",  new QEpicsPv(this));
  connect(motor[".HLS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateHiLimitStatus(QVariant)));
  motor.insert(".LLS",  new QEpicsPv(this));
  connect(motor[".LLS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateLoLimitStatus(QVariant)));
  motor.insert(".HLM",  new QEpicsPv(this));
  connect(motor[".HLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserHiLimit(QVariant)));
  motor.insert(".LLM",  new QEpicsPv(this));
  connect(motor[".LLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUserLoLimit(QVariant)));
  motor.insert(".DHLM", new QEpicsPv(this));
  connect(motor[".DHLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialHiLimit(QVariant)));
  motor.insert(".DLLM", new QEpicsPv(this));
  connect(motor[".DLLM"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDialLoLimit(QVariant)));

  motor.insert(".MRES", new QEpicsPv(this));
  connect(motor[".MRES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMotorResolution(QVariant)));
  motor.insert(".RRES", new QEpicsPv(this));
  connect(motor[".RRES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateReadbackResolution(QVariant)));
  motor.insert(".ERES", new QEpicsPv(this));
  connect(motor[".ERES"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateEncoderResolution(QVariant)));
  motor.insert(".UREV", new QEpicsPv(this));
  connect(motor[".UREV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUnitsPerRev(QVariant)));
  motor.insert(".SREV", new QEpicsPv(this));
  connect(motor[".SREV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateStepsPerRev(QVariant)));

  motor.insert(".VMAX", new QEpicsPv(this));
  connect(motor[".VMAX"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMaximumSpeed(QVariant)));
  motor.insert(".VELO", new QEpicsPv(this));
  connect(motor[".VELO"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateNormalSpeed(QVariant)));
  motor.insert(".S", new QEpicsPv(this));
  connect(motor[".S"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateRevSpeed(QVariant)));
  motor.insert(".BVEL", new QEpicsPv(this));
  connect(motor[".BVEL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklashSpeed(QVariant)));
  motor.insert(".JVEL", new QEpicsPv(this));
  connect(motor[".JVEL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateJogSpeed(QVariant)));

  motor.insert(".ACCL", new QEpicsPv(this));
  connect(motor[".ACCL"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateAcceleration(QVariant)));
  motor.insert(".BACC", new QEpicsPv(this));
  connect(motor[".BACC"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklashAcceleration(QVariant)));
  motor.insert(".JAR",  new QEpicsPv(this));
  connect(motor[".JAR"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateJogAcceleration(QVariant)));

  motor.insert(".BDST", new QEpicsPv(this));
  connect(motor[".BDST"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateBacklash(QVariant)));

  motor.insert(".DMOV", new QEpicsPv(this));
  connect(motor[".DMOV"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateMoving(QVariant)));
  motor.insert(".UEIP", new QEpicsPv(this));
  connect(motor[".UEIP"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUseEncoder(QVariant)));
  motor.insert(".URIP", new QEpicsPv(this));
  connect(motor[".URIP"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateUseReadback(QVariant)));

  motor.insert(".OFF",  new QEpicsPv(this));
  connect(motor[".OFF"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateOffset(QVariant)));
  motor.insert(".FOFF", new QEpicsPv(this));
  connect(motor[".FOFF"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateOffsetMode(QVariant)));
  motor.insert(".DIR",  new QEpicsPv(this));
  connect(motor[".DIR"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateDirection(QVariant)));
  motor.insert(".SET",  new QEpicsPv(this));
  connect(motor[".SET"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateSuMode(QVariant)));
  motor.insert(".SPMG", new QEpicsPv(this));
  connect(motor[".SPMG"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateSpmgMode(QVariant)));
  motor.insert("_ON_STATUS", new QEpicsPv(this));
  connect(motor["_ON_STATUS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updatePower(QVariant)));
  motor.insert("_ON_CMD",    new QEpicsPv(this));
  motor.insert("_CONNECTED_STATUS", new QEpicsPv(this));
  connect(motor["_CONNECTED_STATUS"], SIGNAL(valueUpdated(QVariant)),
          this, SLOT(updateWired(QVariant)));


  foreach ( QString key, motor.keys() )
    if ( key == "_CONNECTED_STATUS" )
      connect(motor[key], SIGNAL(valueInited(QVariant)),
              this, SLOT(updateWired()));
    else if ( key == "_ON_STATUS"  ||  key == "_ON_CMD")
      connect(motor[key], SIGNAL(connectionChanged(bool)),
              SLOT(updatePowerConnection(bool)));
    else
      connect(motor[key], SIGNAL(valueInited(QVariant)),
              SLOT(updateConnection()));

}


QCaMotor::~QCaMotor() {
  setPv();
  foreach(QEpicsPv * mpv, motor)
    delete mpv;
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
      if ( ! fld.isEmpty()  &&  ! val.isEmpty()  &&  motor.contains(fld) )
        motor[fld]->set(val);
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
  if ( ! rtype.isValid() ) {
    emit error("Can't connect to the \"" + pv + "\" PV.");
  } else if ( rtype.toString() != "motor") {
    setPv();
    emit error("Unexpected record type \"" + rtype.toString() + "\""
               " of the \"" + pv + "\" PV.");
    return;
  }

  foreach ( QString key, motor.keys() )
    motor[key]->setPV(pv+key);

}


void QCaMotor::setPv(const QString & pvName) {

  if (iAmConnected)
    emit changedConnected(iAmConnected=false);
  pv = pvName.trimmed();

  emit changedPv(pv);

  if (pv.isEmpty())
    foreach ( QString key, motor.keys() )
      motor[key]->setPV();
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



void QCaMotor::updateConnection(){
  bool suc = true;
  foreach(QString key, motor.keys())
    if ( suc &&
         key != "_ON_STATUS" && key != "_ON_CMD" &&
         key != "_CONNECTED_STATUS" ) // Nonstandard fields
      suc &= motor[key]->isReady();
  if (suc != iAmConnected)
    emit changedConnected(iAmConnected = suc);
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


void QCaMotor::updateHiLimitStatus(const QVariant & data){
  emit changedHiLimitStatus( hiLimitStatus = data.toBool() );
}

void QCaMotor::updateLoLimitStatus(const QVariant & data){
  emit changedHiLimitStatus( loLimitStatus = data.toBool() );
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
  double ardbd = qAbs( QEpicsPv::get(getPv()+".RDBD").toDouble() );
  if ( amres > 0.0  &&  ardbd > amres * 2 )
    QEpicsPv::set(getPv()+".RDBD", amres*2, 200);
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

  // detect the bug described at the motionAttempt declaration.
  if ( ! iAmMoving  &&  qAbs( getRawGoal() - getRawPosition() ) >=2  &&
       ! getLoLimitStatus()  &&  ! getHiLimitStatus()  &&
       getSpmgMode() != PAUSE  &&  getSpmgMode() != STOP  &&
       getUserGoal() >= getUserLoLimit()  &&  getUserGoal() <= getUserHiLimit() )  {

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
    motor["_ON_CMD"]->isConnected() && motor["_ON_STATUS"]->isConnected();
  if (!powerIsConnected)
    updatePower(true);
  emit changedPowerConnection(powerIsConnected);
}

void QCaMotor::updatePower(const QVariant & data){
  emit changedPower(iAmPowered = data.toBool());
}


void QCaMotor::updateWired(const QVariant & data) {
  emit changedWired( iaAmWired =
                    ! motor["_CONNECTED_STATUS"]->isConnected()  ||
                    data.toBool() );
}





void QCaMotor::setField(const QString & key, const QVariant & value){
  if ( ! motor.contains(key) )
    emit error("Unknown field \"" + key + "\".");
  else if ( ! motor[key] || ! motor[key]->isConnected() )
    emit error("Attempt to operate on field \"" + key + "\""
               " of uninitialized or disconnected motor: set PV first.");
  else
    motor[key]->set(value, 100);
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
  SuMode mode = getSuMode();
  setSuMode(SET);
  setField(".VAL", pos);
  setSuMode(mode);
}

void QCaMotor::setDialPosition(double pos){
  SuMode mode = getSuMode();
  setSuMode(SET);
  setField(".DVAL", pos);
  setSuMode(mode);
}

void QCaMotor::setRawPosition(double pos){
  SuMode mode = getSuMode();
  setSuMode(SET);
  setField(".RVAL", pos);
  setSuMode(mode);
}

void QCaMotor::wait_stop(){
  QEventLoop q;
  connect(this, SIGNAL(stopped()), &q, SLOT(quit()));
  connect(this, SIGNAL(changedConnected(bool)), &q, SLOT(quit()));
  connect(this, SIGNAL(changedPv(QString)), &q, SLOT(quit()));
  connect(this, SIGNAL(destroyed()), &q, SLOT(quit()));
  if ( isConnected() && isMoving() )
    q.exec();
}


void QCaMotor::goUserPosition(double pos, bool wait){
  double res = qAbs(getMotorResolution());
  if ( pos >= numeric_limits<int>::max() * res )
    pos = numeric_limits<int>::max() * res;
  else if ( pos <= numeric_limits<int>::min() * res )
    pos = numeric_limits<int>::min() * res;
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField(".VAL", pos);
  if (wait)
    wait_stop();
  setSuMode(mode);
}

void QCaMotor::goDialPosition(double pos, bool wait){
  double res = qAbs(getMotorResolution());
  if ( pos >= numeric_limits<int>::max() * res )
    pos = numeric_limits<int>::max() * res;
  else if ( pos <= numeric_limits<int>::min() * res )
    pos = numeric_limits<int>::min() * res;
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField(".DVAL", pos);
  if (wait)
    wait_stop();
  setSuMode(mode);
}

void QCaMotor::goRawPosition(double pos, bool wait){
  if ( pos >= numeric_limits<int>::max() )
    pos = numeric_limits<int>::max();
  else if ( pos <= numeric_limits<int>::min() )
    pos = numeric_limits<int>::min();
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField(".RVAL", pos);
  if (wait)
    wait_stop();
  setSuMode(mode);
}

void QCaMotor::goLimit(int direction, bool wait){
  jog(true, direction);
  if (wait)
    wait_stop();
}

void QCaMotor::goStep(int direction, bool wait){
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField( ( direction > 0 ) ? ".TWF" : ".TWR", 1);
  if (wait)
    wait_stop();
  setSuMode(mode);
}

void QCaMotor::goRelative(double dist, bool wait){
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField(".RLV" , dist);
  if (wait)
    wait_stop();
  setSuMode(mode);
}

void QCaMotor::jog(bool jg, int direction){
  SuMode mode = getSuMode();
  setSuMode(USE);
  setField( ( direction > 0 ) ? ".JOGF" : ".JOGR", jg ? 1 : 0 );
  setSuMode(mode);
}

void QCaMotor::undoLastMotion(bool wait) {
  if (getLastMotion())
    goRawPosition( getRawPosition() - getLastMotion(), wait );
}

void QCaMotor::setStep(double step){
  setField(".TWV", step);
}

void QCaMotor::setOffset(double dist){
  setField(".OFF", dist);
}

void QCaMotor::setOffsetMode(OffMode mode){
  setField(".FOFF", mode);
}

void QCaMotor::setDirection(Direction direction){
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


void QCaMotor::stop(bool wait){
  setField(".STOP", 1);
  if (wait)
    wait_stop();
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



