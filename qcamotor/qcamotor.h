#ifndef CAMOTOR_H
#define CAMOTOR_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <qtpv.h>

// :DRIVECURRENT (_RBV)
// :HOLDPERCENTAGE (_RBV)



/// \brief Class representing the EPICS motor.
///
/// This class stores all the EPICS motor record's fields, provides methods for manipulating,
/// acquiring information and Qt's signals with the updates.
///

class QCaMotor : public QObject {

  Q_OBJECT;

public:

  /// SPMG field values
  enum SpmgMode {
    STOP=0,                     ///< 0:"Stop"
    PAUSE=1,                    ///< 1:"Pause"
    MOVE=2,                     ///< 2:"Move"
    GO=3                        ///< 3:"Go"
  };

  /// SET field values
  enum SuMode {
    USE=0,                      ///< 0:"Use"
    SET=1                       ///< 1:"Set"
  };

  /// FOFF field values
  enum OffMode {
    VARIABLE=0,                 ///< 0:"Variable"
    FROZEN=1                    ///< 1:"Frozen"
  };

  /// DIR field values
  enum Direction {
    POSITIVE=0,                 ///< 0:"Pos"
    NEGATIVE=1                  ///< 1:"Neg"
  };

  enum HomeReference {
    NOHOM=0,
    POSLS=-1,
    NEGLS=1,
    HOMLS=2
  };

  /// Tells when the functions which move the motor to return
  enum MotionExit {
    IMMIDIATELY=0, ///< right after the command was written
    CONFIRMATION=1, ///< after recieving confirmation of the command
    STARTED=2, ///< after start (DMOV -> 0)
    ACCELERATED=3, ///< after finished the acceleration (theoretically calculated)
    STOPPED=5 ///< after stop (DMOV ->1, may happen to be 1.5 sec after actual stop)
  };

  /// Constructor
  ///
  /// @param parent Parent
  ///
  QCaMotor(QObject *parent=0);

  QCaMotor(const QString & pv, QObject *parent=0);

  ~QCaMotor();

  /// Qt-aware function which returns only after any motion of the motor has finished.
  void wait_stop();

  /// Qt-aware function which returns only after any motion of the motor has started.
  void wait_start();

  template <class Vclass> void waitUpdated (
    const QString & field,
    const Vclass expected,
    Vclass (QCaMotor::* getMethod)() const,
    int delay_msec=0 ) const;

  void waitUpdated ( const QString & field, int delay_msec=0 ) const;

  void saveConfiguration(const QString & fileName) const;
  void saveConfiguration(QTextStream & stream) const;
  void loadConfiguration(const QString & fileName);
  void loadConfiguration(QTextStream & stream);

protected:
  bool eventFilter(QObject *obj, QEvent *event);


private:

  void init();

  template <class num> void updateNum(
    const QVariant & data,
    num & parameter,
    const QString & parameter_name,
    void (QCaMotor::* changedNum)(num) );

  QHash<QString, QEpicsPv*> fields; ///< All motor record's fields used in the class.

  /// Writes new data to the field.
  ///
  /// @param key The field to be set: must be a key from the QCaMotor::motor.
  /// @param value Value to put into the field with the key.
  ///
  void setField(const QString & key, const QVariant & value, bool confirm=false);

  SuMode ensureSuMode(SuMode mode);
  SuMode prepareMotion(MotionExit ex);
  void finilizeMotion(MotionExit ex, SuMode restore_mode);

  // Here I've got a member for each field to avoid conversion
  // from QVariant (returned by the QEpicsPv::get() )
  // each time the value is required.

  QString pv;                   ///< Motor's PV


  QString description;          ///< current value of the DESC field
  int precsision;               ///< current value of the PREC field
  QString units;                ///< current value of the EGU field

  double userPosition;          ///< current value of the RBV field
  double dialPosition;          ///< current value of the DRVB field
  double rawPosition;           ///< current value of the RRVB field
  double userGoal;              ///< current value of the VAL field
  double dialGoal;              ///< current value of the DVAL field
  double rawGoal;               ///< current value of the RVAL field
  double step;                  ///< current value of the TW field
  double deadBand;

  double offset;                ///< current value of the OFF field
  OffMode offsetMode;           ///< current value of the FOFF field
  Direction direction;          ///< current value of the DIR field
  SuMode suMode;                ///< current value of the SET field

