#include "motormx_mainwindow.h"
#include "ui_motormx_mainwindow.h"

#include <iostream>

#include <QLabel>
#include <QScrollBar>
#include <QPoint>
#include <QCursor>
#include <QPaintEvent>
#include <QTimer>
#include <QCheckBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QErrorMessage>
#include <QMessageBox>
#include <QTemporaryFile>
#include <QProcess>

static const QString motsExt = "motors.sh";

MainWindow::MainWindow(QWidget *parent)  :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  presets(new QComboBox(this)),
  saveBut(new QToolButton(this)),
  loadBut(new QToolButton(this)),
  configDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation))
{

  //QEpicsPv::setDebugLevel(1);

  if ( ! configDir.exists() )
    configDir.mkpath(configDir.path());
  ms = new QMotorStack( configDir.canonicalPath() +  "/listOfMotorsInUI.txt", this);

  ui->setupUi(this);
  setCentralWidget(ms);
  ms->setFocus();

  QLabel * conf = new QLabel("Presets:");
  ui->statusBar->addPermanentWidget(conf);

  QMenu * menu;

  saveBut->setText("Save");
  saveBut->setPopupMode(QToolButton::MenuButtonPopup);
  connect(saveBut, SIGNAL(clicked()), SLOT(onSave()));
  menu = new QMenu(saveBut);
  menu->addAction("Save selectively", this, SLOT(onSelectiveSave()));
  menu->addAction("Save with configurations", this, SLOT(onConfigSave()));
  menu->addAction("Save selectively with configurations", this, SLOT(onSelectiveConfigSave()));
  saveBut->setMenu(menu);
  ui->statusBar->addPermanentWidget(saveBut);

  loadBut->setText("Restore");
  loadBut->setPopupMode(QToolButton::MenuButtonPopup);
  connect(loadBut, SIGNAL(clicked()), SLOT(onLoad()));
  menu = new QMenu(loadBut);
  menu->addAction("Add motors to the list", this, SLOT(onListLoad()));
  menu->addAction("Restore and add motors", this, SLOT(onMoveLoad()));
  menu->addAction("Add presets from directory", this, SLOT(onDirectoryLoad()));
  loadBut->setMenu(menu);
  ui->statusBar->addPermanentWidget(loadBut);

  presets->setInsertPolicy(QComboBox::NoInsert);
  presets->setEditable(true);
  presets->addItem("to / from file", "to / from file");
  onDirectoryLoad(QStringList() << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)
                                << QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation)
                                << QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)
                                << QStandardPaths::standardLocations(QStandardPaths::GenericConfigLocation));
  connect(presets, SIGNAL(currentTextChanged(QString)), SLOT(onPresetChanged()));
  presets->installEventFilter(this);
  ui->statusBar->addPermanentWidget(presets);
  QDir::setCurrent(configDir.canonicalPath());

}

MainWindow::~MainWindow() {
  delete ui;
}


bool MainWindow::event(QEvent *ev) {
  if(ev->type() == QEvent::LayoutRequest)
    setFixedWidth(sizeHint().width());
  return QMainWindow::event(ev);
}


bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
  if (obj == presets) {
    if ( event->type() == QEvent::FocusIn  &&  ! presets->currentIndex())
      presets->clearEditText();
    if ( event->type() == QEvent::FocusOut  &&  presets->currentText().trimmed().isEmpty())
      presets->setCurrentIndex(0);
  }
  return QMainWindow::eventFilter(obj,event);
}




void MainWindow::saveConfiguration(bool params, bool select){

  QList<QCaMotorGUI*> motorList(ms->motorList());
  if (select) {
    QStringList selectedMotorList = selectMotors(false, ms->nameList(), true);
    foreach (QCaMotorGUI * motor, motorList)
      if ( ! selectedMotorList.contains(motor->motor()->getPv()) )
        motorList.removeAll(motor);
  }

  QString fileName = fileSL();
  if (fileName.isEmpty())
    fileName = QFileDialog::getSaveFileName(
      0, "Save configuration", QDir::currentPath(), "(*."+motsExt+");;All files (*)");
  if (fileName.isEmpty() || ! ms->count() )
    return;

  QDir::setCurrent(QFileInfo(fileName).canonicalPath());
  QFile file(fileName);
  if ( ! file.open(QFile::WriteOnly | QFile::Truncate) ) {
    QMessageBox::warning(this, "Can't save", "Failed to open requested file: " + fileName);
    return;
  }
  QTextStream fileStream(&file);

  foreach (QCaMotorGUI * motor, motorList ) {
    motor->motor()->saveConfiguration(fileStream, params);
    fileStream << "\n";
  }

  file.close();
  file.setPermissions( (QFileDevice::Permission) 0x7777);

  const QFileInfo cfg(fileName);
  if ( 0 > presets->findData(cfg.canonicalFilePath()) ) {
    presets->addItem(cfg.baseName(), cfg.canonicalFilePath());
    presets->setItemData(presets->count()-1, cfg.canonicalFilePath(), Qt::ToolTipRole);
    onPresetChanged();
  }

}


void MainWindow::onSave(){
  saveConfiguration(false, false);
}

