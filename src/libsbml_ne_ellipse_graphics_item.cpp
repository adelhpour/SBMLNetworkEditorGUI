#include "libsbml_ne_ellipse_graphics_item.h"

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
    qreal cx = boundingBox->x();
    if (ellipse->isSetCX())
        cx += ellipse->getCX().getAbsoluteValue() + 0.01 * ellipse->getCX().getRelativeValue() * boundingBox->width();
    qreal cy = boundingBox->y();
    if (ellipse->isSetCY())
        cy += ellipse->getCY().getAbsoluteValue() + 0.01 * ellipse->getCY().getRelativeValue() * boundingBox->height();
    qreal rx = 0.5 * boundingBox->width();
    if (ellipse->isSetRX())
        rx = ellipse->getRX().getAbsoluteValue() + 0.01 * ellipse->getRX().getRelativeValue() * boundingBox->width();
    qreal ry = 0.5 * boundingBox->height();
    if (ellipse->isSetRY())
        ry = ellipse->getRY().getAbsoluteValue() + 0.01 * ellipse->getRY().getRelativeValue() * boundingBox->height();
    if (ellipse->isSetRatio()) {
        qreal ratio = ellipse->getRatio();
        if ((boundingBox->width() / boundingBox->height()) <= ratio) {
            rx = 0.5 * boundingBox->width();
            ry = 0.5 * boundingBox->width() / ratio;
        }
        else {
            rx = 0.5 * boundingBox->height() / ratio;
            ry = 0.5 * boundingBox->height();
        }
    }
    
    return QRectF(cx - rx, cy - ry, 2 * rx, 2 * ry);
}
