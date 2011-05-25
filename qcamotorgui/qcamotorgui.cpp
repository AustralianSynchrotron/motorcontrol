#include "qcamotorgui.h"

#include <math.h>
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QStringListModel>
#include <QClipboard>



KnownPVTable::KnownPVTable(const QStringList &list, QObject *parent)
  : QAbstractTableModel(parent){
  foreach(QString pvname, list) {
     QEpicsPV * pv = new QEpicsPV(pvname+".DESC", this) ;
     connect(pv, SIGNAL(valueChanged(QVariant)),
             SLOT(updateData()));
     knownPVs << pv;
  }
}

QModelIndex KnownPVTable::indexOf(QEpicsPV* pv) const {
  return knownPVs.contains(pv) ?
      createIndex(knownPVs.indexOf(pv), 1) :
      QModelIndex();
}

void KnownPVTable::updateData() {
  QModelIndex midx = indexOf( (QEpicsPV*) sender() );
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

  QCaMotorGUI::init();

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

  connect(rUi->goRelative, SIGNAL(valueEdited(double)),
          SLOT(goRelative(double)));

  connect(mUi->userPosition, SIGNAL(valueEdited(double)),
          SLOT(goUserPosition(double)));
  connect(mUi->step, SIGNAL(textEdited(QString)),
          SLOT(setStepGui(QString)));
  connect(mUi->step, SIGNAL(activated(QString)),
          SLOT(setStepGui(QString)));
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

  connect(sUi->description, SIGNAL(returnPressed()),
          SLOT(setDescriptionGui()));

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
  connect(sUi->useEncoder, SIGNAL(clicked(bool)),
          SLOT(setUseEncoder(bool)));
  connect(sUi->useReadback, SIGNAL(clicked(bool)),
          SLOT(setUseReadback(bool)));

  connect(sUi->offGroup, SIGNAL(buttonClicked(int)),
          SLOT(setOffsetMode(int)));
  connect(sUi->dirGroup, SIGNAL(buttonClicked(int)),
          SLOT(setOffsetDirection(int)));
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

  connect(sUi->backlash, SIGNAL(valueEdited(double)),
          SLOT(setBacklash(double)));

  connect(sUi->userPosition, SIGNAL(valueEdited(double)),
          SLOT(setUserPosition(double)));
  connect(sUi->rawPosition, SIGNAL(valueEdited(double)),
          SLOT(setRawPosition(double)));
  connect(sUi->userVarGoal, SIGNAL(valueEdited(double)),
          SLOT(goUserPosition(double)));
  connect(sUi->rawVarGoal, SIGNAL(valueEdited(double)),
          SLOT(goRawPosition(double)));
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
  connect(sUi->resolution, SIGNAL(valueEdited(double)),
          SLOT(setMotorResolution(double)));

  //
  // Connect Motor Signals
  //

  connect(this, SIGNAL(changedPv(QString)),
          SLOT(updatePvGui(QString)));

  connect(this, SIGNAL(changedDescription(QString)),
          SLOT(updateDescriptionGui(QString)));
  connect(this, SIGNAL(changedDescription(QString)),
          sUi->description, SLOT(setText(QString)));

  connect(this, SIGNAL(changedPrecision(int)),
          SLOT(updatePrecisionGui(int)));
  connect(this, SIGNAL(changedUnits(QString)),
          SLOT(updateUnitsGui(QString)));

  connect(this, SIGNAL(changedUserPosition(double)),
          mUi->userPosition, SLOT(setValue(double)));
  connect(this, SIGNAL(changedUserPosition(double)),
          sUi->userPosition, SLOT(setValue(double)));
  connect(this, SIGNAL(changedUserPosition(double)),
          sUi->userVarGoal, SLOT(setValue(double)));
  connect(this, SIGNAL(changedUserPosition(double)),
          SLOT(updateGoButtonStyle()));

  connect(this, SIGNAL(changedDialPosition(double)),
          sUi->dialPosition, SLOT(setValue(double)));
  connect(this, SIGNAL(changedDialPosition(double)),
          SLOT(updateGoButtonStyle()));

  connect(this, SIGNAL(changedRawPosition(double)),
          sUi->rawPosition, SLOT(setValue(double)));
  connect(this, SIGNAL(changedRawPosition(double)),
          sUi->rawVarGoal, SLOT(setValue(double)));

  connect(this, SIGNAL(changedUserGoal(double)),
          sUi->userGoal, SLOT(setValue(double)));
  connect(this, SIGNAL(changedDialGoal(double)),
          sUi->dialGoal, SLOT(setValue(double)));
  connect(this, SIGNAL(changedRawGoal(double)),
          sUi->rawGoal, SLOT(setValue(double)));

  connect(this, SIGNAL(changedStep(double)),
          sUi->step, SLOT(setValue(double)));
  connect(this, SIGNAL(changedStep(double)),
          SLOT(updateStepGui(double)));

  connect(this, SIGNAL(changedOffset(double)),
          sUi->offset, SLOT(setValue(double)));
  connect(this, SIGNAL(changedOffsetMode(OffMode)),
          SLOT(updateOffGroup(OffMode)));
  connect(this, SIGNAL(changedOffsetDirection(int)),
          SLOT(updateDirGroup(int)));
  // next connection is needed to address the bug described in
  // QCaMotor::setResolution().
  //connect(this, SIGNAL(changedOffsetDirection(int)),
  //        SLOT(updateMotorResolutionGui()));
  connect(this, SIGNAL(changedSuMode(SuMode)),
          SLOT(updateSetGroup(SuMode)));

  connect(this, SIGNAL(changedHiLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedLoLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));

  connect(this, SIGNAL(changedUserHiLimit(double)),
          SLOT(updateUserLimitGui()));
  connect(this, SIGNAL(changedUserHiLimit(double)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedUserHiLimit(double)),
          sUi->limitHi, SLOT(setValue(double)));
  connect(this, SIGNAL(changedUserLoLimit(double)),
          SLOT(updateUserLimitGui()));
  connect(this, SIGNAL(changedUserLoLimit(double)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedUserLoLimit(double)),
          sUi->limitLo, SLOT(setValue(double)));

  connect(this, SIGNAL(changedDialHiLimit(double)),
          SLOT(updateDialLimitGui()));
  connect(this, SIGNAL(changedDialHiLimit(double)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedDialHiLimit(double)),
          sUi->limitHiDial, SLOT(setValue(double)));
  connect(this, SIGNAL(changedDialLoLimit(double)),
          SLOT(updateDialLimitGui()));
  connect(this, SIGNAL(changedDialLoLimit(double)),
          SLOT(updateGoButtonStyle()));
  connect(this, SIGNAL(changedDialLoLimit(double)),
          sUi->limitLoDial, SLOT(setValue(double)));

  // Connecting to the ::updateMotorResolutionGui() instead of
  // sUi->resolution->setValue(double) is needed to
  // address the bug described in QCaMotor::setResolution().
  connect(this, SIGNAL(changedMotorResolution(double)),
          sUi->resolution, SLOT(setValue(double)));
          //SLOT(updateMotorResolutionGui()));
  connect(this, SIGNAL(changedReadbackResolution(double)),
          sUi->readbackResolution, SLOT(setValue(double)));
  connect(this, SIGNAL(changedEncoderResolution(double)),
          sUi->encoderResolution, SLOT(setValue(double)));
  connect(this, SIGNAL(changedStepsPerRev(int)),
          sUi->stepsPerRev, SLOT(setValue(int)));

  connect(this, SIGNAL(changedMaximumSpeed(double)),
          sUi->maximumSpeed, SLOT(setValue(double)));
  connect(this, SIGNAL(changedMaximumSpeed(double)),
          SLOT(updateMaximumSpeedGui(double)));
  connect(this, SIGNAL(changedNormalSpeed(double)),
          sUi->speed, SLOT(setValue(double)));
  connect(this, SIGNAL(changedRevSpeed(double)),
          sUi->revSpeed, SLOT(setValue(double)));
  connect(this, SIGNAL(changedJogSpeed(double)),
          sUi->jogSpeed, SLOT(setValue(double)));
  connect(this, SIGNAL(changedBacklashSpeed(double)),
          sUi->backlashSpeed, SLOT(setValue(double)));

  connect(this, SIGNAL(changedAcceleration(double)),
          sUi->acceleration, SLOT(setValue(double)));
  connect(this, SIGNAL(changedJogAcceleration(double)),
          sUi->jogAcceleration, SLOT(setValue(double)));
  connect(this, SIGNAL(changedBacklashAcceleration(double)),
          sUi->backlashAcceleration, SLOT(setValue(double)));

  connect(this, SIGNAL(changedConnected(bool)),
          SLOT(updateConnectionGui(bool)));
  connect(this, SIGNAL(changedMoving(bool)),
          SLOT(updateMovingGui(bool)));
  connect(this, SIGNAL(changedUseReadback(bool)),
          sUi->useReadback, SLOT(setChecked(bool)));
  connect(this, SIGNAL(changedUseEncoder(bool)),
          sUi->useEncoder, SLOT(setChecked(bool)));
  connect(this, SIGNAL(changedBacklash(double)),
          SLOT(updateBacklashGui(double)));
  connect(this, SIGNAL(changedSpmgMode(SpmgMode)),
          SLOT(updateSpmgGroup(SpmgMode)));

  connect(this, SIGNAL(changedPowerConnection(bool)),
          SLOT(updatePowerGui()));
  connect(this, SIGNAL(changedPower(bool)),
          SLOT(updatePowerGui()));
  connect(this, SIGNAL(changedWired(bool)),
          SLOT(updateWiredGui(bool)));
  connect(this, SIGNAL(changedMoving(bool)),
          SLOT(updateStopButtonStyle()));

  setViewMode(MICRO);
  setupDialog->update();
  updatePowerGui();
  updateWiredGui(isWired());
  setStepGui();

}

