#include "qcamotorgui.h"

#include <math.h>
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QStringListModel>
#include <QClipboard>
#include <QMessageBox>



KnownPVTable::KnownPVTable(const QStringList &list, QObject *parent)
  : QAbstractTableModel(parent){
  foreach(QString pvname, list) {
     QEpicsPv * pv = new QEpicsPv(pvname+".DESC", this) ;
     connect(pv, SIGNAL(valueChanged(QVariant)),
             SLOT(updateData()));
     knownPVs << pv;
  }
}

QModelIndex KnownPVTable::indexOf(QEpicsPv* pv) const {
  return knownPVs.contains(pv) ?
      createIndex(knownPVs.indexOf(pv), 1) :
      QModelIndex();
}

void KnownPVTable::updateData() {
  QModelIndex midx = indexOf( (QEpicsPv*) sender() );
  if ( midx.isValid() )
    emit (dataChanged(midx, midx));
}


int KnownPVTable::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return knownPVs.size();
}

int KnownPVTable::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 2;
}

QVariant KnownPVTable::data(const QModelIndex &index, int role) const {
  if ( ! index.isValid() ||
       index.row() >= knownPVs.size() || index.row() < 0)
    return QVariant();
  QString pv = knownPVs.at(index.row())->pv();
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0: return pv.remove(".DESC");
    case 1: return knownPVs.at(index.row())->get();
    default: return QVariant();
    }
  } else if (role == Qt::UserRole) {
    return pv.remove(".DESC");
  } else {
    return QVariant();
  }

}

QVariant KnownPVTable::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal )
    return QVariant();
  switch (section) {
  case 0: return QString("PV");
  case 1: return QString("Description");
  default: return QVariant();
  }
}










bool KeyPressEater::eventFilter(QObject *obj, QEvent *event) {

  if ( event->type() != QEvent::KeyPress &&
       event->type() != QEvent::KeyRelease &&
       event->type() != QEvent::ShortcutOverride )
    return QObject::eventFilter(obj, event);

  QLineEdit * search = parent()->findChild<QLineEdit*>("search");
  QTableView * pvTable = parent()->findChild<QTableView*>("pvTable");

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
  int key = keyEvent->key();
  QString text = keyEvent->text();


  if ( key == Qt::Key_Enter ||
       key == Qt::Key_Return ||
       key == Qt::Key_Escape ||
       key == Qt::Key_Tab )
    return QObject::eventFilter(obj, event);
  else if ( pvTable->hasFocus() &&
            ( ! text.isEmpty() ||
              key == Qt::Key_Left ||
              key == Qt::Key_Right ) ) {
    search->setFocus();
    QString stext = search->text();
    if (key== Qt::Key_Backspace)
      search->setText( stext.remove( stext.length()-1, 1) );
    else if ( ! text.isEmpty() ) {
      search->setText( stext + text );
    }
  } else if ( search->hasFocus() &&
              ( key == Qt::Key_Down ||
                key == Qt::Key_Up ) )
    pvTable->setFocus();

  return QObject::eventFilter(obj, event);

}








bool QCaMotorGUI::inited=false;
QMap<QString,QString> QCaMotorGUI::knownConfigs;
KnownPVTable * QCaMotorGUI::knownPVs = 0;
const QString QCaMotorGUI::configsSearchBaseDir="motormx";
const QString QCaMotorGUI::configsExt="motorConfig";
const QString QCaMotorGUI::pvListBaseName = "listOfKnownMotorPVs.txt";


QCaMotorGUI::QCaMotorGUI(QWidget *parent) :
  QCaMotor(parent),
  theWidget(new QWidget),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(new QSortFilterProxyModel(this))
{
  init();
}

QCaMotorGUI::QCaMotorGUI(const QString & pv, QWidget *parent) :
  QCaMotor(pv, parent),
  theWidget(new QWidget),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(new QSortFilterProxyModel(this))
{
  init();
}

QCaMotorGUI::QCaMotorGUI(QCaMotor & base, QWidget *parent) :
  theWidget(new QWidget),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(new QSortFilterProxyModel(this))
{
  init();
}



QCaMotorGUI::~QCaMotorGUI() {
  delete pasteCfgAction;
  delete mUi;
  delete sUi;
  delete rUi;
  delete pUi;
  delete pvDialog;
  delete setupDialog;
  delete relativeDialog;
  delete theWidget;
}



