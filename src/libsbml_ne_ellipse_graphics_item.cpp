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
    if (isSetEllipseShapeCX(ellipse))
        cx += getEllipseShapeCX(ellipse).getAbsoluteValue() + 0.01 * getEllipseShapeCX(ellipse).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal cy = getPositionY(boundingBox);
    if (isSetEllipseShapeCY(ellipse))
        cy += getEllipseShapeCY(ellipse).getAbsoluteValue() + 0.01 * getEllipseShapeCY(ellipse).getRelativeValue() * getDimensionHeight(boundingBox);
    qreal rx = 0.5 * getDimensionWidth(boundingBox);
    if (isSetEllipseShapeRX(ellipse))
        rx = getEllipseShapeRX(ellipse).getAbsoluteValue() + 0.01 * getEllipseShapeRX(ellipse).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal ry = 0.5 * getDimensionHeight(boundingBox);
    if (isSetEllipseShapeRY(ellipse))
        ry = getEllipseShapeRY(ellipse).getAbsoluteValue() + 0.01 * getEllipseShapeRY(ellipse).getRelativeValue() * getDimensionHeight(boundingBox);
    if (isSetEllipseShapeRatio(ellipse)) {
        qreal ratio = getEllipseShapeRatio(ellipse);
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
