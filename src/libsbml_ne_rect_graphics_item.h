#ifndef __LIBSBML_NE_RECT_GRAPHICS_ITEM_H
#define __LIBSBML_NE_RECT_GRAPHICS_ITEM_H

#include "libsbml_ne_2d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyRectGraphicsItem : public My2DShapeGraphicsItem, public QGraphicsPathItem {
    
public:
    MyRectGraphicsItem(QGraphicsItem* parent = nullptr);
    
    void updateFeatures(RenderGroup* group, Rectangle* rectangle, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    const QRectF getRect(Rectangle* rectangle, BoundingBox* boundingBox);
    
    const qreal getRX(Rectangle* rectangle, BoundingBox* boundingBox);
    
    const qreal getRY(Rectangle* rectangle, BoundingBox* boundingBox);
};

#endif