  bool loLimitStatus;           ///< current value of the LLS field
  bool hiLimitStatus;           ///< current value of the HLS field
  double userLoLimit;           ///< current value of the LLM field
  double userHiLimit;           ///< current value of the HLM field
  double dialLoLimit;           ///< current value of the DLLM field
  double dialHiLimit;           ///< current value of the DHLM field

  double motorResolution;       ///< current value of the MRES field
  double readbackResolution;    ///< current value of the RRES field
  double encoderResolution;     ///< current value of the ERES field
  double unitsPerRev;           ///< current value of the UREV field
  int    stepsPerRev;           ///< current value of the SREV field

  double maximumSpeed;          ///< current value of the VMAX field
  double normalSpeed;           ///< current value of the VELO field
  double revSpeed;              ///< current value of the S field
  double backlashSpeed;         ///< current value of the BVEL field
  double jogSpeed;              ///< current value of the JVEL field
  double acceleration;          ///< current value of the ACCL field
  double backlashAcceleration;  ///< current value of the BACC field
  double jogAcceleration;       ///< current value of the JAR field
  int retry;                    ///< current value of the RTRY field

  bool iAmConnected;            ///< true if all fields in ::motor were connected.
  bool iAmMoving;               ///< current value of the DMOV field
  bool useEncoder;              ///< current value of the UEIP field
  bool useReadback;             ///< current value of the URIP field
  double backlash;              ///< current value of the BDST field
  SpmgMode spmgMode;            ///< current value of the SPMG field
  ulong msta;                   ///< current value of the MSTA field
  bool iAmHoming;               ///< derived from HOMF and HOMR
  bool iAmKilled;               ///< current value of the :KILLED
  bool ampIsFaulty;             ///< current value of the :AMPFAULT
  bool iAmInitialized;          ///< current value of the :UNINIT
  bool wrongLimits;             ///< current value of the :WRONGLIMIT
  bool eLoss;                   ///< current value of the :ELOSS
  HomeReference homeRef;        ///< derived from :HOME_FLAG_USER.SVAL

  double driveCurrent;          ///< current value of the :DRIVECURRENT_RBV
  double holdPerCent;           ///< current value of the :HOLDPERCENTAGE_RBV

  double lastMotion;            ///< last motion of the motor (in raw coordinates)
  double lastPreHom;            ///< last RRBV before the moter has homed

  // WARNING: BUG (in EPICS's motor)
  // Sometimes, very rarely, after the request to move the motor, the .DMOV field goes to 0 and immidiately 1,
  // but no actual motion happens. After this the values of .VAL and .RBV are different.
  // In this case it is enough to repeat the motion request and the motor will move. In order to address this issue
  // I introduce the additional member secondMotionAttempt which sets to false on first motion attempt and then is checked on
  // motion stop. If the described bug is detected on stop, then the member is set to true and second attempt to
  // move the motor is requested. If the motor did not move after the second attempt, means something strange is happening.
  //
  // Just found that the bug can be reproduced with high probability after re-fusing the motor channel.
  bool secondMotionAttempt;

private slots:


  /////////////////////
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //  UPDATE SLOTS   //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  /////////////////////


  /// \brief Updates connection status (::iAmConnected)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  void updateConnection(bool suc);

  /// \brief Updates description (::description)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new description.
  void updateDescription(const QVariant & data);

  /// \brief Updates precision (::precision)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new precision.
  void updatePrecision(const QVariant & data);

  /// \brief Updates units (::units)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new units.
  void updateUnits(const QVariant & data);

  /// \brief Updates user position (::userPosition)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new user position.
  void updateUserPosition(const QVariant & data);

  /// \brief Updates dial position (::dialPosition)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new dial position.
  void updateDialPosition(const QVariant & data);

  /// \brief Updates raw position (::rawPosition)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new raw position.
  void updateRawPosition(const QVariant & data);

  /// \brief Updates user goal (::userGoal)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new user goal.
  void updateUserGoal(const QVariant & data);

  /// \brief Updates dial goal (::dialGoal)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new dial goal.
  void updateDialGoal(const QVariant & data);

  /// \brief Updates raw goal (::rawGoal)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new raw goal.
  void updateRawGoal(const QVariant & data);

