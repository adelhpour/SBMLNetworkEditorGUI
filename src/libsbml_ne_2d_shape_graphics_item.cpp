#include "libsbml_ne_2d_shape_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

My2DShapeGraphicsItem::My2DShapeGraphicsItem() {
    
}

const QBrush My2DShapeGraphicsItem::getBrush(RenderGroup* group, BoundingBox* boundingBox) {
    return getBrush(group, boundingBox, QBrush(Qt::transparent, Qt::SolidPattern));
}

const QBrush My2DShapeGraphicsItem::getBrush(GraphicalPrimitive2D* graphicalPrimitive2D, BoundingBox* boundingBox, QBrush brush) {
    if (isSetFillColor(graphicalPrimitive2D)) {
        ColorDefinition* color = emit askForColorDefinition(getFillColor(graphicalPrimitive2D).c_str());
        GradientBase* gradient = emit askForGradientDefinition(getFillColor(graphicalPrimitive2D).c_str());
        if (color)
            brush.setColor(QColor(getValue(color).c_str()));
        else if (gradient)
            brush = QBrush(getGradient(gradient, boundingBox));
        else
            brush.setColor(QColor(getFillColor(graphicalPrimitive2D).c_str()));
    }
    
    return brush;
}

QGradient My2DShapeGraphicsItem::getGradient(GradientBase* gradientBase, BoundingBox* boundingBox) {
    QGradient gradient;
    if (isLinearGradient(gradientBase))
        gradient = *createLinearGradient((LinearGradient*)gradientBase, boundingBox);
    else if (isRadialGradient(gradientBase))
        gradient = *createRadialGradient((RadialGradient*)gradientBase, boundingBox);
    
    return gradient;
}

QGradient* My2DShapeGraphicsItem::createLinearGradient(LinearGradient* linearGradient, BoundingBox* boundingBox) {
    QGradient* gradient = new QLinearGradient();
    setGradientFeatures(gradient, linearGradient);
    // start point
    QPointF startPoint(0.0, 0.0);
    if (isSetLinearGradientX1(linearGradient))
        startPoint.setX(getLinearGradientX1(linearGradient).getAbsoluteValue() + 0.01 * getLinearGradientX1(linearGradient).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetLinearGradientY1(linearGradient))
        startPoint.setY(getLinearGradientY1(linearGradient).getAbsoluteValue() + 0.01 * getLinearGradientY1(linearGradient).getRelativeValue() * getDimensionHeight(boundingBox));
    ((QLinearGradient*)gradient)->setStart(startPoint);
    // final stop point
    QPointF finalStopPoint = startPoint;
    if (isSetLinearGradientX2(linearGradient))
        finalStopPoint.setX(getLinearGradientX2(linearGradient).getAbsoluteValue() + 0.01 * getLinearGradientX2(linearGradient).getRelativeValue() * boundingBox->width());
    if (isSetLinearGradientY2(linearGradient))
        finalStopPoint.setY(getLinearGradientY2(linearGradient).getAbsoluteValue() + 0.01 * getLinearGradientY2(linearGradient).getRelativeValue() * boundingBox->height());
    ((QLinearGradient*)gradient)->setFinalStop(finalStopPoint);
    
    return gradient;
}

QGradient* My2DShapeGraphicsItem::createRadialGradient(RadialGradient* radialGradient, BoundingBox* boundingBox) {
    QGradient* gradient = new QRadialGradient();
    setGradientFeatures(gradient, radialGradient);
    // center
    QPointF centerPoint(0.0, 0.0);
    if (isSetRadialGradientCx(radialGradient))
        centerPoint.setX(getRadialGradientCx(radialGradient).getAbsoluteValue() + 0.01 * getRadialGradientCx(radialGradient).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetRadialGradientCy(radialGradient))
        centerPoint.setY(getRadialGradientCy(radialGradient).getAbsoluteValue() + 0.01 * getRadialGradientCy(radialGradient).getRelativeValue() * getDimensionHeight(boundingBox));
    ((QRadialGradient*)gradient)->setCenter(centerPoint);
    // focal point
    QPointF focalPoint = centerPoint;
    if (isSetRadialGradientFx(radialGradient))
        focalPoint.setX(getRadialGradientFx(radialGradient).getAbsoluteValue() + 0.01 * getRadialGradientFx(radialGradient).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetRadialGradientFy(radialGradient))
        focalPoint.setY(getRadialGradientFy(radialGradient).getAbsoluteValue() + 0.01 * getRadialGradientFy(radialGradient).getRelativeValue() * getDimensionHeight(boundingBox));
    ((QRadialGradient*)gradient)->setFocalPoint(focalPoint);
    // radius
    qreal radius = 0.0;
    if (isSetRadialGradientR(radialGradient))
        radius = getRadialGradientR(radialGradient).getAbsoluteValue() + 0.01 * getRadialGradientR(radialGradient).getRelativeValue() * 0.5 * (getDimensionWidth(boundingBox) + getDimensionHeight(boundingBox));
    ((QRadialGradient*)gradient)->setFocalRadius(radius);
        
    return gradient;
}

void My2DShapeGraphicsItem::setGradientFeatures(QGradient* gradient, GradientBase* gradientBase) {
    // spread method
    if (isSetSpreadMethod(gradientBase)) {
        if (getSpreadMethod(gradientBase) == "pad")
            gradient->setSpread(QGradient::PadSpread);
        else if (getSpreadMethod(gradientBase) == "reflect")
            gradient->setSpread(QGradient::ReflectSpread);
        else if (getSpreadMethod(gradientBase) == "repeat")
            gradient->setSpread(QGradient::RepeatSpread);
    }
    // stops
    QGradientStops gradientStops;
    for (unsigned int i = 0; i < getNumGradientStops(gradientBase); i++) {
        QGradientStop gradientStop;
        if (isSetOffset(getGradientStop(gradientBase, i)))
            gradientStop.first = 0.01 * getOffset(getGradientStop(gradientBase, i)).getRelativeValue();
        if (isSetStopColor(gradientBase, i)) {
            ColorDefinition* color = emit askForColorDefinition(QString(getStopColor(getGradientStop(gradientBase, i)).c_str()));
            if (color)
                gradientStop.second = QColor(getValue(color).c_str());
            else
                gradientStop.second = QColor(getStopColor(getGradientStop(gradientBase, i)).c_str());
        }
        gradientStops.push_back(gradientStop);
    }
    gradient->setStops(gradientStops);
}
