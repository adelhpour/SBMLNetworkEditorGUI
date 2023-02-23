#include "libsbml_ne_text_graphics_item.h"
#include <QTextOption>
#include <QTextDocument>
#include <QFontMetrics>

MyTextGraphicsItem::MyTextGraphicsItem(QGraphicsItem* parent) : QGraphicsTextItem(parent) {
    
}

void MyTextGraphicsItem::updateFeatures(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText) {
    setPlainText(getElidedPlainText(group, boundingBox, plainText));
    setTextWidth(boundingBox->width());
    setPos(getPos(group, boundingBox));
    setDefaultTextColor(getDefaultTextColor(group));
    setFont(getFont(group, boundingBox));
    QTextOption option = document()->defaultTextOption();
    option.setAlignment(getTextHorizontalAlignment(group) | getTextVerticalAlignment(group));
    document()->setDefaultTextOption(option);
}

void MyTextGraphicsItem::updateFeatures(RenderGroup* group, Text* text, BoundingBox* boundingBox, const QString& plainText) {
    setPlainText(getElidedPlainText(text, boundingBox, plainText));
    setTextWidth(boundingBox->width());
    setPos(getPos(text, boundingBox));
    setDefaultTextColor(getDefaultTextColor(group));
    setDefaultTextColor(getDefaultTextColor(text, defaultTextColor()));
    setFont(getFont(group, boundingBox));
    setFont(getFont(text, boundingBox, font()));
    QTextOption option = document()->defaultTextOption();
    option.setAlignment(getTextHorizontalAlignment(text) | getTextVerticalAlignment(text));
    document()->setDefaultTextOption(option);
}

const QString MyTextGraphicsItem::getElidedPlainText(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText) {
    QFontMetrics fontMetrics(getFont(group, boundingBox));
    return fontMetrics.elidedText(plainText, Qt::ElideRight, 0.9 * boundingBox->width());
}

const QString MyTextGraphicsItem::getElidedPlainText(Text* text, BoundingBox* boundingBox, const QString& plainText) {
    QFontMetrics fontMetrics(getFont(text, boundingBox, font()));
    return fontMetrics.elidedText(plainText, Qt::ElideRight, boundingBox->width());
}

const QPointF MyTextGraphicsItem::getPos(RenderGroup* group, BoundingBox* boundingBox) {
    return QPointF(boundingBox->x(), boundingBox->y() + getTextVerticalPadding(group, boundingBox));
}

const QPointF MyTextGraphicsItem::getPos(Text* text, BoundingBox* boundingBox) {
    qreal x = boundingBox->x();
    qreal y = boundingBox->y();
    if (text->isSetX())
        x += text->getX().getAbsoluteValue() + 0.01 * text->getX().getRelativeValue() * boundingBox->width();
    if (text->isSetY())
        y += text->getY().getAbsoluteValue() + 0.01 * text->getY().getRelativeValue() * boundingBox->height();
    
    return QPointF(x, y + getTextVerticalPadding(text, boundingBox));
}

const QColor MyTextGraphicsItem::getDefaultTextColor(RenderGroup* group) {
    return getDefaultTextColor(group, QColor(Qt::black));
}

const QColor MyTextGraphicsItem::getDefaultTextColor(GraphicalPrimitive1D* graphicalPrimitive1D, QColor textColor) {
    if (graphicalPrimitive1D->isSetStroke()) {
        ColorDefinition* color = emit askForColorDefinition(graphicalPrimitive1D->getStroke().c_str());
        if (color)
            textColor = QColor(color->getValue().c_str());
        else
            textColor = QColor(graphicalPrimitive1D->getStroke().c_str());
    }

    return textColor;
}

const QFont MyTextGraphicsItem::getFont(RenderGroup* group, BoundingBox* boundingBox) {
    QFont font;
    if (group->isSetFontFamily())
        font.setFamily(group->getFontFamily().c_str());
    if (group->isSetFontSize())
        font.setPointSize(group->getFontSize().getAbsoluteValue() + 0.01 * group->getFontSize().getRelativeValue() * boundingBox->width());
    if (group->isSetFontWeight()) {
        if (group->getFontWeightAsString () == "bold")
            font.setBold(true);;
    }
    if (group->isSetFontStyle()) {
        if (group->getFontStyleAsString() == "italic")
            font.setItalic(true);
    }

    return font;
}
                        
