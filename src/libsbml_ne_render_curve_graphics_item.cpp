#include "libsbml_ne_render_curve_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyRenderCurveGraphicsItem::MyRenderCurveGraphicsItem(QGraphicsItem* parent) : QGraphicsPathItem(parent) {

}

void MyRenderCurveGraphicsItem::updateFeatures(RenderGroup* group, RenderCurve* renderCurve, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPen(getPen(group));
    setPen(getPen(renderCurve, pen()));
    setPath(getRenderCurve(renderCurve, boundingBox));
}

const QPainterPath MyRenderCurveGraphicsItem::getRenderCurve(RenderCurve* renderCurve, BoundingBox* boundingBox) {
    QPainterPath path;
    RenderPoint* renderPoint = NULL;
    QPointF lastPoint;
    for (unsigned int i = 0; i <  getGeometricShapeNumElements(renderCurve); i++) {
        renderPoint = renderCurve->getElement(i);
        QPointF point = QPointF(getPositionX(boundingBox) +  getGeometricShapeElementX(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeElementX(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) +  getGeometricShapeElementY(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeElementY(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
        if (i == 0) {
            path.moveTo(point);
            lastPoint = point;
        }
        else {
            QPointF controlPoint1 = lastPoint;
            QPointF controlPoint2 = point;
            if (isRenderCubicBezier(renderCurve, i)) {
                controlPoint1 = QPointF(getPositionX(boundingBox) +  getGeometricShapeBasePoint1X(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeBasePoint1X(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) +  getGeometricShapeBasePoint1Y(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeBasePoint1Y(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
                controlPoint2 = QPointF(getPositionX(boundingBox) +  getGeometricShapeBasePoint2X(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeBasePoint2X(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) +  getGeometricShapeBasePoint2Y(renderCurve, i).getAbsoluteValue() + 0.01 *  getGeometricShapeBasePoint2Y(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
            }
            path.cubicTo(controlPoint1, controlPoint2, point);
        }
        lastPoint = point;
    }

    return path;
}
