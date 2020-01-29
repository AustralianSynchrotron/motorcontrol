%Module pyqcamotor

%Import QtCore/QtCoremod.sip



class QCaMotor : public QObject {

%TypeHeaderCode
#include "qcamotor.h"
%End


public:

  enum SpmgMode {
    STOP,
    PAUSE,
    MOVE,
    GO
  };

  enum SuMode {
    USE,
    SET
  };

  enum OffMode {
    VARIABLE,
    FROZEN
  };

  enum Direction {
    POSITIVE,
    NEGATIVE
  };

  enum MotionExit {
    IMMIDIATELY,
    CONFIRMATION,
    STARTED,
    ACCELERATED,
    STOPPED
  };

  enum HomeReference {
    POSLS,
    NEGLS,
    HOMLS,
    NOHOM
  };

  QCaMotor(QObject *parent /TransferThis/ =0);
  QCaMotor(const QString & pv, QObject *parent /TransferThis/ =0);

  ~QCaMotor();

  void wait_stop();

  void wait_start();

  void saveConfiguration(const QString & fileName, bool params = false) const;
  void loadConfiguration(const QString & fileName, bool params = false);

  const QString & getPv() const;
  const QString & getOut() const;
  const QString & getDescription() const;
  int getPrecision() const;
  const QString & getUnits() const;
  double getUserPosition() const;
  double get() const;
  double getDialPosition() const;
  double getRawPosition() const;
  double getUserGoal() const;
  double getDialGoal() const;
  double getRawGoal() const;
  double getStep() const;
  double getDeadBand() const;
  double getLastMotion() const;
  double getOffset() const;
  OffMode getOffsetMode() const;
  Direction getDirection() const;
  SuMode getSuMode() const;
  bool getHiLimitStatus() const;
  bool getLoLimitStatus() const;
  bool getLimitStatus() const;
  double getUserHiLimit() const;
  double getUserLoLimit() const;
  double getDialLoLimit() const;
  double getDialHiLimit() const;
  double getMotorResolution() const;
  double getReadbackResolution() const;
  double getEncoderResolution() const;
  double getUnitsPerRev() const;
  int getStepsPerRev() const;
  double getMaximumSpeed() const;
  double getNormalSpeed() const;
  double getRevSpeed() const;
  double getBacklashSpeed() const;
  double getJogSpeed() const;
  double getAcceleration() const;
  double getBacklashAcceleration() const;
  double getJogAcceleration() const;
  int getMaxRetry() const;
  bool isConnected() const;
  bool isMoving() const;
  bool getUseReadback() const;
  bool getUseEncoder() const;
  double getBacklash() const;
  SpmgMode getSpmgMode() const;
  bool isSplitStall() const;
  bool hasProblems() const;
  bool commError() const;
  bool isPlugged() const;
  bool isKilled() const;
  bool amplifierIsFaulty() const;
  bool isInitialized() const;
  bool limitsAreWrong() const;
  bool encoderIsLost() const;
  HomeReference getHomeRef() const;
  bool isHoming() const;
  bool getStatus() const;
  double getDriveCurrent() const;
  double getHoldPerCent() const;

public slots:

