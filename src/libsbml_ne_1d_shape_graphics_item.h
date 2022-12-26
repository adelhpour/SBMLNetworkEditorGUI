#ifndef __LIBSBML_NE_1D_SHAPE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_1D_SHAPE_GRAPHICS_ITEM_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include <QPen>
#include <QFont>

class My1DShapeGraphicsItem : public QObject {
    Q_OBJECT
    
public:
    My1DShapeGraphicsItem();
    
    const QPen getPen(RenderGroup* group);
    
    const QPen getPen(GraphicalPrimitive1D* graphicalPrimitive1D, QPen pen);
    
signals:
    
    ColorDefinition* askForColorDefinition(const QString&);
    
    GradientBase* askForGradientDefinition(const QString&);
};

#endif
