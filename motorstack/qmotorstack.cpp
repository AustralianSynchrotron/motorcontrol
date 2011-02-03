#include "qmotorstack.h"

QMotorStack::QMotorStack(const QString & _motorsFile, QWidget *parent) :
    QWidget(parent),
    motorsFile  (  _motorsFile.isEmpty()  ?
                   QString()  :  QString(getenv("HOME")) + "/." + _motorsFile ),
    ui(new Ui::MotorStack)
{
  //QTimer::singleShot(0, this, SLOT(initialize()));
  initialize();
}


QMotorStack::QMotorStack(QWidget *parent) :
    QWidget(parent),
    motorsFile(),
    ui(new Ui::MotorStack)
{
  //QTimer::singleShot(0, this, SLOT(initialize()));
  initialize();
}


QMotorStack::~QMotorStack() {
  motorsFile.close();
  foreach(MotBut motor, motors) {
    delete motor.first;
    delete motor.second;
  }
  delete ui;
}


void QMotorStack::initialize() {

  ui->setupUi(this);
  connect(ui->add, SIGNAL(clicked()), this, SLOT(addMotor()));

  if ( motorsFile.open(QIODevice::ReadWrite | QIODevice::Text) &&
       motorsFile.isReadable() )
    while (!motorsFile.atEnd()) {
    QByteArray line = motorsFile.readLine();
    addMotor(line.trimmed(), false, true);
  }
  if ( ! motorsFile.isWritable() )
    motorsFile.close();

}


void QMotorStack::constructLayout() {
  QStringList list;
  foreach(MotBut motor, motors){
    list << motor.first->getPv();
    int position = motors.indexOf(motor);
    ui->scrollLayout->addWidget(motor.second, position, 0);
    motor.first->positionInLayout(ui->scrollLayout, position, 1);
  }
  update();
}


void QMotorStack::upMotor(interbutt * button){

  int mIndex = indexOf(button);
  if (mIndex<1)
    return;
  motors.swap(mIndex,mIndex-1);

  QPoint mouseCursor = button->mapFromGlobal(QCursor::pos());
  constructLayout();
  // Is it a Qt bug? The repaint() does not do the job;
  button->setVisible(false);
  button->setVisible(true);
  //button->repaint();
  QCursor::setPos(button->mapToGlobal(mouseCursor));

  updateMotorsFile();

}

void QMotorStack::downMotor(interbutt * button){

  int mIndex = indexOf(button);
  if (mIndex<0 || mIndex >= motors.size() - 1)
    return;
  motors.swap(mIndex,mIndex+1);

  QPoint mouseCursor = button->mapFromGlobal(QCursor::pos());
  constructLayout();
  // Is it a Qt bug? The repaint() does not do the job;
  button->setVisible(false);
  button->setVisible(true);
  //button->repaint(;)
  QCursor::setPos(button->mapToGlobal(mouseCursor));

  updateMotorsFile();

}

void QMotorStack::addMotor(const QString & presetpv, bool lock, bool noFileSave){

  QCaMotorGUI * motor = new QCaMotorGUI(this);
  motor->setPv(presetpv);

  interbutt * button = new interbutt(ui->scrollAreaWidgetContents);
  connect(button, SIGNAL(remove(interbutt*)), this, SLOT(removeMotor(interbutt*)));
  connect(button, SIGNAL(up(interbutt*)), this, SLOT(upMotor(interbutt*)));
  connect(button, SIGNAL(down(interbutt*)), this, SLOT(downMotor(interbutt*)));

  motors << MotBut(motor,button);

  if (lock) {
    motor->lock(true);
    button->setVisible(false);
  } else
    connect( motor, SIGNAL(changedPv(QString)), this, SLOT(updateMotorsFile()));

  constructLayout();
  if ( ! noFileSave )
    updateMotorsFile();

}

void QMotorStack::removeMotor(interbutt * button){

  int mIndex = indexOf(button);
  if (mIndex<0)
    return;

  delete motors[mIndex].first;
  delete motors[mIndex].second;
  motors.removeAt(mIndex);

  constructLayout();
  updateMotorsFile();

}


void QMotorStack::clear(){
  foreach(MotBut motor, motors)
    removeMotor(motor.second);
}


QList < const QCaMotor * > QMotorStack::motorList() const {
  QList < const QCaMotor * > list;
  foreach(MotBut motor, motors)
    list << motor.first;
  return list;
}


void QMotorStack::updateMotorsFile() {
  if ( ! motorsFile.isOpen() )
    return;
  motorsFile.reset();
  motorsFile.resize(0);
  foreach (MotBut motor, motors)
    motorsFile.write( ( motor.first->getPv() + "\n" ).toAscii());
  motorsFile.flush();
}


int QMotorStack::indexOf(interbutt* but) {
  foreach(MotBut motor, motors)
    if (motor.second == but)
      return motors.indexOf(motor);
  return -1;
}

int QMotorStack::indexOf(QCaMotorGUI* mot) {
  foreach(MotBut motor, motors)
    if (motor.first == mot)
      return motors.indexOf(motor);
  return -1;
}


void QMotorStack::lock(bool lck) {
  foreach(MotBut motor, motors)
    motor.second->setVisible(!lck);
  ui->add->setVisible(!lck);
}
