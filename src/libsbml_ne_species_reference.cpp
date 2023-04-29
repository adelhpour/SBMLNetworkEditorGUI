#include "libsbml_ne_species_reference.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QtMath>
#include <QGridLayout>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MySpeciesReference::MySpeciesReference(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {

}

void MySpeciesReference::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addCurveGraphicsItem(getRenderGroup(_style), getCurve(_graphicalObject));
    updateLineEndingsGraphicsItem();
}

void MySpeciesReference::updateLineEndingsGraphicsItem() {
    if (isSetStartHead(getRenderGroup(_style)))
        addLineEndingGraphicsItem(getStartHeadId(), getStartPoint(), getStartSlope());
    if (isSetEndHead(getRenderGroup(_style)))
        addLineEndingGraphicsItem(getEndHeadId(), getEndPoint(), getEndSlope());
}

void MySpeciesReference::addLineEndingGraphicsItem(const QString& lineEndingId, const QPointF& position, const qreal rotation) {
    LineEnding* lineEnding = emit askForLineEnding(lineEndingId);
    if (lineEnding)
        ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(getRenderGroup(lineEnding), getBoundingBox(lineEnding), position, getAdjustedRotation(lineEnding, rotation));
}

const QPointF MySpeciesReference::getStartPoint() {
    if (getNumCurveSegments(_graphicalObject)) {
        return QPointF(getCurveSegmentStartPointX(_graphicalObject, 0), getCurveSegmentStartPointY(_graphicalObject, 0));
    }
    
    return QPointF(0.0, 0.0);
}

const QPointF MySpeciesReference::getEndPoint() {
    if (getNumCurveSegments(_graphicalObject)) {
        return QPointF(getCurveSegmentEndPointX(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1), getCurveSegmentEndPointY(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1));
    }
    
    return QPointF(0.0, 0.0);
}

const qreal MySpeciesReference::getStartSlope() {
    if (getNumCurveSegments(_graphicalObject)) {
        QPointF secondPoint = QPointF(getCurveSegmentStartPointX(_graphicalObject, 0), getCurveSegmentStartPointY(_graphicalObject, 0));
        QPointF firstPoint = QPointF(getCurveSegmentEndPointX(_graphicalObject, 0), getCurveSegmentEndPointY(_graphicalObject, 0));
        if (isCubicBezier(getCurveSegment(_graphicalObject, 0)))
            firstPoint = QPointF(getCurveSegmentBasePoint1X(_graphicalObject, 0), getCurveSegmentBasePoint1Y(_graphicalObject, 0));
        return qRadiansToDegrees(qAtan2((secondPoint.y() - firstPoint.y()), (secondPoint.x() - firstPoint.x())));
    }
    
    return 0.0;
}

const qreal MySpeciesReference::getEndSlope() {
    if (getNumCurveSegments(_graphicalObject)) {
        QPointF secondPoint = QPointF(getCurveSegmentEndPointX(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1), getCurveSegmentEndPointY(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1));
        QPointF firstPoint = QPointF(getCurveSegmentStartPointX(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1), getCurveSegmentStartPointY(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1));
        if (isCubicBezier(getCurveSegment(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1)))
            firstPoint = QPointF(getCurveSegmentBasePoint2X(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1), getCurveSegmentBasePoint2Y(_graphicalObject, getNumCurveSegments(_graphicalObject) - 1));
        return qRadiansToDegrees(qAtan2((secondPoint.y() - firstPoint.y()), (secondPoint.x() - firstPoint.x())));
    }
    
    return 0.0;
}

const qreal MySpeciesReference::getAdjustedRotation(LineEnding* lineEnding, const qreal& rotation) {
    if (isSetEnableRotationalMapping(lineEnding) && !getEnableRotationalMapping(lineEnding))
        return 0.0;

    return rotation;
}

const QString MySpeciesReference::getType() {
    return QString("Species Reference");
}

const QString MySpeciesReference::getId() {
    if (getSpeciesReferenceId((SpeciesReferenceGlyph*)_graphicalObject).empty())
        return QString((getSpeciesReferenceId((SpeciesReferenceGlyph*)_graphicalObject).c_str()));
    else
        return "N/A";
}

const QString MySpeciesReference::getSpeciesGlyphId() {
    return QString(LIBSBML_NETWORKEDITOR_CPP_NAMESPACE::getSpeciesGlyphId((SpeciesReferenceGlyph*)_graphicalObject).c_str());
}

const QString MySpeciesReference::getRole() {
    return QString(LIBSBML_NETWORKEDITOR_CPP_NAMESPACE::getRole((SpeciesReferenceGlyph*)_graphicalObject).c_str());
}

const QString MySpeciesReference::getStartHeadId() {
    return QString(getStartHead(getRenderGroup(_style)).c_str());
}

const QString MySpeciesReference::getEndHeadId() {
    return QString(getEndHead(getRenderGroup(_style)).c_str());
}

QWidget* MySpeciesReference::elementFeatureMenu() {
    QWidget* elementFeatureMenu = MyNetworkElementBase::elementFeatureMenu();
    QGridLayout* contentLayout = (QGridLayout*)(elementFeatureMenu->layout());
    
    // species glyph
    contentLayout->addWidget(new MyLabel("Species Glyph Id"), contentLayout->rowCount(), 0);
    contentLayout->addWidget(new MyReadOnlyLineEdit(getSpeciesGlyphId()), contentLayout->rowCount() - 1, 1);
    
    // role
    contentLayout->addWidget(new MyLabel("Role"), contentLayout->rowCount(), 0);
    contentLayout->addWidget(new MyReadOnlyLineEdit(getRole()), contentLayout->rowCount() - 1, 1);

    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);

    MyTreeView* featureMenuTree = new MyTreeView(elementFeatureMenu);

    // stroke
    QWidget* _strokeMenu = new MyStrokeMenu(_style->getGroup());
    connect(_strokeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_strokeMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_strokeMenu, "Stroke");

    // curve
    QWidget* _curveMenu = new MyCurveMenu(_graphicalObject);
    connect(_curveMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect(_curveMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
    featureMenuTree->addBranchWidget(_curveMenu, "Curve");

    // start line ending
    LineEnding* startLineEnding = askForLineEnding(getStartHeadId());
    if (startLineEnding) {
        QWidget* lineEndingMenu = new MyLineEndingMenu(startLineEnding);
        connect(lineEndingMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(lineEndingMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(lineEndingMenu, "Start Head");
    }

    // end line ending
    LineEnding* endLineEnding = askForLineEnding(getEndHeadId());
    if (endLineEnding) {
        QWidget* lineEndingMenu = new MyLineEndingMenu(endLineEnding);
        connect(lineEndingMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(lineEndingMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(lineEndingMenu, "End Head");
    }

    contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);

    return elementFeatureMenu;
}


