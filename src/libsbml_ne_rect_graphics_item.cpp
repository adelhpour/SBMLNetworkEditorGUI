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
    if (isSetGeometricShapeX(rectangle))
        x += getGeometricShapeX(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeX(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal y = getPositionY(boundingBox);
    if (isSetGeometricShapeY(rectangle))
        y += getGeometricShapeY(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeY(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    qreal width = 0.0;
    if (isSetGeometricShapeWidth(rectangle))
        width = getGeometricShapeWidth(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeWidth(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);
    qreal height = 0.0;
    if (isSetGeometricShapeHeight(rectangle))
        height = getGeometricShapeHeight(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeHeight(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    if (isSetGeometricShapeRatio(rectangle)) {
        qreal ratio = getGeometricShapeRatio(rectangle);
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
    if (isSetGeometricShapeCornerCurvatureRadiusX(rectangle))
        rx = getGeometricShapeCornerCurvatureRadiusX(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeCornerCurvatureRadiusX(rectangle).getRelativeValue() * getDimensionWidth(boundingBox);

    return rx;
}

const qreal MyRectGraphicsItem::getRY(Rectangle* rectangle, BoundingBox* boundingBox) {
    qreal ry = 0.0;
    if (isSetGeometricShapeCornerCurvatureRadiusY(rectangle))
        ry = getGeometricShapeCornerCurvatureRadiusY(rectangle).getAbsoluteValue() + 0.01 * getGeometricShapeCornerCurvatureRadiusY(rectangle).getRelativeValue() * getDimensionHeight(boundingBox);
    
    return ry;
}

