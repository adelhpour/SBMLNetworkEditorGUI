#include "libsbml_ne_rect_graphics_item.h"

MyRectGraphicsItem::MyRectGraphicsItem(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
    
}

void MyRectGraphicsItem::updateFeatures(RenderGroup* group, Rectangle* rectangle, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPos(position);
    setRotation(rotation);
    setPen(getPen(group));
    setPen(getPen(rectangle, pen()));
    setBrush(getBrush(group, boundingBox));
    setBrush(getBrush(rectangle, boundingBox, brush()));
    
    QPainterPath path;
    path.addRoundedRect(getRect(rectangle, boundingBox), getRX(rectangle, boundingBox), getRY(rectangle, boundingBox));
    QGraphicsPathItem::setPath(path);
}

const QRectF MyRectGraphicsItem::getRect(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal x = boundingBox->x();
    if (rectangle->isSetX())
        x += rectangle->getX().getAbsoluteValue() + 0.01 * rectangle->getX().getRelativeValue() * boundingBox->width();
    qreal y = boundingBox->y();
    if (rectangle->isSetY())
        y += rectangle->getY().getAbsoluteValue() + 0.01 * rectangle->getY().getRelativeValue() * boundingBox->height();
    qreal width = 0.0;
    if (rectangle->isSetWidth())
        width = rectangle->getWidth().getAbsoluteValue() + 0.01 * rectangle->getWidth().getRelativeValue() * boundingBox->width();
    qreal height = 0.0;
    if (rectangle->isSetHeight())
        height = rectangle->getHeight().getAbsoluteValue() + 0.01 * rectangle->getHeight().getRelativeValue() * boundingBox->height();
    if (rectangle->isSetRatio()) {
        qreal ratio = rectangle->getRatio();
        if ((boundingBox->width() / boundingBox->height()) <= ratio) {
            width = boundingBox->width();
            height = boundingBox->width() / ratio;
        }
        else {
            width = boundingBox->height() / ratio;
            height = boundingBox->height();
        }
    }
    
    return QRectF(x, y, width, height);
}

const qreal MyRectGraphicsItem::getRX(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal rx = 0.0;
    if (rectangle->isSetRX())
        rx = rectangle->getRX().getAbsoluteValue() + 0.01 * rectangle->getRX().getRelativeValue() * boundingBox->width();
    
    return rx;
}

const qreal MyRectGraphicsItem::getRY(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal ry = 0.0;
    if (rectangle->isSetRY())
        ry = rectangle->getRY().getAbsoluteValue() + 0.01 * rectangle->getRY().getRelativeValue() * boundingBox->height();
    
    return ry;
}

