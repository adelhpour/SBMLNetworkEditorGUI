#include "libsbml_ne_species.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MySpecies::MySpecies(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

void MySpecies::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(getRenderGroup(_style), getBoundingBox(_graphicalObject));
}

const QString MySpecies::getType() {
    return QString("Species");
}

const QString MySpecies::getId() {
    return QString(getSpeciesId(_graphicalObject).c_str());
}

const QString MySpecies::getCompartmentId() {
    SBase* species = askForModelEntity(getSpeciesId(_graphicalObject).c_str());
    if (species)
        return ((Species*)species)->getCompartment().c_str();
    else
        return "N/A";
}

QWidget* MySpecies::elementFeatureMenu() {
    QWidget* elementFeatureMenu = MyNetworkElementBase::elementFeatureMenu();
    QGridLayout* contentLayout = (QGridLayout*)(elementFeatureMenu->layout());
    
    // compartment
    contentLayout->addWidget(new MyLabel("Compartment Id"), contentLayout->rowCount(), 0);
    contentLayout->addWidget(new MyReadOnlyLineEdit(getCompartmentId()), contentLayout->rowCount() - 1, 1);
    
    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);
    
    MyTreeView* featureMenuTree = new MyTreeView(elementFeatureMenu);
    
    // bounding box
    QWidget* _boundingBoxMenu = new MyBoundingBoxMenu(getBoundingBox(_graphicalObject));
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_boundingBoxMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_boundingBoxMenu, "BoundingBox");
    
    // geometric shape
    QWidget* _geometricShapeMenu = new MyGeometricShapesMenu(getRenderGroup(_style));
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
