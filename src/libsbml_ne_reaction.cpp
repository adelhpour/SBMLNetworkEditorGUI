#include "libsbml_ne_reaction.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyReaction::MyReaction(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {

}

void MyReaction::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    if (((ReactionGlyph*)_graphicalObject)->isSetCurve())
        ((MyElementGraphicsItem*)_graphicsItem)->addCurveGraphicsItem(getRenderGroup(_style), getCurve(_graphicalObject));
    else
        ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(getRenderGroup(_style), getBoundingBox(_graphicalObject));
}

const QString MyReaction::getType() {
    return QString("Reaction");
}

const QString MyReaction::getId() {
    return QString(getReactionId((ReactionGlyph*)_graphicalObject).c_str());
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

    _reactionFeaturesMenu = NULL;
    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);
    _reactionBoundingBoxCurveSwitch = new MyReactionBoundingBoxCurveSwitch(_graphicalObject, elementFeatureMenu);
    connect(_reactionBoundingBoxCurveSwitch, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    connect((MyReactionBoundingBoxCurveSwitch*)_reactionBoundingBoxCurveSwitch, &MyReactionBoundingBoxCurveSwitch::isUpdated, this, [this, contentLayout] () { setReactionFeaturesMenu(contentLayout); });
    contentLayout->addWidget(_reactionBoundingBoxCurveSwitch, contentLayout->rowCount(), 0, 1, 2);
    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);
    setReactionFeaturesMenu(contentLayout);

    return elementFeatureMenu;
}

void MyReaction::setReactionFeaturesMenu(QGridLayout* contentLayout) {
    if (_reactionFeaturesMenu != NULL) {
        contentLayout->removeWidget(_reactionFeaturesMenu);
        _reactionFeaturesMenu->deleteLater();
    }
    _reactionFeaturesMenu = createReactionFeaturesMenuTree();
    contentLayout->addWidget(_reactionFeaturesMenu, contentLayout->rowCount(), 0, 1, 2);
}

QWidget* MyReaction::createReactionFeaturesMenuTree() {
    MyTreeView* featureMenuTree = new MyTreeView(NULL);

    if (isSetCurve(_graphicalObject)) {
        // stroke
        QWidget* _strokeMenu = new MyStrokeMenu(getRenderGroup(_style));
        connect(_strokeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(_strokeMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(_strokeMenu, "Stroke");

        // curve
        QWidget* _curveMenu = new MyCurveMenu(_graphicalObject);
        connect(_curveMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(_curveMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(_curveMenu, "Curve");
    }
    else {
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
    }

    // texts
    QList<QWidget*> textsMenu = askForAssociatedTextsMenu(getGlyphId());
    if (textsMenu.size()) {
        QWidget* elementTextsMenu = new MyElementTextsMenu(textsMenu);
        connect(elementTextsMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(elementTextsMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(elementTextsMenu, "Texts");
    }

    return featureMenuTree;
}

MyReactionBoundingBoxCurveSwitch::MyReactionBoundingBoxCurveSwitch(GraphicalObject* graphicalObject, QWidget* parent) {
    setContentsMargins(0.0, 0.0, 0.0, 0.0);
    setFixedSize(250.0, 50.0);
    _graphicalObject = graphicalObject;
    QGridLayout* contentLayout = new QGridLayout(this);
    _boundingBoxRadioButton = new QRadioButton("BoundingBox");
    contentLayout->addWidget(_boundingBoxRadioButton, contentLayout->rowCount(), 0);
    _curveRadioButton = new QRadioButton("Curve");
    contentLayout->addWidget(_curveRadioButton, contentLayout->rowCount() - 1, 1);
    initializeButtons();
    connect(_boundingBoxRadioButton, SIGNAL(toggled(bool)), this, SLOT(enableBoundingBox(bool)));
    connect(_curveRadioButton, SIGNAL(toggled(bool)), this, SLOT(enableCurve(bool)));
    setLayout(contentLayout);
}

void MyReactionBoundingBoxCurveSwitch::initializeButtons() {
    if (getNumCurveSegments(_graphicalObject))
        _curveRadioButton->setChecked(true);
    else
        _boundingBoxRadioButton->setChecked(true);
}

void MyReactionBoundingBoxCurveSwitch::enableBoundingBox(bool checked) {
    if (checked) {
        _curveRadioButton->setChecked(false);
        removeCurve();
    }
}

void MyReactionBoundingBoxCurveSwitch::enableCurve(bool checked) {
    if (checked) {
        _boundingBoxRadioButton->setChecked(false);
        addCurve();
    }
}

void MyReactionBoundingBoxCurveSwitch::addCurve() {
    if (!getNumCurveSegments(_graphicalObject))
        createLineCurveSegment(_graphicalObject);
    emit isUpdated();
}

void MyReactionBoundingBoxCurveSwitch::removeCurve() {
    while(getNumCurveSegments(_graphicalObject))
        removeCurveSegment(_graphicalObject, 0);
    emit isUpdated();
}