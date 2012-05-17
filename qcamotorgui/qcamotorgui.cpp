#include "qcamotorgui-local.h"

#include "ui_qcamotorgui.h"
#include "ui_qcamotorgui-setup.h"
#include "ui_qcamotorgui-pv.h"
#include "ui_qcamotorgui-relative.h"


#include <math.h>
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QStringListModel>
#include <QClipboard>
#include <QMessageBox>



QModelIndex KnownPVTable::indexOf(QEpicsPv* pv) const {
  return knownPVs.contains(pv) ?
        createIndex(knownPVs.indexOf(pv), 1) :
        QModelIndex();
}


KnownPVTable::KnownPVTable(const QStringList &list, QObject *parent)
  : QAbstractTableModel(parent){
  foreach(QString pvname, list) {
    QEpicsPv * pv = new QEpicsPv(pvname+".DESC", this) ;
    connect(pv, SIGNAL(valueChanged(QVariant)),
            SLOT(updateData()));
    knownPVs << pv;
  }
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


void KnownPVTable::updateData() {
  QModelIndex midx = indexOf( (QEpicsPv*) sender() );
  if ( midx.isValid() )
    emit (dataChanged(midx, midx));
}




















class FilterPVsProxyModel : private QSortFilterProxyModel {
private:
  QStringList searchWords;
public:
  FilterPVsProxyModel( KnownPVTable * pvTable , QObject * parent=0) :
    QSortFilterProxyModel(parent) {
    setSourceModel(pvTable);
    setDynamicSortFilter(true);
    setFilterKeyColumn(-1);
    sort(0, Qt::AscendingOrder);
  }
  QAbstractItemModel * aModel() { return this; }
public slots:
  void setSearch(const QString & str = QString() ) {
    searchWords = str.split(QRegExp("\\s+"));
    searchWords.removeDuplicates();
    searchWords.removeOne("");
    invalidateFilter();
  }
protected:

  bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const {
    int column_count = sourceModel()->columnCount(source_parent);
    for (int column = 0; column < column_count; ++column) {
      QModelIndex source_index = sourceModel()->index(source_row, column, source_parent);
      QString key = sourceModel()->data(source_index).toString();
      bool found = true;
      foreach (QString word, searchWords) {
        found &= (bool) key.contains(word, Qt::CaseInsensitive);
        if (!found)
          break;
      }
      if (found)
        return true;
    }
    return false;
  }

};





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
  QWidget(parent),
  mot(new QCaMotor(parent)),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(0)
{
  init();
}

QCaMotorGUI::QCaMotorGUI(const QString & pv, QWidget *parent) :
  QWidget(parent),
  mot(new QCaMotor(pv, parent)),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(0)
{
  init();
}


QCaMotorGUI::QCaMotorGUI(QCaMotor * _mot, QWidget *parent) :
  QWidget(parent),
  mot(_mot),
  mUi(new Ui::MotorControl),
  sUi(new Ui::MotorSetup),
  rUi(new Ui::GoRelative),
  pUi(new Ui::PVtable),
  setupDialog(new QDialog(parent)),
  pvDialog(new QDialog(parent)),
  relativeDialog(new QDialog(parent)),
  proxyModel(0)
{
  mot->setParent(parent);
  connect(mot, SIGNAL(destroyed()), SLOT(onMotorDestruction()));
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
}



void QCaMotorGUI::init() {

  QCaMotorGUI::static_init();

  locked=false;

  mUi->setupUi(this);
  sUi->setupUi(setupDialog);
  rUi->setupUi(relativeDialog);
  pUi->setupUi(pvDialog);

  pvDialog->setWindowTitle("Choose motor PV");
  setupDialog->setWindowTitle("MotorMx, setup");
  relativeDialog->setWindowTitle("Move relatively");

  proxyModel = new FilterPVsProxyModel(knownPVs, this);
  pUi->pvTable->setModel(proxyModel->aModel());
  pUi->pvTable->resizeColumnsToContents();

  KeyPressEater * keater = new KeyPressEater(pvDialog);
  pvDialog->installEventFilter(keater);

  sUi->hidden->hide();
  sUi->description->setText(mUi->setup->text());

  sUi->spmgGroup->setId(sUi->Spmg, QCaMotor::STOP);
  sUi->spmgGroup->setId(sUi->sPmg, QCaMotor::PAUSE);
  sUi->spmgGroup->setId(sUi->spMg, QCaMotor::MOVE);
  sUi->spmgGroup->setId(sUi->spmG, QCaMotor::GO);

  sUi->setGroup->setId(sUi->useMode, QCaMotor::USE);
  sUi->setGroup->setId(sUi->setMode, QCaMotor::SET);

  sUi->offGroup->setId(sUi->offsetVar, QCaMotor::VARIABLE);
  sUi->offGroup->setId(sUi->offsetFrz, QCaMotor::FROZEN);

  sUi->dirGroup->setId(sUi->dirPos, QCaMotor::POSITIVE);
  sUi->dirGroup->setId(sUi->dirNeg, QCaMotor::NEGATIVE);

  sUi->loadConfig->addItems(knownConfigs.keys());

  connect(motor(), SIGNAL(changedPv(QString)), SLOT(updateName()));

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
          mot, SLOT(goRelative(double)));

  connect(mUi->userPosition, SIGNAL(valueEdited(double)),
          mot, SLOT(goUserPosition(double)));
  connect(mUi->step, SIGNAL(textEdited(QString)),
          SLOT(setStep(QString)));
  connect(mUi->step, SIGNAL(activated(QString)),
          SLOT(setStep(QString)));
  connect(mUi->stop, SIGNAL(clicked()),
          SLOT(pressStop()));
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
          mot, SLOT(setPower(bool)));

  connect(sUi->pv, SIGNAL(clicked()),
          SLOT(copyPV()));
  connect(sUi->viewMode, SIGNAL(activated(int)),
          SLOT(setViewMode(int)));
  connect(sUi->loadConfig, SIGNAL(activated(QString)),
          SLOT(onLoad(QString)));
  connect(sUi->saveConfig, SIGNAL(clicked()),
          SLOT(onSave()));

  connect(sUi->description, SIGNAL(editingFinished(QString)),
          mot, SLOT(setDescription(QString)));

  connect(sUi->power, SIGNAL(clicked(bool)),
          mot, SLOT(setPower(bool)));
  connect(sUi->precision, SIGNAL(valueEdited(int)),
          mot, SLOT(setPrecision(int)));
  connect(sUi->units, SIGNAL(textEdited(QString)),
          mot, SLOT(setUnits(QString)));

  connect(sUi->spmgGroup, SIGNAL(buttonClicked(int)),
          mot, SLOT(setSpmgMode(int)));

  connect(sUi->goLimitM, SIGNAL(clicked()),
          SLOT(goLimitM()));
  connect(sUi->goLimitP, SIGNAL(clicked()),
          SLOT(goLimitP()));
  connect(sUi->goHomeM, SIGNAL(clicked()),
          SLOT(goHomeM()));
  connect(sUi->goHomeP, SIGNAL(clicked()),
          SLOT(goHomeP()));
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
          mot, SLOT(setStep(double)));
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
          mot, SLOT(setDialPosition(double)));
  connect(sUi->dialGoal, SIGNAL(valueEdited(double)),
          mot, SLOT(goDialPosition(double)));
  connect(sUi->limitLoDial, SIGNAL(valueEdited(double)),
          mot, SLOT(setDialLoLimit(double)));
  connect(sUi->limitHiDial, SIGNAL(valueEdited(double)),
          mot, SLOT(setDialHiLimit(double)));

  connect(sUi->readbackResolution, SIGNAL(valueEdited(double)),
          mot, SLOT(setReadbackResolution(double)));
  connect(sUi->encoderResolution, SIGNAL(valueEdited(double)),
          mot, SLOT(setEncoderResolution(double)));
  connect(sUi->stepsPerRev, SIGNAL(valueEdited(int)),
          mot, SLOT(setStepsPerRev(int)));
  connect(sUi->unitsPerStep, SIGNAL(valueEdited(double)),
          mot, SLOT(setMotorResolution(double)));
  connect(sUi->unitsPerRev, SIGNAL(valueEdited(double)),
          mot, SLOT(setUnitsPerRev(double)));
  connect(sUi->unitsPerRevAndDir, SIGNAL(valueEdited(double)),
          SLOT(setUnitsPerRevAndDirection(double)));

  connect(sUi->useEncoder, SIGNAL(clicked(bool)),
          mot, SLOT(setUseEncoder(bool)));
  connect(sUi->useReadback, SIGNAL(clicked(bool)),
          mot, SLOT(setUseReadback(bool)));

  connect(sUi->offGroup, SIGNAL(buttonClicked(int)),
          mot, SLOT(setOffsetMode(int)));
  connect(sUi->dirGroup, SIGNAL(buttonClicked(int)),
          mot, SLOT(setDirection(int)));
  connect(sUi->setGroup, SIGNAL(buttonClicked(int)),
          mot, SLOT(setSuMode(int)));

  connect(sUi->maximumSpeed, SIGNAL(valueEdited(double)),
          mot, SLOT(setMaximumSpeed(double)));
  connect(sUi->speed, SIGNAL(valueEdited(double)),
          mot, SLOT(setNormalSpeed(double)));
  connect(sUi->revSpeed, SIGNAL(valueEdited(double)),
          mot, SLOT(setRevSpeed(double)));
  connect(sUi->backlashSpeed, SIGNAL(valueEdited(double)),
          mot, SLOT(setBacklashSpeed(double)));
  connect(sUi->jogSpeed, SIGNAL(valueEdited(double)),
          mot, SLOT(setJogSpeed(double)));
  connect(sUi->acceleration, SIGNAL(valueEdited(double)),
          mot, SLOT(setAcceleration(double)));
  connect(sUi->backlashAcceleration, SIGNAL(valueEdited(double)),
          mot, SLOT(setBacklashAcceleration(double)));
  connect(sUi->jogAcceleration, SIGNAL(valueEdited(double)),
          mot, SLOT(setJogAcceleration(double)));
  connect(sUi->accelerationS, SIGNAL(valueEdited(double)),
          SLOT(setAccelerationS(double)));
  connect(sUi->speedS, SIGNAL(valueEdited(double)),
          SLOT(setSpeedS(double)));
  connect(sUi->equalizeSpeeds, SIGNAL(clicked()),
          SLOT(setSpeedS()));
  connect(sUi->equalizeAccelerations, SIGNAL(clicked()),
          SLOT(setAccelerationS()));

  connect(sUi->backlash, SIGNAL(valueEdited(double)),
          mot, SLOT(setBacklash(double)));

  connect(sUi->userPosition, SIGNAL(valueEdited(double)),
          mot, SLOT(setUserPosition(double)));
  connect(sUi->rawPosition, SIGNAL(valueEdited(double)),
          mot, SLOT(setRawPosition(double)));
  connect(sUi->userVarGoal, SIGNAL(valueEdited(double)),
          mot, SLOT(goUserPosition(double)));
  connect(sUi->userGoal, SIGNAL(valueEdited(double)),
          mot, SLOT(goUserPosition(double)));
  connect(sUi->rawGoal, SIGNAL(valueEdited(double)),
          mot, SLOT(goRawPosition(double)));
  connect(sUi->callRelative, SIGNAL(clicked()),
          relativeDialog, SLOT(show()) );
  connect(sUi->offset, SIGNAL(valueEdited(double)),
          mot, SLOT(setOffset(double)));
  connect(sUi->limitLo, SIGNAL(valueEdited(double)),
          mot, SLOT(setUserLoLimit(double)));
  connect(sUi->limitHi, SIGNAL(valueEdited(double)),
          mot, SLOT(setUserHiLimit(double)));

  //
  // Connect Motor Signals
  //

  connect(mot, SIGNAL(changedPv(QString)),
          SLOT(updatePv(QString)));

  connect(mot, SIGNAL(changedDescription(QString)),
          SLOT(updateDescription(QString)));
  connect(mot, SIGNAL(changedPrecision(int)),
          SLOT(updatePrecision(int)));
  connect(mot, SIGNAL(changedUnits(QString)),
          SLOT(updateUnits(QString)));

  connect(mot, SIGNAL(changedUserPosition(double)),
          SLOT(updateUserPosition(double)));
  connect(mot, SIGNAL(changedDialPosition(double)),
          SLOT(updateDialPosition(double)));
  connect(mot, SIGNAL(changedRawPosition(double)),
          sUi->rawPosition, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedUserGoal(double)),
          sUi->userGoal, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedDialGoal(double)),
          sUi->dialGoal, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedRawGoal(double)),
          sUi->rawGoal, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedStep(double)),
          SLOT(updateStep(double)));

  connect(mot, SIGNAL(changedOffset(double)),
          sUi->offset, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedOffsetMode(QCaMotor::OffMode)),
          SLOT(updateOffsetMode(QCaMotor::OffMode)));
  connect(mot, SIGNAL(changedSuMode(QCaMotor::SuMode)),
          SLOT(updateSuMode(QCaMotor::SuMode)));
  connect(mot, SIGNAL(changedDirection(QCaMotor::Direction)),
          SLOT(updateDirection(QCaMotor::Direction)));
  connect(mot, SIGNAL(changedSpmgMode(QCaMotor::SpmgMode)),
          SLOT(updateSpmgMode(QCaMotor::SpmgMode)));

  connect(mot, SIGNAL(changedHiLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));
  connect(mot, SIGNAL(changedLoLimitStatus(bool)),
          SLOT(updateGoButtonStyle()));
  connect(mot, SIGNAL(changedDialHiLimit(double)),
          SLOT(updateDialHiLimit(double)));
  connect(mot, SIGNAL(changedDialLoLimit(double)),
          SLOT(updateDialLoLimit(double)));
  connect(mot, SIGNAL(changedUserHiLimit(double)),
          SLOT(updateUserHiLimit(double)));
  connect(mot, SIGNAL(changedUserLoLimit(double)),
          SLOT(updateUserLoLimit(double)));

  connect(mot, SIGNAL(changedMotorResolution(double)),
          sUi->unitsPerStep, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedReadbackResolution(double)),
          sUi->readbackResolution, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedEncoderResolution(double)),
          sUi->encoderResolution, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedStepsPerRev(int)),
          sUi->stepsPerRev, SLOT(setValue(int)));
  connect(mot, SIGNAL(changedUnitsPerRev(double)),
          SLOT(updateUnitsPerRev(double)));

  connect(mot, SIGNAL(changedMaximumSpeed(double)),
          SLOT(updateMaximumSpeed(double)));
  connect(mot, SIGNAL(changedNormalSpeed(double)),
          SLOT(updateNormalSpeed(double)));
  connect(mot, SIGNAL(changedRevSpeed(double)),
          sUi->revSpeed, SLOT(setValue(double)));
  connect(mot, SIGNAL(changedJogSpeed(double)),
          SLOT(updateJogSpeed(double)));
  connect(mot, SIGNAL(changedBacklashSpeed(double)),
          SLOT(updateBacklashSpeed(double)));

  connect(mot, SIGNAL(changedAcceleration(double)),
          SLOT(updateAcceleration(double)));
  connect(mot, SIGNAL(changedJogAcceleration(double)),
          SLOT(updateJogAcceleration(double)));
  connect(mot, SIGNAL(changedBacklashAcceleration(double)),
          SLOT(updateBacklashAcceleration(double)));

  connect(mot, SIGNAL(changedUseReadback(bool)),
          sUi->useReadback, SLOT(setChecked(bool)));
  connect(mot, SIGNAL(changedUseEncoder(bool)),
          sUi->useEncoder, SLOT(setChecked(bool)));

  connect(mot, SIGNAL(changedConnected(bool)),
          SLOT(updateConnection(bool)));
  connect(mot, SIGNAL(changedMoving(bool)),
          SLOT(updateMoving(bool)));
  connect(mot, SIGNAL(changedBacklash(double)),
          SLOT(updateBacklash(double)));
  connect(mot, SIGNAL(changedPower(bool)),
          SLOT(updatePower(bool)));
  connect(mot, SIGNAL(changedWired(bool)),
          SLOT(updateWired(bool)));


  setViewMode(COMFO);
  setupDialog->update();
  updatePower(mot->getPower());
  updateWired(mot->isWired());
  setStep();

}

