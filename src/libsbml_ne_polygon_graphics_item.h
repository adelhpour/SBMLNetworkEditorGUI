#ifndef __LIBSBML_NE_POLYGON_GRAPHICS_ITEM_H
#define __LIBSBML_NE_POLYGON_GRAPHICS_ITEM_H

#include "libsbml_ne_2d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyPolygonGraphicsItem : public My2DShapeGraphicsItem, public QGraphicsPolygonItem {
    
public:
    MyPolygonGraphicsItem(QGraphicsItem* parent = nullptr);
    
    void updateFeatures(RenderGroup* group, Polygon* polygon, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);
    
    const QPolygonF getPolygon(Polygon* polygon, BoundingBox* boundingBox);
};

#endif
