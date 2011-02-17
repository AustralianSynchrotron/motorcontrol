#include "motormx_mainwindow.h"
#include "ui_mainwindow.h"

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
  ui(new Ui::MainWindow),
  ms(new QMotorStack("motormxListOfMotors.txt", this))
{

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


  ui->statusBar->addPermanentWidget(new QLabel("  GUI:"));

  QPushButton * reset = new QPushButton("Reset");
  reset->setFlat(true);
  connect(reset, SIGNAL(clicked()), ms, SLOT(resetHeader()));
  ui->statusBar->addPermanentWidget(reset);

  QCheckBox * lock = new QCheckBox("Lock");
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
