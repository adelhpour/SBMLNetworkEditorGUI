#include "libsbml_ne_network_element.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

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

const QString MyNetworkElementBase::getGlyphId() {
    return QString(_graphicalObject->getId().c_str());
}

bool MyNetworkElementBase::hasAssociatedModelEntity() {
    return true;
}

GraphicalObject* MyNetworkElementBase::getGraphicalObject()  {
    return _graphicalObject;
}

Style* MyNetworkElementBase::getStyle()  {
    return _style;
}

QWidget* MyNetworkElementBase::getFeatureMenu() {
    return new MyFeatureMenu(elementFeatureMenu());
}

QWidget* MyNetworkElementBase::elementFeatureMenu() {
    QWidget* elementFeatureMenu = new MyGroupBox();
    QGridLayout* contentLayout = new QGridLayout();
    elementFeatureMenu->setLayout(contentLayout);
    
    // title
    contentLayout->addWidget(new MyTitleLabel(getType()), contentLayout->rowCount(), 0, 1, 2, Qt::AlignCenter);
    
    // spacer
    QLayoutItem* spacerItem = new MySpacerItem(0, 10);
    contentLayout->addItem(spacerItem, contentLayout->rowCount(), 0, 1, 2);
    
    // id
    if (hasAssociatedModelEntity()) {
        contentLayout->addWidget(new MyLabel("Id"), contentLayout->rowCount(), 0);
        contentLayout->addWidget(new MyReadOnlyLineEdit(getId()), contentLayout->rowCount() - 1, 1);
    }
    
    // glyph id
    contentLayout->addWidget(new MyLabel("Glyph Id"), contentLayout->rowCount(), 0);
    contentLayout->addWidget(new MyReadOnlyLineEdit(getGlyphId()), contentLayout->rowCount() - 1, 1);
    
    return elementFeatureMenu;
}
