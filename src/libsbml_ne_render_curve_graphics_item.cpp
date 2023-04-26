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
    for (unsigned int i = 0; i < getRenderCurveShapeNumElements(renderCurve); i++) {
        renderPoint = renderCurve->getElement(i);
        QPointF point = QPointF(getPositionX(boundingBox) + getRenderCurveShapeElementX(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeElementX(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) + getRenderCurveShapeElementY(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeElementY(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
        if (i == 0) {
            path.moveTo(point);
            lastPoint = point;
        }
        else {
            QPointF controlPoint1 = lastPoint;
            QPointF controlPoint2 = point;
            if (isRenderCubicBezier(renderCurve, i)) {
                controlPoint1 = QPointF(getPositionX(boundingBox) + getRenderCurveShapeBasePoint1X(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeBasePoint1X(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) + getRenderCurveShapeBasePoint1Y(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeBasePoint1Y(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
                controlPoint2 = QPointF(getPositionX(boundingBox) + getRenderCurveShapeBasePoint2X(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeBasePoint2X(renderCurve, i).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) + getRenderCurveShapeBasePoint2Y(renderCurve, i).getAbsoluteValue() + 0.01 * getRenderCurveShapeBasePoint2Y(renderCurve, i).getRelativeValue() * getDimensionHeight(boundingBox));
            }
            path.cubicTo(controlPoint1, controlPoint2, point);
        }
        lastPoint = point;
    }

    return path;
}
