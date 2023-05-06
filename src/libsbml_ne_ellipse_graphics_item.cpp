#include "libsbml_ne_ellipse_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyEllipseGraphicsItem::MyEllipseGraphicsItem(QGraphicsItem* parent) : QGraphicsEllipseItem(parent) {
    
}

void MyEllipseGraphicsItem::updateFeatures(RenderGroup* group, Ellipse* ellipse, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPos(position);
    setRotation(rotation);
    setPen(getPen(group));
    setPen(getPen(ellipse, pen()));
    setBrush(getBrush(group, boundingBox));
    setBrush(getBrush(ellipse, boundingBox, brush()));
    setRect(getRect(ellipse, boundingBox));
}

const QRectF MyEllipseGraphicsItem::getRect(Ellipse* ellipse, BoundingBox* boundingBox) {
    qreal cx = getPositionX(boundingBox);
    if (isSetGeometricShapeCenterX(ellipse))
        cx += getGeometricShapeCenterX(ellipse).getAbsoluteValue() + 0.01 * getGeometricShapeCenterX(ellipse).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal cy = getPositionY(boundingBox);
    if (isSetGeometricShapeCenterY(ellipse))
        cy += getGeometricShapeCenterY(ellipse).getAbsoluteValue() + 0.01 * getGeometricShapeCenterY(ellipse).getRelativeValue() * getDimensionHeight(boundingBox);
    qreal rx = 0.5 * getDimensionWidth(boundingBox);
    if (isSetGeometricShapeRadiusX(ellipse))
        rx = getGeometricShapeRadiusX(ellipse).getAbsoluteValue() + 0.01 * getGeometricShapeRadiusX(ellipse).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal ry = 0.5 * getDimensionHeight(boundingBox);
    if (isSetGeometricShapeRadiusY(ellipse))
        ry = getGeometricShapeRadiusY(ellipse).getAbsoluteValue() + 0.01 * getGeometricShapeRadiusY(ellipse).getRelativeValue() * getDimensionHeight(boundingBox);
    if (isSetGeometricShapeRatio(ellipse)) {
        qreal ratio = getGeometricShapeRatio(ellipse);
        if ((getDimensionWidth(boundingBox) / getDimensionHeight(boundingBox)) <= ratio) {
            rx = 0.5 * getDimensionWidth(boundingBox);
            ry = 0.5 * getDimensionWidth(boundingBox) / ratio;
        }
        else {
            rx = 0.5 * getDimensionHeight(boundingBox) / ratio;
            ry = 0.5 * getDimensionHeight(boundingBox);
        }
    }
    
    return QRectF(cx - rx, cy - ry, 2 * rx, 2 * ry);
}