void QCaMotorGUI::onMotorDestruction() {
  QString pv = mot->getPv();
  mot = new QCaMotor(pv, parent());
  init();
}



void QCaMotorGUI::copyPV() {
  if ( ! mot->getPv().isEmpty() )
    QApplication::clipboard()->setText(
          mot->getPv());
}

void QCaMotorGUI::copyDescription() {
  if ( ! mot->getDescription().isEmpty() )
    QApplication::clipboard()->setText(
          mot->getDescription());
}

void QCaMotorGUI::copyPosition() {
  if ( mot->isConnected() )
    QApplication::clipboard()->setText(
          QString::number(mot->getUserPosition()) );
}

void QCaMotorGUI::copyConfiguration() {
  if ( ! mot->isConnected() )
    QMessageBox::warning(0, "Warning!",
                         "Copying configuration of the disconnected motor.");
  QString cfg;
  QTextStream stream(&cfg);
  mot->saveConfiguration(stream);
  QApplication::clipboard()->setText(cfg);
}

void QCaMotorGUI::pasteConfiguration() {
  if ( ! mot->isConnected() ) {
    QMessageBox::warning(0, "Error",
                         "Cannot paste configuration because the motor is not connected.");
    return;
  }
  QString cfg = QApplication::clipboard()->text();
  QTextStream stream(&cfg);
  mot->loadConfiguration(stream);
}

