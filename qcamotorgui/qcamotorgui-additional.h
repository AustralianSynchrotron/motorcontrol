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

#include <math.h>

/// Widget which modifies the behaviour of the QDoubleSpinBox.
///
/// The modifications:
/// 1) Setting new value must be confirmed with the press of the Enter key.
///    If the spinbox loses the focus without confirmation, the previous value
///    is restored.
/// 2) The meaningless zeros after the decimal point are erased (f.e. 0.0300 is reduced to 0.03).
/// 3) Step of the spinbox is recalculated from the current value as 1/10 of the most significant
///    order.
///
class QMDoubleSpinBox : public QDoubleSpinBox {
  Q_OBJECT;
private:

  /// Stores the value in the spinbox while the new value is being edited.
  /// Needed to restore the old value if the new one was not confirmed with the
  /// Enter press.
  double oldvalue;

  /// Reimplements the QDoubleSpinBox::focusInEvent().
  /// Updates the ::oldvalue and selects the text in the edit line.
  /// @param event focusing event.
  void focusInEvent(QFocusEvent * event);

  /// Reimplements the QDoubleSpinBox::focusOutEvent().
  /// @param event focusing event.
  void focusOutEvent(QFocusEvent * event);

  /// \brief Reimplements the QDoubleSpinBox::keyPressEvent().
  ///
  /// Updates the ::oldvalue with the edited on Enter pressed,
  /// escapes on Escape pressed.
  ///
  /// @param event key press event.
  ///
  void keyPressEvent( QKeyEvent * event );

public:

  /// Constructor
  /// @param paren object's parent.
  QMDoubleSpinBox(QWidget * parent = 0);

  /// Reduces the meaningless zeros from the string representing a double value.
  /// @param value value to represent as the string
  /// @return String representation of the value.
  QString textFromValue ( double value ) const ;

signals:

  /// Emitted on the confirmed value change.
  /// @param double new value
  void valueEdited(double);

  /// Emitted when the focus is lost or Escape pressed.
  void escaped();

public slots:

  /// Slot made from the QDoubleSpinBox::setMinimum().
  /// @param min new minimum.
  inline void setMin(double min) {setMinimum(min);}

  /// Slot made from the QDoubleSpinBox::setMaximum().
  /// @param max new maximum.
  inline void setMax(double max) {setMaximum(max);}

  /// Slot made from the QDoubleSpinBox::setDecimals().
  /// @param prec new precision.
  inline void setPrec(int prec) {setDecimals(prec);}

private slots:

  /// Calculates and sets new single step of the spinbox:
  /// 1/10 of the current value's most significant order.
  /// @param val current value of the spinbox.
  void recalculateStep(double val);

  /// Restores the ::oldvalue (on escape).
  inline void restore() { setValue(oldvalue); }

};



/// Widget which modifies the behaviour of the QSpinBox.
///
/// Setting new value must be confirmed with the press of the Enter key.
/// If the spinbox loses the focus without confirmation, the previous value
/// is restored.
///
class QMSpinBox : public QSpinBox {
  Q_OBJECT;
private:

  /// Stores the value in the spinbox while the new value is being edited.
  /// Needed to restore the old value if the new one was not confirmed with the
  /// Enter press.
  int oldvalue;

  /// Reimplements the QSpinBox::focusInEvent().
  /// Updates the ::oldvalue and selects the text in the edit line.
  /// @param event focusing event.
  void focusInEvent(QFocusEvent * event);

  /// Reimplements the QSpinBox::focusOutEvent().
  /// @param event focusing event.
  void focusOutEvent(QFocusEvent * event);

  /// \brief Reimplements the QSpinBox::keyPressEvent().
  ///
  /// Updates the ::oldvalue with the edited on Enter pressed,
  /// escapes on Escape pressed.
  ///
  /// @param event key press event.
  ///
  void keyPressEvent( QKeyEvent * event );

public:

  /// Constructor
  /// @param paren object's parent.
  QMSpinBox(QWidget * parent = 0);

signals:

  /// Emitted on the confirmed value change.
  /// @param double new value
  void valueEdited(int);

  /// Emitted when the focus is lost or Escape pressed.
  void escaped();

public slots:

  /// Slot made from the QSpinBox::setMinimum().
  /// @param min new minimum.
  inline void setMin(int min) {setMinimum(min);}

  /// Slot made from the QSpinBox::setMaximum().
  /// @param max new maximum.
  inline void setMax(int max) {setMaximum(max);}

private slots:

  /// Restores the ::oldvalue (on escape).
  inline void restore() {setValue(oldvalue);}

};






/// Widget which modifies the behaviour of the QComboBox.
///
/// Setting new value must be confirmed with the press of the Enter key.
/// If the widget loses the focus without confirmation, the previous value
/// is restored.
///
class QMComboBox : public QComboBox {
  Q_OBJECT;

private:

  /// Stores the value in the spinbox while the new value is being edited.
  /// Needed to restore the old value if the new one was not confirmed with the
  /// Enter press.
  int oldvalue;

  /// Reimplements the QComboBox::focusInEvent().
  /// Updates the ::oldvalue and selects the text in the edit line.
  /// @param event focusing event.
  void focusInEvent(QFocusEvent * event);

  /// Reimplements the QComboBox::focusOutEvent().
  /// @param event focusing event.
  void focusOutEvent(QFocusEvent * event);

  /// \brief Reimplements the QComboBox::keyPressEvent().
  ///
  /// Updates the ::oldvalue with the edited on Enter pressed,
  /// escapes on Escape pressed.
  ///
  /// @param event key press event.
  ///
  void keyPressEvent( QKeyEvent * event );

public:

  /// Constructor
  /// @param paren object's parent.
  QMComboBox(QWidget * parent = 0);

signals:

  /// Emitted on the confirmed value change.
  /// @param double new value
  void textEdited(QString);

  /// Emitted when the focus is lost or Escape pressed.
  void escaped();

public slots:

  /// Slot made from the QComboBox::setCurrentIndex().
  /// @param text text to search in the combobox.
  void setIndexFromText(const QString & text);

private slots:

  /// Restores the ::oldvalue (on escape).
  inline void restore() { setCurrentIndex(oldvalue); }

};







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
class LineEdit : public QLineEdit
{
    Q_OBJECT;

private:
  QToolButton *clearButton; ///< button which clears the text

public:

  /// Constructor.
  /// @param parent object's parent.
  LineEdit(QWidget *parent)
    : QLineEdit(parent)
  {
    clearButton = new QToolButton(this);
    clearButton->setToolTip("Clear text");
    clearButton->setArrowType(Qt::LeftArrow);
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
  }

protected:

  /// Reimplemented resize event
  void resizeEvent(QResizeEvent *) {
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
  }

private slots:

  /// Shows/hides the button
  void updateCloseButton(const QString& text) {
    clearButton->setVisible(!text.isEmpty());
  }

};


#endif // QMSPINBOX_H