  /// \brief Updates step (::step)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new step.
  void updateStep(const QVariant & data);

  void updateDeadBand(const QVariant & data);


  /// \brief Updates hi limit status (::hiLimitStatus)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new status.
  void updateHiLimitStatus(const QVariant & data);

  /// \brief Updates lo limit status (::loLimitStatus)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new status.
  void updateLoLimitStatus(const QVariant & data);

  /// \brief Updates user hi limit (::userHiLimit)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new limit.
  void updateUserHiLimit(const QVariant & data);

  /// \brief Updates user lo limit (::userLoLimit)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new limit.
  void updateUserLoLimit(const QVariant & data);

  /// \brief Updates dial lo limit (::dialLoLimit)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new limit.
  void updateDialLoLimit(const QVariant & data);

  /// \brief Updates dial high limit (::dialHiLimit)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new limit.
  void updateDialHiLimit(const QVariant & data);


  /// \brief Updates motor resolution (::motorResolution)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new resolution.
  void updateMotorResolution(const QVariant & data);

  /// \brief Updates readback resolution (::readbackResolution)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new resolution.
  void updateReadbackResolution(const QVariant & data);

  /// \brief Updates encoder resolution (::encoderResolution)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new resolution.
  void updateEncoderResolution(const QVariant & data);

  /// \brief Updates EGU's per resolution (::unitsPerRev)
  /// Used to catch the signal valueUpdated(QVariant)
  /// from the corresponding field (a member of ::motor).
  /// @param data new value.
  void updateUnitsPerRev(const QVariant & data);

  /// \brief Updates steps per resolution (::stepsPerRev)
  /// Used to catch the signal valueUpdated(QVariant)
  /// from the corresponding field (a member of ::motor).
  /// @param data new value.
  void updateStepsPerRev(const QVariant & data);


  /// \brief Updates maximum speed (::maximumSpeed)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new speed.
  void updateMaximumSpeed(const QVariant & data);

  /// \brief Updates normal speed (::normalSpeed)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new speed.
  void updateNormalSpeed(const QVariant & data);

  /// \brief Updates revolving speed: turns per second (::revSpeed)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new speed.
  void updateRevSpeed(const QVariant & data);

  /// \brief Updates backlash speed (::backlashSpeed)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new speed.
  void updateBacklashSpeed(const QVariant & data);

  /// \brief Updates jog speed (::jogSpeed)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new speed.
  void updateJogSpeed(const QVariant & data);

  /// \brief Updates acceleration (::acceleration)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new acceleration.
  void updateAcceleration(const QVariant & data);

  /// \brief Updates backlash acceleration (::backlashAcceleration)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new acceleration.
  void updateBacklashAcceleration(const QVariant & data);

  /// \brief Updates jog acceleration (::jogAcceleration)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new acceleration.
  void updateJogAcceleration(const QVariant & data);


  void updateMaxRetry(const QVariant & data);


  /// \brief Updates backlash (::backlash)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new backlash.
  void updateBacklash(const QVariant & data);


  /// \brief Updates moving status (::iAmMoving)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new status.
  void updateMoving(const QVariant & data);

  /// \brief Updates use readback parameter (::useReadback)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new value.
  void updateUseReadback(const QVariant & data);

  /// \brief Updates use encoder parameter (::useEncoder)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new value.
  void updateUseEncoder(const QVariant & data);


  /// \brief Updates direction (::direction)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new direction.
  void updateDirection(const QVariant & data);

  /// \brief Updates offset mode (::offsetMode)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new mode.
  void updateOffsetMode(const QVariant & data);

  /// \brief Updates offset (::offset)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new offset.
  void updateOffset(const QVariant & data);

  /// \brief Updates SPMG mode (::spmgMode)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new mode.
  void updateSpmgMode(const QVariant & data);

  /// \brief Updates set mode (::suMode)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new mode.
  void updateSuMode(const QVariant & data);

  /// \brief Updates MSTA (::msta)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new msta.
  void updateMSTA(const QVariant & data);

  /// \brief Updates set mode (::homeRef)
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new reference.
  void updateHomeRef(const QVariant & data);

  /// \brief Updates homing status
  /// Used to catch the signal valueUpdated(QVariant) signal
  /// from the corresponding field (a member of ::motor).
  /// @param data new reference.
  void updateHoming(const QVariant &);