void QCaMotorGUI::filterPV(const QString & _text){
  proxyModel->setSearch(_text);
//  proxyModel->setFilterRegExp( QRegExp(
//      QString(".*%1.*").arg(_text), Qt::CaseInsensitive) );
}

void QCaMotorGUI::choosePV(const QModelIndex & index){
  pvDialog->hide();
  mot->setPv(index.data(Qt::UserRole).toString());
}

void QCaMotorGUI::pvFromSearch(){
  pvDialog->hide();
  mot->setPv(pUi->search->text());
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

QPushButton * QCaMotorGUI::setupButton() {
  return mUi->setup;
}


Ui::MotorControl * QCaMotorGUI::basicUI() {
  return mUi;
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
  if (mot->getPv().isEmpty() )
    pvDialog->show();
  else
    setupDialog->show();
}




void QCaMotorGUI::onSave() {
  // WARNING: PORTING ISSUE.
  QString fileName = QFileDialog::getSaveFileName
                     (0, "Save configuration",
                      QDir::currentPath() + "/" + mot->getDescription() + "." + configsExt,
                      "All files (*);;Motor configuration files (*." + configsExt + ")");
  mot->saveConfiguration(fileName);
}

void QCaMotorGUI::onLoad(const QString & text) {
  QString fileName =  ( text == sUi->loadConfig->itemText(0) ) ?
        QFileDialog::getOpenFileName
        (0, "Load configuration", "",
         "Motor configuration files (*." + configsExt + ");;All files (*)") :
        knownConfigs[text];
  mot->loadConfiguration(fileName);
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
  } else if (text == "relative") {
    relativeDialog->show();
  } else if (text == "limit -") {
    mot->goLimit(-1);
    mUi->step->fixup();
  } else if (text == "limit +") {
    mot->goLimit(1);
    mUi->step->fixup();
  } else {
    if ( ok && val != mot->getStep() )
      mot->setStep(val);
    mUi->goM->setVisible(true);
    mUi->goP->setVisible(true);
    mUi->jogM->setVisible(false);
    mUi->jogP->setVisible(false);
  }
}


