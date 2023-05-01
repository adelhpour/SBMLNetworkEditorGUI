#include "libsbml_ne_image_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyImageGraphicsItem::MyImageGraphicsItem(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {

}

void MyImageGraphicsItem::updateFeatures(Image* image, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    setPixmap(getImage(image, boundingBox));
    setPos(getPosition(image, boundingBox));
}

const QPixmap MyImageGraphicsItem::getImage(Image* image, BoundingBox* boundingBox) {
    QPixmap pixmapImage(getImageShapeHref(image).c_str());
    if (!pixmapImage.isNull())
        pixmapImage = pixmapImage.scaled(getImageShapeWidth(image).getAbsoluteValue() + 0.01 *  getImageShapeWidth(image).getRelativeValue() * getDimensionWidth(boundingBox), getImageShapeHeight(image).getAbsoluteValue() + 0.01 * getImageShapeHeight(image).getRelativeValue() * getDimensionHeight(boundingBox));
    return pixmapImage;
}

const QPointF MyImageGraphicsItem::getPosition(Image* image, BoundingBox* boundingBox) {
    return QPointF(getPositionX(boundingBox) + getImageShapeX(image).getAbsoluteValue() + 0.01 * getImageShapeX(image).getRelativeValue() * getDimensionWidth(boundingBox), getPositionY(boundingBox) + getImageShapeY(image).getAbsoluteValue() + 0.01 *  getImageShapeY(image).getRelativeValue() * getDimensionHeight(boundingBox));
}