void MainWindow::onSelectiveSave(){
  saveConfiguration(false, true);
}

void MainWindow::onConfigSave(){
  saveConfiguration(true, false);
}

void MainWindow::onSelectiveConfigSave(){
  saveConfiguration(true, true);
}



void MainWindow::loadConfiguration(bool move, bool add, bool select) {

  QStringList fileNames( QStringList() << fileSL() );
  if (fileNames.at(0).isEmpty())
    fileNames = QFileDialog::getOpenFileNames(0, "Load configuration(s)", QDir::currentPath(),
                                              "(*."+motsExt+");;All files (*)");
  if (fileNames.isEmpty())
    return;

  QStringList motorList;
  const QRegularExpression repv("^\\# MOTORPV (.*)$");
  foreach( QString fileName, fileNames ) {
    QFile file(fileName);
    if ( ! file.open(QFile::ReadOnly) ) {
      QMessageBox::warning(this, "Can't open", "Failed to open requested file: " + fileName);
    } else {
      QDir::setCurrent(QFileInfo(fileName).canonicalPath());
      QTextStream fileStream(&file);
      QString fline;
      while (fileStream.readLineInto(&fline)) {
        QRegularExpressionMatch match = repv.match(fline);
        if (match.hasMatch())
          motorList << match.captured(1);
      }
      file.close();
      const QFileInfo cfg(file);
      presets->addItem(cfg.baseName(), cfg.canonicalFilePath());
      presets->setItemData(presets->count()-1, cfg.canonicalFilePath(), Qt::ToolTipRole);
    }
  }
  onPresetChanged();

  motorList.removeDuplicates();
  if (select)
    motorList = selectMotors(false, motorList, true);

  if (add)
    foreach(QString pvn, motorList)
      ms->addMotor(pvn);

  if (move) {
    const QRegularExpression rego("^caput (.+) [\\.0-9]+$");
    QTemporaryFile ofile;
    QTextStream oStream(&ofile);
    if (!ofile.open()) {
      qDebug() << "Error! Failed to open temporary file" << ofile.fileName();
    } else {
      foreach( QString fileName, QStringList(fileNames) ) {
        QFile ifile(fileName);
        if ( ! ifile.open(QFile::ReadOnly) ) {
          QMessageBox::warning(this, "Can't open", "Failed to open requested file: " + fileName);
        } else {
          QTextStream iStream(&ifile);
          QString fline;
          while (iStream.readLineInto(&fline)) {
            QRegularExpressionMatch match = rego.match(fline);
            if ( match.hasMatch() &&
                 ( ! select  ||  motorList.contains(match.captured(1)) ) )
              oStream << fline;
          }
        }
        ifile.close();
      }
      QProcess::execute( "/bin/sh " + ofile.fileName());
    }
  }

}




void MainWindow::onLoad() {
  loadConfiguration(true, false, false);
}

void MainWindow::onListLoad() {
  loadConfiguration(false, true, true);
}

void MainWindow::onMoveLoad() {
  loadConfiguration(true, false, true);
}

void MainWindow::onDirectoryLoad(const QStringList & pths) {
  foreach(QString pth, pths)
    if (!pth.isEmpty())
      onDirectoryLoad(pth);
}

void MainWindow::onDirectoryLoad(QString dirName) {

  if (dirName.isEmpty())
      dirName = QFileDialog::getExistingDirectory(0, "Load presets from the directory", QString());
  if (dirName.isEmpty())
    return;

  const QFont roItemFont(QFont().family(),-1,-1,true);
  QDir dir(dirName);
  QDir::setCurrent(dir.canonicalPath());
  foreach(QFileInfo cfg, dir.entryInfoList(QStringList() << "*." + motsExt, QDir::Files) ) {
    qDebug() << cfg.canonicalFilePath();
    presets->addItem(cfg.baseName(), cfg.canonicalFilePath());
    presets->setItemData(presets->count()-1, cfg.canonicalFilePath(), Qt::ToolTipRole);
    if (!cfg.isWritable())
      presets->setItemData(presets->count()-1, roItemFont, Qt::FontRole);
  }

}


QString MainWindow::fileSL() {
  const QString curText = presets->currentText();
  const int fndIdx = presets->findText(curText);
  if ( curText.isEmpty() || curText == presets->itemText(0) )
    return QString();
  else if ( fndIdx > 0 )
    return presets->itemData(fndIdx).toString();
  else
    return configDir.canonicalPath() + "/" + curText + "." + motsExt;
}



void MainWindow::onPresetChanged() {

  presets->setToolTip(presets->currentData(Qt::ToolTipRole).toString());
  const QString ctxt = presets->currentText();
  const int txtIdx = presets->findText(ctxt);
  if ( txtIdx > 0 )
    presets->setCurrentIndex(txtIdx>0 ? txtIdx : 0);

  const QFileInfo flInf(fileSL());
  loadBut->setEnabled( flInf.fileName().isEmpty() || ( flInf.exists() && flInf.isReadable() ) );
  saveBut->setEnabled( flInf.fileName().isEmpty() || ! flInf.exists() || flInf.isWritable() );

}