  void updateKilled(const QVariant & data);

  void updateAmpFault(const QVariant & data);

  void updateInitialized(const QVariant & data);

  void updateWrongLimits(const QVariant & data);

  void updateEncoderLoss(const QVariant & data);

  void updateDriveCurrent(const QVariant & data);

  void updateHoldPerCent(const QVariant & data);

  /// Used by ::setPv() through QTimer::singleShot()
  void preSetPv();


public slots:

  /////////////////
  //             //
  //             //
  //             //
  //             //
  //             //
  //  SET SLOTS  //
  //             //
  //             //
  //             //
  //             //
  //             //
  //             //
  /////////////////



  /// Sets the new PV name of the motor or disconnects current motor if the name is empty.
  ///
  /// @param pvName new PV name.
  /// @param confirm if false then returns immediately after setting the name, if true then waits
  /// for the motors fields to be all connected and ready to use.
  ///
  void setPv(const QString & pvName="");

  /// Sets the description of the motor (DESC field).
  /// @param desc new decription.
  void setDescription(const QString & desc);

  /// Sets precision (PREC field).
  /// @param prec new precision.
  void setPrecision(int prec);

  /// Sets units (EGU field).
  /// @param units new units.
  void setUnits(const QString & units);


  /// Sets user position without moving the motor (RBV field).
  /// @param pos new position.
  void setUserPosition(double pos);

  /// Sets dial position without moving the motor (DRBV field).
  /// @param pos new position.
  void setDialPosition(double pos);

  /// Sets raw position without moving the motor (RRBV field).
  /// @param pos new position.
  void setRawPosition(double pos);


  /// Moves the motor to the absolute value of the user position.
  ///
  /// @param pos position to move to
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goUserPosition(double pos, MotionExit ex=IMMIDIATELY);

  /// Moves the motor to the absolute value of the dial position.
  ///
  /// @param pos position to move to
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goDialPosition(double pos, MotionExit ex=IMMIDIATELY);

  /// Moves the motor to the absolute value of the raw position.
  ///
  /// @param pos position to move to
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goRawPosition(double pos, MotionExit ex=IMMIDIATELY);

  /// Moves the motor to the limit (hard or soft, whatever is reached first).
  ///
  /// @param direction direction to move in (defined by the sign)
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the   /// WARNING: BUG (in EPICS's motor)motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goLimit(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);

  /// Moves the motor by the one step (see ::setStep() and ::getStep() ).
  ///
  /// @param direction direction to move in (defined by the sign)
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goStep(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);

  /// Moves the motor home.
  ///
  /// @param direction to move in (defined by the sign)
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goHome(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);

  /// Moves the motor home.
  ///
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goHome(MotionExit ex=IMMIDIATELY);

  /// Executes whole homing routine: if HomeRef is one of the limit then drives motor
  /// into it and calls goHome.
  ///
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void executeHomeRoutine(bool synch=true);


  /// Moves the motor relatively by the specified distance.
  ///
  /// @param dist distance to move.
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void goRelative(double dist, MotionExit ex=IMMIDIATELY);

  /// Starts/stops jogging the motor.
  ///
  /// @param jg starts jogging if true, stops otherwise.
  /// @param direction direction to move in (defined by the sign)
  ///
  void jog(bool jg, QCaMotor::Direction direction);

  /// Sets the size of one step used in ::goStep() method.
  /// @param step new step.
  void setStep(double step);

  void setDeadBand(double rdbd);

  /// Undo last motion seen by the object (cannot undo any motion done before the construction of the object).
  ///
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void undoLastMotion(MotionExit ex=IMMIDIATELY);


  /// Sets offset (OFF field).
  /// @param dist new offset.
  void setOffset(double dist);

  /// Sets offset mode (FOFF field).
  /// @param mode new mode.
  void setOffsetMode(QCaMotor::OffMode mode);

  /// Sets direction (DIR field).
  /// @param direction new direction.
  void setDirection(QCaMotor::Direction direction);

  /// Sets the Set/Use mode (SET field).
  /// @param mode new mode.
  void setSuMode(QCaMotor::SuMode mode);

  /// Sets user high limit (HLM field).
  /// @param limit new limit.
  void setUserHiLimit(double limit);

