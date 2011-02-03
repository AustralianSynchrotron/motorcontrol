#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QScrollBar>
#include <QPoint>
#include <QCursor>
#include <QPaintEvent>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)  :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  ms(new QMotorStack("motormxListOfMotors.txt", this))
{
  ui->setupUi(this);
  setCentralWidget(ms);
}

MainWindow::~MainWindow() {
  delete ui;
}
