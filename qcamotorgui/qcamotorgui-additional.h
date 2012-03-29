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

#include <math.h>



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
