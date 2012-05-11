#ifndef MOTORCONTROLDESIGNER_H
#define MOTORCONTROLDESIGNER_H

#include <QtDesigner>
#include <qplugin.h>

class MotorControlDesigner : public QObject, public QDesignerCustomWidgetCollectionInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
  
public:
  explicit MotorControlDesigner(QObject *parent = 0);
  
  virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
  
private:
  QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif
