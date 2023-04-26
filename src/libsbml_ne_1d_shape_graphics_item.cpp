#include "libsbml_ne_1d_shape_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

My1DShapeGraphicsItem::My1DShapeGraphicsItem() {
    
}

const QPen My1DShapeGraphicsItem::getPen(RenderGroup* group) {
    return getPen(group, QPen(QBrush(Qt::black), 2.0 ,Qt::SolidLine));
}

const QPen My1DShapeGraphicsItem::getPen(GraphicalPrimitive1D* graphicalPrimitive1D, QPen pen) {
    if (isSetStrokeWidth(graphicalPrimitive1D))
        pen.setWidth(getStrokeWidth(graphicalPrimitive1D));
    
    if (isSetStrokeColor(graphicalPrimitive1D)) {
        ColorDefinition* color = emit askForColorDefinition(getStrokeColor(graphicalPrimitive1D).c_str());
        if (color)
            pen.setColor(QColor(color->getValue().c_str()));
        else
            pen.setColor(QColor(getStrokeColor(graphicalPrimitive1D).c_str()));
    }
    
    if (isSetStrokeDashArray(graphicalPrimitive1D)) {
        QVector<qreal> dashes;
        for (unsigned int i = 0; i < getNumStrokeDashes(graphicalPrimitive1D); i++)
            dashes.push_back(qreal(getDash(graphicalPrimitive1D, i)));
        pen.setDashPattern(dashes);
    }
    
    return pen;
}