QCaMotorGUI::~QCaMotorGUI() {
  delete mUi;
  delete sUi;
  delete rUi;
  delete pUi;
  delete pvDialog;
  delete setupDialog;
  delete relativeDialog;
  delete theWidget;
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

void QCaMotorGUI::updatePvGui(const QString & newpv){
  sUi->pv->setText(newpv);
  mUi->setup->disconnect();
  if (newpv.isEmpty()) {
    connect(mUi->setup, SIGNAL(clicked()),
            pvDialog, SLOT(show()) );
    updateDescriptionGui("SETUP");
    mUi->setup->setContextMenuPolicy(Qt::NoContextMenu);
  } else {
    connect(mUi->setup, SIGNAL(clicked()),
            setupDialog, SLOT(show()) );
    updateDescriptionGui(newpv);
    mUi->setup->setContextMenuPolicy(Qt::ActionsContextMenu);
  }
}



void QCaMotorGUI::lock(bool lck){
  locked = lck;
  pvDialog->hide();
}


void QCaMotorGUI::init() {

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

void QCaMotorGUI::setStepGui(const QString & _text){
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
  } else if (text == "limit" || !ok) {
    mUi->goM->setVisible(false);
    mUi->goP->setVisible(false);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
    mUi->limitM->setVisible(true);
    mUi->limitP->setVisible(true);
  } else {
    if (val != getStep() )
      setStep(val);
    mUi->goM->setVisible(true);
    mUi->goP->setVisible(true);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
    mUi->limitM->setVisible(false);
    mUi->limitP->setVisible(false);
  }
}


/*
void QCaMotorGUI::updateMotorResolutionGui() {
  double vRes = getMotorResolution();
  if ( getOffsetDirection() == NEGATIVE )
    vRes *= -1.0;
  sUi->resolution->setValue(vRes);
}
*/


void QCaMotorGUI::setViewMode(ViewMode mode){

  if ( mode == SETUP ) {
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
  sUi->layHide->insertWidget(0,sUi->rawVarGoal);
  sUi->layHide->insertWidget(0,sUi->userGoal);
  sUi->layHide->insertWidget(0,sUi->userPosition);
  sUi->layHide->insertWidget(0,sUi->userVarGoal);
  sUi->layHide->insertWidget(0,sUi->resolution);
  sUi->layHide->insertWidget(0,sUi->limitHi);
  sUi->layHide->insertWidget(0,sUi->limitLo);
  sUi->layHide->insertWidget(0,sUi->offset);
  sUi->layHide->insertWidget(0,sUi->speed);
  sUi->layHide->insertWidget(0,sUi->callRelative);
  sUi->layHide->insertWidget(0,sUi->absLabel);


  switch (mode) {

  case SETUP: // Does not do enything because returns above.

    /*

    sUi->pv->setVisible(true);
    sUi->label_2->setVisible(true);
    sUi->label_20->setVisible(true);

    sUi->line_5->setVisible(false);
    sUi->generalSetup->setVisible(false);
    sUi->control->setVisible(false);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->placeControlUser->setVisible(false);
    sUi->placeControlRaw->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->userVarGoal);
    sUi->placeControlRel->setVisible(false);
    sUi->goLimitM->setText("|<");
    sUi->goLimitP->setText(">|");
    sUi->jogM->setText("<<");
    sUi->jogP->setText(">>");
    sUi->stepD2->setVisible(false);
    sUi->stepD10->setVisible(false);
    sUi->stepM2->setVisible(false);
    sUi->stepM10->setVisible(false);
    sUi->line_4->setVisible(false);

    sUi->miliAdd->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);
    sUi->callibrationSetup->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->speedSetup->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

     */

    break;

  case NANO:

    if (isConnected())
      setSpmgMode(GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);
    sUi->loadSave->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->line_5->setVisible(true);
    sUi->control->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->placeControlUser->setVisible(false);
    sUi->placeControlRaw->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->userVarGoal);
    sUi->placeControlRel->setVisible(true);
    sUi->goLimitM->setText("|<");
    sUi->goLimitP->setText(">|");
    sUi->jogM->setText("<<");
    sUi->jogP->setText(">>");
    sUi->stepD2->setVisible(false);
    sUi->stepD10->setVisible(false);
    sUi->stepM2->setVisible(false);
    sUi->stepM10->setVisible(false);
    sUi->line_4->setVisible(false);

    sUi->miliAdd->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);
    sUi->callibrationSetup->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->speedSetup->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

    break;


  case MICRO:

    if (isConnected())
      setSpmgMode(GO);

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);
    sUi->loadSave->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->line_5->setVisible(true);
    sUi->control->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlUser->insertWidget(0, sUi->absLabel);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->userVarGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->placeControlRel->setVisible(true);
    sUi->goLimitM->setText("|<");
    sUi->goLimitP->setText(">|");
    sUi->jogM->setText("<<");
    sUi->jogP->setText(">>");
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->stepD2->setText("/2");
    sUi->stepD10->setText("/10");
    sUi->stepM2->setText("*2");
    sUi->stepM10->setText("*10");
    sUi->line_4->setVisible(false);

    sUi->miliAdd->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);
    sUi->callibrationSetup->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->speedSetup->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

    break;


  case MILI:

    if (isConnected()) {
      setOffsetMode(FROZEN);
      setSpmgMode(GO);
    }

    sUi->pv->setVisible(false);
    sUi->label_2->setVisible(false);
    sUi->label_20->setVisible(false);
    sUi->loadSave->setVisible(false);

    sUi->generalSetup->setVisible(false);
    sUi->line_5->setVisible(true);
    sUi->control->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(true);
    sUi->label_7->setVisible(true);
    sUi->label_21->setVisible(true);
    sUi->layControlUser->insertWidget(0, sUi->userGoal);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->rawGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->placeControlRel->setVisible(true);
    sUi->goLimitM->setText("LIMIT<");
    sUi->goLimitP->setText(">LIMIT");
    sUi->jogM->setText("JOG<");
    sUi->jogP->setText(">JOG");
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->stepD2->setText("step/2");
    sUi->stepD10->setText("step/10");
    sUi->stepM2->setText("step*2");
    sUi->stepM10->setText("step*10");
    sUi->line_4->setVisible(true);

    sUi->layMiliUser->insertWidget(0, sUi->userPosition);
    sUi->layMiliRaw->insertWidget(0, sUi->rawPosition);
    sUi->layMiliSpeed->insertWidget(0, sUi->speed);
    sUi->miliAdd->setVisible(true);


    sUi->line_2->setVisible(false);

    sUi->epics->setVisible(false);
    sUi->callibrationSetup->setVisible(false);
    sUi->line_6->setVisible(false);
    sUi->speedSetup->setVisible(false);
    sUi->line_9->setVisible(false);
    sUi->backlashSetup->setVisible(false);

    break;

  case MACRO:

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
    sUi->control->setVisible(true);
    sUi->spmgSetup->setVisible(false);

    sUi->label_3->setVisible(true);
    sUi->label_7->setVisible(true);
    sUi->label_21->setVisible(true);
    sUi->layControlUser->insertWidget(0, sUi->userGoal);
    sUi->placeControlUser->setVisible(true);
    sUi->layControlRaw->insertWidget(0, sUi->rawGoal);
    sUi->placeControlRaw->setVisible(true);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->placeControlRel->setVisible(true);
    sUi->goLimitM->setText("LIMIT<");
    sUi->goLimitP->setText(">LIMIT");
    sUi->jogM->setText("JOG<");
    sUi->jogP->setText(">JOG");
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->stepD2->setText("step/2");
    sUi->stepD10->setText("step/10");
    sUi->stepM2->setText("step*2");
    sUi->stepM10->setText("step*10");
    sUi->line_4->setVisible(true);

    sUi->miliAdd->setVisible(false);
    sUi->line_2->setVisible(false);
    sUi->epics->setVisible(false);

    sUi->layMacroUser->insertWidget(0, sUi->userPosition);
    sUi->layMacroResolution->insertWidget(0, sUi->resolution);
    sUi->layMacroRaw->insertWidget(0, sUi->rawPosition);
    sUi->layMacroOffset->insertWidget(0, sUi->offset);
    sUi->layMacroHi->insertWidget(0, sUi->limitHi);
    sUi->layMacroLo->insertWidget(0, sUi->limitLo);
    sUi->layMacroSpeed->insertWidget(0, sUi->speed);
    sUi->callibrationSetup->setVisible(true);


    sUi->line_6->setVisible(true);
    sUi->speedSetup->setVisible(true);
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
    sUi->control->setVisible(true);
    sUi->spmgSetup->setVisible(true);

    sUi->label_3->setVisible(false);
    sUi->label_7->setVisible(false);
    sUi->label_21->setVisible(false);
    sUi->layControlRel->insertWidget(0, sUi->callRelative);
    sUi->goLimitM->setText("LIMIT<");
    sUi->goLimitP->setText(">LIMIT");
    sUi->jogM->setText("JOG<");
    sUi->jogP->setText(">JOG");
    sUi->stepD2->setVisible(true);
    sUi->stepD10->setVisible(true);
    sUi->stepM2->setVisible(true);
    sUi->stepM10->setVisible(true);
    sUi->stepD2->setText("step/2");
    sUi->stepD10->setText("step/10");
    sUi->stepM2->setText("step*2");
    sUi->stepM10->setText("step*10");
    sUi->line_4->setVisible(true);

    sUi->miliAdd->setVisible(false);
    sUi->line_2->setVisible(false);

    sUi->layEpicsUserMove->insertWidget(0, sUi->userGoal);
    sUi->layEpicsRawMove->insertWidget(0, sUi->rawGoal);
    sUi->layEpicsUserSet->insertWidget(0, sUi->userPosition);
    sUi->layEpicsResolution->insertWidget(0, sUi->resolution);
    sUi->layEpicsRawSet->insertWidget(0, sUi->rawPosition);
    sUi->layEpicsOffset->insertWidget(0, sUi->offset);
    sUi->layEpicsHi->insertWidget(0, sUi->limitHi);
    sUi->layEpicsLo->insertWidget(0, sUi->limitLo);
    sUi->epics->setVisible(true);

    sUi->callibrationSetup->setVisible(false);
    sUi->line_6->setVisible(true);

    sUi->layMacroSpeed->insertWidget(0, sUi->speed);
    sUi->speedSetup->setVisible(true);

    sUi->line_9->setVisible(true);
    sUi->backlashSetup->setVisible(true);


    break;

  }

}











