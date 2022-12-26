#include "libsbml_ne_species.h"
#include "libsbml_ne_element_graphics_item.h"

MySpecies::MySpecies(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

void MySpecies::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(_style->getGroup(), _graphicalObject->getBoundingBox());
}