  /// Sets user low limit (LLM field).
  /// @param limit new limit.
  void setUserLoLimit(double limit);

  /// Sets dial high limit (DHLM field).
  /// @param limit new limit.
  void setDialHiLimit(double limit);

  /// Sets user high limit (DLLM field).
  /// @param limit new limit.
  void setDialLoLimit(double limit);


  /// Sets motor resolution (MRES field).
  ///
  /// Currently there is a bug in the EPICS motor driver:
  /// after changing the resolution to a negative value
  /// the motor stops reacting to any moving command.
  ///
  /// WARNING: BUG (in EPICS's motor)
  ///
  /// @param res new resolution.
  ///
  void setMotorResolution(double res);

  /// Sets readback resolution (RRES field).
  /// @param res new resolution.
  void setReadbackResolution(double res);

  /// Sets encoder resolution (ERES field).
  /// @param res new resolution.
  void setEncoderResolution(double res);

  /// Sets EGU's per revolution (UREV field).
  /// @param units new units-per-rev.
  void setUnitsPerRev(double units);

  /// Sets esteps per revolution (SREV field).
  /// @param st new steps-per-rev.
  void setStepsPerRev(int st);



  /// Sets maximum speed (VMAX field).
  /// @param speed new maximum speed.
  void setMaximumSpeed(double speed);

  /// Sets normal speed (VELO field).
  /// @param speed new speed.
  void setNormalSpeed(double speed);

  /// Sets normal speed (S field).
  /// @param speed new revolving speed.
  void setRevSpeed(double speed);

  /// Sets backlash speed (BVEL field).
  /// @param  speed new speed.
  void setBacklashSpeed(double speed);

  /// Sets jogging speed (JVEL field).
  /// @param speed new speed.
  void setJogSpeed(double speed);


  /// Sets acceleration (ACCL field).
  /// @param acc new acceleration.
  void setAcceleration(double acc);

  /// Sets backlash acceleration (BACC field).
  /// @param acc new acceleration.
  void setBacklashAcceleration(double acc);

  /// Sets jogging acceleration (JAR field).
  /// @param acc new acceleration.
  void setJogAcceleration(double acc);

  void setMaxRetry(int rtr);

  /// Stops any motor motion.
  ///
  /// @param wait if false then sends the command and returns immediately,
  /// if true then waits for the motion to complete and then returns
  /// (waiting is Qt-aware).
  ///
  void stop(MotionExit ex=IMMIDIATELY);

  /// Kills motor.
  void kill();

  /// Sets "use readback" property (URIP field).
  /// @param use new value.
  void setUseReadback(bool use);

  /// Sets "use encoder" property (UEIP field).
  /// @param use new value.
  void setUseEncoder(bool use);

  /// Sets backlash distance (BDST field).
  /// @param dist new distance.
  void setBacklash(double dist);

  /// Sets SPMG mode (SPMG field).
  /// @param mode new mode.
  void setSpmgMode(SpmgMode mode);

  void resetAmpFault(bool synch=false);

  void resetEncoderLoss(bool synch=false);

  void resetWrongLimits(bool synch=false);

  void initializeMortor(bool synch=false);

  void setDriveCurrent(double curr);

  void setHoldPerCent(double percent);

  /// Prints an error message to the stderr.
  /// @param err Error message.
  inline void printError(const QString & err) const { qDebug() << "ERROR in QCaMotor!" << err; }


public:


  /////////////////////
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //  GET METHODS    //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  /////////////////////





  /// Returns current pv name
  /// @return ::pv
  inline const QString &  getPv() const { return pv; }

  /// Returns current description
  /// @return ::description
  inline const QString &  getDescription() const { return description; }

  /// Returns current precision
  /// @return ::precision.
  inline int       getPrecision() const { return precsision; }

  /// Returns current units
  /// @return ::units
  inline const QString & getUnits() const { return units; }


  /// Returns current user position
  /// @return ::userPosition
  inline double    getUserPosition() const { return userPosition; }

  /// Returns current user position (just the shortcut for ::getUserPosition() )
  /// @return ::userPosition
  inline double    get() const {return getUserPosition();}

  /// Returns current dial position
  /// @return ::dialPosition
  inline double    getDialPosition() const { return dialPosition; }

