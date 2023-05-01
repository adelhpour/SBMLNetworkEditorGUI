#include "libsbml_ne_curve_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyCurveGraphicsItem::MyCurveGraphicsItem(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
    
}

void MyCurveGraphicsItem::updateFeatures(RenderGroup* group, Curve* curve) {
    setPen(getPen(group));
    setPath(getCurve(curve));
}

const QPainterPath MyCurveGraphicsItem::getCurve(Curve* curve) {
    QPainterPath path;
    for (unsigned int i = 0; i < getNumCurveSegments(curve); i++) {
        QPointF startPoint(getCurveSegmentStartPointX(curve, i), getCurveSegmentStartPointY(curve, i));
        QPointF endPoint(getCurveSegmentEndPointX(curve, i), getCurveSegmentEndPointY(curve, i));
        QPointF controlPoint1 = startPoint;
        QPointF controlPoint2 = endPoint;
        if (isCubicBezier(curve, i)) {
            controlPoint1 = QPointF(getCurveSegmentBasePoint1X(curve, i), getCurveSegmentBasePoint1Y(curve, i));
            controlPoint2 = QPointF(getCurveSegmentBasePoint2X(curve, i), getCurveSegmentBasePoint2Y(curve, i));
        }
        path.moveTo(startPoint);
        path.cubicTo(controlPoint1, controlPoint2, endPoint);
    }
    
    return path;
}
