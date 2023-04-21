#include "libsbml_ne_compartment.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

MyCompartment::MyCompartment(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
}

void MyCompartment::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(_style->getGroup(), _graphicalObject->getBoundingBox());
}

const QString MyCompartment::getType() {
    return QString("Compartment");
}

const QString MyCompartment::getId() {
    return QString(((CompartmentGlyph*)_graphicalObject)->getCompartmentId().c_str());
}

QWidget* MyCompartment::elementFeatureMenu() {
    QWidget* elementFeatureMenu = MyNetworkElementBase::elementFeatureMenu();
    QGridLayout* contentLayout = (QGridLayout*)(elementFeatureMenu->layout());
    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);
    
    MyTreeView* featureMenuTree = new MyTreeView(elementFeatureMenu);
    
    // bounding box
    QWidget* _boundingBoxMenu = new MyBoundingBoxMenu(_graphicalObject->getBoundingBox());
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_boundingBoxMenu, "BoundingBox");
    
    // geometric shape
    QWidget* _geometricShapeMenu = new MyGeometricShapesMenu(_style->getGroup());
    connect(_geometricShapeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_geometricShapeMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_geometricShapeMenu, "Geometric Shapes");

    // texts
    QList<QWidget*> textsMenu = askForAssociatedTextsMenu(getGlyphId());
    if (textsMenu.size()) {
        QWidget* elementTextsMenu = new MyElementTextsMenu(textsMenu);
        connect(elementTextsMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(elementTextsMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(elementTextsMenu, "Texts");
    }
    
    contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);
    
    return elementFeatureMenu;
}
