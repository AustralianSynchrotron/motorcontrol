

%Module qcamotor

%Import QtCore/QtCoremod.sip



class QCaMotor : public QObject {

%TypeHeaderCode
#include "qcamotor.h"
%End


public:

  enum SpmgMode {
    STOP=0,
    PAUSE=1,
    MOVE=2,
    GO=3
  };

  enum SuMode {
    USE=0,
    SET=1
  };

  enum OffMode {
    VARIABLE=0,
    FROZEN=1
  };

  enum Direction {
    POSITIVE=0,
    NEGATIVE=1
  };

  enum MotionExit {
    IMMIDIATELY=0,
    CONFIRMATION=1,
    STARTED=2,
    ACCELERATED=3,
    STOPPED=5
  };

  QCaMotor(QObject *parent /TransferThis/ =0);
  QCaMotor(const QString & pv, QObject *parent /TransferThis/ =0);

  ~QCaMotor();

  void wait_stop();

  void wait_start();

  void saveConfiguration(const QString & fileName) const;
  void loadConfiguration(const QString & fileName);

  const QString & getPv() const;
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
  bool isConnected() const;
  bool isMoving() const;
  bool getUseReadback() const;
  bool getUseEncoder() const;
  double getBacklash() const;
  SpmgMode getSpmgMode() const;
  bool getPower() const;
  bool getPowerConnection() const;
  bool isWired() const;

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
  void goLimit(int direction, MotionExit ex=IMMIDIATELY);
  void goStep(int direction, MotionExit ex=IMMIDIATELY);
  void goHome(int direction, MotionExit ex=IMMIDIATELY);
  void goRelative(double dist, MotionExit ex=IMMIDIATELY);
  void jog(bool jg, int direction);
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
  void stop(MotionExit ex=IMMIDIATELY);
  void setUseReadback(bool use);
  void setUseEncoder(bool use);
  void setBacklash(double dist);
  void setSpmgMode(SpmgMode mode);
  void setPower(bool pwr);
  void printError(const QString & err) const;

signals:

  void changedPv(QString pvName=QString());
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
  void changedConnected(bool con);
  void changedMoving(bool mov);
  void stopped();
  void changedUseReadback(bool status);
  void changedUseEncoder(bool status);
  void changedBacklash(double dist);
  void changedSpmgMode(QCaMotor::SpmgMode mode);
  void changedPower(bool pwr);
  void changedPowerConnection(bool status);
  void changedWired(bool status);
  void error(QString msg);

};
