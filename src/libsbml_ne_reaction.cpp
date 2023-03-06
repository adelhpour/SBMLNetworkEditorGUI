#include "libsbml_ne_reaction.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

MyReaction::MyReaction(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

void MyReaction::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    if (((ReactionGlyph*)_graphicalObject)->isSetCurve())
        ((MyElementGraphicsItem*)_graphicsItem)->addCurveGraphicsItem(_style->getGroup(), ((ReactionGlyph*)_graphicalObject)->getCurve());
    else
        ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(_style->getGroup(), _graphicalObject->getBoundingBox());
}

const QString MyReaction::getType() {
    return QString("Reaction");
}

const QString MyReaction::getId() {
    return QString(((ReactionGlyph*)_graphicalObject)->getReactionId().c_str());
}

const QString MyReaction::getCompartmentId() {
    SBase* reaction = askForModelEntity(((ReactionGlyph*)_graphicalObject)->getReactionId().c_str());
    if (reaction && !((Reaction*)reaction)->getCompartment().empty())
        return ((Reaction*)reaction)->getCompartment().c_str();
    else
        return "N/A";
}

QWidget* MyReaction::elementFeatureMenu() {
    QWidget* elementFeatureMenu = MyNetworkElementBase::elementFeatureMenu();
    QGridLayout* contentLayout = (QGridLayout*)(elementFeatureMenu->layout());
    
    // compartment
    contentLayout->addWidget(new MyLabel("Compartment Id"), contentLayout->rowCount(), 0);
    contentLayout->addWidget(new MyReadOnlyLineEdit(getCompartmentId()), contentLayout->rowCount() - 1, 1);
    
    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);
    
    MyTreeView* featureMenuTree = new MyTreeView(elementFeatureMenu);
    
    // bounding box
    QWidget* _boundingBoxMenu = new MyBoundingBoxMenu(_graphicalObject);
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_boundingBoxMenu, "BoundingBox");
    
    // geometric shape
    QWidget* _geometricShapeMenu = new MyGeometricShapesMenu(_style->getGroup());
    connect(_geometricShapeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_geometricShapeMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_geometricShapeMenu, "Geometric Shapes");
    
    contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);
    
    return elementFeatureMenu;
}

