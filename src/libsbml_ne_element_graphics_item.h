#ifndef __LIBSBML_NE_ELEMENT_GRAPHICS_ITEM_H
#define __LIBSBML_NE_ELEMENT_GRAPHICS_ITEM_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class MyElementGraphicsItem : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    
public:
    MyElementGraphicsItem(const qreal& zValue, QGraphicsItem* parent = nullptr);
    
    void clear();
    
    void addGeometricShapes(RenderGroup* group, BoundingBox* boundingBox, const QPointF& position = QPointF(0.0, 0.0), const qreal& rotation = 0.0);
    
    void addGeometricShape(RenderGroup* group, Transformation2D* geometricShape, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    void addRectangleGraphicsItem(RenderGroup* group, Rectangle* rectangle, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    void addEllipseGraphicsItem(RenderGroup* group, Ellipse* ellipse, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    void addPolygonGraphicsItem(RenderGroup* group, Polygon* polygon, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);

    void addRenderCurveGraphicsItem(RenderGroup* group, RenderCurve* renderCurve, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);

    void addImageGraphicsItem(Image* image, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);

    void addCurveGraphicsItem(RenderGroup* group, Curve* curve);
    
    void addTextGraphicsItem(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText);
    
signals:
    
    ColorDefinition* askForColorDefinition(const QString&);
    GradientBase* askForGradientDefinition(const QString&);
    
    void mouseLeftButtonIsDoubleClicked();
    
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif
