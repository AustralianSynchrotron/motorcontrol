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
    out(),
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
    retry(0),
    iAmConnected(false),
    iAmMoving(false), // false is crusial here to distinguish first and further updates in ::updateMoving()
    useEncoder(false),
    useReadback(false),
    backlash(0),
    homeRef(NOHOM),
    status(false),
    driveCurrent(0),
    holdPerCent(0),
    lastMotion(0),
    lastPreHom(0)
{
    init();
}


QCaMotor::QCaMotor(const QString & _pv, QObject *parent) :
    QObject(parent),
    pv(),
    out(),
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
    retry(0),
    iAmConnected(false),
    iAmMoving(false), // false is crusial here to distinguish first and further updates in ::updateMoving()
    useEncoder(false),
    useReadback(false),
    backlash(0),
    homeRef(NOHOM),
    status(false),
    driveCurrent(0),
    holdPerCent(0),
    lastMotion(0),
    lastPreHom(0)
{
    init();
    setPv(_pv);
}


void QCaMotor::init() {

    installEventFilter(this);

    connect(this, SIGNAL(error(QString)), this, SLOT(printError(QString)));

    // write only fields
    fields.insert(".TWR", new QEpicsPv(this));
    fields.insert(".TWF", new QEpicsPv(this));
    fields.insert(".JOGR", new QEpicsPv(this));
    fields.insert(".JOGF", new QEpicsPv(this));
    fields.insert(".RLV", new QEpicsPv(this));
    fields.insert(".STOP", new QEpicsPv(this));
    // non-standard fields
    fields.insert(":ABORT_HOME", new QEpicsPv(this));
    fields.insert(":KILL", new QEpicsPv(this));
    fields.insert(":AMPFAULTRESET.PROC", new QEpicsPv(this));
    fields.insert(":ELOSSRC.A", new QEpicsPv(this));
    fields.insert(":WRONGLIMITRESET.PROC", new QEpicsPv(this));
    fields.insert(":INIT.PROC", new QEpicsPv(this));
    fields.insert(":HOLDPERCENTAGE", new QEpicsPv(this));
    fields.insert(":DRIVECURRENT", new QEpicsPv(this));


    // read/write fields
#define insField(FLD, SLT) \
    fields.insert(FLD, new QEpicsPv(this)); \
    connect(fields[FLD], SIGNAL(valueUpdated(QVariant)), SLOT(update ## SLT(QVariant)));

    insField(".OUT" , Out                  );
    insField(".DESC", Description          );
    insField(".PREC", Precision            );
    insField(".EGU" , Units                );
    insField(".RBV" , UserPosition         );
    insField(".DRBV", DialPosition         );
    insField(".RRBV", RawPosition          );
    insField(".VAL" , UserGoal             );
    insField(".DVAL", DialGoal             );
    insField(".RVAL", RawGoal              );
    insField(".TWV" , Step                 );
    insField(".RDBD", DeadBand             );
    insField(".HOMR", Homing               );
    insField(".HOMF", Homing               );
    insField(".HLS" , HiLimitStatus        );
    insField(".LLS" , LoLimitStatus        );
    insField(".HLM" , UserHiLimit          );
    insField(".LLM" , UserLoLimit          );
    insField(".DHLM", DialHiLimit          );
    insField(".DLLM", DialLoLimit          );
    insField(".MRES", MotorResolution      );
    insField(".RRES", ReadbackResolution   );
    insField(".ERES", EncoderResolution    );
    insField(".UREV", UnitsPerRev          );
    insField(".SREV", StepsPerRev          );
    insField(".VMAX", MaximumSpeed         );
    insField(".VELO", NormalSpeed          );
    insField(".S"   , RevSpeed             );
    insField(".BVEL", BacklashSpeed        );
    insField(".JVEL", JogSpeed             );
    insField(".ACCL", Acceleration         );
    insField(".BACC", BacklashAcceleration );
    insField(".JAR" , JogAcceleration      );
    insField(".RTRY", MaxRetry             );
    insField(".BDST", Backlash             );
    insField(".DMOV", Moving               );
    insField(".UEIP", UseEncoder           );
    insField(".URIP", UseReadback          );
    insField(".OFF" , Offset               );
    insField(".FOFF", OffsetMode           );
    insField(".DIR" , Direction            );
    insField(".SET" , SuMode               );
    insField(".SPMG", SpmgMode             );
    insField(".MSTA", MSTA                 );
    // non-standard fields
    insField(":STATUS", Status      );
    insField(":KILLED", Killed      );
    insField(":AMPFAULT", AmpFault    );
    insField(":UNINIT", Initialized );
    insField(":WRONGLIMIT", WrongLimits );
    insField(":ELOSS", EncoderLoss );
    insField(":HOME_FLAG_USER.SVAL", HomeRef     );
    insField(":HOLDPERCENTAGE_RBV", HoldPerCent );
    insField(":DRIVECURRENT_RBV", DriveCurrent);

#undef insField

    foreach ( QString key, fields.keys() )
        if ( key.at(0) == '.' )
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



void QCaMotor::saveConfiguration(QTextStream & stream, bool params) const {

  if ( ! isConnected() ) {
    printError("Warning: not saving configuration of the disconnected motor." );
    return;
  }

  stream << "# MOTORPV " << getPv() << "\n";
  stream << "#         " << getDescription() << "\n";
  stream << "caput " << getPv() << " " << getUserGoal() << "\n";
  if (isConnected() && params)
    foreach(QString fld, QStringList()
      << ".OUT"
      << ".DESC"
      << ".PREC"
      << ".EGU"
      << ".MRES"
      << ".RRES"
      << ".ERES"
      << ".UREV"
      << ".SREV"
      << ".DIR"
      << ".OFF"
      << ".LLM"
      << ".HLM"
      << ".VMAX"
      << ".VELO"
      << ".ACCL"
      << ".JVEL"
      << ".JAR"
      << ".BVEL"
      << ".BACC"
      << ".BDST"
      << ":HOLDPERCENTAGE"
      << ":DRIVECURRENT"
    ) stream << "echo caput " << getPv() << fld << " " << fields[fld]->get().toString() << "\n";


}



void QCaMotor::saveConfiguration(const QString & fileName, bool params) const {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        printError("Cannot open file \"" + fileName + "\" for writing.");
        return;
    }
    QTextStream out(&file);
    saveConfiguration(out, params);
}

void QCaMotor::loadConfiguration(QTextStream & stream, bool restore) {
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


void QCaMotor::loadConfiguration(const QString & fileName, bool restore) {
    QFile file(fileName);
    if ( ! file.open(QIODevice::ReadOnly) ) {
        printError("Cannot open file \"" + fileName + "\" for reading.");
        return;
    }
    QTextStream in(&file);
    loadConfiguration(in, restore);
}



void QCaMotor::preSetPv() {
    QVariant rtype = QEpicsPv::get(pv+".RTYP");
    foreach ( QString key, fields.keys() )
        fields[key]->setPV();
    if ( ! rtype.isValid() )
        emit error("Can't connect to the " + pv + " PV.");
    else if ( rtype.toString() != "motor")
        emit error("Unexpected record type " + rtype.toString() + " of the " + pv + " PV.");
    else
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



void QCaMotor::updateConnection(bool suc) {
    if (suc)
        foreach(QString key, fields.keys())
            suc &= ( key.at(0) != '.' ) || fields[key]->isConnected();
    if (suc != iAmConnected) {
        emit changedConnected(iAmConnected = suc);
        // below want to set lastMotion to 0;
        qtWait(fields[".DMOV"], SIGNAL(valueUpdated(QVariant)), 200);
        qtWait(100); //needed to let the ::updateMoving() to deal with the lastMotion
        lastMotion = 0;
    }
}

void QCaMotor::updateOut(const QVariant & data) {
  emit changedOut(out = data.toString());
}


void QCaMotor::updateDescription(const QVariant & data) {
  emit changedDescription(description = data.toString());
}

void QCaMotor::updatePrecision(const QVariant & data) {
  updateNum(data, precsision, "prescision", &QCaMotor::changedPrecision);
}

void QCaMotor::updateUnits(const QVariant & data) {
  emit changedUnits(units = data.toString());
}


void QCaMotor::updateUserPosition(const QVariant & data) {
    updateNum(data, userPosition, "user position", &QCaMotor::changedUserPosition);
}

void QCaMotor::updateDialPosition(const QVariant & data) {
    updateNum(data, dialPosition, "dial position", &QCaMotor::changedDialPosition);
}

void QCaMotor::updateRawPosition(const QVariant & data) {
    // WARNING! BUG!
    // .toInt() in the nextline is needed because the data's type returned
    // is qlonglong, not int and therefore negative numbers are treated incorrectly
    // f.e. -100 turns to 4294967196
    updateNum(data.toInt(), rawPosition, "raw position", &QCaMotor::changedRawPosition);
    if ( isHoming() && getRawPosition() != 0.0 )
        lastPreHom = getRawPosition();
}

void QCaMotor::updateUserGoal(const QVariant & data) {
    updateNum(data, userGoal, "user goal", &QCaMotor::changedUserGoal);
}

void QCaMotor::updateDialGoal(const QVariant & data) {
    updateNum(data, dialGoal, "dial goal", &QCaMotor::changedDialGoal);
}

void QCaMotor::updateRawGoal(const QVariant & data) {
    // WARNING! BUG!
    // .toInt() in the nextline is needed because the data's type returned
    // is qlonglong, not int and therefore negative numbers are treated incorrectly
    // f.e. -100 turns to 4294967196
    updateNum(data.toInt(), rawGoal, "raw goal", &QCaMotor::changedRawGoal);
}

void QCaMotor::updateStep(const QVariant & data) {
    updateNum(data, step, "step", &QCaMotor::changedStep);
}

void QCaMotor::updateDeadBand(const QVariant & data) {
    updateNum(data, deadBand, "dead band", &QCaMotor::changedDeadBand);
}

void QCaMotor::updateHiLimitStatus(const QVariant & data) {
    emit changedHiLimitStatus( hiLimitStatus = data.toBool() );
}

void QCaMotor::updateLoLimitStatus(const QVariant & data) {
    emit changedLoLimitStatus( loLimitStatus = data.toBool() );
}

void QCaMotor::updateUserHiLimit(const QVariant & data) {
    updateNum(data, userHiLimit, "user hi limit",
                 &QCaMotor::changedUserHiLimit);
}

void QCaMotor::updateUserLoLimit(const QVariant & data) {
    updateNum(data, userLoLimit, "user lo limit",
                 &QCaMotor::changedUserLoLimit);
}

void QCaMotor::updateDialHiLimit(const QVariant & data) {
    updateNum(data, dialHiLimit, "dial hi limit",
                 &QCaMotor::changedDialHiLimit);
}

void QCaMotor::updateDialLoLimit(const QVariant & data) {
    updateNum(data, dialLoLimit, "dial lo limit",
                 &QCaMotor::changedDialLoLimit);
}


void QCaMotor::updateMotorResolution(const QVariant & data) {
    updateNum(data, motorResolution, "motor resolution",
                 &QCaMotor::changedMotorResolution);

    /// BUG
    // Actually not a bug, but many users called it a bug:
    // When RDBD field is too high.
    double amres = qAbs( getMotorResolution() );
    double ardbd = qAbs( getDeadBand() );
    if ( amres > 0.0  &&  ardbd > amres * 2 )
        setDeadBand(amres*2);
}

void QCaMotor::updateReadbackResolution(const QVariant & data) {
    updateNum(data, readbackResolution, "readback resolution",
                 &QCaMotor::changedReadbackResolution);
}

void QCaMotor::updateEncoderResolution(const QVariant & data) {
    updateNum(data, encoderResolution, "encoder resolution",
                 &QCaMotor::changedEncoderResolution);
}

void QCaMotor::updateUnitsPerRev(const QVariant & data) {
    updateNum(data, unitsPerRev, "units per revolution",
                 &QCaMotor::changedUnitsPerRev);
}

void QCaMotor::updateStepsPerRev(const QVariant & data) {
  updateNum(data, stepsPerRev, "steps per revolution",
            &QCaMotor::changedStepsPerRev);
  if (stepsPerRev < 0)
    qDebug() << "Warning! New value of the steps per revolution (SREV) field is negative.";
}


void QCaMotor::updateMaximumSpeed(const QVariant & data) {
    updateNum(data, maximumSpeed, "maximum speed",
                 &QCaMotor::changedMaximumSpeed);
}

void QCaMotor::updateNormalSpeed(const QVariant & data) {
    updateNum(data, normalSpeed, "normal speed",
                 &QCaMotor::changedNormalSpeed);
}

void QCaMotor::updateRevSpeed(const QVariant & data) {
    updateNum(data, normalSpeed, "revolving speed",
                 &QCaMotor::changedRevSpeed);
}

void QCaMotor::updateBacklashSpeed(const QVariant & data) {
    updateNum(data, backlashSpeed, "backlash speed",
                 &QCaMotor::changedBacklashSpeed);
}

void QCaMotor::updateJogSpeed(const QVariant & data) {
    updateNum(data, jogSpeed, "jog speed",
                 &QCaMotor::changedJogSpeed);
}


void QCaMotor::updateAcceleration(const QVariant & data) {
    updateNum(data, acceleration, "acceleration",
                 &QCaMotor::changedAcceleration);
}

void QCaMotor::updateBacklashAcceleration(const QVariant & data) {
    updateNum(data, backlashAcceleration, "backlash acceleration",
                 &QCaMotor::changedBacklashAcceleration);
}

void QCaMotor::updateJogAcceleration(const QVariant & data) {
    updateNum(data, jogAcceleration, "jog acceleration",
                 &QCaMotor::changedJogAcceleration);
}

void QCaMotor::updateMaxRetry(const QVariant & data) {
  updateNum(data, retry, "max retry",
                 &QCaMotor::changedMaxRetry);
}

void QCaMotor::updateBacklash(const QVariant & data) {
    updateNum(data, backlash, "backlash", &QCaMotor::changedBacklash);
}


void QCaMotor::updateMoving(const QVariant & data) {

    const bool newMov = ! data.toBool();
    const bool firstUpdate = newMov == iAmMoving;

    if ( firstUpdate ) lastMotion = 0;
    else if ( newMov ) lastMotion = getRawPosition();
    else               lastMotion = getRawPosition() - lastMotion;

    iAmMoving = newMov;
    emit changedMoving(iAmMoving);
    if ( ! iAmMoving )
        emit stopped();
    else
        return; // to avoid bug check

    if (firstUpdate)
        return;

    // detect the bug described at the motionAttempt declaration.
    qtWait(100); // to allow update of the goal and position
    if ( ! iAmMoving  &&  qAbs(getUserGoal()-getUserPosition()) > qMax( qAbs(getDeadBand()), qPow(-getPrecision(),10) ) ) {
        if (secondMotionAttempt) // it is second time when the bug manifests itself.
            qDebug() << "The undone motion bug happened twice. Something is wrong. Please report to the developers.";
        else
            goRawPosition(getRawGoal()); // do second attempt
        secondMotionAttempt = ! secondMotionAttempt;
    } else // stopped without the bug
        secondMotionAttempt = false;

}

void QCaMotor::updateUseReadback(const QVariant & data) {
    emit changedUseReadback( useReadback = data.toBool() );
}

void QCaMotor::updateUseEncoder(const QVariant & data) {
    emit changedUseEncoder( useEncoder = data.toBool() );
}

void QCaMotor::updateDirection(const QVariant & data) {
    emit changedDirection( direction = (Direction) data.toInt() );
}

void QCaMotor::updateOffsetMode(const QVariant & data) {
    emit changedOffsetMode( offsetMode = (OffMode) data.toInt() );
}

void QCaMotor::updateOffset(const QVariant & data) {
    updateNum(data, offset, "offset", &QCaMotor::changedOffset);
}

void QCaMotor::updateSpmgMode(const QVariant & data) {
    emit changedSpmgMode( spmgMode = (SpmgMode) data.toInt() );
}

void QCaMotor::updateMSTA(const QVariant & data) {
    msta = data.toULongLong();
    emit changedSlipStall(isSplitStall());
    emit changedProblems(hasProblems());
    emit changedCommErr(commError());
}

void QCaMotor::updateKilled(const QVariant & data) {
    emit changedKilled( iAmKilled = data.toBool() );
}

void QCaMotor::updateAmpFault(const QVariant & data) {
    emit changedAmplifierFault( ampIsFaulty = data.toBool() );
}

void QCaMotor::updateInitialized(const QVariant & data) {
    emit changedInitialized( iAmInitialized = ! data.toBool() );
}

void QCaMotor::updateWrongLimits(const QVariant & data) {
    emit changedWrongLimits( wrongLimits = data.toBool() );
}

void QCaMotor::updateEncoderLoss(const QVariant & data) {
    emit changedEncoderLoss( eLoss = data.toBool() );
}

void QCaMotor::updateStatus(const QVariant & data) {
    emit changedStatus( status = data.toInt() < 2); // no problems
}



void QCaMotor::updateHomeRef(const QVariant & data) {
    const QString dataStr = data.toString();
    HomeReference hr;
    if      (dataStr.contains("Positive")) hr = POSLS;
    else if (dataStr.contains("Negative")) hr = NEGLS;
    else if (dataStr.contains("Home")    ) hr = HOMLS;
    else                                   hr = NOHOM;
    emit changedHomeRef(homeRef = hr);
}

void QCaMotor::updateHoming(const QVariant &) {
  emit changedHoming( iAmHoming =
    fields[".HOMF"]->get().toBool() || fields[".HOMR"]->get().toBool() );
}

void QCaMotor::updateSuMode(const QVariant & data) {
    emit changedSuMode( suMode = (SuMode) data.toInt() );
}

void QCaMotor::updateDriveCurrent(const QVariant & data) {
    updateNum(data, driveCurrent, "drive current", &QCaMotor::changedDriveCurrent);
}

void QCaMotor::updateHoldPerCent(const QVariant & data) {
    updateNum(data, holdPerCent, "holding percantage", &QCaMotor::changedHoldPerCent);
}






void QCaMotor::setField(const QString & key, const QVariant & value, bool confirm) {
    if ( ! fields.contains(key) )
        emit error("Unknown field \"" + key + "\".");
    else if ( ! fields[key] )
        emit error("Attempt to operate on uninitialized field \"" + key + "\".");
    else if (confirm)
        fields[key]->set(value, 2 * QEpicsPv::expectedResponse);
    else
        fields[key]->set(value);
}


void QCaMotor::setDescription(const QString & desc) {
    setField(".DESC", desc);
}

void QCaMotor::setPrecision(int prec) {
    setField(".PREC", prec);
}

void QCaMotor::setUnits(const QString & units) {
    setField(".EGU", units);
}


void QCaMotor::setUserPosition(double pos) {
    SuMode restore_mode = ensureSuMode(SET);
    setField(".VAL", pos);
    if ( getSuMode() != restore_mode )
        setSuMode(restore_mode);
}

void QCaMotor::setDialPosition(double pos) {
    SuMode restore_mode = ensureSuMode(SET);
    setField(".DVAL", pos);
    if ( getSuMode() != restore_mode )
        setSuMode(restore_mode);
}

void QCaMotor::setRawPosition(double pos) {
    SuMode restore_mode = ensureSuMode(SET);
    setField(".RVAL", pos);
    if ( getSuMode() != restore_mode )
        setSuMode(restore_mode);
}

void QCaMotor::wait_stop() {
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
            qtWait(this, SIGNAL(changedMoving(bool)), 1000);

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

void QCaMotor::goLimit(Direction direction, MotionExit ex) {
    double goal = (direction == POSITIVE) ?
                  getUserHiLimit() - 2 * qAbs(getBacklash()) :
                  getUserLoLimit() + 2 * qAbs(getBacklash()) ;
    goUserPosition(goal, ex);
}

void QCaMotor::goStep(Direction direction, MotionExit ex) {
    SuMode store_mode = prepareMotion(ex);
    setField( ( direction == POSITIVE ) ? ".TWF" : ".TWR", 1);
    finilizeMotion(ex, store_mode);
}

void QCaMotor::goHome(Direction direction, MotionExit ex) {
    SuMode store_mode = prepareMotion(ex);
    setField( ( direction == POSITIVE ) ? ".HOMF" : ".HOMR", 1);
    finilizeMotion(ex, store_mode);
}

void QCaMotor::goHome(MotionExit ex) {
    switch (getHomeRef()) {
    case NEGLS:
    case HOMLS:
        goHome(POSITIVE, ex);
        break;
    case POSLS:
        goHome(NEGATIVE, ex);
        break;
    default:
        emit error("Auto homing cannot be complete due to unknown home reference.");
    }
}

void QCaMotor::executeHomeRoutine(bool synch) {

    if (!synch) {
        QTimer::singleShot(0, this, SLOT(executeHomeRoutine()));
        return;
    }

    if ( ! isConnected() || isMoving() )
        return;
    const HomeReference hr = getHomeRef();
    if ( ! hr ) {
        emit error("Homing routine cannot be complete due to unknown home reference.");
        return;
    }

    const double orig = getRawPosition();

    if (hr == POSLS)
        goLimit(POSITIVE, STOPPED);
    else if (hr == NEGLS)
        goLimit(NEGATIVE, STOPPED);
    goHome(STOPPED);

    if (getRawPosition() == 0.0)
        goRawPosition(orig - lastPreHom, STOPPED);
    else
        emit error("Homing routine has failed.");

}

void QCaMotor::goRelative(double dist, MotionExit ex) {
    SuMode store_mode = prepareMotion(ex);
    setField(".RLV", dist);
    finilizeMotion(ex, store_mode);
}

void QCaMotor::jog(bool jg, Direction direction) {
    SuMode store_mode = prepareMotion(IMMIDIATELY);
    setField( ( direction == POSITIVE ) ? ".JOGF" : ".JOGR", jg ? 1 : 0 );
    finilizeMotion(IMMIDIATELY, store_mode);
}

void QCaMotor::undoLastMotion(MotionExit ex) {
    if ( getLastMotion() != 0.0 )
        goRawPosition( getRawPosition() - getLastMotion(), ex );
}

void QCaMotor::stop(MotionExit ex) {
    if (fields[":ABORT_HOME"]->isConnected())
        setField(":ABORT_HOME", 1);
    setField(".STOP", 1, (bool) ex );
    if ( ex == STOPPED )
        wait_stop();
}

void QCaMotor::kill() {
    setField(":KILL", 1);
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


void QCaMotor::setUserHiLimit(double limit) {
    setField(".HLM", limit);
}


void QCaMotor::setUserLoLimit(double limit) {
    setField(".LLM", limit);
}

void QCaMotor::setDialHiLimit(double limit) {
    setField(".DHLM", limit);
}

void QCaMotor::setDialLoLimit(double limit) {
    setField(".DLLM", limit);
}


void QCaMotor::setMotorResolution(double res) {
    setField(".MRES", res);
}

void QCaMotor::setReadbackResolution(double res) {
    setField(".RRES", res);
}

void QCaMotor::setEncoderResolution(double res) {
    setField(".ERES", res);
}

void QCaMotor::setUnitsPerRev(double units) {
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


void QCaMotor::setMaximumSpeed(double speed) {
    setField(".VMAX", speed);
}

void QCaMotor::setNormalSpeed(double speed) {
    setField(".VELO", speed);
}

void QCaMotor::setRevSpeed(double speed) {
    setField(".S", speed);
}

void QCaMotor::setBacklashSpeed(double speed) {
    setField(".BVEL", speed);
}

void QCaMotor::setJogSpeed(double speed) {
    setField(".JVEL", speed);
}


void QCaMotor::setAcceleration(double acc) {
    setField(".ACCL", acc);
}

void QCaMotor::setBacklashAcceleration(double acc) {
    setField(".BACC", acc);
}

void QCaMotor::setJogAcceleration(double acc) {
    setField(".JAR", acc);
}

void QCaMotor::setMaxRetry(int rtr) {
    setField(".RTRY", rtr);
}


void QCaMotor::setUseReadback(bool use) {
    setField(".URIP", use);
}

void QCaMotor::setUseEncoder(bool use) {
    setField(".UEIP", use);
}

void QCaMotor::setBacklash(double dist) {
    setField(".BDST", dist);
}

void QCaMotor::setSpmgMode(SpmgMode mode) {
    setField(".SPMG", mode);
}

void QCaMotor::resetAmpFault(bool synch) {
    setField(":AMPFAULTRESET.PROC", 1);
    if (synch)
        qtWait(this, SIGNAL(changedAmplifierFault(bool)), 5000);
}

void QCaMotor::resetEncoderLoss(bool synch) {
    setField(":ELOSSRC.A", 1);
    if (synch)
        qtWait(this, SIGNAL(changedEncoderLoss(bool)), 5000);
}

void QCaMotor::resetWrongLimits(bool synch) {
    setField(":WRONGLIMITRESET.PROC", 1);
    if (synch)
        qtWait(this, SIGNAL(changedWrongLimits(bool)), 5000);
}

void QCaMotor::initializeMortor(bool synch) {
    setField(":INIT.PROC", 1);
    if (synch)
        qtWait(this, SIGNAL(changedInitializedFault(bool)), 5000);
}

void QCaMotor::setDriveCurrent(double curr) {
    setField(":DRIVECURRENT", curr);
}

void QCaMotor::setHoldPerCent(double percent) {
    setField(":HOLDPERCENTAGE", percent);
}



