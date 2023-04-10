#include "libsbml_ne_image_graphics_item.h"

MyImageGraphicsItem::MyImageGraphicsItem(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {

}

void MyImageGraphicsItem::updateFeatures(Image* image, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPixmap(getImage(image, boundingBox));
    setPos(getPosition(image, boundingBox));
}

const QPixmap MyImageGraphicsItem::getImage(Image* image, BoundingBox* boundingBox) {
    QPixmap pixmapImage(image->getHref().c_str());
    if (!pixmapImage.isNull())
        pixmapImage = pixmapImage.scaled(image->getWidth().getAbsoluteValue() + 0.01 *  image->getWidth().getRelativeValue() * boundingBox->width(), image->getHeight().getAbsoluteValue() + 0.01 *  image->getHeight().getRelativeValue() * boundingBox->height());
    return pixmapImage;
}

const QPointF MyImageGraphicsItem::getPosition(Image* image, BoundingBox* boundingBox) {
    return QPointF(boundingBox->x() + image->getX().getAbsoluteValue() + 0.01 *  image->getX().getRelativeValue() * boundingBox->width(), boundingBox->y() + image->getY().getAbsoluteValue() + 0.01 *  image->getY().getRelativeValue() * boundingBox->height());
}