void QCaMotorGUI::init() {

  QCaMotorGUI::static_init();

  locked=false;

  mUi->setupUi(theWidget);
  sUi->setupUi(setupDialog);
  rUi->setupUi(relativeDialog);
  pUi->setupUi(pvDialog);

  pvDialog->setWindowTitle("Choose motor PV");
  setupDialog->setWindowTitle("MotorMx, setup");
  relativeDialog->setWindowTitle("Move relatively");

  proxyModel->setSourceModel(knownPVs);
  proxyModel->setDynamicSortFilter(true);
  proxyModel->setFilterKeyColumn(-1);
  proxyModel->sort(0, Qt::AscendingOrder);
  pUi->pvTable->setModel(proxyModel);
  pUi->pvTable->resizeColumnsToContents();

  KeyPressEater * keater = new KeyPressEater(pvDialog);
  pvDialog->installEventFilter(keater);

  sUi->hidden->hide();
  sUi->description->setText(mUi->setup->text());

  sUi->spmgGroup->setId(sUi->Spmg, STOP);
  sUi->spmgGroup->setId(sUi->sPmg, PAUSE);
  sUi->spmgGroup->setId(sUi->spMg, MOVE);
  sUi->spmgGroup->setId(sUi->spmG, GO);

  sUi->setGroup->setId(sUi->useMode, USE);
  sUi->setGroup->setId(sUi->setMode, SET);

  sUi->offGroup->setId(sUi->offsetVar, VARIABLE);
  sUi->offGroup->setId(sUi->offsetFrz, FROZEN);

  sUi->dirGroup->setId(sUi->dirPos, POSITIVE);
  sUi->dirGroup->setId(sUi->dirNeg, NEGATIVE);

  sUi->loadConfig->addItems(knownConfigs.keys());

  //
  // Connect GUI Actions
  //

  connect(pUi->search, SIGNAL(textChanged(QString)),
          SLOT(filterPV(QString)));
  connect(pUi->search, SIGNAL(returnPressed()),
          SLOT(pvFromSearch()));
  connect(pUi->pvTable, SIGNAL(activated(QModelIndex)),
          SLOT(choosePV(QModelIndex)));

  connect(mUi->userPosition, SIGNAL(valueChanged(QString)),
          SIGNAL(ioPositionChanged(QString)));
  connect(mUi->setup, SIGNAL(clicked()),
          SLOT(onSetupClicked()) );


  QAction * action;

  action = new QAction("Copy PV", mUi->setup);
  mUi->setup->addAction(action);
  connect(action, SIGNAL(triggered()), SLOT(copyPV()));

  action = new QAction("Copy description", mUi->setup);
  mUi->setup->addAction(action);
  connect(action, SIGNAL(triggered()), SLOT(copyDescription()));

  action = new QAction("Copy position", mUi->setup);
  mUi->setup->addAction(action);
  connect(action, SIGNAL(triggered()), SLOT(copyPosition()));

  action = new QAction("Copy configuration", mUi->setup);
  mUi->setup->addAction(action);
  connect(action, SIGNAL(triggered()), SLOT(copyConfiguration()));

  pasteCfgAction = new QAction("Paste configuration", mUi->setup);
  pasteCfgAction->setEnabled(false);
  mUi->setup->addAction(pasteCfgAction);
  connect(pasteCfgAction, SIGNAL(triggered()), SLOT(pasteConfiguration()));

  action = new QAction("Set PV", mUi->setup);
  mUi->setup->addAction(action);
  connect(action, SIGNAL(triggered()), pvDialog, SLOT(show()));


  connect(rUi->goRelative, SIGNAL(valueEdited(double)),
          SLOT(goRelative(double)));

  connect(mUi->userPosition, SIGNAL(valueEdited(double)),
          SLOT(goUserPosition(double)));
  connect(mUi->step, SIGNAL(textEdited(QString)),
          SLOT(setStep(QString)));
  connect(mUi->step, SIGNAL(activated(QString)),
          SLOT(setStep(QString)));
  connect(mUi->stop, SIGNAL(clicked()),
          SLOT(pressStop()));
  connect(mUi->limitM, SIGNAL(clicked()),
          SLOT(goLimitM()));
  connect(mUi->limitP, SIGNAL(clicked()),
          SLOT(goLimitP()));
  connect(mUi->jogM, SIGNAL(pressed()),
          SLOT(jogMstart()));
  connect(mUi->jogM, SIGNAL(released()),
          SLOT(jogMstop()));
  connect(mUi->jogP, SIGNAL(pressed()),
          SLOT(jogPstart()));
  connect(mUi->jogP, SIGNAL(released()),
          SLOT(jogPstop()));
  connect(mUi->goM, SIGNAL(clicked()),
          SLOT(goStepM()));
  connect(mUi->goP, SIGNAL(clicked()),
          SLOT(goStepP()));
  connect(mUi->power, SIGNAL(clicked(bool)),
          SLOT(setPower(bool)));

  connect(sUi->pv, SIGNAL(clicked()),
          SLOT(copyPV()));
  connect(sUi->viewMode, SIGNAL(activated(int)),
          SLOT(setViewMode(int)));
  connect(sUi->loadConfig, SIGNAL(activated(QString)),
          SLOT(onLoad(QString)));
  connect(sUi->saveConfig, SIGNAL(clicked()),
          SLOT(onSave()));

  connect(sUi->description, SIGNAL(editingFinished(QString)),
          SLOT(setDescription(QString)));

  connect(sUi->power, SIGNAL(clicked(bool)),
          SLOT(setPower(bool)));
  connect(sUi->precision, SIGNAL(valueEdited(int)),
          SLOT(setPrecision(int)));
  connect(sUi->units, SIGNAL(textEdited(QString)),
          SLOT(setUnits(QString)));

  connect(sUi->spmgGroup, SIGNAL(buttonClicked(int)),
          SLOT(setSpmgMode(int)));

  connect(sUi->goLimitM, SIGNAL(clicked()),
          SLOT(goLimitM()));
  connect(sUi->goLimitP, SIGNAL(clicked()),
          SLOT(goLimitP()));
  connect(sUi->goM, SIGNAL(clicked()),
          SLOT(goStepM()));
  connect(sUi->goP, SIGNAL(clicked()),
          SLOT(goStepP()));
  connect(sUi->stepD10, SIGNAL(clicked()),
          SLOT(stepD10()));
  connect(sUi->stepD2, SIGNAL(clicked()),
          SLOT(stepD2()));
  connect(sUi->stepM2, SIGNAL(clicked()),
          SLOT(stepM2()));
  connect(sUi->stepM10, SIGNAL(clicked()),
          SLOT(stepM10()));
  connect(sUi->step, SIGNAL(valueEdited(double)),
          SLOT(setStep(double)));
  connect(sUi->jogM, SIGNAL(pressed()),
          SLOT(jogMstart()));
  connect(sUi->jogM, SIGNAL(released()),
          SLOT(jogMstop()));
  connect(sUi->jogP, SIGNAL(pressed()),
          SLOT(jogPstart()));
  connect(sUi->jogP, SIGNAL(released()),
          SLOT(jogPstop()));
  connect(sUi->stop, SIGNAL(clicked()),
          SLOT(pressStop()));

  connect(sUi->dialPosition, SIGNAL(valueEdited(double)),
          SLOT(setDialPosition(double)));
  connect(sUi->dialGoal, SIGNAL(valueEdited(double)),
          SLOT(goDialPosition(double)));
  connect(sUi->limitLoDial, SIGNAL(valueEdited(double)),
          SLOT(setDialLoLimit(double)));
  connect(sUi->limitHiDial, SIGNAL(valueEdited(double)),
          SLOT(setDialHiLimit(double)));

  connect(sUi->readbackResolution, SIGNAL(valueEdited(double)),
          SLOT(setReadbackResolution(double)));
  connect(sUi->encoderResolution, SIGNAL(valueEdited(double)),
          SLOT(setEncoderResolution(double)));
  connect(sUi->stepsPerRev, SIGNAL(valueEdited(int)),
          SLOT(setStepsPerRev(int)));
  connect(sUi->unitsPerStep, SIGNAL(valueEdited(double)),
          SLOT(setMotorResolution(double)));
  connect(sUi->unitsPerRev, SIGNAL(valueEdited(double)),
          SLOT(setUnitsPerRev(double)));
  connect(sUi->unitsPerRevAndDir, SIGNAL(valueEdited(double)),
          SLOT(setUnitsPerRevAndDirection(double)));

  connect(sUi->useEncoder, SIGNAL(clicked(bool)),
          SLOT(setUseEncoder(bool)));
  connect(sUi->useReadback, SIGNAL(clicked(bool)),
          SLOT(setUseReadback(bool)));

  connect(sUi->offGroup, SIGNAL(buttonClicked(int)),
          SLOT(setOffsetMode(int)));
  connect(sUi->dirGroup, SIGNAL(buttonClicked(int)),
          SLOT(setDirection(int)));
  connect(sUi->setGroup, SIGNAL(buttonClicked(int)),
          SLOT(setSuMode(int)));

  connect(sUi->maximumSpeed, SIGNAL(valueEdited(double)),
          SLOT(setMaximumSpeed(double)));
  connect(sUi->speed, SIGNAL(valueEdited(double)),
          SLOT(setNormalSpeed(double)));
  connect(sUi->revSpeed, SIGNAL(valueEdited(double)),
          SLOT(setRevSpeed(double)));
  connect(sUi->backlashSpeed, SIGNAL(valueEdited(double)),
          SLOT(setBacklashSpeed(double)));
  connect(sUi->jogSpeed, SIGNAL(valueEdited(double)),
          SLOT(setJogSpeed(double)));
  connect(sUi->acceleration, SIGNAL(valueEdited(double)),
          SLOT(setAcceleration(double)));
  connect(sUi->backlashAcceleration, SIGNAL(valueEdited(double)),
          SLOT(setBacklashAcceleration(double)));
  connect(sUi->jogAcceleration, SIGNAL(valueEdited(double)),
          SLOT(setJogAcceleration(double)));
  connect(sUi->accelerationS, SIGNAL(valueEdited(double)),
          SLOT(setAccelerationS(double)));
  connect(sUi->speedS, SIGNAL(valueEdited(double)),
          SLOT(setSpeedS(double)));
  connect(sUi->equalizeSpeeds, SIGNAL(clicked()),
          SLOT(setSpeedS()));
  connect(sUi->equalizeAccelerations, SIGNAL(clicked()),
          SLOT(setAccelerationS()));

  connect(sUi->backlash, SIGNAL(valueEdited(double)),
          SLOT(setBacklash(double)));

  connect(sUi->userPosition, SIGNAL(valueEdited(double)),
          SLOT(setUserPosition(double)));
  connect(sUi->rawPosition, SIGNAL(valueEdited(double)),
          SLOT(setRawPosition(double)));
  connect(sUi->userVarGoal, SIGNAL(valueEdited(double)),
          SLOT(goUserPosition(double)));
  connect(sUi->userGoal, SIGNAL(valueEdited(double)),
          SLOT(goUserPosition(double)));
  connect(sUi->rawGoal, SIGNAL(valueEdited(double)),
          SLOT(goRawPosition(double)));
  connect(sUi->callRelative, SIGNAL(clicked()),
          relativeDialog, SLOT(show()) );
  connect(sUi->offset, SIGNAL(valueEdited(double)),
          SLOT(setOffset(double)));
  connect(sUi->limitLo, SIGNAL(valueEdited(double)),
          SLOT(setUserLoLimit(double)));
  connect(sUi->limitHi, SIGNAL(valueEdited(double)),
          SLOT(setUserHiLimit(double)));

  //
  // Connect Motor Signals
  //

  connect(this, SIGNAL(changedPv(QString)),
          SLOT(updatePv(QString)));

  connect(this, SIGNAL(changedRawPosition(double)),
          sUi->rawPosition, SLOT(setValue(double)));

  connect(this, SIGNAL(changedUserGoal(double)),
          sUi->userGoal, SLOT(setValue(double)));
  connect(this, SIGNAL(changedDialGoal(double)),
          sUi->dialGoal, SLOT(setValue(double)));
  connect(this, SIGNAL(changedRawGoal(double)),
          sUi->rawGoal, SLOT(setValue(double)));

  connect(this, SIGNAL(changedOffset(double)),
          sUi->offset, SLOT(setValue(double)));

  connect(this, SIGNAL(changedHiLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedLoLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));

  connect(this, SIGNAL(changedMotorResolution(double)),
          sUi->unitsPerStep, SLOT(setValue(double)));
  connect(this, SIGNAL(changedReadbackResolution(double)),
          sUi->readbackResolution, SLOT(setValue(double)));
  connect(this, SIGNAL(changedEncoderResolution(double)),
          sUi->encoderResolution, SLOT(setValue(double)));
  connect(this, SIGNAL(changedStepsPerRev(int)),
          sUi->stepsPerRev, SLOT(setValue(int)));

  connect(this, SIGNAL(changedRevSpeed(double)),
          sUi->revSpeed, SLOT(setValue(double)));

  connect(this, SIGNAL(changedUseReadback(bool)),
          sUi->useReadback, SLOT(setChecked(bool)));
  connect(this, SIGNAL(changedUseEncoder(bool)),
          sUi->useEncoder, SLOT(setChecked(bool)));

  setViewMode(COMFO);
  setupDialog->update();
  updatePower(getPower());
  updateWired(isWired());
  setStep();

}



