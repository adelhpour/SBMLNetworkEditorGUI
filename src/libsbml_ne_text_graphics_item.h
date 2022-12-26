#ifndef __LIBSBML_NE_TEXT_GRAPHICS_ITEM_H
#define __LIBSBML_NE_TEXT_GRAPHICS_ITEM_H

#include "libsbml_ne_1d_shape_graphics_item.h"
#include <QGraphicsItem>

class MyTextGraphicsItem : public My1DShapeGraphicsItem, public QGraphicsTextItem {
    
public:
    
    MyTextGraphicsItem(QGraphicsItem* parent = nullptr);
    
    void updateFeatures(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText);
    
    void updateFeatures(RenderGroup* group, Text* text, BoundingBox* boundingBox, const QString& plainText);
    
    const QString getElidedPlainText(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText);
    
    const QString getElidedPlainText(Text* text, BoundingBox* boundingBox, const QString& plainText);
    
    const QPointF getPos(RenderGroup* group, BoundingBox* boundingBox);
    
    const QPointF getPos(Text* text, BoundingBox* boundingBox);
    
    const QColor getDefaultTextColor(RenderGroup* group);
    
    const QColor getDefaultTextColor(GraphicalPrimitive1D* graphicalPrimitive1D, QColor textColor);
    
    const QFont getFont(RenderGroup* group, BoundingBox* boundingBox);
    
    const QFont getFont(Text* text, BoundingBox* boundingBox, QFont font);
    
    const Qt::Alignment getTextHorizontalAlignment(Text* text);
    
    const Qt::Alignment getTextHorizontalAlignment(RenderGroup* group);
    
    const Qt::Alignment getTextVerticalAlignment(Text* text);
    
    const Qt::Alignment getTextVerticalAlignment(RenderGroup* group);
    
    const qreal getTextVerticalPadding(Text* text, BoundingBox* boundingBox);
    
    const qreal getTextVerticalPadding(RenderGroup* group, BoundingBox* boundingBox);
};

#endif
