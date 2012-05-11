#include "qcamotordesigner.h"
#include "qcamotordesignerplugin.h"

#include <QtPlugin>

QCaMotorDesignerPlugin::QCaMotorDesignerPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QCaMotorDesignerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QCaMotorDesignerPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QCaMotorDesignerPlugin::createWidget(QWidget *parent)
{
  return new QCaMotorDesigner(parent);
}

QString QCaMotorDesignerPlugin::name() const
{
  return QLatin1String("QCaMotorDesigner");
}

QString QCaMotorDesignerPlugin::group() const
{
  return QLatin1String("");
}

QIcon QCaMotorDesignerPlugin::icon() const
{
  return QIcon();
}

QString QCaMotorDesignerPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QCaMotorDesignerPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QCaMotorDesignerPlugin::isContainer() const
{
  return false;
}

QString QCaMotorDesignerPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QCaMotorDesigner\" name=\"qCaMotorDesigner\">\n</widget>\n");
}

QString QCaMotorDesignerPlugin::includeFile() const
{
  return QLatin1String("qcamotordesigner.h");
}