void QCaMotorGUI::copyPV() {
  if ( ! getPv().isEmpty() )
    QApplication::clipboard()->setText(getPv());
}

void QCaMotorGUI::copyDescription() {
  if ( ! getDescription().isEmpty() )
    QApplication::clipboard()->setText(getDescription());
}

void QCaMotorGUI::copyPosition() {
  if ( isConnected() )
    QApplication::clipboard()->setText( QString::number(getUserPosition()) );
}

void QCaMotorGUI::copyConfiguration() {
  if ( ! isConnected() )
    QMessageBox::warning(0, "Warning!",
                         "Copying configuration of the disconnected motor.");
  QString cfg;
  QTextStream stream(&cfg);
  saveConfiguration(stream);
  QApplication::clipboard()->setText(cfg);
}

void QCaMotorGUI::pasteConfiguration() {
  if ( ! isConnected() ) {
    QMessageBox::warning(0, "Error",
                         "Cannot paste configuration because the motor is not connected.");
    return;
  }
  QString cfg = QApplication::clipboard()->text();
  QTextStream stream(&cfg);
  loadConfiguration(stream);
}

void QCaMotorGUI::filterPV(const QString & _text){
  proxyModel->setFilterRegExp( QRegExp(
      QString(".*%1.*").arg(_text), Qt::CaseInsensitive) );
}

