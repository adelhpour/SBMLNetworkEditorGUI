#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

// MyFeatureMenu

MyFeatureMenu::MyFeatureMenu(QWidget* elementFeatureMenu, QWidget* parent) : MyGroupBox(parent) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setStyleSheet("QGroupBox { background-color: white; font: bold; border: 1px white; border-radius: 5px; margin-top: 1ex; }" "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px 0px 5px; }");
    setContentsMargins(0, 0, 0, 0);
    
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->addWidget(elementFeatureMenu, contentLayout->rowCount(), 0);
    setLayout(contentLayout);
}

// MyBoundingBoxMenu

MyBoundingBoxMenu::MyBoundingBoxMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);

    // x
    _xParameter = new MyBoundingBoxXParameter(graphicalObject);
    _xParameter->read();
    connect(_xParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // y
    _yParameter = new MyBoundingBoxYParameter(graphicalObject);
    _yParameter->read();
    connect(_yParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // width
    _widthParameter = new MyBoundingBoxWidthParameter(graphicalObject);
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // height
    _heightParameter = new MyBoundingBoxHeightParameter(graphicalObject);
    _heightParameter->read();
    connect(_heightParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    setLayout(contentLayout);
}

// MyGeometricShapesMenu

MyGeometricShapesMenu::MyGeometricShapesMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->addWidget(createGeometricShapesMenu(graphicalObject, style), contentLayout->rowCount(), 0);
    setLayout(contentLayout);
}

QWidget* MyGeometricShapesMenu::createGeometricShapesMenu(GraphicalObject* graphicalObject, Style* style) {
    
    MyTreeView* geometricShapesMenuTree = new MyTreeView(this);
    for (unsigned int i = 0; i < style->getGroup()->getNumElements(); i++) {
        Transformation2D* shape = style->getGroup()->getElement(i);
        QWidget* geometricShapeMenu = NULL;
        if (shape->isRectangle()) {
            geometricShapeMenu = new MyRectangleShapeMenu(graphicalObject->getBoundingBox(), (Rectangle*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, "Rectangle");
        }
        else if (shape->isEllipse()) {
            geometricShapeMenu = new MyEllipseShapeMenu(graphicalObject->getBoundingBox(), (Ellipse*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, "Ellipse");
        }
        else if (shape->isPolygon()) {
            geometricShapeMenu = new MyPolygonShapeMenu(graphicalObject->getBoundingBox(), (Polygon*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, "Polygon");
        }
        connect(geometricShapeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    }

    return geometricShapesMenuTree;
}

// My1DGeometricShapeMenu

My1DGeometricShapeMenu::My1DGeometricShapeMenu(BoundingBox* boundingBox, GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    
    // stroke width
    _strokeWidthParameter = new MyStrokeWidthParameter(graphicalPrimitive1D);
    _strokeWidthParameter->read();
    connect(_strokeWidthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_strokeWidthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_strokeWidthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // stroke color
    _strokeColorParameter = new MyStrokeColorParameter(graphicalPrimitive1D);
    _strokeColorParameter->read();
    connect(_strokeColorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_strokeColorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_strokeColorParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    
    // stroke dasharray
    _strokeDashArrayParameter = new MyStrokeDashArrayParameter(graphicalPrimitive1D);
    _strokeDashArrayParameter->read();
    connect(_strokeDashArrayParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_strokeDashArrayParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_strokeDashArrayParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    
    setLayout(contentLayout);
}

// My2DGeometricShapeMenu

My2DGeometricShapeMenu::My2DGeometricShapeMenu(BoundingBox* boundingBox, GraphicalPrimitive2D* graphicalPrimitive2D, QWidget* parent) : My1DGeometricShapeMenu(boundingBox, graphicalPrimitive2D, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // fill
    _fillParameter = new MyFillParameter(graphicalPrimitive2D);
    _fillParameter->read();
    connect(_fillParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fillParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fillParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyRectangleShapeMenu

MyRectangleShapeMenu::MyRectangleShapeMenu(BoundingBox* boundingBox, Rectangle* rectangle, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, rectangle, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // x
    _xAbsParameter = new MyRectangleShapeXAbsoluteParameter(rectangle);
    _xAbsParameter->read();
    connect(_xAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _xRelParameter = new MyRectangleShapeXRelativeParameter(rectangle);
    _xRelParameter->read();
    connect(_xRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // y
    _yAbsParameter = new MyRectangleShapeYAbsoluteParameter(rectangle);
    _yAbsParameter->read();
    connect(_yAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _yRelParameter = new MyRectangleShapeYRelativeParameter(rectangle);
    _yRelParameter->read();
    connect(_yRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // width
    _widthAbsParameter = new MyRectangleShapeWidthAbsoluteParameter(rectangle);
    _widthAbsParameter->read();
    connect(_widthAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _widthRelParameter = new MyRectangleShapeWidthRelativeParameter(rectangle);
    _widthRelParameter->read();
    connect(_widthRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // height
    _heightAbsParameter = new MyRectangleShapeHeightAbsoluteParameter(rectangle);
    _heightAbsParameter->read();
    connect(_heightAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _heightRelParameter = new MyRectangleShapeHeightRelativeParameter(rectangle);
    _heightRelParameter->read();
    connect(_heightRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // ratio
    _ratioParameter = new MyRectangleShapeRatioParameter(rectangle);
    _ratioParameter->read();
    connect(_ratioParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_ratioParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_ratioParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // rx
    _rXAbsParameter = new MyRectangleShapeRXAbsoluteParameter(rectangle);
    _rXAbsParameter->read();
    connect(_rXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rXRelParameter = new MyRectangleShapeRXRelativeParameter(rectangle);
    _rXRelParameter->read();
    connect(_rXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // ry
    _rYAbsParameter = new MyRectangleShapeRYAbsoluteParameter(rectangle);
    _rYAbsParameter->read();
    connect(_rYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rYAbsParameter = new MyRectangleShapeRYRelativeParameter(rectangle);
    _rYAbsParameter->read();
    connect(_rYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyEllipseShapeMenu

MyEllipseShapeMenu::MyEllipseShapeMenu(BoundingBox* boundingBox, Ellipse* ellipse, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, ellipse, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // cx
    _cXAbsParameter = new MyEllipseShapeCXAbsoluteParameter(ellipse);
    _cXAbsParameter->read();
    connect(_cXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_cXAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_cXAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _cXRelParameter = new MyEllipseShapeCXRelativeParameter(ellipse);
    _cXRelParameter->read();
    connect(_cXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_cXRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_cXRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // cy
    _cYAbsParameter = new MyEllipseShapeCYAbsoluteParameter(ellipse);
    _cYAbsParameter->read();
    connect(_cYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_cYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_cYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _cYRelParameter = new MyEllipseShapeCYRelativeParameter(ellipse);
    _cYRelParameter->read();
    connect(_cYRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_cYRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_cYRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // rx
    _rXAbsParameter = new MyEllipseShapeRXAbsoluteParameter(ellipse);
    _rXAbsParameter->read();
    connect(_rXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rXRelParameter = new MyEllipseShapeRXRelativeParameter(ellipse);
    _rXRelParameter->read();
    connect(_rXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // ry
    _rYAbsParameter = new MyEllipseShapeRYAbsoluteParameter(ellipse);
    _rYAbsParameter->read();
    connect(_rYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rYRelParameter = new MyEllipseShapeRYRelativeParameter(ellipse);
    _rYRelParameter->read();
    connect(_rYRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // ratio
    _ratioParameter = new MyEllipseShapeRatioParameter(ellipse);
    _ratioParameter->read();
    connect(_ratioParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_ratioParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_ratioParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyPolygonShapeMenu

MyPolygonShapeMenu::MyPolygonShapeMenu(BoundingBox* boundingBox, Polygon* polygon, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, polygon, parent) {
    
}

// MyStrokeMenu

MyStrokeMenu::MyStrokeMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    /*
    // width
    _widthParameter = new MyStrokeWidthParameter(graphicalObject, style->getGroup());
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // color
    _colorParameter = new MyStrokeColorParameter(graphicalObject, style->getGroup());
    _colorParameter->read();
    connect(_colorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_colorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_colorParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    
    // dasharray
    _dashArrayParameter = new MyStrokeDashArrayParameter(graphicalObject, style->getGroup());
    _dashArrayParameter->read();
    connect(_dashArrayParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_dashArrayParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_dashArrayParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    */
    setLayout(contentLayout);
}
