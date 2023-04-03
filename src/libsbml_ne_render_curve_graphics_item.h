#ifndef __LIBSBML_NE_RENDER_CURVE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_RENDER_CURVE_GRAPHICS_ITEM_H

#include "libsbml_ne_1d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyRenderCurveGraphicsItem : public My1DShapeGraphicsItem, public QGraphicsPathItem {

public:
    MyRenderCurveGraphicsItem(QGraphicsItem* parent = nullptr);

    void updateFeatures(RenderGroup* group, RenderCurve* renderCurve, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);

    const QPainterPath getRenderCurve(RenderCurve* renderCurve, BoundingBox* boundingBox);
};

#endif
