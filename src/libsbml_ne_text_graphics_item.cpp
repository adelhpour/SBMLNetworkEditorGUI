#include "libsbml_ne_text_graphics_item.h"
#include <QTextOption>
#include <QTextDocument>
#include <QFontMetrics>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyTextGraphicsItem::MyTextGraphicsItem(QGraphicsItem* parent) : QGraphicsTextItem(parent) {
    
}

void MyTextGraphicsItem::updateFeatures(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText) {
    setPlainText(getElidedPlainText(group, boundingBox, plainText));
    setTextWidth(getDimensionWidth(boundingBox));
    setPos(getPos(group, boundingBox));
    setDefaultTextColor(getDefaultTextColor(group));
    setFont(getFont(group, boundingBox));
    QTextOption option = document()->defaultTextOption();
    option.setAlignment(getTextHorizontalAlignment(group) | getTextVerticalAlignment(group));
    document()->setDefaultTextOption(option);
}

void MyTextGraphicsItem::updateFeatures(RenderGroup* group, Text* text, BoundingBox* boundingBox, const QString& plainText) {
    setPlainText(getElidedPlainText(text, boundingBox, plainText));
    setTextWidth(getDimensionWidth(boundingBox));
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
    return fontMetrics.elidedText(plainText, Qt::ElideRight, 0.9 * getDimensionWidth(boundingBox));
}

const QString MyTextGraphicsItem::getElidedPlainText(Text* text, BoundingBox* boundingBox, const QString& plainText) {
    QFontMetrics fontMetrics(getFont(text, boundingBox, font()));
    return fontMetrics.elidedText(plainText, Qt::ElideRight, getDimensionWidth(boundingBox));
}

const QPointF MyTextGraphicsItem::getPos(RenderGroup* group, BoundingBox* boundingBox) {
    return QPointF(getPositionX(boundingBox), getPositionY(boundingBox) + getTextVerticalPadding(group, boundingBox));
}

const QPointF MyTextGraphicsItem::getPos(Text* text, BoundingBox* boundingBox) {
    qreal x = getPositionX(boundingBox);
    qreal y = getPositionY(boundingBox);
    if (isSetTextShapeX(text))
        x += getTextShapeX(text).getAbsoluteValue() + 0.01 * getTextShapeX(text).getRelativeValue() * getDimensionWidth(boundingBox);
    if (isSetTextShapeY(text))
        y += getTextShapeY(text).getAbsoluteValue() + 0.01 * getTextShapeY(text).getRelativeValue() * getDimensionHeight(boundingBox);
    
    return QPointF(x, y + getTextVerticalPadding(text, boundingBox));
}

const QColor MyTextGraphicsItem::getDefaultTextColor(RenderGroup* group) {
    return getDefaultTextColor(group, QColor(Qt::black));
}

const QColor MyTextGraphicsItem::getDefaultTextColor(GraphicalPrimitive1D* graphicalPrimitive1D, QColor textColor) {
    if (isSetStrokeColor(graphicalPrimitive1D)) {
        ColorDefinition* color = emit askForColorDefinition(getStrokeColor(graphicalPrimitive1D).c_str());
        if (color)
            textColor = QColor(color->getValue().c_str());
        else
            textColor = QColor(getStrokeColor(graphicalPrimitive1D).c_str());
    }

    return textColor;
}

const QFont MyTextGraphicsItem::getFont(RenderGroup* group, BoundingBox* boundingBox) {
    QFont font;
    if (isSetFontFamily(group))
        font.setFamily(getFontFamily(group).c_str());
    if (isSetFontSize(group))
        font.setPointSize(getFontSize(group).getAbsoluteValue() + 0.01 * getFontSize(group).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetFontWeight(group)) {
        if (getFontWeight (group) == "bold")
            font.setBold(true);;
    }
    if (isSetFontStyle(group)) {
        if (getFontStyle(group) == "italic")
            font.setItalic(true);
    }

    return font;
}
                        
