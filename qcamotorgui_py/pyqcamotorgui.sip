%Module pyqcamotorgui

%Import pyqcamotor.sip
%Import QtWidgets/QtWidgetsmod.sip


class QCaMotorGUI : public QWidget {

%TypeHeaderCode
#include "qcamotorgui.h"
%End


public:

  const QString pvListBaseName;
  const QString configsSearchBaseDir;
  const QString configsExt;

  enum ViewMode {
    SETPV=0,
    MINI=1,
    COMFO=2,
    CONFIG=3,
    EPICS=4
  };

  QCaMotorGUI(QWidget *parent /TransferThis/ =0);
  QCaMotorGUI(const QString & pv, QWidget *parent /TransferThis/ =0);

  QCaMotor * motor();
  void lock(bool lck);
  QPushButton * setupButton();
  QDoubleSpinBox * currentPosition(bool readOnly);

  void setViewMode(ViewMode mode);
  void showSetup(bool shown=true);
  void showPvSetup(bool shown=true);

signals:
  void ioPositionChanged(QString);

};
