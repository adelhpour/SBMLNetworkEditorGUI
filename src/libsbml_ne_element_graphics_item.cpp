#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_curve_graphics_item.h"
#include "libsbml_ne_rect_graphics_item.h"
#include "libsbml_ne_ellipse_graphics_item.h"
#include "libsbml_ne_polygon_graphics_item.h"
#include "libsbml_ne_render_curve_graphics_item.h"
#include "libsbml_ne_image_graphics_item.h"
#include "libsbml_ne_text_graphics_item.h"

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

MyElementGraphicsItem::MyElementGraphicsItem(const qreal& zValue, QGraphicsItem* parent) : QGraphicsItemGroup(parent) {
    setHandlesChildEvents(false);
    setZValue(zValue);
}

void MyElementGraphicsItem::clear() {
    for (QGraphicsItem* item : childItems()) {
        removeFromGroup(item);
        delete item;
    }
}

void MyElementGraphicsItem::addGeometricShapes(RenderGroup* group, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    for (unsigned int i = 0; i < getNumGeometricShapes(group); i++)
        addGeometricShape(group, getGeometricShape(group, i), boundingBox, position, rotation);
}

void MyElementGraphicsItem::addGeometricShape(RenderGroup* group, Transformation2D* geometricShape, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    if (isRectangle(geometricShape))
        addRectangleGraphicsItem(group, (Rectangle*)geometricShape, boundingBox, position, rotation);
    else if (isEllipse(geometricShape))
        addEllipseGraphicsItem(group, (Ellipse*)geometricShape, boundingBox, position, rotation);
    else if (isPolygon(geometricShape))
        addPolygonGraphicsItem(group, (Polygon*)geometricShape, boundingBox, position, rotation);
    else if (isRenderCurve(geometricShape))
        addRenderCurveGraphicsItem(group, (RenderCurve*)geometricShape, boundingBox, position, rotation);
    else if (isImage(geometricShape))
        addImageGraphicsItem((Image*)geometricShape, boundingBox, position, rotation);
}

void MyElementGraphicsItem::addRectangleGraphicsItem(RenderGroup* group, Rectangle* rectangle, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    MyRectGraphicsItem* shape = new MyRectGraphicsItem(this);
    connect(shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect(shape, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
    shape->updateFeatures(group, rectangle, boundingBox, position, rotation);
    addToGroup(shape);
}

void MyElementGraphicsItem::addEllipseGraphicsItem(RenderGroup* group, Ellipse* ellipse, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    MyEllipseGraphicsItem* shape = new MyEllipseGraphicsItem(this);
    connect(shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect(shape, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
    shape->updateFeatures(group, ellipse, boundingBox, position, rotation);
    addToGroup(shape);
}

void MyElementGraphicsItem::addPolygonGraphicsItem(RenderGroup* group, Polygon* polygon, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    MyPolygonGraphicsItem* shape = new MyPolygonGraphicsItem(this);
    connect(shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect(shape, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
    shape->updateFeatures(group, polygon, boundingBox, position, rotation);
    addToGroup(shape);
}

void MyElementGraphicsItem::addRenderCurveGraphicsItem(RenderGroup* group, RenderCurve* renderCurve, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    MyRenderCurveGraphicsItem* shape = new MyRenderCurveGraphicsItem(this);
    connect(shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    connect(shape, SIGNAL(askForGradientDefinition(const QString&)), this, SIGNAL(askForGradientDefinition(const QString&)));
    shape->updateFeatures(group, renderCurve, boundingBox, position, rotation);
    addToGroup(shape);
}

void MyElementGraphicsItem::addImageGraphicsItem(Image* image, BoundingBox* boundingBox, const QPointF& position, const qreal& rotation) {
    MyImageGraphicsItem* shape = new MyImageGraphicsItem(this);
    shape->updateFeatures(image, boundingBox, position, rotation);
    addToGroup(shape);
}

void MyElementGraphicsItem::addCurveGraphicsItem(RenderGroup* group, Curve* curve) {
    MyCurveGraphicsItem* shape = new MyCurveGraphicsItem(this);
    connect(shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    shape->updateFeatures(group, curve);
    addToGroup(shape);
}

void MyElementGraphicsItem::addTextGraphicsItem(RenderGroup* group, BoundingBox* boundingBox, const QString& plainText) {
    MyTextGraphicsItem* shape = new MyTextGraphicsItem(this);
    connect((My1DShapeGraphicsItem*)shape, SIGNAL(askForColorDefinition(const QString&)), this, SIGNAL(askForColorDefinition(const QString&)));
    for (unsigned int i = 0; i < getNumGeometricShapes(group); i++) {
        Transformation2D* geometricShape = getGeometricShape(group, i);
        if (isText(geometricShape)) {
            shape->updateFeatures(group, (Text*)geometricShape, boundingBox, plainText);
            addToGroup(shape);
            return;
        }
    }
    shape->updateFeatures(group, boundingBox, plainText);
}

void MyElementGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseDoubleClickEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit mouseLeftButtonIsDoubleClicked();
        event->accept();
    }
}