  /// Returns current raw position
  /// @return ::rawPosition
  inline double    getRawPosition() const { return rawPosition; }

  /// Returns current user goal
  /// @return ::userGoal
  inline double    getUserGoal() const { return userGoal; }

  /// Returns current dial goal
  /// @return ::dialGoal
  inline double    getDialGoal() const { return dialGoal; }

  /// Returns current raw goal
  /// @return ::rawGoal
  inline double    getRawGoal() const { return rawGoal; }

  /// Returns current step
  /// @return ::step
  inline double    getStep() const { return step; }

  inline double getDeadBand() const {return deadBand;}

  /// Returns current distance of the last motion
  /// @return lastMotion
  inline double    getLastMotion() const { return isMoving()  ?  0  :  lastMotion; }


  /// Returns current offset
  /// @return ::offset
  inline double    getOffset() const { return offset; }

  /// Returns current offset mode
  /// @return ::offsetMode
  inline OffMode   getOffsetMode() const { return offsetMode; }

  /// Returns current direction
  /// @return ::direction
  inline Direction getDirection() const { return direction; }

  /// Returns current set/use mode
  /// @return ::suMode
  inline SuMode    getSuMode() const { return suMode; }


  /// Returns current high limit status
  /// @return ::hiLimitStatus
  inline bool      getHiLimitStatus() const { return hiLimitStatus; }

  /// Returns current low limit status
  /// @return ::loLimitStatus
  inline bool      getLoLimitStatus() const { return loLimitStatus; }

  inline bool      getLimitStatus() const {return getLoLimitStatus() || getHiLimitStatus();}

  /// Returns current high user limit
  /// @return ::userHiLimit
  inline double    getUserHiLimit() const { return userHiLimit; }

  /// Returns current low user limit
  /// @return ::userLoLimit
  inline double    getUserLoLimit() const { return userLoLimit; }

  /// Returns current dial low limit
  /// @return ::dialLoLimit
  inline double    getDialLoLimit() const { return dialLoLimit; }

  /// Returns current dial high limit
  /// @return ::dialHiLimit
  inline double    getDialHiLimit() const { return dialHiLimit; }


  /// Returns current motor resolution
  /// @return ::motorResolution
  inline double    getMotorResolution() const { return motorResolution; }

  /// Returns current readback resolution
  /// @return ::readbackResolution
  inline double    getReadbackResolution() const { return readbackResolution; }

  /// Returns current encoder resolution
  /// @return ::encoderResolution
  inline double    getEncoderResolution() const { return encoderResolution; }

  /// Returns current EGU's per revolution
  /// @return ::unitsPerRev
  inline double    getUnitsPerRev() const { return unitsPerRev; }

  /// Returns current steps per revolution
  /// @return ::stepsPerRev
  inline int       getStepsPerRev() const { return stepsPerRev; }



  /// Returns current maximum speed
  /// @return ::maximumSpeed
  inline double    getMaximumSpeed() const { return maximumSpeed; }

  /// Returns current normal speed
  /// @return ::normalSpeed
  inline double    getNormalSpeed() const { return normalSpeed; }

  /// Returns current speed in terms of turns per second
  /// @return ::revSpeed
  inline double    getRevSpeed() const { return revSpeed; }

  /// Returns current backlash speed
  /// @return ::backlashSpeed
  inline double    getBacklashSpeed() const { return backlashSpeed; }

  /// Returns current jogging speed
  /// @return ::jogSpeed
  inline double    getJogSpeed() const { return jogSpeed; }


  /// Returns current acceleration
  /// @return ::acceleration
  inline double    getAcceleration() const { return acceleration; }

  /// Returns current backlash acceleration
  /// @return ::backlashAcceleration
  inline double    getBacklashAcceleration() const { return backlashAcceleration; }

  /// Returns current jogging acceleration
  /// @return jogAcceleration
  inline double    getJogAcceleration() const { return jogAcceleration; }

  inline int       getMaxRetry() const { return retry; }

  /// Returns current connection status
  /// @return ::iAmConnected
  inline bool      isConnected() const { return iAmConnected; }

  /// Returns current moving status
  /// @return ::iAmMoving
  inline bool      isMoving() const { return iAmMoving; }

  /// Returns current "use readback" status
  /// @return ::useReadback
  inline bool      getUseReadback() const { return useReadback; }

