#include "libsbml_ne_rect_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

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
    qreal x = getPositionX(boundingBox);
    if (isSetRectangleShapeX(rectangle))
        x += getRectangleShapeX(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeX(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal y = getPositionY(boundingBox);
    if (isSetRectangleShapeY(rectangle))
        y += getRectangleShapeY(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeY(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    qreal width = 0.0;
    if (isSetRectangleShapeWidth(rectangle))
        width = getRectangleShapeWidth(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeWidth(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal height = 0.0;
    if (isSetRectangleShapeHeight(rectangle))
        height = getRectangleShapeHeight(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeHeight(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    if (isSetRectangleShapeRatio(rectangle)) {
        qreal ratio = getRectangleShapeRatio(rectangle);
        if ((getDimensionWidth(boundingBox) / getDimensionHeight(boundingBox)) <= ratio) {
            width = getDimensionWidth(boundingBox);
            height = getDimensionWidth(boundingBox) / ratio;
        }
        else {
            width = getDimensionHeight(boundingBox) / ratio;
            height = getDimensionHeight(boundingBox);
        }
    }
    
    return QRectF(x, y, width, height);
}

const qreal MyRectGraphicsItem::getRX(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal rx = 0.0;
    if (isSetRectangleShapeRX(rectangle))
        rx = getRectangleShapeRX(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeRX(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);
    
    return rx;
}

const qreal MyRectGraphicsItem::getRY(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal ry = 0.0;
    if (isSetRectangleShapeRY(rectangle))
        ry = getRectangleShapeRY(rectangle).getAbsoluteValue() + 0.01 * getRectangleShapeRY(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    
    return ry;
}

