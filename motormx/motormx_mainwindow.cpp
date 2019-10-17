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
  loadBut(new QToolButton(this))
{

  //QEpicsPv::setDebugLevel(1);

  QDir configDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
  if ( ! configDir.exists() )
    configDir.mkpath(configDir.path());
  ms = new QMotorStack( configDir.canonicalPath() +  "/listOfMotorsInUI.txt", this);

  ui->setupUi(this);
  setCentralWidget(ms);

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
  loadBut->setMenu(menu);

  ui->statusBar->addPermanentWidget(loadBut);

  const QFont roItemFont(QFont().family(),-1,-1,true);
  presets->setDuplicatesEnabled(true);
  presets->addItem("to / from file");
  foreach(QString pth, QStandardPaths::standardLocations(QStandardPaths::AppDataLocation) ) {
    QDir dir(pth);
    foreach(QFileInfo cfg, dir.entryInfoList(QStringList() << "*." + motsExt, QDir::Files) ) {
      presets->addItem(cfg.baseName(), cfg.canonicalFilePath());
      presets->setItemData(presets->count()-1, cfg.canonicalFilePath(), Qt::ToolTipRole);
      if (!cfg.isWritable())
        presets->setItemData(presets->count()-1, roItemFont, Qt::FontRole);
    }
  }
  connect(presets, SIGNAL(currentIndexChanged(int)), SLOT(onPresetChanged()));
  ui->statusBar->addPermanentWidget(presets);

}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::saveConfiguration(bool params, bool select){

  QList<QCaMotorGUI*> motorList(ms->motorList());
  if (select) {
    QStringList selectedMotorList = selectMotors(false, ms->nameList(), true);
    foreach (QCaMotorGUI * motor, motorList)
      if ( ! selectedMotorList.contains(motor->motor()->getPv()) )
        motorList.removeAll(motor);
  }

  const QVariant & curData = presets->currentData();
  const QString fileName  =  curData.isValid()  ?  curData.toString()
    :  QFileDialog::getSaveFileName(0, "Save configuration", QString(),
                                    "(*."+motsExt+");;All files (*)");
  if (fileName.isEmpty() || ! ms->count() )
    return;
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

  const QFileInfo cfg(fileName);
  if ( ! curData.isValid() and cfg.exists() ) {
    presets->addItem(cfg.baseName(), cfg.canonicalFilePath());
    presets->setItemData(presets->count()-1, cfg.canonicalFilePath(), Qt::ToolTipRole);
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

  const QVariant & curData = presets->currentData();
  const QStringList fileNames  =  curData.isValid()  ?  QStringList() << curData.toString()
    :  QFileDialog::getOpenFileNames(0, "Load configuration(s)", QString(),
                                    "(*."+motsExt+");;All files (*)");
  if (fileNames.isEmpty())
    return;

  QStringList motorList;
  const QRegularExpression repv("^# MOTORPV (\\w+)$");
  foreach( QString fileName, fileNames ) {
    QFile file(fileName);
    if ( ! file.open(QFile::ReadOnly) ) {
      QMessageBox::warning(this, "Can't open", "Failed to open requested file: " + fileName);
    } else {
      QTextStream fileStream(&file);
      QString fline;
      while (fileStream.readLineInto(&fline)) {
        QRegularExpressionMatch match = repv.match(fline);
        if (match.hasMatch())
          motorList << match.captured(1);
      }
      file.close();
    }
  }

  motorList.removeDuplicates();
  if (select)
    motorList = selectMotors(false, motorList, true);

  if (add)
    foreach(QString pvn, motorList)
      ms->addMotor(pvn);

  if (move) {
    const QRegularExpression rego("^caput (\\w+) \\d+$");
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
            QRegularExpressionMatch match = repv.match(fline);
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





void MainWindow::onPresetChanged() {
  presets->setToolTip(presets->currentData(Qt::ToolTipRole).toString());
  if (presets->currentData(Qt::FontRole).isValid())
    saveBut->setEnabled( ! presets->currentData(Qt::FontRole).value<QFont>().italic() );
}