  /// Returns current "use encoder"
  /// @return ::useEncoder
  inline bool      getUseEncoder() const { return useEncoder; }

  /// Returns current backlashAcceleration distance
  /// @return ::backlash
  inline double    getBacklash() const { return backlash; }

  /// Returns current SPMG mode
  /// @return ::spmgMode
  inline SpmgMode  getSpmgMode() const { return spmgMode; }

  inline bool isSplitStall() const {return msta & 0b0000000001000000;}

  inline bool hasProblems() const {return msta & 0b0000001000000000;}

  inline bool commError() const {return msta & 0b0001000000000000;}

  inline bool isKilled() const {return iAmKilled;}

  inline bool amplifierIsFaulty() const {return ampIsFaulty;}

  inline bool isInitialized() const {return iAmInitialized;}

  inline bool limitsAreWrong() const {return wrongLimits;}

  inline bool encoderIsLost() const {return eLoss;}

  inline double getDriveCurrent() const {return driveCurrent;}

  inline double getHoldPerCent() const {return holdPerCent;}

  /// Returns current home reference
  /// @return ::homeRef
  inline HomeReference  getHomeRef() const { return homeRef; }

  inline bool isHoming() const {return iAmHoming;}

  inline bool isPlugged() const {return ! ( getLoLimitStatus() and ! getHiLimitStatus() );}


signals:

  /////////////////////
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //  CHANGED SIGS   //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  //                 //
  /////////////////////


  /// The signal is emitted whenever pv name is changed.
  /// @param pvName new pv name
  void changedPv(QString pvName=QString());

  /// The signal is emitted whenever description is changed.
  /// @param desc new description
  void changedDescription(QString desc);

  /// The signal is emitted whenever precision  is changed.
  /// @param prec new precision
  void changedPrecision(int prec);

  /// The signal is emitted whenever units is changed.
  /// @param units new units
  void changedUnits(QString units);


  /// The signal is emitted whenever user position is changed.
  /// @param pos new user position
  void changedUserPosition(double pos);

  /// The signal is emitted whenever dial position is changed.
  /// @param pos new position
  void changedDialPosition(double pos);

  /// The signal is emitted whenever raw position is changed.
  /// @param pos new position
  void changedRawPosition(double pos);

  /// The signal is emitted whenever user goal is changed.
  /// @param pos new goal
  void changedUserGoal(double pos);

  /// The signal is emitted whenever dial goal is changed.
  /// @param pos new goal
  void changedDialGoal(double pos);

  /// The signal is emitted whenever raw goal is changed.
  /// @param pos new goal
  void changedRawGoal(double pos);

  /// The signal is emitted whenever step is changed.
  /// @param pos new step
  void changedStep(double pos);

  void changedDeadBand(double rdbd);


  /// The signal is emitted whenever offset is changed.
  /// @param off new offset
  void changedOffset(double off);

  /// The signal is emitted whenever offset mode is changed.
  /// @param mode new mode
  void changedOffsetMode(QCaMotor::OffMode mode);

  /// The signal is emitted whenever direction is changed.
  /// @param dir new direction
  void changedDirection(QCaMotor::Direction dir);

  /// The signal is emitted whenever set/use mode is changed.
  /// @param mode new mode
  void changedSuMode(QCaMotor::SuMode mode);



  /// The signal is emitted whenever high limit status is changed.
  /// @param status new status
  void changedHiLimitStatus(bool status);

  /// The signal is emitted whenever lo limit status is changed.
  /// @param status new status
  void changedLoLimitStatus(bool status);

  /// The signal is emitted whenever user high limit is changed.
  /// @param limit new limit
  void changedUserHiLimit(double limit);

  /// The signal is emitted whenever low limit is changed.
  /// @param limit new limit
  void changedUserLoLimit(double limit);

  /// The signal is emitted whenever dial low limit is changed.
  /// @param limit new limit
  void changedDialLoLimit(double limit);

  /// The signal is emitted whenever dial high limit is changed.
  /// @param limit new limit
  void changedDialHiLimit(double limit);


  /// The signal is emitted whenever motor resolution is changed.
  /// @param res new resolution
  void changedMotorResolution(double res);

  /// The signal is emitted whenever readback resolution is changed.
  /// @param res new readback resolution
  void changedReadbackResolution(double res);