void QCaMotorGUI::updateStepGui(double step){
  QString textStep = QString::number(step);
  int knownIndex = mUi->step->findText(textStep);
  if (knownIndex == -1)
    mUi->step->insertItem(knownIndex = 3, textStep);
  mUi->step->setCurrentIndex(knownIndex);
  setStepGui(step);
}

void QCaMotorGUI::updateConnectionGui(bool suc) {
  sUi->message->setText
      ( suc ? "Connection established." : "Connection lost.");
  updateStopButtonStyle();
  updateAllElements();
  if ( suc ) {
    if ( sUi->viewMode->currentIndex() == MILI ||
         sUi->viewMode->currentIndex() == MACRO )
      setOffsetMode(FROZEN);
  }
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


void QCaMotorGUI::updateDescriptionGui(const QString & data){
  mUi->setup->setText(data);
  setupDialog->setWindowTitle(data);
  relativeDialog->setWindowTitle(data);
  sUi->description->setText(data);
}


void QCaMotorGUI::updateMovingGui(bool mov){

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
    double undo = - ( getOffsetDirection() == NEGATIVE ? -1.0 : 1.0) *
        getMotorResolution() * getLastMotion();
    const QString txt("Undo last motion ("
                      + QString::number(undo) + getUnits() + ")");
    mUi->stop->setToolTip(txt);
    sUi->stop->setToolTip(txt);
  }

}

