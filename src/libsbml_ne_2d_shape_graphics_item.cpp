#include "libsbml_ne_2d_shape_graphics_item.h"

My2DShapeGraphicsItem::My2DShapeGraphicsItem() {
    
}

const QBrush My2DShapeGraphicsItem::getBrush(RenderGroup* group, BoundingBox* boundingBox) {
    return getBrush(group, boundingBox, QBrush(Qt::transparent, Qt::SolidPattern));
}

const QBrush My2DShapeGraphicsItem::getBrush(GraphicalPrimitive2D* graphicalPrimitive2D, BoundingBox* boundingBox, QBrush brush) {
    if (graphicalPrimitive2D->isSetFill()) {
        ColorDefinition* color = emit askForColorDefinition(graphicalPrimitive2D->getFill().c_str());
        GradientBase* gradient = emit askForGradientDefinition(graphicalPrimitive2D->getFill().c_str());
        if (color)
            brush.setColor(QColor(color->getValue().c_str()));
        else if (gradient)
            brush = QBrush(getGradient(gradient, boundingBox));
        else
            brush.setColor(QColor(graphicalPrimitive2D->getFill().c_str()));
    }
    
    return brush;
}

QGradient My2DShapeGraphicsItem::getGradient(GradientBase* gradientBase, BoundingBox* boundingBox) {
    QGradient gradient;
    if (gradientBase->isLinearGradient())
        gradient = *createLinearGradient((LinearGradient*)gradientBase, boundingBox);
    else if (gradientBase->isRadialGradient())
        gradient = *createRadialGradient((RadialGradient*)gradientBase, boundingBox);
    
    return gradient;
}

QGradient* My2DShapeGraphicsItem::createLinearGradient(LinearGradient* linearGradinet, BoundingBox* boundingBox) {
    QGradient* gradient = new QLinearGradient();
    setGradientFeatures(gradient, linearGradinet);
    // start point
    QPointF startPoint(0.0, 0.0);
    if (linearGradinet->isSetX1())
        startPoint.setX(linearGradinet->getX1().getAbsoluteValue() + 0.01 * linearGradinet->getX1().getRelativeValue() * boundingBox->width());
    if (linearGradinet->isSetY1())
        startPoint.setY(linearGradinet->getY1().getAbsoluteValue() + 0.01 * linearGradinet->getY1().getRelativeValue() * boundingBox->height());
    ((QLinearGradient*)gradient)->setStart(startPoint);
    // final stop point
    QPointF finalStopPoint = startPoint;
    if (linearGradinet->isSetX2())
        finalStopPoint.setX(linearGradinet->getX2().getAbsoluteValue() + 0.01 * linearGradinet->getX2().getRelativeValue() * boundingBox->width());
    if (linearGradinet->isSetY2())
        finalStopPoint.setY(linearGradinet->getY2().getAbsoluteValue() + 0.01 * linearGradinet->getY2().getRelativeValue() * boundingBox->height());
    ((QLinearGradient*)gradient)->setFinalStop(finalStopPoint);
    return gradient;
}

QGradient* My2DShapeGraphicsItem::createRadialGradient(RadialGradient* radialGradient, BoundingBox* boundingBox) {
    QGradient* gradient = new QRadialGradient();
    setGradientFeatures(gradient, radialGradient);
    // center
    QPointF centerPoint(0.0, 0.0);
    if (radialGradient->isSetCx())
        centerPoint.setX(radialGradient->getCx().getAbsoluteValue() + 0.01 * radialGradient->getCx().getRelativeValue() * boundingBox->width());
    if (radialGradient->isSetCy())
        centerPoint.setY(radialGradient->getCy().getAbsoluteValue() + 0.01 * radialGradient->getCy().getRelativeValue() * boundingBox->height());
    ((QRadialGradient*)gradient)->setCenter(centerPoint);
    // focal point
    QPointF focalPoint = centerPoint;
    if (radialGradient->isSetFx())
        focalPoint.setX(radialGradient->getFx().getAbsoluteValue() + 0.01 * radialGradient->getFx().getRelativeValue() * boundingBox->width());
    if (radialGradient->isSetFy())
        focalPoint.setY(radialGradient->getFy().getAbsoluteValue() + 0.01 * radialGradient->getFy().getRelativeValue() * boundingBox->height());
    ((QRadialGradient*)gradient)->setFocalPoint(focalPoint);
    // radius
    qreal radius = 0.0;
    if (radialGradient->isSetR())
        radius = radialGradient->getR().getAbsoluteValue() + 0.01 * radialGradient->getR().getRelativeValue() * 0.5 * (boundingBox->width() + boundingBox->height());
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