  void setPv(const QString & pvName="");
  void setDescription(const QString & desc);
  void setPrecision(int prec);
  void setUnits(const QString & units);
  void setUserPosition(double pos);
  void setDialPosition(double pos);
  void setRawPosition(double pos);
  void goUserPosition(double pos, MotionExit ex=IMMIDIATELY);
  void goDialPosition(double pos, MotionExit ex=IMMIDIATELY);
  void goRawPosition(double pos, MotionExit ex=IMMIDIATELY);
  void goLimit(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);
  void goStep(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);
  void goHome(QCaMotor::Direction direction, MotionExit ex=IMMIDIATELY);
  void goHome(MotionExit ex=IMMIDIATELY);
  void executeHomeRoutine(bool synch=true);
  void goRelative(double dist, MotionExit ex=IMMIDIATELY);
  void jog(bool jg, QCaMotor::Direction direction);
  void setStep(double step);
  void setDeadBand(double rdbd);
  void undoLastMotion(MotionExit ex=IMMIDIATELY);
  void setOffset(double dist);
  void setOffsetMode(OffMode mode);
  void setDirection(Direction direction);
  void setSuMode(SuMode mode);
  void setUserHiLimit(double limit);
  void setUserLoLimit(double limit);
  void setDialHiLimit(double limit);
  void setDialLoLimit(double limit);
  void setMotorResolution(double res);
  void setReadbackResolution(double res);
  void setEncoderResolution(double res);
  void setUnitsPerRev(double units);
  void setStepsPerRev(int st);
  void setMaximumSpeed(double speed);
  void setNormalSpeed(double speed);
  void setRevSpeed(double speed);
  void setBacklashSpeed(double speed);
  void setJogSpeed(double speed);
  void setAcceleration(double acc);
  void setBacklashAcceleration(double acc);
  void setJogAcceleration(double acc);
  void setMaxRetry(int rtr);
  void stop(MotionExit ex=IMMIDIATELY);
  void kill();
  void setUseReadback(bool use);
  void setUseEncoder(bool use);
  void setBacklash(double dist);
  void setSpmgMode(SpmgMode mode);
  void printError(const QString & err) const;
  void resetAmpFault(bool synch=false);
  void resetEncoderLoss(bool synch=false);
  void resetWrongLimits(bool synch=false);
  void initializeMortor(bool synch=false);
  void setDriveCurrent(double curr);
  void setHoldPerCent(double percent);


signals:

  void changedPv(QString pvName=QString());
  void changedOut(QString out);
  void changedDescription(QString desc);
  void changedPrecision(int prec);
  void changedUnits(QString units);
  void changedUserPosition(double pos);
  void changedDialPosition(double pos);
  void changedRawPosition(double pos);
  void changedUserGoal(double pos);
  void changedDialGoal(double pos);
  void changedRawGoal(double pos);
  void changedStep(double pos);
  void changedDeadBand(double rdbd);
  void changedOffset(double off);
  void changedOffsetMode(QCaMotor::OffMode mode);
  void changedDirection(QCaMotor::Direction dir);
  void changedSuMode(QCaMotor::SuMode mode);
  void changedPlugged(bool plgd);
  void changedHiLimitStatus(bool status);
  void changedLoLimitStatus(bool status);
  void changedUserHiLimit(double limit);
  void changedUserLoLimit(double limit);
  void changedDialLoLimit(double limit);
  void changedDialHiLimit(double limit);
  void changedMotorResolution(double res);
  void changedReadbackResolution(double res);
  void changedEncoderResolution(double res);
  void changedUnitsPerRev(double units);
  void changedStepsPerRev(int st);
  void changedMaximumSpeed(double speed);
  void changedNormalSpeed(double speed);
  void changedRevSpeed(double speed);
  void changedBacklashSpeed(double speed);
  void changedJogSpeed(double speed);
  void changedAcceleration(double acc);
  void changedBacklashAcceleration(double acc);
  void changedJogAcceleration(double acc);
  void changedMaxRetry(int rtr);
  void changedConnected(bool con);
  void changedMoving(bool mov);
  void stopped();
  void changedUseReadback(bool status);
  void changedUseEncoder(bool status);
  void changedBacklash(double dist);
  void changedSpmgMode(QCaMotor::SpmgMode mode);
  void changedSlipStall(bool slst);
  void changedProblems(bool probs);
  void changedCommErr(bool commerr);
  void changedKilled(bool killed);
  void changedAmplifierFault(bool ampFlt);
  void changedInitialized(bool inited);
  void changedWrongLimits(bool badLs);
  void changedEncoderLoss(bool eloss);
  void changedHomeRef(QCaMotor::HomeReference href);
  void changedHoming(bool hom);
  void changedDriveCurrent(double cnt);
  void changedHoldPerCent(double percent);
  void changedStatus(bool sts);
  void error(QString msg);

};