void QCaMotorGUI::setUnitsPerRevAndDirection(double res) {
  mot->setUnitsPerRev(qAbs(res));
  mot->setDirection( res < 0 ? QCaMotor::NEGATIVE : QCaMotor::POSITIVE );
}

void QCaMotorGUI::setSpeedS(double spd) {
  if (spd<=0.0)
    return;
  if ( ! sUi->lockMaximumSpeed->isChecked() ) {
    mot->setMaximumSpeed(spd);
    qtWait(200); // let the maximum speed to be updated.
  }
  if ( spd <= motor()->getMaximumSpeed() ) {
    mot->setJogSpeed(spd);
    mot->setBacklashSpeed(spd);
    mot->setNormalSpeed(spd);
  }
}

void QCaMotorGUI::setAccelerationS(double acc) {
  if (acc<=0.0)
    acc = sUi->accelerationS->value();
  mot->setBacklashAcceleration(acc);
  mot->setAcceleration(acc);
  if (acc)
    mot->setJogAcceleration( motor()->getNormalSpeed() / acc );
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

    if (mot->isConnected())
      mot->setSpmgMode(QCaMotor::GO);

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
    sUi->goHomeM->setVisible(false);
    sUi->goHomeP->setVisible(false);
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

    if (mot->isConnected())
      mot->setSpmgMode(QCaMotor::GO);

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
    sUi->goHomeM->setVisible(false);
    sUi->goHomeP->setVisible(false);
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

    if (mot->isConnected()) {
      mot->setOffsetMode(QCaMotor::FROZEN);
      mot->setSpmgMode(QCaMotor::GO);
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
    sUi->goHomeM->setVisible(true);
    sUi->goHomeP->setVisible(true);
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
    sUi->goHomeM->setVisible(true);
    sUi->goHomeP->setVisible(true);
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
  if (mot->isMoving()) mot->stop();
  else mot->undoLastMotion();
}


void QCaMotorGUI::updateConnection(bool suc) {
  sUi->message->setText
      ( suc ? "Connection established." : "Connection lost.");
  pasteCfgAction->setEnabled(suc);
  updateStopButtonStyle();
  updateAllElements();
  if ( suc &&
       sUi->viewMode->currentIndex() != EPICS &&
       mot->getOffsetMode() != QCaMotor::FROZEN )
    mot->setOffsetMode(QCaMotor::FROZEN);
}


void QCaMotorGUI::updateUserPosition(double ps) {
  mUi->userPosition->setValue(ps);
  sUi->userPosition->setValue(ps);
  sUi->userVarGoal->setValue(ps);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialPosition(double ps) {
  sUi->dialPosition->setValue(ps);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateStep(double stp) {
  sUi->step->setValue(stp);
  QString textStep = QString::number(stp);
  int knownIndex = mUi->step->findText(textStep);
  if (knownIndex == -1)
    mUi->step->insertItem(knownIndex = 4, textStep);
  mUi->step->setCurrentIndex(knownIndex);
}


void QCaMotorGUI::updateDescription(const QString & dsc){
  mUi->setup->setText(dsc);
  setupDialog->setWindowTitle(dsc);
  relativeDialog->setWindowTitle(dsc);
  sUi->description->setText(dsc);
}


void QCaMotorGUI::updateMoving(bool mov){

  updateAllElements();

  // Updates status of the jog buttons on stop
  if ( !mov ) {
    sUi->jogM->setDown(false);
    sUi->jogP->setDown(false);
    if ( mUi->goM->isDown() )
      mUi->goM->setDown(false);
    if ( mUi->goP->isDown() )
      mUi->goP->setDown(false);
  } else {
    mUi->userPosition->setFocus();
  }

  if (mov)
    sUi->message->setText("Moving...");
  else if (sUi->message->text() == "Moving...")
    sUi->message->clear();

  updateStopButtonStyle();

}


void QCaMotorGUI::updatePower(bool pwr) {

  bool pwrC = mot->getPowerConnection();

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


void QCaMotorGUI::updateWired(bool wr) {
  if (wr)
    sUi->message->setText("Cable connected.");
  else
    sUi->message->setText("Cable disconnected.");
  updateStopButtonStyle();
  updateAllElements();
}

void QCaMotorGUI::updateUnitsPerRev(double vRes) {
  sUi->unitsPerRev->setValue(vRes);
  if ( mot->getDirection() == QCaMotor::NEGATIVE )
    vRes *= -1.0;
  sUi->unitsPerRevAndDir->setValue(vRes);
}

void QCaMotorGUI::updateUnits(const QString & egu){
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
  sUi->jogAcceleration->setSuffix(egu+"/s"+QChar(0x00B2));
}

void QCaMotorGUI::updatePrecision(int prec){
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

void QCaMotorGUI::updateMaximumSpeed(double maxSpeed) {
  sUi->speed->setMaximum(maxSpeed);
  sUi->jogSpeed->setMaximum(maxSpeed);
  sUi->backlashSpeed->setMaximum(maxSpeed);
  sUi->maximumSpeed->setValue(maxSpeed);
  updateSpeeds();
}

void QCaMotorGUI::updateNormalSpeed(double spd) {
  sUi->speed->setValue(spd);
  sUi->speedS->setValue(spd);
  updateSpeeds();
}

void QCaMotorGUI::updateBacklashSpeed(double spd) {
  sUi->backlashSpeed->setValue(spd);
  updateSpeeds();
}

void QCaMotorGUI::updateJogSpeed(double spd) {
  sUi->jogSpeed->setValue(spd);
  updateSpeeds();
}

void QCaMotorGUI::updateAcceleration(double acc) {
  sUi->acceleration->setValue(acc);
  sUi->accelerationS->setValue(acc);
  updateAccelerations();
}

void QCaMotorGUI::updateBacklashAcceleration(double acc) {
  sUi->backlashAcceleration->setValue(acc);
  updateAccelerations();
}

void QCaMotorGUI::updateJogAcceleration(double acc) {
  sUi->jogAcceleration->setValue(acc);
  updateAccelerations();
}

void QCaMotorGUI::updateBacklash(double blsh) {
  sUi->backlash->setValue(blsh);
  if (blsh != 0.0 && mot->getBacklashSpeed() == 0.0) {
    mot->setBacklashSpeed(mot->getNormalSpeed());
    sUi->message->setText("Backlash speed set to normal speed.");
  }
}


void QCaMotorGUI::updateUserHiLimit(double hiL) {
  double loL=mot->getUserLoLimit();
  mUi->userPosition->setMaximum(hiL);
  sUi->userPosition->setMaximum(hiL);
  sUi->userGoal->setMaximum(hiL);
  sUi->userVarGoal->setMaximum(hiL);
  sUi->limitHi->setValue(hiL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateUserLoLimit(double loL) {
  double hiL=mot->getUserHiLimit();
  mUi->userPosition->setMinimum(loL);
  sUi->userPosition->setMinimum(loL);
  sUi->userGoal->setMinimum(loL);
  sUi->userVarGoal->setMinimum(loL);
  sUi->limitLo->setValue(loL);
  sUi->step->setRange(loL-hiL, hiL-loL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialHiLimit(double hiL){
  sUi->dialPosition->setMaximum(hiL);
  sUi->dialGoal->setMaximum(hiL);
  sUi->limitHiDial->setValue(hiL);
  updateGoButtonStyle();
}

void QCaMotorGUI::updateDialLoLimit(double loL){
  sUi->dialPosition->setMinimum(loL);
  sUi->dialGoal->setMinimum(loL);
  sUi->limitLoDial->setValue(loL);
  updateGoButtonStyle();
}



void QCaMotorGUI::updateSuMode(QCaMotor::SuMode mode) {
  sUi->setGroup->button(mode)->setChecked(true);
  // the rest is needed in here to revert to the original
  // values in the GUI.
  updateUserPosition(mot->getUserPosition());
  updateDialPosition(mot->getDialPosition());
  sUi->rawPosition->setValue(mot->getRawPosition());
  sUi->userGoal->setValue(mot->getUserGoal());
  sUi->dialGoal->setValue(mot->getDialGoal());
  sUi->rawGoal->setValue(mot->getRawGoal());
}

void QCaMotorGUI::updateOffsetMode(QCaMotor::OffMode mode) {
  sUi->offGroup->button(mode)->setChecked(true);
}

void QCaMotorGUI::updateDirection(QCaMotor::Direction dir) {
  updateUnitsPerRev(mot->getUnitsPerRev()); // needed to address the bug described in QCaMotor::setResolution().
  sUi->dirGroup->button(dir)->setChecked(true);
}

void QCaMotorGUI::updateSpmgMode(QCaMotor::SpmgMode mode) {
  sUi->spmgGroup->button(mode)->setChecked(true);
}


void QCaMotorGUI::updateSpeeds() {
  double spd = mot->getNormalSpeed();
  sUi->equalizeSpeeds->setVisible( spd != mot->getMaximumSpeed() ||
        spd != mot->getBacklashSpeed() ||  spd != mot->getJogSpeed() );
}

void QCaMotorGUI::updateAccelerations() {
  double acc = mot->getAcceleration();
  sUi->equalizeAccelerations->setVisible (
        acc != mot->getBacklashAcceleration() ||
      mot->getJogAcceleration() ||
      acc != mot->getNormalSpeed() / mot->getJogAcceleration() ) ;
}

void QCaMotorGUI::updateGoButtonStyle(){

  QString style;
  const QString hardStyle = "background-color: rgb(128, 0, 0); color: rgb(255, 255, 255);";
  const QString softStyle = "background-color: rgb(128, 64, 0); color: rgb(255, 255, 255);";

  if (mot->getLoLimitStatus())
    style = hardStyle;
  else if ( mot->getUserPosition() <= mot->getUserLoLimit() ||
            mot->getDialPosition() <= mot->getDialLoLimit() )
    style = softStyle;
  else
    style = "";
  mUi->goM->setStyleSheet(style);
  mUi->jogM->setStyleSheet(style);
  sUi->goM->setStyleSheet(style);
  sUi->goLimitM->setStyleSheet(style);
  sUi->goHomeM->setStyleSheet(style);
  sUi->jogM->setStyleSheet(style);

  if (mot->getHiLimitStatus())
    style = hardStyle;
  else if ( mot->getUserPosition() >= mot->getUserHiLimit() ||
            mot->getDialPosition() >= mot->getDialHiLimit() )
    style = softStyle;
  else
    style = "";
  mUi->goP->setStyleSheet(style);
  mUi->jogP->setStyleSheet(style);
  sUi->goP->setStyleSheet(style);
  sUi->goLimitP->setStyleSheet(style);
  sUi->goHomeP->setStyleSheet(style);
  sUi->jogP->setStyleSheet(style);


}

void QCaMotorGUI::updateStopButtonStyle() {

  static const QString
      movstyle("background-color: rgb(128, 0, 0); color: rgb(255, 255, 255);"),
      wrdstyle("color: rgb(255, 0, 0);");

  if ( ! mot->isConnected() ) {
    mUi->stop->setStyleSheet("");
    sUi->stop->setStyleSheet("");
    mUi->stop->setText("No link");
    sUi->stop->setText("No link");
  } else if (mot->isMoving()) {
    mUi->stop->setStyleSheet(movstyle);
    sUi->stop->setStyleSheet(movstyle);
    mUi->stop->setText("STOP");
    sUi->stop->setText("STOP");
    mUi->stop->setToolTip("Stop motion");
    sUi->stop->setToolTip("Stop motion");
  } else if ( ! mot->isWired() ) {
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
    double undo = - ( mot->getDirection() == QCaMotor::NEGATIVE ? -1.0 : 1.0) *
        mot->getMotorResolution() * mot->getLastMotion();
    const QString txt("Undo last motion ("
                      + QString::number(undo) + mot->getUnits() + ")");
    mUi->stop->setToolTip(txt);
    sUi->stop->setToolTip(txt);
  }

}

void QCaMotorGUI::updateAllElements(){

  bool
      pwr = mot->getPower(),
      mv  = mot->isMoving(),
      cn  = mot->isConnected(),
      wr  = mot->isWired(),
      std = cn && !mv;

  rUi->goRelative             ->setEnabled(std && wr && pwr);

  mUi->goM                    ->setEnabled(std && wr && pwr);
  mUi->goP                    ->setEnabled(std && wr && pwr);
  mUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogM->isDown()) );
  mUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || mUi->jogP->isDown()) );
  mUi->userPosition           ->setEnabled(std && wr && pwr);
  mUi->step                   ->setEnabled(std);
  mUi->stop                   ->setEnabled(cn && wr && pwr);

  sUi->goLimitM               ->setEnabled(std && wr && pwr);
  sUi->goLimitP               ->setEnabled(std && wr && pwr);
  sUi->goHomeM               ->setEnabled(std && wr && pwr);
  sUi->goHomeP               ->setEnabled(std && wr && pwr);
  sUi->goM                    ->setEnabled(std && wr && pwr);
  sUi->goP                    ->setEnabled(std && wr && pwr);
  sUi->jogM                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogM->isDown()) );
  sUi->jogP                   ->setEnabled
    (cn && pwr && wr && ( ! mv || sUi->jogP->isDown()) );
  sUi->stop                   ->setEnabled(cn && wr && pwr);
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
