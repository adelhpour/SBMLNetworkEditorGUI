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
    
    const QRectF getExtents();
    
    virtual const QString getType() = 0;
    
    virtual const QString getId() = 0;

    GraphicalObject* getGraphicalObject();

    Style* getStyle();
    
    const QString getGlyphId();
    
    QWidget* getFeatureMenu();
    
    virtual QWidget* elementFeatureMenu();
    
signals:
    void askForSetDocumentModified();
    SBase* askForModelEntity(const QString&);
    GraphicalObject* askForGraphicalObject(const QString&);
    QList<QWidget*> askForAssociatedTextsMenu(const QString&);
    ColorDefinition* askForColorDefinition(const QString&);
    GradientBase* askForGradientDefinition(const QString&);
    LineEnding* askForLineEnding(const QString&);
    void askForDisplayFeatureMenu(QWidget*);
    void isUpdated();
    
public slots:
    
    virtual void updateGraphicsItem() = 0;
    
protected:
    GraphicalObject* _graphicalObject;
    Style* _style;
    QGraphicsItem* _graphicsItem;
};

#endif
