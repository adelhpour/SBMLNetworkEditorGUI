#ifndef __LIBSBML_NE_2D_SHAPE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_2D_SHAPE_GRAPHICS_ITEM_H

#include "libsbml_ne_1d_shape_graphics_item.h"

class My2DShapeGraphicsItem : public My1DShapeGraphicsItem {
    
public:
    My2DShapeGraphicsItem();
    
    const QBrush getBrush(RenderGroup* group, BoundingBox* boundingBox);
    
    const QBrush getBrush(GraphicalPrimitive2D* graphicalPrimitive2D, BoundingBox* boundingBox, QBrush brush);
    
    QGradient getGradient(GradientBase* gradientBase, BoundingBox* boundingBox);
    
    QGradient* createLinearGradient(LinearGradient* linearGradinet, BoundingBox* boundingBox);
    
    QGradient* createRadialGradient(RadialGradient* radialGradient, BoundingBox* boundingBox);
    
    void setGradientFeatures(QGradient* gradient, GradientBase* gradientBase);
};

#endif