  /// The signal is emitted whenever encoder resolution is changed.
  /// @param res new resolution
  void changedEncoderResolution(double res);

  /// The signal is emitted whenever units-per-rev is changed.
  /// @param units new value
  void changedUnitsPerRev(double units);

  /// The signal is emitted whenever steps-per-rev is changed.
  /// @param res new value
  void changedStepsPerRev(int st);

  /// The signal is emitted whenever maximum speed is changed.
  /// @param speed new speed
  void changedMaximumSpeed(double speed);

  /// The signal is emitted whenever normal speed is changed.
  /// @param speed new speed
  void changedNormalSpeed(double speed);

  /// The signal is emitted whenever revolving speed is changed.
  /// @param speed new speed
  void changedRevSpeed(double speed);

  /// The signal is emitted whenever backlash speed is changed.
  /// @param speed new speed
  void changedBacklashSpeed(double speed);

  /// The signal is emitted whenever jogging speed is changed.
  /// @param speed new speed
  void changedJogSpeed(double speed);


  /// The signal is emitted whenever acceleration is changed.
  /// @param acc new acceleration
  void changedAcceleration(double acc);

  /// The signal is emitted whenever backlash acceleration is changed.
  /// @param acc new acceleration
  void changedBacklashAcceleration(double acc);

  /// The signal is emitted whenever jog acceleration is changed.
  /// @param acc new acceleration
  void changedJogAcceleration(double acc);

  void changedMaxRetry(int rtr);


  /// The signal is emitted whenever connection status is changed.
  /// @param con new status
  void changedConnected(bool con);

  /// The signal is emitted whenever moving status is changed.
  /// @param mov new status
  void changedMoving(bool mov);

  /// The signal is emitted whenever motor have stopped.
  void stopped();


  /// The signal is emitted whenever "use readback" property is changed.
  /// @param status new value
  void changedUseReadback(bool status);

  /// The signal is emitted whenever "use encoder" property is changed.
  /// @param status new value
  void changedUseEncoder(bool status);

  /// The signal is emitted whenever backlash distance is changed.
  /// @param dist new backlash
  void changedBacklash(double dist);

  /// The signal is emitted whenever SPMG mode is changed.
  /// @param mode new mode
  void changedSpmgMode(QCaMotor::SpmgMode mode);

  /// The signal is emitted whenever slip/stall is changed.
  /// @param slst new status
  void changedSlipStall(bool slst);

  /// The signal is emitted whenever problem bit of MSTA is changed.
  /// @param probs new status
  void changedProblems(bool probs);

  /// The signal is emitted whenever communication error is detected.
  /// @param commerr new mode
  void changedCommErr(bool commerr);

  void changedKilled(bool killed);

  void changedAmplifierFault(bool ampFlt);

  void changedInitialized(bool inited);

  void changedWrongLimits(bool badLs);

  void changedEncoderLoss(bool eloss);

  /// The signal is emitted whenever home reference is changed.
  /// @param mode new reference
  void changedHomeRef(QCaMotor::HomeReference href);

  /// The signal is emitted whenever home reference is changed.
  /// @param mode new reference
  void changedHoming(bool hom);

  void changedDriveCurrent(double cnt);

  void changedHoldPerCent(double percent);

  void changedPlugged(bool plg);


  /// The signal is emitted on any error
  /// @param msg error message.
  void error(QString msg);

};



template <class Vclass> void QCaMotor::waitUpdated(
    const QString & field,
    const Vclass expected,
    Vclass (QCaMotor::* getMethod)() const,
    int delay_msec
    ) const {
  if ( (this->*getMethod)() == expected )
    return;
  if ( ! fields.contains(field) )
    return;
  qtWait(fields[field], SIGNAL(valueUpdated(QVariant)), delay_msec);
}


template <class num> void QCaMotor::updateNum(
  const QVariant & data,
  num & parameter,
  const QString & parameter_name,
  void (QCaMotor::* changedNum)(num)
  ) {
  if (data.canConvert<num>())
    emit (this->*changedNum)(parameter = data.value<num>());
  else
    emit error("Could not convert QVariant \"" + data.toString()
                 + "\" to " + parameter_name + ".");
}



#endif // CAMOTOR_H
