#include "motormx_mainwindow.h"
#include "ui_motormx_mainwindow.h"

#include <iostream>

#include <QScrollBar>
#include <QPoint>
#include <QCursor>
#include <QPaintEvent>
#include <QTimer>
#include <QCheckBox>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)  :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  //QEpicsPv::setDebugLevel(1);

  const QString configPath = QString(getenv("HOME")) + "/." + QCaMotorGUI::configsSearchBaseDir;
  QDir configDir(configPath);
  if ( ! configDir.exists() )
    configDir.mkpath(configPath);
  ms = new QMotorStack( configPath +  "/listOfMotorsInUI.txt", this);

  ui->setupUi(this);
  setCentralWidget(ms);

  QLabel * conf = new QLabel("Configuration:");
  ui->statusBar->addPermanentWidget(conf);

  QPushButton * save = new QPushButton("Save");
  save->setFlat(true);
  connect(save, SIGNAL(clicked()), SLOT(onSave()));
  ui->statusBar->addPermanentWidget(save);

  QPushButton * load = new QPushButton("Load");
  load->setFlat(true);
  connect(load, SIGNAL(clicked()), SLOT(onLoad()));
  ui->statusBar->addPermanentWidget(load);

  QCheckBox * lock = new QCheckBox("Lock GUI");
  connect(lock, SIGNAL(toggled(bool)), ms, SLOT(lock(bool)));
  connect(lock, SIGNAL(toggled(bool)), save, SLOT(setHidden(bool)));
  connect(lock, SIGNAL(toggled(bool)), load, SLOT(setHidden(bool)));
  connect(lock, SIGNAL(toggled(bool)), conf, SLOT(setHidden(bool)));
  lock->setCheckState(Qt::Unchecked);
  ui->statusBar->addPermanentWidget(lock);

}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onSave(){
  QString fileName = QFileDialog::getSaveFileName(0, "Save configuration");
  ms->saveConfiguration(fileName);
}

void MainWindow::onLoad() {
  QString fileName = QFileDialog::getOpenFileName(0, "Load configuration");
  ms->loadConfiguration(fileName);
}
