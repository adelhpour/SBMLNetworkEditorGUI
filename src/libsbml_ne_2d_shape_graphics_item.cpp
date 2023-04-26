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
            brush.setColor(QColor(color->getValue().c_str()));
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

QGradient* My2DShapeGraphicsItem::createLinearGradient(LinearGradient* linearGradinet, BoundingBox* boundingBox) {
    QGradient* gradient = new QLinearGradient();
    setGradientFeatures(gradient, linearGradinet);
    // start point
    QPointF startPoint(0.0, 0.0);
    if (isSetLinearGradientX1(linearGradinet))
        startPoint.setX(getLinearGradientX1(linearGradinet).getAbsoluteValue() + 0.01 * getLinearGradientX1(linearGradinet).getRelativeValue() * getDimensionWidth(boundingBox));
    if (isSetLinearGradientY1(linearGradinet))
        startPoint.setY(getLinearGradientY1(linearGradinet).getAbsoluteValue() + 0.01 * getLinearGradientY1(linearGradinet).getRelativeValue() * getDimensionHeight(boundingBox));
    ((QLinearGradient*)gradient)->setStart(startPoint);
    // final stop point
    QPointF finalStopPoint = startPoint;
    if (isSetLinearGradientX2(linearGradinet))
        finalStopPoint.setX(getLinearGradientX2(linearGradinet).getAbsoluteValue() + 0.01 * getLinearGradientX2(linearGradinet).getRelativeValue() * boundingBox->width());
    if (isSetLinearGradientY2(linearGradinet))
        finalStopPoint.setY(getLinearGradientY2(linearGradinet).getAbsoluteValue() + 0.01 * getLinearGradientY2(linearGradinet).getRelativeValue() * boundingBox->height());
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
    if (gradientBase->isSetSpreadMethod()) {
        if (gradientBase->getSpreadMethod() == GRADIENT_SPREADMETHOD_PAD)
            gradient->setSpread(QGradient::PadSpread);
        else if (gradientBase->getSpreadMethod() == GRADIENT_SPREADMETHOD_REFLECT)
            gradient->setSpread(QGradient::ReflectSpread);
        else if (gradientBase->getSpreadMethod() == GRADIENT_SPREADMETHOD_REPEAT)
            gradient->setSpread(QGradient::RepeatSpread);
    }
    // stops
    QGradientStops gradientStops;
    for (unsigned int i = 0; i < gradientBase->getNumGradientStops(); i++) {
        QGradientStop gradientStop;
        if (gradientBase->getGradientStop(i)->isSetOffset())
            gradientStop.first = 0.01 * gradientBase->getGradientStop(i)->getOffset().getRelativeValue();
        if (gradientBase->getGradientStop(i)->isSetStopColor()) {
            ColorDefinition* color = emit askForColorDefinition(QString(gradientBase->getGradientStop(i)->getStopColor().c_str()));
            if (color)
                gradientStop.second = QColor(color->getValue().c_str());
            else
                gradientStop.second = QColor(gradientBase->getGradientStop(i)->getStopColor().c_str());
        }
        gradientStops.push_back(gradientStop);
    }
    gradient->setStops(gradientStops);
}
