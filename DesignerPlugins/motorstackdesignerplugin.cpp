#include "motorstackdesigner.h"
#include "motorstackdesignerplugin.h"

#include <QtPlugin>

MotorStackDesignerPlugin::MotorStackDesignerPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void MotorStackDesignerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;
  
  // Add extension registrations, etc. here
  
  m_initialized = true;
}

bool MotorStackDesignerPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *MotorStackDesignerPlugin::createWidget(QWidget *parent)
{
  return new MotorStackDesigner(parent);
}

QString MotorStackDesignerPlugin::name() const
{
  return QLatin1String("MotorStackDesigner");
}

QString MotorStackDesignerPlugin::group() const
{
  return QLatin1String("");
}

QIcon MotorStackDesignerPlugin::icon() const
{
  return QIcon();
}

QString MotorStackDesignerPlugin::toolTip() const
{
  return QLatin1String("");
}

QString MotorStackDesignerPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool MotorStackDesignerPlugin::isContainer() const
{
  return false;
}

QString MotorStackDesignerPlugin::domXml() const
{
  return QLatin1String("<widget class=\"MotorStackDesigner\" name=\"motorStackDesigner\">\n</widget>\n");
}

QString MotorStackDesignerPlugin::includeFile() const
{
  return QLatin1String("motorstackdesigner.h");
}

