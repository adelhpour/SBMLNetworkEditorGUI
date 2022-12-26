#include "libsbml_ne_reaction.h"
#include "libsbml_ne_element_graphics_item.h"

MyReaction::MyReaction(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

void MyReaction::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    if (((ReactionGlyph*)_graphicalObject)->isSetCurve())
        ((MyElementGraphicsItem*)_graphicsItem)->addCurveGraphicsItem(_style->getGroup(), ((ReactionGlyph*)_graphicalObject)->getCurve());
    else
        ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(_style->getGroup(), _graphicalObject->getBoundingBox());
}

