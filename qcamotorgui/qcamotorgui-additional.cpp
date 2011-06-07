#include "qcamotorgui-additional.h"
#include <QHBoxLayout>





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
