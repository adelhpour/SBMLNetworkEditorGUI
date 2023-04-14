#include "libsbml_ne_curve_graphics_item.h"

MyCurveGraphicsItem::MyCurveGraphicsItem(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
    
}

void MyCurveGraphicsItem::updateFeatures(RenderGroup* group, Curve* curve) {
    setPen(getPen(group));
    setPath(getCurve(curve));
}

const QPainterPath MyCurveGraphicsItem::getCurve(Curve* curve) {
    QPainterPath path;
    LineSegment* lineSegment = NULL;
    for (unsigned int i = 0; i < curve->getNumCurveSegments(); i++) {
        lineSegment = curve->getCurveSegment(i);
        QPointF startPoint(lineSegment->getStart()->x(), lineSegment->getStart()->y());
        QPointF endPoint(lineSegment->getEnd()->x(), lineSegment->getEnd()->y());
        QPointF controlPoint1 = startPoint;
        QPointF controlPoint2 = endPoint;
        CubicBezier* cubicBezier = dynamic_cast<CubicBezier*>(lineSegment);
        if (cubicBezier) {
            controlPoint1 = QPointF(cubicBezier->getBasePoint1()->x(), cubicBezier->getBasePoint1()->y());
            controlPoint2 = QPointF(cubicBezier->getBasePoint2()->x(), cubicBezier->getBasePoint2()->y());
        }
        path.moveTo(startPoint);
        path.cubicTo(controlPoint1, controlPoint2, endPoint);
    }
    
    return path;
}
