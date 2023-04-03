#include "libsbml_ne_render_curve_graphics_item.h"

MyRenderCurveGraphicsItem::MyRenderCurveGraphicsItem(QGraphicsItem* parent) : QGraphicsPathItem(parent) {

}

void MyPolygonGraphicsItem::updateFeatures(RenderGroup* group, RenderCurve* renderCurve, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPen(getPen(group));
    setPen(getPen(renderCurve, pen()));
    setBrush(getBrush(group, boundingBox));
    setBrush(getBrush(renderCurve, boundingBox, brush()));
    setPath(getRenderCurve(renerCurve, boundingBox));
}

const QPolygonF MyPolygonGraphicsItem::getRenderCurve(RenderCurve* renderCurve, BoundingBox* boundingBox) {
    QPainterPath path;
    RenderPoint* renderPoint = NULL;
    for (unsigned int i = 0; i < renderCurve->getNumElements(); i++) {
        renderPoint = renderCurve->getElement(i);
        QPointF point = QPointF(boundingBox->x() + renderPoint->getX().getAbsoluteValue() + 0.01 * renderPoint->getX().getRelativeValue() * boundingBox->width(), boundingBox->y() + renderPoint->getY().getAbsoluteValue() + 0.01 * renderPoint->getY().getRelativeValue() * boundingBox->height());
        if (renderPoint->isRenderCubicBezier()) {

        }
    }


    for (unsigned int i = 0; i < curve->getNumCurveSegments(); i++) {
        lineSegment = curve->getCurveSegment(i);
        QPointF startPoint(lineSegment->getStart()->x(), lineSegment->getStart()->y());
        QPointF endPoint(lineSegment->getEnd()->x(), lineSegment->getEnd()->y());
        QPointF controlPoint1 = startPoint;
        QPointF controlPoint2 = endPoint;
        const CubicBezier* cubicBezier = dynamic_cast< const CubicBezier* >(lineSegment);
        if (cubicBezier) {
            controlPoint1 = QPointF(cubicBezier->getBasePoint1()->x(), cubicBezier->getBasePoint1()->y());
            controlPoint2 = QPointF(cubicBezier->getBasePoint2()->x(), cubicBezier->getBasePoint2()->y());
        }
        path.moveTo(startPoint);
        path.cubicTo(controlPoint1, controlPoint2, endPoint);
    }

    return path;
}
