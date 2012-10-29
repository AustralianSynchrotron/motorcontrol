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
  return ( input == "jog" ||
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

void QMultiComboBox::fixup() {
  QString fixstring = currentText();
  validator()->fixup(fixstring);
  int idx = findText(fixstring);
  if (idx >= 0)
    setCurrentIndex(idx);
}



QMultiComboBox::QMultiComboBox(QWidget * parent)
  : QComboBox(parent),
  stepValidator(new StepValidator(this))
{
  // Direct call to the setValidator(stepValidator) does not work
  // here because the construction has to be completed in prior.
  QTimer::singleShot(0, this, SLOT(fixme()));
}



LineEdit::LineEdit(QWidget *parent)
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

void LineEdit::resizeEvent(QResizeEvent *) {
  QSize sz = clearButton->sizeHint();
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  clearButton->move(rect().right() - frameWidth - sz.width(),
                    (rect().bottom() + 1 - sz.height())/2);
}

void LineEdit::updateCloseButton(const QString& text) {
  clearButton->setVisible(!text.isEmpty());
}





QHistoryDSB::QHistoryDSB(QWidget * parent) :
    QMDoubleSpinBox(parent),
    history_menu(new QMenu(this)),
    rememberMe(new QAction("Record current in history", this))
{
    lineEdit()->installEventFilter(this);
    history_menu->setDisabled(true);
    connect(rememberMe, SIGNAL(triggered()), SLOT(rememberInHistory()));
}


bool QHistoryDSB::eventFilter(QObject *obj, QEvent *event) {
    QChildEvent * chev = dynamic_cast<QChildEvent*>(event);
    QMenu * menu=0;
    if ( chev && chev->polished() && (menu = dynamic_cast<QMenu*>(chev->child())) ) {
        QAction * action = new QAction(QString("History"), menu);
        action->setMenu(history_menu);
        QAction * fact = menu->actions().value(0);
        menu->insertAction(fact, action);
        menu->insertAction(fact, rememberMe);
        menu->insertSeparator(fact);
    }
    return QDoubleSpinBox::eventFilter(obj,event);
}

void QHistoryDSB::rememberInHistory() {
    history_menu->setEnabled(true);
    QAction * exists = history.key(value());
    if ( exists ) {
        history.remove(exists);
        history_menu->removeAction(exists);
    }
    QAction * act = new QAction(QString::number(value()), history_menu);
    connect(act, SIGNAL(triggered()), SLOT(execHistory()));
    history[act] = value();
    history_menu->insertAction(lastHistory, act);
    lastHistory = act;
  }

void QHistoryDSB::execHistory() {
    QAction * act = dynamic_cast<QAction*> (sender());
    if (act && history.contains(act)) {
        setValue(history[act]);
        emit valueEdited(history[act]);
    }
}









