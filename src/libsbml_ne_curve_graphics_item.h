#ifndef __LIBSBML_NE_CURVE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_CURVE_GRAPHICS_ITEM_H

#include "libsbml_ne_1d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyCurveGraphicsItem : public My1DShapeGraphicsItem, public QGraphicsPathItem {
    
public:
    MyCurveGraphicsItem(QGraphicsItem* parent = nullptr);
    
    void updateFeatures(RenderGroup* group, Curve* curve);
    
    const QPainterPath getCurve(Curve* curve);
};

#endif