const QFont MyTextGraphicsItem::getFont(Text* text, BoundingBox* boundingBox, QFont font) {
    if (text->isSetFontFamily())
        font.setFamily(text->getFontFamily().c_str());
    if (text->isSetFontSize())
        font.setPointSize(text->getFontSize().getAbsoluteValue() + 0.01 * text->getFontSize().getRelativeValue() * boundingBox->width());
    if (text->isSetFontWeight()) {
        if (text->getFontWeightAsString () == "bold")
            font.setBold(true);;
    }
    if (text->isSetFontStyle()) {
        if (text->getFontStyleAsString() == "italic")
            font.setItalic(true);
    }

    return font;
}

const Qt::Alignment MyTextGraphicsItem::getTextHorizontalAlignment(RenderGroup* group) {
    if (group->isSetTextAnchor()) {
        if (group->getTextAnchorAsString() == "start")
            return Qt::AlignLeft;
        else if (group->getTextAnchorAsString() == "middle")
            return Qt::AlignHCenter;
        else if (group->getTextAnchorAsString() == "end")
            return Qt::AlignRight;
    }

    return Qt::AlignHCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextHorizontalAlignment(Text* text) {
    if (text->isSetTextAnchor()) {
        if (text->getTextAnchorAsString() == "start")
            return Qt::AlignLeft;
        else if (text->getTextAnchorAsString() == "middle")
            return Qt::AlignHCenter;
        else if (text->getTextAnchorAsString() == "end")
            return Qt::AlignRight;
    }

    return Qt::AlignHCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextVerticalAlignment(RenderGroup* group) {
    if (group->isSetVTextAnchor()) {
        if (group->getVTextAnchorAsString() == "top")
            return Qt::AlignTop;
        else if (group->getVTextAnchorAsString() == "middle")
            return Qt::AlignVCenter;
        else if (group->getVTextAnchorAsString() == "bottom")
            return Qt::AlignBottom;
        else if (group->getVTextAnchorAsString() == "baseline")
            return Qt::AlignBaseline;
    }

    return Qt::AlignVCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextVerticalAlignment(Text* text) {
    if (text->isSetVTextAnchor()) {
        if (text->getVTextAnchorAsString() == "top")
            return Qt::AlignTop;
        else if (text->getVTextAnchorAsString() == "middle")
            return Qt::AlignVCenter;
        else if (text->getVTextAnchorAsString() == "bottom")
            return Qt::AlignBottom;
        else if (text->getVTextAnchorAsString() == "baseline")
            return Qt::AlignBaseline;
    }

    return Qt::AlignVCenter;
}

const qreal MyTextGraphicsItem::getTextVerticalPadding(RenderGroup* group, BoundingBox* boundingBox) {
    QFontMetrics fontMetrics(getFont(group, boundingBox));
    if (boundingBox->height() > fontMetrics.height()) {
        if (getTextVerticalAlignment(group) == Qt::AlignVCenter)
            return 0.5 * boundingBox->height() - 0.75 * fontMetrics.height();
        else if (getTextVerticalAlignment(group) == Qt::AlignBaseline)
            return 0.5 * boundingBox->height() - 0.5 * fontMetrics.height();
        else if (getTextVerticalAlignment(group) == Qt::AlignBottom)
            return boundingBox->height() - 1.5 * fontMetrics.height();
    }
    
    return 0.000;
}

const qreal MyTextGraphicsItem::getTextVerticalPadding(Text* text, BoundingBox* boundingBox) {
    QFontMetrics fontMetrics(getFont(text, boundingBox, font()));
    if (boundingBox->height() > fontMetrics.height()) {
        if (getTextVerticalAlignment(text) == Qt::AlignVCenter)
            return 0.5 * boundingBox->height() - 0.75 * fontMetrics.height();
        else if (getTextVerticalAlignment(text) == Qt::AlignBaseline)
            return 0.5 * boundingBox->height() - 0.5 * fontMetrics.height();
        else if (getTextVerticalAlignment(text) == Qt::AlignBottom)
            return boundingBox->height() - 1.5 * fontMetrics.height();
    }
    
    return 0.000;
}

void MyTextGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseDoubleClickEvent(event);
}
