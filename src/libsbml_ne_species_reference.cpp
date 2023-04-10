#include "libsbml_ne_species_reference.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QtMath>
#include <QGridLayout>

MySpeciesReference::MySpeciesReference(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
}

void MySpeciesReference::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    ((MyElementGraphicsItem*)_graphicsItem)->addCurveGraphicsItem(_style->getGroup(), ((SpeciesReferenceGlyph*)_graphicalObject)->getCurve());
    updateLineEndingsGraphicsItem();
}

void MySpeciesReference::updateLineEndingsGraphicsItem() {
    if (_style->getGroup()->isSetStartHead())
        addLineEndingGraphicsItem(QString(_style->getGroup()->getStartHead().c_str()), getStartPoint(), getStartSlope());
    if (_style->getGroup()->isSetEndHead())
        addLineEndingGraphicsItem(QString((_style->getGroup()->getEndHead().c_str())), getEndPoint(), getEndSlope());
}

void MySpeciesReference::addLineEndingGraphicsItem(const QString& lineEndingId, const QPointF& position, const qreal rotation) {
    LineEnding* lineEnding = emit askForLineEnding(lineEndingId);
    if (lineEnding)
        ((MyElementGraphicsItem*)_graphicsItem)->addGeometricShapes(lineEnding->getGroup(), lineEnding->getBoundingBox(), position, rotation);
}

const QPointF MySpeciesReference::getStartPoint() {
    Curve* curve = ((SpeciesReferenceGlyph*)_graphicalObject)->getCurve();
    if (curve->getNumCurveSegments()) {
        return QPointF(curve->getCurveSegment(0)->getStart()->x(), curve->getCurveSegment(0)->getStart()->y());
    }
    
    return QPointF(0.0, 0.0);
}

const QPointF MySpeciesReference::getEndPoint() {
    Curve* curve = ((SpeciesReferenceGlyph*)_graphicalObject)->getCurve();
    if (curve->getNumCurveSegments()) {
        return QPointF(curve->getCurveSegment(curve->getNumCurveSegments() - 1)->getEnd()->x(), curve->getCurveSegment(curve->getNumCurveSegments() - 1)->getEnd()->y());
    }
    
    return QPointF(0.0, 0.0);
}

const qreal MySpeciesReference::getStartSlope() {
    Curve* curve = ((SpeciesReferenceGlyph*)_graphicalObject)->getCurve();
    if (curve->getNumCurveSegments()) {
        LineSegment* lineSegment = curve->getCurveSegment(0);
        QPointF secondPoint = QPointF(lineSegment->getStart()->x(), lineSegment->getStart()->y());
        QPointF firstPoint = QPointF(lineSegment->getEnd()->x(), lineSegment->getEnd()->y());
        const CubicBezier* cubicBezier = dynamic_cast< const CubicBezier* >(lineSegment);
        if (cubicBezier)
            firstPoint = QPointF(cubicBezier->getBasePoint1()->x(), cubicBezier->getBasePoint1()->y());
        return qRadiansToDegrees(qAtan2((secondPoint.y() - firstPoint.y()), (secondPoint.x() - firstPoint.x())));
    }
    
    return 0.0;
}

const qreal MySpeciesReference::getEndSlope() {
    Curve* curve = ((SpeciesReferenceGlyph*)_graphicalObject)->getCurve();
    if (curve->getNumCurveSegments()) {
        LineSegment* lineSegment = curve->getCurveSegment(curve->getNumCurveSegments() - 1);
        QPointF secondPoint = QPointF(lineSegment->getEnd()->x(), lineSegment->getEnd()->y());
        QPointF firstPoint = QPointF(lineSegment->getStart()->x(), lineSegment->getStart()->y());
        const CubicBezier* cubicBezier = dynamic_cast< const CubicBezier* >(lineSegment);
        if (cubicBezier)
            firstPoint = QPointF(cubicBezier->getBasePoint2()->x(), cubicBezier->getBasePoint2()->y());
        return qRadiansToDegrees(qAtan2((secondPoint.y() - firstPoint.y()), (secondPoint.x() - firstPoint.x())));
    }
    
    return 0.0;
}

const QString MySpeciesReference::getType() {
    return QString("Species Reference");
}

const QString MySpeciesReference::getId() {
    if (!((SpeciesReferenceGlyph*)_graphicalObject)->getSpeciesReferenceId().empty())
        return QString(((SpeciesReferenceGlyph*)_graphicalObject)->getSpeciesReferenceId().c_str());
    else
        return "N/A";
}

const QString MySpeciesReference::getSpeciesGlyphId() {
    return QString(((SpeciesReferenceGlyph*)_graphicalObject)->getSpeciesGlyphId().c_str());
}

const QString MySpeciesReference::getRole() {
    return QString(((SpeciesReferenceGlyph*)_graphicalObject)->getRoleString().c_str());
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

    contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);

    return elementFeatureMenu;
}


