#include "qcamotordesignerplugin.h"
#include "motorstackdesignerplugin.h"
#include "motorcontroldesigner.h"

MotorControlDesigner::MotorControlDesigner(QObject *parent)
  : QObject(parent)
{
  m_widgets.append(new QCaMotorDesignerPlugin(this));
  m_widgets.append(new MotorStackDesignerPlugin(this));
  
}

QList<QDesignerCustomWidgetInterface*> MotorControlDesigner::customWidgets() const
{
  return m_widgets;
}

Q_EXPORT_PLUGIN2(motorcontroldesignerplugin, MotorControlDesigner)
