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
    _xParameter = new MyBoundingBoxXParameter(graphicalObject, style->getGroup());
    _xParameter->read();
    connect(_xParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // y
    _yParameter = new MyBoundingBoxYParameter(graphicalObject, style->getGroup());
    _yParameter->read();
    connect(_yParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // width
    _widthParameter = new MyBoundingBoxWidthParameter(graphicalObject, style->getGroup());
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // height
    _heightParameter = new MyBoundingBoxHeightParameter(graphicalObject, style->getGroup());
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
    
    // width
    _widthParameter = new MyStrokeWidthParameter(NULL, graphicalPrimitive1D);
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // color
    _colorParameter = new MyStrokeColorParameter(NULL, graphicalPrimitive1D);
    _colorParameter->read();
    connect(_colorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_colorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_colorParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    
    // dasharray
    _dashArrayParameter = new MyStrokeDashArrayParameter(NULL, graphicalPrimitive1D);
    _dashArrayParameter->read();
    connect(_dashArrayParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_dashArrayParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_dashArrayParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);
    
    setLayout(contentLayout);
}

// My2DGeometricShapeMenu

My2DGeometricShapeMenu::My2DGeometricShapeMenu(BoundingBox* boundingBox, GraphicalPrimitive2D* graphicalPrimitive2D, QWidget* parent) : My1DGeometricShapeMenu(boundingBox, graphicalPrimitive2D, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // fill
    _fillParameter = new MyFillParameter(NULL, graphicalPrimitive2D);
    _fillParameter->read();
    connect(_fillParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fillParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fillParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyRectangleShapeMenu

MyRectangleShapeMenu::MyRectangleShapeMenu(BoundingBox* boundingBox, Rectangle* rectangle, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, rectangle, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // x
    _xAbsParameter = new MyRelAbsAbsolutePositionalParameter("X (abs)", &rectangle->getX());
    _xAbsParameter->read();
    connect(_xAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _xRelParameter = new MyRelAbsRelativePositionalParameter("X (rel) %", &rectangle->getX());
    _xRelParameter->read();
    connect(_xRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // y
    _yAbsParameter = new MyRelAbsAbsolutePositionalParameter("Y (abs)", &rectangle->getY());
    _yAbsParameter->read();
    connect(_yAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _yRelParameter = new MyRelAbsRelativePositionalParameter("Y (rel) %", &rectangle->getY());
    _yRelParameter->read();
    connect(_yRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // width
    _widthAbsParameter = new MyRelAbsAbsoluteDimensionalParameter("Width (abs)", &rectangle->getWidth());
    _widthAbsParameter->read();
    connect(_widthAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _widthRelParameter = new MyRelAbsRelativeDimensionalParameter("Width (rel) %", &rectangle->getWidth());
    _widthRelParameter->read();
    connect(_widthRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // height
    _heightAbsParameter = new MyRelAbsAbsoluteDimensionalParameter("Height (abs)", &rectangle->getHeight());
    _heightAbsParameter->read();
    connect(_heightAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _heightRelParameter = new MyRelAbsRelativeDimensionalParameter("Height (rel) %", &rectangle->getHeight());
    _heightRelParameter->read();
    connect(_heightRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // rx
    _rXAbsParameter = new MyRelAbsAbsoluteDimensionalParameter("RX (abs)", &rectangle->getRX());
    _rXAbsParameter->read();
    connect(_rXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rXRelParameter = new MyRelAbsRelativeDimensionalParameter("RX (rel) %", &rectangle->getRX());
    _rXRelParameter->read();
    connect(_rXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rXRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rXRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // ry
    _rYAbsParameter = new MyRelAbsAbsoluteDimensionalParameter("RX (abs)", &rectangle->getRY());
    _rYAbsParameter->read();
    connect(_rYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    _rYAbsParameter = new MyRelAbsRelativeDimensionalParameter("RY (rel) %", &rectangle->getRY());
    _rYAbsParameter->read();
    connect(_rYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_rYAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_rYAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyEllipseShapeMenu

MyEllipseShapeMenu::MyEllipseShapeMenu(BoundingBox* boundingBox, Ellipse* ellipse, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, ellipse, parent) {
    
}

// MyPolygonShapeMenu

MyPolygonShapeMenu::MyPolygonShapeMenu(BoundingBox* boundingBox, Polygon* polygon, QWidget* parent) : My2DGeometricShapeMenu(boundingBox, polygon, parent) {
    
}

// MyStrokeMenu

MyStrokeMenu::MyStrokeMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    
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
    
    setLayout(contentLayout);
}
