#include "libsbml_ne_polygon_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

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
    for (unsigned int i = 0; i < getGeometricShapeNumElements(polygon); i++) {
        qreal x = getPositionX(boundingBox) +  getGeometricShapeElementX(polygon, i).getAbsoluteValue() + 0.01 *  getGeometricShapeElementX(polygon, i).getRelativeValue() * getDimensionWidth(boundingBox);
        qreal y = getPositionY(boundingBox) +  getGeometricShapeElementY(polygon, i).getAbsoluteValue() + 0.01 *  getGeometricShapeElementY(polygon, i).getRelativeValue() * getDimensionHeight(boundingBox);
        polygonShape << QPointF(x, y);
    }
    
    return polygonShape;
    return polygonShape;
}
