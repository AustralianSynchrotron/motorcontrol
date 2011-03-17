#include "qcamotorgui-additional.h"

void QMDoubleSpinBox::focusInEvent(QFocusEvent * event){
  QDoubleSpinBox::focusInEvent(event);
  selectAll();
  oldvalue = value();
}


void QMDoubleSpinBox::focusOutEvent(QFocusEvent * event){
  QDoubleSpinBox::focusOutEvent(event);
  emit escaped();
}

void QMDoubleSpinBox::keyPressEvent( QKeyEvent * event ){
  QDoubleSpinBox::keyPressEvent(event);
  int key = event->key();
  if ( key == Qt::Key_Enter || key == Qt::Key_Return )
    emit valueEdited(oldvalue=value());
  else if ( key == Qt::Key_Escape )
    emit escaped();
}


QMDoubleSpinBox::QMDoubleSpinBox(QWidget * parent) :
  QDoubleSpinBox(parent)
{
  connect(this, SIGNAL(valueChanged(double)), SLOT(recalculateStep(double)));
  connect(this, SIGNAL(escaped()), SLOT(restore()));
  recalculateStep(value());
}

/// Reduces the meaningless zeros from the string representing a double value.
/// @param value value to represent as the string
/// @return String representation of the value.
QString QMDoubleSpinBox::textFromValue ( double value ) const {
  QString prn = QString::number(value, 'f', decimals());
  if (prn.contains('.')) {
    while (prn.endsWith('0'))
      prn.chop(1);
    if (prn.endsWith('.'))
      prn.chop(1);
  }
  return prn;
}

void QMDoubleSpinBox::recalculateStep(double val){
  int power;
  QString vals = QString::number(val,'e');
  power = vals.remove(0, vals.indexOf('e') + 1).toInt();
  if ( -power >= decimals() || val == 0.0 )
    power = -decimals() + 1 ;
  double step = pow(10, power - 1);
  if ( step != singleStep() )
    setSingleStep(step);
}



void QMSpinBox::focusInEvent(QFocusEvent * event){
  QSpinBox::focusInEvent(event);
  selectAll();
  oldvalue = value();
}

void QMSpinBox::focusOutEvent(QFocusEvent * event){
  QSpinBox::focusOutEvent(event);
  emit escaped();
}

void QMSpinBox::keyPressEvent( QKeyEvent * event ){
  QSpinBox::keyPressEvent(event);
  int key = event->key();
  if ( key == Qt::Key_Enter || key == Qt::Key_Return )
    emit valueEdited(oldvalue=value());
  else if ( key == Qt::Key_Escape )
    emit escaped();
}


QMSpinBox::QMSpinBox(QWidget * parent)  :
  QSpinBox(parent)
{
  connect(this, SIGNAL(escaped()), SLOT(restore()));
}







void QMComboBox::focusInEvent(QFocusEvent * event){
  QComboBox::focusInEvent(event);
  oldvalue = currentIndex();
}

void QMComboBox::focusOutEvent(QFocusEvent * event){
  QComboBox::focusOutEvent(event);
  emit escaped();
}

void QMComboBox::keyPressEvent( QKeyEvent * event ){
  QComboBox::keyPressEvent(event);
  int key = event->key();
  if ( key == Qt::Key_Enter || key == Qt::Key_Return ) {
    emit textEdited(currentText());
    oldvalue = currentIndex();
  } else if ( key == Qt::Key_Escape )
    emit escaped();
}

QMComboBox::QMComboBox(QWidget * parent) :
  QComboBox(parent)
{
  connect(this, SIGNAL(escaped()), SLOT(restore()));
}


void QMComboBox::setIndexFromText(const QString & text) {
  int idx = findText(text);
  if (idx >= 0)
    setCurrentIndex( findText(text) );
}







StepValidator::StepValidator(QWidget * parent)  :
  QValidator(parent),
  last(),
  min(-2147483647),
  max(2147483647)
{}

QValidator::State StepValidator::validate ( QString & input, int &) const {
  bool okst;
  double ndouble = input.toDouble(&okst);
  return ( input == "limit" || input == "jog" ||
           ( okst && ndouble >= min && ndouble <= max ) )
    ?  Acceptable  :  Intermediate ;
}




void QMultiComboBox::keyPressEvent( QKeyEvent * event ) {
  QComboBox::keyPressEvent(event);
  int key = event->key();
  if ( key == Qt::Key_Enter || key == Qt::Key_Return )
    emit textEdited(currentText());
  else if ( key == Qt::Key_Escape )
    emit escaped();
}

void QMultiComboBox::focusInEvent(QFocusEvent * event){
  QComboBox::focusInEvent(event);
  stepValidator->setLast(currentText());
}


QMultiComboBox:: QMultiComboBox(QWidget * parent)
  : QComboBox(parent),
  stepValidator(new StepValidator(this))
{
  // Direct call to the setValidator(stepValidator) does not work
  // here because the construction has to be completed in prior.
  QTimer::singleShot(0, this, SLOT(fixme()));
}