#ifndef QMSPINBOX_H
#define QMSPINBOX_H


#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QLineEdit>
#include <QToolButton>
#include <QLabel>
#include <qtpvwidgets.h>
#include <QAction>
#include <QMenu>
#include <QPushButton>
#include <QDialog>
#include <math.h>
#include <qtpv.h>



/// Validator for the multifunctional combobox QMultiComboBox.
class StepValidator : public QValidator {

public:

  /// Constructor.
  /// @param parent Object's parent.
  StepValidator(QWidget * parent);

  /// The validating method.
  /// @param input String to be validated.
  /// @return same as QValidator::validate().
  QValidator::State validate ( QString & input, int &) const;

  /// Fixer.
  /// @param input string to be fixed.
  inline void fixup ( QString & input ) const { input = last; }

  /// Sets the ranges for the step.
  /// @param _m minimum
  /// @param _M maximum
  inline void setRange(double _m, double _M){min = _m; max = _M;}

  /// Sets the ::last
  /// @param text new value
  inline void setLast(const QString & text){last=text;}

private:

  QString last;                 ///< Last correct value.
  double min;                   ///< Minimum allowed step.
  double max;                   ///< Maximum allowed step.

};



/// Widget implementing the multifunctional combobox for the
/// Step/Drive widget in the motor's main widget.
///
/// Features of the widget:
/// 1) Setting new value must be confirmed with the press of the Enter key.
///    If the widget loses the focus without confirmation, the previous value
///    is restored.
/// 2) The combobox can be used either to enter a double number to set the motor
///    step or the drive mode ( go-to-limit / go-by-step / go-relatively )
///
class QMultiComboBox : public QComboBox {

  Q_OBJECT;

private:

  /// \brief Reimplements the QComboBox::keyPressEvent().
  ///
  /// Confirm the new step value on Enter pressed,
  /// escapes on Escape pressed.
  ///
  /// @param event key press event.
  ///
  void keyPressEvent( QKeyEvent * event );

  /// Reimplements the QComboBox::focusInEvent().
  /// Updates the last value.
  /// @param event focusing event.
  void focusInEvent(QFocusEvent * event);

  void focusOutEvent(QFocusEvent * event);

  StepValidator * stepValidator; ///< the validator

public:

  /// Constructor
  /// @param parent object's parent.
  QMultiComboBox(QWidget * parent = 0);

  /// Sets the allowed step range.
  /// @param min minimum
  /// @param max maximum
  inline void setRange(double min, double max){
    stepValidator->setRange(min,max);
  }

  void fixup();

signals:

  /// Emitted when the value has changed and was confirmed.
  /// @param QString new value.
  void textEdited(QString);

  /// Emitted when the focus is lost or Escape pressed.
  void escaped();

private slots:

  /// Just to fix the problem in the constructor (see coments in the constructor's body).
  inline void fixme(){ setValidator(stepValidator); }

};




/// QlineEdit with the "clear text" button imbedded into it.
class LineEdit : public QLineEdit {
    Q_OBJECT;

private:
  QToolButton *clearButton; ///< button which clears the text

public:
  /// Constructor.
  /// @param parent object's parent.
  LineEdit(QWidget *parent);

protected:
  /// Reimplemented resize event
  void resizeEvent(QResizeEvent *);

private slots:
  /// Shows/hides the button
  void updateCloseButton(const QString& text);
};




class QHistoryDSB : public QMDoubleSpinBox {
    Q_OBJECT;
    QMenu * history_menu;
    QAction * lastHistory;

protected:
  bool eventFilter(QObject *obj, QEvent *event);

public:
  QHistoryDSB(QWidget * parent = 0);

public slots:

  void rememberInHistory();

private slots:

  void execHistory();

};



namespace Ui {
  class MotorSelection;
}


class FilterPVsProxyModel;


class KnownPVTable : public QAbstractTableModel {
  Q_OBJECT;
private:
  static const QString pvListBaseName;
  QList <QEpicsPv*> knownPVs;   ///< List of the motors' description fields.
  QModelIndex indexOf(QEpicsPv* pv) const;
public:
  KnownPVTable(QObject * parent);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QModelIndex addPv(const QString & newPv);
  QList<QModelIndex> addPv(const QStringList & newPvs);
private slots:
  void updateData();            ///< Slot used to catch the data change.
};




// here to create and poplulate new instance of the MotorSelection on start
class MotorSelectionAutoPopulator : public QObject {
  Q_OBJECT;
public:
  MotorSelectionAutoPopulator();
public slots:
  void updateMe();
};



class MotorSelection : public QDialog {
  Q_OBJECT;
public:
  MotorSelection(QWidget * parent=0);
  void limitSelection(const QStringList & acceptedPvs = QStringList(), bool selectRestricted=false);
  void setSingleSelection(bool sng=true);
  QStringList selected();
private:
  Ui::MotorSelection * ui;
  KnownPVTable * knownPVs;
  FilterPVsProxyModel *proxyModel;
  bool isSingleSelection() const;
private slots:
  void filterPV(const QString & _text);
  void clickPV(const QModelIndex & index);
  void doubleClickPV(const QModelIndex & index);
  void pvFromSearch();
  void selectInvert();
};





#endif // QMSPINBOX_H
