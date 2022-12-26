#include "libsbml_ne_1d_shape_graphics_item.h"

My1DShapeGraphicsItem::My1DShapeGraphicsItem() {
    
}

const QPen My1DShapeGraphicsItem::getPen(RenderGroup* group) {
    return getPen(group, QPen(QBrush(Qt::black), 2.0 ,Qt::SolidLine));
}

const QPen My1DShapeGraphicsItem::getPen(GraphicalPrimitive1D* graphicalPrimitive1D, QPen pen) {
    if (graphicalPrimitive1D->isSetStrokeWidth())
        pen.setWidth(graphicalPrimitive1D->getStrokeWidth());
    
    if (graphicalPrimitive1D->isSetStroke()) {
        ColorDefinition* color = emit askForColorDefinition(graphicalPrimitive1D->getStroke().c_str());
        if (color)
            pen.setColor(QColor(color->getValue().c_str()));
        else
            pen.setColor(QColor(graphicalPrimitive1D->getStroke().c_str()));
    }
    
    if (graphicalPrimitive1D->isSetDashArray()) {
        QVector<qreal> dashes;
        for (unsigned int i = 0; i < graphicalPrimitive1D->getDashArray().size(); i++)
            dashes.push_back(qreal(graphicalPrimitive1D->getDashByIndex(i)));
        pen.setDashPattern(dashes);
    }
    
    return pen;
}
