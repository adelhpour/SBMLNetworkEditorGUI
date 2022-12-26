#ifndef __LIBSBML_NE_ELLIPSE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_ELLIPSE_GRAPHICS_ITEM_H

#include "libsbml_ne_2d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyEllipseGraphicsItem : public My2DShapeGraphicsItem, public QGraphicsEllipseItem {
    
public:
    MyEllipseGraphicsItem(QGraphicsItem* parent = nullptr);
    
    void updateFeatures(RenderGroup* group, Ellipse* ellipse, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    const QRectF getRect(Ellipse* ellipse, BoundingBox* boundingBox);
};

#endif