void QCaMotorGUI::choosePV(const QModelIndex & index){
  pvDialog->hide();
  setPv(index.data(Qt::UserRole).toString());
}

void QCaMotorGUI::pvFromSearch(){
  pvDialog->hide();
  setPv(pUi->search->text());
  pUi->search->clear();
}

void QCaMotorGUI::updatePv(const QString & newpv){
  sUi->pv->setText(newpv);
  mUi->setup->disconnect();
  if (newpv.isEmpty()) {
    connect(mUi->setup, SIGNAL(clicked()),
            pvDialog, SLOT(show()) );
    updateDescription("SETUP");
    mUi->setup->setContextMenuPolicy(Qt::NoContextMenu);
  } else {
    connect(mUi->setup, SIGNAL(clicked()),
            setupDialog, SLOT(show()) );
    updateDescription(newpv);
    mUi->setup->setContextMenuPolicy(Qt::ActionsContextMenu);
  }
}



void QCaMotorGUI::lock(bool lck){
  locked = lck;
  pvDialog->hide();
}


void QCaMotorGUI::static_init() {

  if (inited)
    return;
  inited = true;

  // Known PVs

  // WARNING: PORTING ISSUE.
  QStringList fileNames;
  fileNames
    << "/etc/" + configsSearchBaseDir + "/" + pvListBaseName
    << QString(getenv("HOME")) + "/." + configsSearchBaseDir + "/" + pvListBaseName;

  QStringList readPVs;

  foreach(QString fileName, fileNames) {
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) && file.isReadable() ) {
      while (!file.atEnd()) {
        QByteArray line = file.readLine().trimmed();
        //line.chop(1);
        if ( ! line.isEmpty() )
          readPVs << line;
      }
      file.close();
    }
  }

  readPVs.removeDuplicates();

  knownPVs = new KnownPVTable(readPVs);


  // Known stage configurations.

  fileNames.clear();

  // WARNING: PORTING ISSUE.
  fileNames << "*."+configsExt;
  QDir dir;
  dir.setNameFilters(fileNames);
  fileNames.clear();

  dir.setPath( "/etc/"+configsSearchBaseDir );
  fileNames << dir.entryList(QDir::Files).replaceInStrings(QRegExp("^"), dir.path()+"/");
  dir.setPath( QString(getenv("HOME")) + "/." + configsSearchBaseDir );
  fileNames << dir.entryList(QDir::Files).replaceInStrings(QRegExp("^"), dir.path()+"/");

  foreach (const QString filename , fileNames) {
    if ( filename.endsWith("."+configsExt) ) {
      // WARNING: PORTING ISSUE.
      QString entry = filename.section('/',-1);
      entry.chop(configsExt.length()+1);
      knownConfigs[ entry ] = filename;
    }
  }

}



void QCaMotorGUI::onSetupClicked() {
  if ( getPv().isEmpty() )
    pvDialog->show();
  else
    setupDialog->show();
}




void QCaMotorGUI::onSave() {
  // WARNING: PORTING ISSUE.
  QString fileName = QFileDialog::getSaveFileName
                     (0, "Save configuration",
                      QDir::currentPath() + "/" + getDescription() + "." + configsExt,
                      "All files (*);;Motor configuration files (*." + configsExt + ")");
  saveConfiguration(fileName);
}

void QCaMotorGUI::onLoad(const QString & text) {
  QString fileName =  ( text == sUi->loadConfig->itemText(0) ) ?
        QFileDialog::getOpenFileName
        (0, "Load configuration", "",
         "Motor configuration files (*." + configsExt + ");;All files (*)") :
        knownConfigs[text];
  loadConfiguration(fileName);
}

void QCaMotorGUI::setStep(const QString & _text){
  QString text = _text.toLower();
  bool ok;
  double val = text.toDouble(&ok);
  if (text == "jog") {
    mUi->goM->setVisible(false);
    mUi->goP->setVisible(false);
    mUi->jogM->setVisible(true);
    mUi->jogP->setVisible(true);
    mUi->limitM->setVisible(false);
    mUi->limitP->setVisible(false);
  } else if (text == "relative") {
    relativeDialog->show();
  } else if (text == "limit") {
    mUi->goM->setVisible(false);
    mUi->goP->setVisible(false);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
    mUi->limitM->setVisible(true);
    mUi->limitP->setVisible(true);
  } else {
    if ( ok && val != getStep() )
      QCaMotor::setStep(val);
    mUi->goM->setVisible(true);
    mUi->goP->setVisible(true);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
    mUi->limitM->setVisible(false);
    mUi->limitP->setVisible(false);
  }
}


