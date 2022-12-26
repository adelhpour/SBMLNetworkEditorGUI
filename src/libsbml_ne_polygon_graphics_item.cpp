#include "libsbml_ne_polygon_graphics_item.h"

MyPolygonGraphicsItem::MyPolygonGraphicsItem(QGraphicsItem* parent) : QGraphicsPolygonItem(parent) {
    
}

void MyPolygonGraphicsItem::updateFeatures(RenderGroup* group, Polygon* polygon, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPos(position);
    setRotation(rotation);
    setPen(getPen(group));
    setPen(getPen(polygon, pen()));
    setBrush(getBrush(group, boundingBox));
    setBrush(getBrush(polygon, boundingBox, brush()));
    setPolygon(getPolygon(polygon, boundingBox));
}

const QPolygonF MyPolygonGraphicsItem::getPolygon(Polygon* polygon, BoundingBox* boundingBox) {
    QPolygonF polygonShape;
    for (unsigned int i = 0; i < polygon->getNumElements(); i++) {
        qreal x = boundingBox->x() + polygon->getElement(i)->getX().getAbsoluteValue() + 0.01 * polygon->getElement(i)->getX().getRelativeValue() * boundingBox->width();
        qreal y = boundingBox->y() + polygon->getElement(i)->getY().getAbsoluteValue() + 0.01 * polygon->getElement(i)->getY().getRelativeValue() * boundingBox->height();
        polygonShape << QPointF(x, y);
    }
    
    return polygonShape;
}
