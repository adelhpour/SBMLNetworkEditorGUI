#include "libsbml_ne_network_element.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"

MyNetworkElementBase::MyNetworkElementBase(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) {
    _graphicalObject = graphicalObject;
    _style = style;
    _graphicsItem = new MyElementGraphicsItem(graphicsItemZValue);
    connect((MyElementGraphicsItem*)_graphicsItem, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect((MyElementGraphicsItem*)_graphicsItem, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
    connect((MyElementGraphicsItem*)_graphicsItem, &MyElementGraphicsItem::mouseLeftButtonIsDoubleClicked, this, [this] () {emit askForDisplayFeatureMenu(getFeatureMenu());});
}

QGraphicsItem* MyNetworkElementBase::graphicsItem() {
    return _graphicsItem;
}

const QRectF MyNetworkElementBase::getExtents() {
    return ((MyElementGraphicsItem*)graphicsItem())->boundingRect();
}

QWidget* MyNetworkElementBase::getFeatureMenu() {
    return new MyFeatureMenu();
}
