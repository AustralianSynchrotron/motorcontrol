#include "interbutt.h"

interbutt::interbutt(QWidget *parent) :
  QWidget(parent)
{

  horizontalLayout = new QHBoxLayout(this);
  horizontalLayout->setContentsMargins(0, 0, 0, 0);
  horizontalLayout->setSpacing(0);

  _remove = new QToolButton(this);
  _remove->setText("-");
  _remove->setToolTip("Remove the motor from the main interface.");
  connect(_remove, SIGNAL(clicked()), this, SLOT(on_remove_clicked()));
  horizontalLayout->addWidget(_remove);

  _up = new QToolButton(this);
  _up->setArrowType(Qt::UpArrow);
  _up->setToolTip("Move motor one step up");
  connect(_up, SIGNAL(clicked()), this, SLOT(on_up_clicked()));
  horizontalLayout->addWidget(_up);

  _down = new QToolButton(this);
  _down->setArrowType(Qt::DownArrow);
  _down->setToolTip("Move motor one step down");
  connect(_down, SIGNAL(clicked()), this, SLOT(on_down_clicked()));
  horizontalLayout->addWidget(_down);


}

interbutt::~interbutt(){
}

void interbutt::on_remove_clicked() {
  emit remove(this);
}

void interbutt::on_up_clicked() {
  emit up(this);
}

void interbutt::on_down_clicked() {
  emit down(this);
}
