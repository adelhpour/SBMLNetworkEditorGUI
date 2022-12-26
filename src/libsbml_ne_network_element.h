#ifndef __LIBSBML_NE_NETWORK_ELEMENT_H
#define __LIBSBML_NE_NETWORK_ELEMENT_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include <QObject>
#include <QGraphicsItem>

class MyNetworkElementBase : public QObject {
Q_OBJECT
    
public:
    MyNetworkElementBase(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    QGraphicsItem* graphicsItem();
    
    virtual void updateGraphicsItem() = 0;
    
    const QRectF getExtents();
    
signals:
    SBase* askForModelEntity(const QString&);
    GraphicalObject* askForGraphicalObject(const QString&);
    ColorDefinition* askForColorDefinition(const QString&);
    GradientBase* askForGradientDefinition(const QString&);
    LineEnding* askForLineEnding(const QString&);
    
protected:
    GraphicalObject* _graphicalObject;
    Style* _style;
    QGraphicsItem* _graphicsItem;
};

#endif
