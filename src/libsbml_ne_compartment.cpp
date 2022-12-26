#include "libsbml_ne_compartment.h"
#include "libsbml_ne_element_graphics_item.h"

#include <iostream>
MyCompartment::MyCompartment(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
}

void MyCompartment::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(_style->getGroup(), _graphicalObject->getBoundingBox());
}
