%Module pyqmotorstack

%Import pyqcamotorgui.sip
%Import QtWidgets/QtWidgetsmod.sip



class QMotorStack : public QWidget {
  %TypeHeaderCode
  #include "qmotorstack.h"
  %End

public:

  QMotorStack(const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(const QStringList & _motorsList, const QString & _motorsFile=QString(), QWidget *parent = 0);
  QMotorStack(const QStringList & _motorsList, QWidget *parent);
  QMotorStack(QWidget *parent);

  bool isLocked();
  QList < QCaMotorGUI * > motorList() const;
  QStringList nameList() const;

public slots:

  void lock(bool lck);
  void showGeneral(bool showall=true);
  QCaMotorGUI * addMotor(const QString & presetpv = "", bool lock = false, bool noFileSave = false);
  void addMotor(QCaMotorGUI * motor, bool noFileSave = false);
  QCaMotorGUI * addMotor(QCaMotor * motor, bool lock = false, bool noFileSave = false);
  void addMotor(const QList<QCaMotor*> & motorList, bool lock = false, bool noFileSave = false);
  void addMotor(const QList<QCaMotorGUI*> & motorList, bool noFileSave = false);
  void removeMotor(QCaMotorGUI * motor);
  void clear();
  void saveConfiguration(const QString & fileName);
  void loadConfiguration(const QString & fileName);

signals:

  void listChanged();

};