const QFont MyTextGraphicsItem::getFont(Text* text, BoundingBox* boundingBox, QFont font) {
    if (isSetFontFamily(text))
        font.setFamily(getFontFamily(text).c_str());
    if (isSetFontSize(text))
        font.setPointSize(getFontSize(text).getAbsoluteValue() + 0.01 * getFontSize(text).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetFontWeight(text)) {
        if (getFontWeight(text) == "bold")
            font.setBold(true);;
    }
    if (isSetFontStyle(text)) {
        if (getFontStyle(text) == "italic")
            font.setItalic(true);
    }

    return font;
}

const Qt::Alignment MyTextGraphicsItem::getTextHorizontalAlignment(RenderGroup* group) {
    if (isSetTextAnchor(group)) {
        if (getTextAnchor(group) == "start")
            return Qt::AlignLeft;
        else if (getTextAnchor(group) == "middle")
            return Qt::AlignHCenter;
        else if (getTextAnchor(group) == "end")
            return Qt::AlignRight;
    }

    return Qt::AlignHCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextHorizontalAlignment(Text* text) {
    if (isSetTextAnchor(text)) {
        if (getTextAnchor(text) == "start")
            return Qt::AlignLeft;
        else if (getTextAnchor(text) == "middle")
            return Qt::AlignHCenter;
        else if (getTextAnchor(text) == "end")
            return Qt::AlignRight;
    }

    return Qt::AlignHCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextVerticalAlignment(RenderGroup* group) {
    if (isSetVTextAnchor(group)) {
        if (getVTextAnchor(group) == "top")
            return Qt::AlignTop;
        else if (getVTextAnchor(group) == "middle")
            return Qt::AlignVCenter;
        else if (getVTextAnchor(group) == "bottom")
            return Qt::AlignBottom;
        else if (getVTextAnchor(group) == "baseline")
            return Qt::AlignBaseline;
    }

    return Qt::AlignVCenter;
}

const Qt::Alignment MyTextGraphicsItem::getTextVerticalAlignment(Text* text) {
    if (text->isSetVTextAnchor()) {
        if (getVTextAnchor(text) == "top")
            return Qt::AlignTop;
        else if (getVTextAnchor(text) == "middle")
            return Qt::AlignVCenter;
        else if (getVTextAnchor(text) == "bottom")
            return Qt::AlignBottom;
        else if (getVTextAnchor(text) == "baseline")
            return Qt::AlignBaseline;
    }

    return Qt::AlignVCenter;
}

const qreal MyTextGraphicsItem::getTextVerticalPadding(RenderGroup* group, BoundingBox* boundingBox) {
    QFontMetrics fontMetrics(getFont(group, boundingBox));
    if (getDimensionHeight(boundingBox) > fontMetrics.height()) {
        if (getTextVerticalAlignment(group) == Qt::AlignVCenter)
            return 0.5 * getDimensionHeight(boundingBox) - 0.75 * fontMetrics.height();
        else if (getTextVerticalAlignment(group) == Qt::AlignBaseline)
            return 0.5 * getDimensionHeight(boundingBox) - 0.5 * fontMetrics.height();
        else if (getTextVerticalAlignment(group) == Qt::AlignBottom)
            return getDimensionHeight(boundingBox) - 1.5 * fontMetrics.height();
    }
    
    return 0.000;
}

const qreal MyTextGraphicsItem::getTextVerticalPadding(Text* text, BoundingBox* boundingBox) {
    QFontMetrics fontMetrics(getFont(text, boundingBox, font()));
    if (getDimensionHeight(boundingBox) > fontMetrics.height()) {
        if (getTextVerticalAlignment(text) == Qt::AlignVCenter)
            return 0.5 * getDimensionHeight(boundingBox) - 0.75 * fontMetrics.height();
        else if (getTextVerticalAlignment(text) == Qt::AlignBaseline)
            return 0.5 * getDimensionHeight(boundingBox) - 0.5 * fontMetrics.height();
        else if (getTextVerticalAlignment(text) == Qt::AlignBottom)
            return getDimensionHeight(boundingBox) - 1.5 * fontMetrics.height();
    }
    
    return 0.000;
}

void MyTextGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseDoubleClickEvent(event);
}