void QCaMotorGUI::setUnitsPerRevAndDirection(double res) {
  setUnitsPerRev(qAbs(res));
  setDirection( res < 0 ? NEGATIVE : POSITIVE );
}

void QCaMotorGUI::setSpeedS(double spd) {
  if (spd<=0.0)
    spd = sUi->speedS->value();
  setMaximumSpeed(spd);
  setJogSpeed(spd);
  setBacklashSpeed(spd);
  setNormalSpeed(spd);
}

void QCaMotorGUI::setAccelerationS(double acc) {
  if (acc<=0.0)
    acc = sUi->accelerationS->value();
  setJogAcceleration(acc);
  setBacklashAcceleration(acc);
  setAcceleration(acc);
}






void QCaMotorGUI::setViewMode(ViewMode mode){

  if ( mode == SETPV ) {
    if (!locked)
      pvDialog->show();
    sUi->viewMode->setCurrentIndex(currentView);
    return;
  }

  sUi->viewMode->blockSignals(true);
  currentView = mode;
  sUi->viewMode->setCurrentIndex(currentView);
  sUi->viewMode->blockSignals(false);

  sUi->layHide->insertWidget(0,sUi->rawGoal);
  sUi->layHide->insertWidget(0,sUi->rawPosition);
  sUi->layHide->insertWidget(0,sUi->userGoal);
  sUi->layHide->insertWidget(0,sUi->userPosition);
  sUi->layHide->insertWidget(0,sUi->userVarGoal);
  sUi->layHide->insertWidget(0,sUi->limitHi);
  sUi->layHide->insertWidget(0,sUi->limitLo);
  sUi->layHide->insertWidget(0,sUi->callRelative);
  sUi->layHide->insertWidget(0,sUi->absLabel);
  sUi->layHide->insertWidget(0,sUi->stepsPerRev);


  switch (mode) {

  case SETPV:

    // Does not do enything because returns above.

    break;

  case MINI:

    if (isConnected())
      setSpmgMode(GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);
    sUi->loadSave->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->line_5->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->placeControlUser->setVisible(false);
    sUi->placeControlRaw->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->userVarGoal);
    sUi->stepD2->setVisible(false);
    sUi->stepD10->setVisible(false);
    sUi->stepM2->setVisible(false);
    sUi->stepM10->setVisible(false);
    sUi->line_4->setVisible(false);

    sUi->configure->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

    break;


  case COMFO:

    if (isConnected())
      setSpmgMode(GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);
    sUi->loadSave->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->line_5->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlUser->insertWidget(0, sUi->absLabel);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->userVarGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->line_4->setVisible(false);

    sUi->configure->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

    break;


  case CONFIG:

    if (isConnected()) {
      setOffsetMode(FROZEN);
      setSpmgMode(GO);
    }

    sUi->pv->setVisible(true);
    sUi->label_2->setVisible(true);
    sUi->label_20->setVisible(true);
    sUi->loadSave->setVisible(true);

    sUi->generalSetup->setVisible(true);
    sUi->line_5->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(true);
    sUi->label_7->setVisible(true);
    sUi->label_21->setVisible(true);
    sUi->layControlUser->insertWidget(0, sUi->userGoal);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->rawGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->line_4->setVisible(true);

    sUi->layCfgUser->insertWidget(0, sUi->userPosition);
    sUi->layCfgRaw->insertWidget(0, sUi->rawPosition);
    sUi->layCfgLo->insertWidget(0, sUi->limitLo);
    sUi->layCfgHi->insertWidget(0, sUi->limitHi);
    sUi->layCfgStepsPerRev->insertWidget(0, sUi->stepsPerRev);

    sUi->configure->setVisible(true);


    sUi->line_2->setVisible(false);

    sUi->epics->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->line_9->setVisible(true);
    sUi->backlashSetup->setVisible(true);

    break;


  case EPICS:

    sUi->pv->setVisible(true);
    sUi->label_2->setVisible(true);
    sUi->label_20->setVisible(true);
    sUi->loadSave->setVisible(true);

    sUi->generalSetup->setVisible(true);
    sUi->line_5->setVisible(true);
    sUi->spmgSetup->setVisible(true);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->line_4->setVisible(true);

    sUi->configure->setVisible(false);
    sUi->line_2->setVisible(false);

    sUi->layEpicsUserMove->insertWidget(0, sUi->userGoal);
    sUi->layEpicsRawMove->insertWidget(0, sUi->rawGoal);
    sUi->layEpicsUserSet->insertWidget(0, sUi->userPosition);
    sUi->layEpicsRawSet->insertWidget(0, sUi->rawPosition);
    sUi->layEpicsHi->insertWidget(0, sUi->limitHi);
    sUi->layEpicsLo->insertWidget(0, sUi->limitLo);
    sUi->layEpicsStepsPerRev->insertWidget(0, sUi->stepsPerRev);
    sUi->epics->setVisible(true);

    sUi->line_6->setVisible(true);

    sUi->line_9->setVisible(true);
    sUi->backlashSetup->setVisible(true);


    break;

  }

}

void QCaMotorGUI::pressStop(){
  if ( ! getPower() ) setPower(true);
  else if (isMoving()) stop();
  else undoLastMotion();
}


void QCaMotorGUI::updateConnection(bool suc) {
  QCaMotor::updateConnection(suc);
  suc = isConnected();
  sUi->message->setText
      ( suc ? "Connection established." : "Connection lost.");
  pasteCfgAction->setEnabled(suc);
  updateStopButtonStyle();
  updateAllElements();
  if ( suc &&
       sUi->viewMode->currentIndex() != EPICS &&
       getOffsetMode() != FROZEN )
    setOffsetMode(FROZEN);
}


