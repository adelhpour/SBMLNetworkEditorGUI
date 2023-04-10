#ifndef __LIBSBML_NE_IMAGE_GRAPHICS_ITEM_H
#define __LIBSBML_NE_IMAGE_GRAPHICS_ITEM_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include <QGraphicsItem>

class MyImageGraphicsItem : public QObject, public QGraphicsPixmapItem {

public:
    MyImageGraphicsItem(QGraphicsItem* parent = nullptr);

    void updateFeatures(Image* image, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation);

    const QPixmap getImage(Image* image, BoundingBox* boundingBox);

    const QPointF getPosition(Image* image, BoundingBox* boundingBox);
};

#endif