void QCaMotorGUI::updatePowerGui() {

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

void QCaMotorGUI::updateWiredGui(bool wr) {
  if (wr)
    sUi->message->setText("Cable connected.");
  else
    sUi->message->setText("Cable disconnected.");
  updateStopButtonStyle();
  updateAllElements();
}

void QCaMotorGUI::pressStop(){
  if ( ! getPower() ) setPower(true);
  else if (isMoving()) stop();
  else undoLastMotion();
}

void QCaMotorGUI::updateUnitsGui(const QString & data){
  rUi->goRelative->setSuffix(data);
  mUi->userPosition->setSuffix(data);
  sUi->speed->setSuffix(data+"/s");
  sUi->step->setSuffix(data);
  sUi->units->setText(data);
  sUi->limitHiDial->setSuffix(data);
  sUi->userPosition->setSuffix(data);
  sUi->dialPosition->setSuffix(data);
  sUi->limitLoDial->setSuffix(data);
  sUi->limitLo->setSuffix(data);
  sUi->limitHi->setSuffix(data);
  sUi->maximumSpeed->setSuffix(data+"/s");
  sUi->backlash->setSuffix(data);
  sUi->resolution->setSuffix(data+"/step");
  sUi->readbackResolution->setSuffix(data+"/step");
  sUi->encoderResolution->setSuffix(data+"/step");
  sUi->userGoal->setSuffix(data);
  sUi->userVarGoal->setSuffix(data);
  sUi->dialGoal->setSuffix(data);
  sUi->offset->setSuffix(data);
  sUi->backlashSpeed->setSuffix(data+"/s");
  sUi->jogSpeed->setSuffix(data+"/s");
}

void QCaMotorGUI::updatePrecisionGui(int prec){

  sUi->precision->setValue(prec);

  rUi->goRelative->setDecimals(prec);
  mUi->userPosition->setDecimals(prec);
  sUi->speed->setDecimals(prec);
  sUi->step->setDecimals(prec);
  sUi->userPosition->setDecimals(prec);
  sUi->dialPosition->setDecimals(prec);
  sUi->limitLo->setDecimals(prec);
  sUi->limitHi->setDecimals(prec);
  sUi->limitLoDial->setDecimals(prec);
  sUi->limitHiDial->setDecimals(prec);
  sUi->acceleration->setDecimals(prec);
  sUi->maximumSpeed->setDecimals(prec);
  sUi->backlash->setDecimals(prec);
  sUi->resolution->setDecimals(qMax(prec,7));
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

void QCaMotorGUI::updateMaximumSpeedGui(double maxSpeed){
  sUi->speed->setMaximum(maxSpeed);
  sUi->jogSpeed->setMaximum(maxSpeed);
  sUi->backlashSpeed->setMaximum(maxSpeed);
  sUi->maximumSpeed->setValue(maxSpeed);
}

void QCaMotorGUI::updateBacklashGui(double blsh){
  sUi->backlash->setValue(blsh);
  if (blsh != 0.0 && getBacklashSpeed() == 0.0) {
    setBacklashSpeed(getNormalSpeed());
    sUi->message->setText("Backlash speed set to normal speed.");
  }
}


void QCaMotorGUI::updateUserLimitGui(){
  double loL=getUserLoLimit(), hiL=getUserHiLimit(), pos=getUserPosition();
  mUi->userPosition->setRange(loL, hiL);
  mUi->userPosition->setValue(pos);
  sUi->userPosition->setRange(loL, hiL);
  sUi->userPosition->setValue(pos);
  sUi->userGoal->setRange(loL, hiL);
  sUi->userGoal->setValue(pos);
  sUi->userVarGoal->setRange(loL, hiL);
  sUi->userVarGoal->setValue(pos);
  sUi->step->setRange(loL-hiL, hiL-loL);
}

void QCaMotorGUI::updateDialLimitGui(){
  double loL=getDialLoLimit(), hiL=getDialHiLimit(), pos=getDialPosition();
  sUi->dialPosition->setRange(loL, hiL);
  sUi->dialPosition->setValue(pos);
  sUi->dialGoal->setRange(loL, hiL);
  sUi->dialGoal->setValue(pos);
}



void QCaMotorGUI::updateSetGroup(SuMode mode){
  sUi->setGroup->button(mode)->setChecked(true);
}

void QCaMotorGUI::updateOffGroup(OffMode mode){
  sUi->offGroup->button(mode)->setChecked(true);
}

void QCaMotorGUI::updateDirGroup(int direction){
  sUi->dirGroup->button(direction > 0 ? 1 : 0)->setChecked(true);
}

void QCaMotorGUI::updateSpmgGroup(SpmgMode mode){
  sUi->spmgGroup->button(mode)->setChecked(true);
}


void QCaMotorGUI::updateAllElements(){

  bool
      pwr = getPower(),
      mv  = isMoving(),
      cn  = isConnected(),
      wr  = isWired(),
      std = cn && pwr && !mv;


  rUi->goRelative             ->setEnabled(std && wr);
  mUi->goM                    ->setEnabled(std && wr);
  mUi->goP                    ->setEnabled(std && wr);
  mUi->limitM                 ->setEnabled(std && wr);
  mUi->limitP                 ->setEnabled(std && wr);
  mUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogM->isDown()) );
  mUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogP->isDown()) );
  mUi->userPosition           ->setEnabled(std && wr);
  mUi->step                   ->setEnabled(std && wr);
  mUi->stop                   ->setEnabled(cn && wr);
  sUi->saveConfig             ->setEnabled(cn && !mv);
  sUi->loadConfig             ->setEnabled(cn && !mv);
  sUi->goLimitM               ->setEnabled(std && wr);
  sUi->goLimitP               ->setEnabled(std && wr);
  sUi->goM                    ->setEnabled(std && wr);
  sUi->goP                    ->setEnabled(std && wr);
  sUi->stepD2                 ->setEnabled(std);
  sUi->stepD10                ->setEnabled(std);
  sUi->stepM2                 ->setEnabled(std);
  sUi->stepM10                ->setEnabled(std);
  sUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogM->isDown()) );
  sUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogP->isDown()) );
  sUi->userPosition           ->setEnabled(std);
  sUi->dialPosition           ->setEnabled(std);
  sUi->rawPosition            ->setEnabled(std);
  sUi->step                   ->setEnabled(std);
  sUi->stop                   ->setEnabled(cn && wr);
  sUi->speed                  ->setEnabled(std);
  sUi->revSpeed               ->setEnabled(std);
  sUi->acceleration           ->setEnabled(std);
  sUi->backlash               ->setEnabled(std);
  sUi->backlashAcceleration   ->setEnabled(std);
  sUi->backlashSpeed          ->setEnabled(std);
  sUi->limitHi                ->setEnabled(std);
  sUi->limitHiDial            ->setEnabled(std);
  sUi->jogAcceleration        ->setEnabled(std);
  sUi->jogSpeed               ->setEnabled(std);
  sUi->limitLo                ->setEnabled(std);
  sUi->limitLoDial            ->setEnabled(std);
  sUi->maximumSpeed           ->setEnabled(std);
  sUi->description            ->setEnabled(std);
  sUi->precision              ->setEnabled(std);
  sUi->rawGoal                ->setEnabled(std);
  sUi->userGoal               ->setEnabled(std);
  sUi->dialGoal               ->setEnabled(std);
  sUi->rawVarGoal             ->setEnabled(std);
  sUi->userVarGoal            ->setEnabled(std);
  sUi->resolution             ->setEnabled(std);
  sUi->readbackResolution     ->setEnabled(std);
  sUi->encoderResolution      ->setEnabled(std);
  sUi->stepsPerRev            ->setEnabled(std);
  sUi->useEncoder             ->setEnabled(std);
  sUi->useReadback            ->setEnabled(std);
  sUi->offsetFrz              ->setEnabled(std);
  sUi->offsetVar              ->setEnabled(std);
  sUi->offset                 ->setEnabled(std);
  sUi->dirNeg                 ->setEnabled(std);
  sUi->dirPos                 ->setEnabled(std);
  sUi->setMode                ->setEnabled(std);
  sUi->useMode                ->setEnabled(std);
  sUi->spmgSetup              ->setEnabled(cn && pwr);
  sUi->units                  ->setEnabled(std);
  sUi->callRelative           ->setEnabled(std);
  sUi->power                  ->setEnabled(cn && !mv);
  mUi->power                  ->setEnabled(cn && !mv);


}