void QCaMotorGUI::updateUserPosition(const QVariant & data) {
  QCaMotor::updateUserPosition(data);
  double ps = getUserPosition();
  mUi->userPosition->setValue(ps);
  sUi->userPosition->setValue(ps);
  sUi->userVarGoal->setValue(ps);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialPosition(const QVariant & data) {
  QCaMotor::updateDialPosition(data);
  sUi->dialPosition->setValue(getDialPosition());
  updateGoButtonStyle();
}

void QCaMotorGUI::updateStep(const QVariant & data) {
  QCaMotor::updateStep(data);
  double stp = getStep();
  sUi->step->setValue(stp);
  QString textStep = QString::number(stp);
  int knownIndex = mUi->step->findText(textStep);
  if (knownIndex == -1)
    mUi->step->insertItem(knownIndex = 3, textStep);
  mUi->step->setCurrentIndex(knownIndex);
}


void QCaMotorGUI::updateDescription(const QVariant & data){
  QCaMotor::updateDescription(data);
  const QString & dsc = getDescription();
  mUi->setup->setText(dsc);
  setupDialog->setWindowTitle(dsc);
  relativeDialog->setWindowTitle(dsc);
  sUi->description->setText(dsc);
}


void QCaMotorGUI::updateMoving(const QVariant & data){

  QCaMotor::updateMoving(data);
  bool mov = isMoving();

  updateAllElements();

  // Updates status of the jog buttons on stop
  if ( !mov ) {
    sUi->jogM->setDown(false);
    sUi->jogP->setDown(false);
    if ( mUi->goM->isDown() )
      mUi->goM->setDown(false);
    if ( mUi->goP->isDown() )
      mUi->goP->setDown(false);
  }

  if (mov)
    sUi->message->setText("Moving...");
  else if (sUi->message->text() == "Moving...")
    sUi->message->clear();

  updateStopButtonStyle();

}


void QCaMotorGUI::updatePower(const QVariant &data) {

  QCaMotor::updatePower(data);
  bool pwrC = getPowerConnection(), pwr = getPower();

  sUi->power->setVisible(pwrC);
  sUi->label_19->setVisible(pwrC);
  sUi->label_23->setVisible(pwrC);
  mUi->power->setVisible(pwrC);

  sUi->power->setChecked(pwr);
  sUi->power->setText( pwr ? "ON" : "OFF" );
  sUi->power->setStyleSheet
      ( pwr ?
         "background-color: rgb(0, 128, 0);   color: rgb(255, 255, 255);" :
         "background-color: rgb(0, 0, 0); color: rgb(255, 255, 255);" );

  mUi->power->setChecked(pwr);
  mUi->power->setStyleSheet
      ( pwr ?
         "background-color: rgb(0, 128, 0)" :
         "background-color: rgb(0, 0, 0)" );

  updateStopButtonStyle();
  updateAllElements();
}


void QCaMotorGUI::updateWired(const QVariant &data) {
  QCaMotor::updateWired(data);
  bool wr=isWired();
  if (wr)
    sUi->message->setText("Cable connected.");
  else
    sUi->message->setText("Cable disconnected.");
  updateStopButtonStyle();
  updateAllElements();
}

void QCaMotorGUI::updateUnitsPerRev(const QVariant & data) {
  QCaMotor::updateUnitsPerRev(data);
  double vRes = getUnitsPerRev();
  sUi->unitsPerRev->setValue(vRes);
  if ( getDirection() == NEGATIVE )
    vRes *= -1.0;
  sUi->unitsPerRevAndDir->setValue(vRes);
}

void QCaMotorGUI::updateUnits(const QVariant & data){

  QCaMotor::updateUnits(data);
  const QString & egu = getUnits();

  rUi->goRelative->setSuffix(egu);
  mUi->userPosition->setSuffix(egu);
  sUi->speed->setSuffix(egu+"/s");
  sUi->speedS->setSuffix(egu+"/s");
  sUi->step->setSuffix(egu);
  sUi->units->setText(egu);
  sUi->limitHiDial->setSuffix(egu);
  sUi->userPosition->setSuffix(egu);
  sUi->dialPosition->setSuffix(egu);
  sUi->limitLoDial->setSuffix(egu);
  sUi->limitLo->setSuffix(egu);
  sUi->limitHi->setSuffix(egu);
  sUi->maximumSpeed->setSuffix(egu+"/s");
  sUi->backlash->setSuffix(egu);
  sUi->unitsPerStep->setSuffix(egu+"/step");
  sUi->unitsPerRev->setSuffix(egu+"/rev");
  sUi->unitsPerRevAndDir->setSuffix(egu+"/rev");
  sUi->readbackResolution->setSuffix(egu+"/step");
  sUi->encoderResolution->setSuffix(egu+"/step");
  sUi->userGoal->setSuffix(egu);
  sUi->userVarGoal->setSuffix(egu);
  sUi->dialGoal->setSuffix(egu);
  sUi->offset->setSuffix(egu);
  sUi->backlashSpeed->setSuffix(egu+"/s");
  sUi->jogSpeed->setSuffix(egu+"/s");
}

void QCaMotorGUI::updatePrecision(const QVariant & data){

  QCaMotor::updatePrecision(data);
  int prec = getPrecision();

  sUi->precision->setValue(prec);

  rUi->goRelative->setDecimals(prec);
  mUi->userPosition->setDecimals(prec);
  sUi->speed->setDecimals(prec);
  sUi->speedS->setDecimals(prec);
  sUi->step->setDecimals(prec);
  sUi->userPosition->setDecimals(prec);
  sUi->dialPosition->setDecimals(prec);
  sUi->limitLo->setDecimals(prec);
  sUi->limitHi->setDecimals(prec);
  sUi->limitLoDial->setDecimals(prec);
  sUi->limitHiDial->setDecimals(prec);
  sUi->acceleration->setDecimals(prec);
  sUi->accelerationS->setDecimals(prec);
  sUi->maximumSpeed->setDecimals(prec);
  sUi->backlash->setDecimals(prec);
  sUi->unitsPerStep->setDecimals(qMax(prec,7));
  sUi->unitsPerRev->setDecimals(qMax(prec,7));
  sUi->unitsPerRevAndDir->setDecimals(qMax(prec,7));
  sUi->readbackResolution->setDecimals(qMax(prec,7));
  sUi->encoderResolution->setDecimals(qMax(prec,7));
  sUi->userGoal->setDecimals(prec);
  sUi->userVarGoal->setDecimals(prec);
  sUi->offset->setDecimals(prec);
  sUi->dialGoal->setDecimals(prec);
  sUi->backlashSpeed->setDecimals(prec);
  sUi->backlashAcceleration->setDecimals(prec);
  sUi->jogSpeed->setDecimals(prec);
  sUi->jogAcceleration->setDecimals(prec);

}

void QCaMotorGUI::updateMaximumSpeed(const QVariant & data){
  QCaMotor::updateMaximumSpeed(data);
  double maxSpeed = getMaximumSpeed();
  sUi->speed->setMaximum(maxSpeed);
  sUi->jogSpeed->setMaximum(maxSpeed);
  sUi->backlashSpeed->setMaximum(maxSpeed);
  sUi->maximumSpeed->setValue(maxSpeed);
  updateSpeeds();
}

void QCaMotorGUI::updateNormalSpeed(const QVariant & data) {
  QCaMotor::updateNormalSpeed(data);
  sUi->speed->setValue(getNormalSpeed());
  sUi->speedS->setValue(getNormalSpeed());
  updateSpeeds();
}

void QCaMotorGUI::updateBacklashSpeed(const QVariant & data) {
  QCaMotor::updateBacklashSpeed(data);
  sUi->backlashSpeed->setValue(getBacklashSpeed());
  updateSpeeds();
}

void QCaMotorGUI::updateJogSpeed(const QVariant & data) {
  QCaMotor::updateJogSpeed(data);
  sUi->jogSpeed->setValue(getJogSpeed());
  updateSpeeds();
}

void QCaMotorGUI::updateAcceleration(const QVariant & data) {
  QCaMotor::updateAcceleration(data);
  sUi->acceleration->setValue(getAcceleration());
  sUi->accelerationS->setValue(getAcceleration());
  updateAccelerations();
}

void QCaMotorGUI::updateBacklashAcceleration(const QVariant & data) {
  QCaMotor::updateBacklashAcceleration(data);
  sUi->backlashAcceleration->setValue(getBacklashAcceleration());
  updateAccelerations();
}

void QCaMotorGUI::updateJogAcceleration(const QVariant & data) {
  QCaMotor::updateJogAcceleration(data);
  sUi->jogAcceleration->setValue(getJogAcceleration());
  updateAccelerations();
}

void QCaMotorGUI::updateBacklash(const QVariant & data){
  QCaMotor::updateBacklash(data);
  double blsh = getBacklash();
  sUi->backlash->setValue(blsh);
  if (blsh != 0.0 && getBacklashSpeed() == 0.0) {
    setBacklashSpeed(getNormalSpeed());
    sUi->message->setText("Backlash speed set to normal speed.");
  }
}


void QCaMotorGUI::updateUserHiLimit(const QVariant &data) {
  QCaMotor::updateUserHiLimit(data);
  double loL=getUserLoLimit(), hiL=getUserHiLimit();
  mUi->userPosition->setMaximum(hiL);
  sUi->userPosition->setMaximum(hiL);
  sUi->userGoal->setMaximum(hiL);
  sUi->userVarGoal->setMaximum(hiL);
  sUi->limitHi->setValue(hiL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateUserLoLimit(const QVariant &data) {
  QCaMotor::updateUserLoLimit(data);
  double loL=getUserLoLimit(), hiL=getUserHiLimit();
  mUi->userPosition->setMinimum(loL);
  sUi->userPosition->setMinimum(loL);
  sUi->userGoal->setMinimum(loL);
  sUi->userVarGoal->setMinimum(loL);
  sUi->limitLo->setValue(loL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialHiLimit(const QVariant &data){
  QCaMotor::updateDialHiLimit(data);
  double hiL=getDialHiLimit();
  sUi->dialPosition->setMaximum(hiL);
  sUi->dialGoal->setMaximum(hiL);
  sUi->limitHiDial->setValue(hiL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialLoLimit(const QVariant &data){
  QCaMotor::updateDialLoLimit(data);
  double loL=getDialLoLimit();
  sUi->dialPosition->setMinimum(loL);
  sUi->dialGoal->setMinimum(loL);
  sUi->limitLoDial->setValue(loL);
  updateGoButtonStyle();
}



void QCaMotorGUI::updateSuMode(const QVariant & data) {
  QCaMotor::updateSuMode(data);
  sUi->setGroup->button(getSuMode())->setChecked(true);
}

void QCaMotorGUI::updateOffsetMode(const QVariant & data) {
  QCaMotor::updateOffsetMode(data);
  sUi->offGroup->button(getOffsetMode())->setChecked(true);
}

void QCaMotorGUI::updateDirection(const QVariant & data){
  QCaMotor::updateDirection(data);
  updateUnitsPerRev(getUnitsPerRev()); // needed to address the bug described in QCaMotor::setResolution().
  sUi->dirGroup->button(getDirection() > 0 ? 1 : 0)->setChecked(true);
}

void QCaMotorGUI::updateSpmgMode(const QVariant & data){
  QCaMotor::updateSpmgMode(data);
  sUi->spmgGroup->button(getSpmgMode())->setChecked(true);
}


void QCaMotorGUI::updateSpeeds() {
  double spd = getNormalSpeed();
  sUi->equalizeSpeeds->setVisible( spd != getMaximumSpeed() ||
        spd != getBacklashSpeed() ||  spd != getJogSpeed() );
}

void QCaMotorGUI::updateAccelerations() {
  double acc = getAcceleration();
  sUi->equalizeAccelerations->setVisible(
        acc != getBacklashAcceleration() ||  acc != getJogAcceleration() );
}

void QCaMotorGUI::updateGoButtonStyle(){

  QString style;
  const QString hardStyle = "background-color: rgb(128, 0, 0); color: rgb(255, 255, 255);";
  const QString softStyle = "background-color: rgb(128, 64, 0); color: rgb(255, 255, 255);";

  if (getLoLimitStatus())
    style = hardStyle;
  else if ( getUserPosition() <= getUserLoLimit() ||
            getDialPosition() <= getDialLoLimit() )
    style = softStyle;
  else
    style = "";
  mUi->goM->setStyleSheet(style);
  mUi->jogM->setStyleSheet(style);
  mUi->limitM->setStyleSheet(style);
  sUi->goM->setStyleSheet(style);
  sUi->goLimitM->setStyleSheet(style);
  sUi->jogM->setStyleSheet(style);

  if (getHiLimitStatus())
    style = hardStyle;
  else if ( getUserPosition() >= getUserHiLimit() ||
            getDialPosition() >= getDialHiLimit() )
    style = softStyle;
  else
    style = "";
  mUi->goP->setStyleSheet(style);
  mUi->jogP->setStyleSheet(style);
  mUi->limitP->setStyleSheet(style);
  sUi->goP->setStyleSheet(style);
  sUi->goLimitP->setStyleSheet(style);
  sUi->jogP->setStyleSheet(style);


}

void QCaMotorGUI::updateStopButtonStyle() {

  static const QString
      movstyle("background-color: rgb(128, 0, 0); color: rgb(255, 255, 255);"),
      wrdstyle("color: rgb(255, 0, 0);"),
      pwrstyle("background-color: rgb(0, 128, 0); color: rgb(255, 255, 255);");

  if ( ! isConnected() ) {
    mUi->stop->setStyleSheet("");
    sUi->stop->setStyleSheet("");
    mUi->stop->setText("Disconnected");
    sUi->stop->setText("Disconnected");
  } else if (isMoving()) {
    mUi->stop->setStyleSheet(movstyle);
    sUi->stop->setStyleSheet(movstyle);
    mUi->stop->setText("STOP");
    sUi->stop->setText("STOP");
    mUi->stop->setToolTip("Stop motion");
    sUi->stop->setToolTip("Stop motion");
  } else if ( ! getPower() ) {
    mUi->stop->setStyleSheet(pwrstyle);
    sUi->stop->setStyleSheet(pwrstyle);
    mUi->stop->setText("POWER ON");
    sUi->stop->setText("POWER ON");
    const QString txt("Click to turn power on");
    mUi->stop->setToolTip(txt);
    sUi->stop->setToolTip(txt);
  } else if ( ! isWired() ) {
    mUi->stop->setStyleSheet(wrdstyle);
    sUi->stop->setStyleSheet(wrdstyle);
    mUi->stop->setText("No cable");
    sUi->stop->setText("No cable");
    mUi->stop->setToolTip("");
    sUi->stop->setToolTip("");
  } else {
    mUi->stop->setStyleSheet("");
    sUi->stop->setStyleSheet("");
    mUi->stop->setText("UNDO");
    sUi->stop->setText("UNDO");
    double undo = - ( getDirection() == NEGATIVE ? -1.0 : 1.0) *
        getMotorResolution() * getLastMotion();
    const QString txt("Undo last motion ("
                      + QString::number(undo) + getUnits() + ")");
    mUi->stop->setToolTip(txt);
    sUi->stop->setToolTip(txt);
  }

}

void QCaMotorGUI::updateAllElements(){

  bool
      pwr = getPower(),
      mv  = isMoving(),
      cn  = isConnected(),
      wr  = isWired(),
      std = cn && !mv;

  rUi->goRelative             ->setEnabled(std && wr && pwr);

  mUi->goM                    ->setEnabled(std && wr && pwr);
  mUi->goP                    ->setEnabled(std && wr && pwr);
  mUi->limitM                 ->setEnabled(std && wr && pwr);
  mUi->limitP                 ->setEnabled(std && wr && pwr);
  mUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogM->isDown()) );
  mUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogP->isDown()) );
  mUi->userPosition           ->setEnabled(std && wr && pwr);
  mUi->step                   ->setEnabled(std);
  mUi->stop                   ->setEnabled(cn);

  sUi->goLimitM               ->setEnabled(std && wr && pwr);
  sUi->goLimitP               ->setEnabled(std && wr && pwr);
  sUi->goM                    ->setEnabled(std && wr && pwr);
  sUi->goP                    ->setEnabled(std && wr && pwr);
  sUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogM->isDown()) );
  sUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogP->isDown()) );
  sUi->stop                   ->setEnabled(cn && wr);
  sUi->spmgSetup              ->setEnabled(cn);
  sUi->rawGoal                ->setEnabled(std && wr && pwr);
  sUi->userGoal               ->setEnabled(std && wr && pwr);
  sUi->dialGoal               ->setEnabled(std && wr && pwr);
  sUi->userVarGoal            ->setEnabled(std && wr && pwr);
  sUi->callRelative           ->setEnabled(std && wr && pwr);

  sUi->loadConfig             ->setEnabled(std);

  sUi->control                ->setEnabled(cn);
  sUi->loadSave               ->setEnabled(cn);
  sUi->backlashSetup          ->setEnabled(std);
  sUi->configure              ->setEnabled(std);
  sUi->epics                  ->setEnabled(std);
  sUi->generalSetup           ->setEnabled(std);

  sUi->power                  ->setEnabled(cn && !mv);
  mUi->power                  ->setEnabled(cn && !mv);


}
