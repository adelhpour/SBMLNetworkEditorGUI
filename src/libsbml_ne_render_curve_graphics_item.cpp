#include "libsbml_ne_render_curve_graphics_item.h"

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
    for (unsigned int i = 0; i < renderCurve->getNumElements(); i++) {
        renderPoint = renderCurve->getElement(i);
        QPointF point = QPointF(boundingBox->x() + renderPoint->getX().getAbsoluteValue() + 0.01 * renderPoint->getX().getRelativeValue() * boundingBox->width(), boundingBox->y() + renderPoint->getY().getAbsoluteValue() + 0.01 * renderPoint->getY().getRelativeValue() * boundingBox->height());
        if (i == 0)
            path.moveTo(point);
        else {
            QPointF controlPoint1 = lastPoint;
            QPointF controlPoint2 = point;
            if (renderPoint->isRenderCubicBezier()) {
                controlPoint1 = QPointF(boundingBox->x() + ((RenderCubicBezier*)renderPoint)->getBasePoint1_x().getAbsoluteValue() + 0.01 * ((RenderCubicBezier*)renderPoint)->getBasePoint1_x().getRelativeValue() * boundingBox->width(), boundingBox->y() + ((RenderCubicBezier*)renderPoint)->getBasePoint1_y().getAbsoluteValue() + 0.01 * ((RenderCubicBezier*)renderPoint)->getBasePoint1_y().getRelativeValue() * boundingBox->height());
                controlPoint2 = QPointF(boundingBox->x() + ((RenderCubicBezier*)renderPoint)->getBasePoint2_x().getAbsoluteValue() + 0.01 * ((RenderCubicBezier*)renderPoint)->getBasePoint2_x().getRelativeValue() * boundingBox->width(), boundingBox->y() + ((RenderCubicBezier*)renderPoint)->getBasePoint2_y().getAbsoluteValue() + 0.01 * ((RenderCubicBezier*)renderPoint)->getBasePoint2_y().getRelativeValue() * boundingBox->height());
            }
            path.cubicTo(controlPoint1, controlPoint2, point);
        }
        lastPoint = point;
    }

    return path;
}
