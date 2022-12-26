#include "libsbml_ne_network_element.h"
#include "libsbml_ne_element_graphics_item.h"

MyNetworkElementBase::MyNetworkElementBase(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) {
    _graphicalObject = graphicalObject;
    _style = style;
    _graphicsItem = new MyElementGraphicsItem(graphicsItemZValue);
    connect((MyElementGraphicsItem*)_graphicsItem, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect((MyElementGraphicsItem*)_graphicsItem, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
}

QGraphicsItem* MyNetworkElementBase::graphicsItem() {
    return _graphicsItem;
}

const QRectF MyNetworkElementBase::getExtents() {
    return ((MyElementGraphicsItem*)graphicsItem())->boundingRect();
}
