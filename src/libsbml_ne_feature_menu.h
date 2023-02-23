#ifndef __LIBSBML_NE_FEATURE_MENU_H
#define __LIBSBML_NE_FEATURE_MENU_H
#include "libsbml_ne_parameters.h"

class MyFeatureMenu : public MyGroupBox {
    
public:
    MyFeatureMenu(QWidget* elementFeatureMenu, QWidget* parent = nullptr);
    
};

class MyBoundingBoxMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    MyBoundingBoxMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent = nullptr);
    
signals:
    void isUpdated();
    
protected:
    MyParameterBase* _xParameter;
    MyParameterBase* _yParameter;
    MyParameterBase* _widthParameter;
    MyParameterBase* _heightParameter;
};

class MyGeometricShapesMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    MyGeometricShapesMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent = nullptr);
    
    QWidget* createGeometricShapesMenu(GraphicalObject* graphicalObject, Style* style);
    
signals:
    void isUpdated();
};

class My1DGeometricShapeMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    My1DGeometricShapeMenu(BoundingBox* boundingBox, GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent = nullptr);
    
signals:
    void isUpdated();
    
protected:
    MyParameterBase* _widthParameter;
    MyParameterBase* _colorParameter;
    MyParameterBase* _dashArrayParameter;
};

class My2DGeometricShapeMenu : public My1DGeometricShapeMenu {
    Q_OBJECT
    
public:
    My2DGeometricShapeMenu(BoundingBox* boundingBox, GraphicalPrimitive2D* graphicalPrimitive2D, QWidget* parent = nullptr);
    
protected:
    MyParameterBase* _fillParameter;
};

class MyRectangleShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyRectangleShapeMenu(BoundingBox* boundingBox, Rectangle* rectangle, QWidget* parent = nullptr);
    
protected:
    MyParameterBase* _xAbsParameter;
    MyParameterBase* _xRelParameter;
    MyParameterBase* _yAbsParameter;
    MyParameterBase* _yRelParameter;
    MyParameterBase* _widthAbsParameter;
    MyParameterBase* _widthRelParameter;
    MyParameterBase* _heightAbsParameter;
    MyParameterBase* _heightRelParameter;
    MyParameterBase* _rXAbsParameter;
    MyParameterBase* _rXRelParameter;
    MyParameterBase* _rYAbsParameter;
    MyParameterBase* _rYRelParameter;
};

class MyEllipseShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyEllipseShapeMenu(BoundingBox* boundingBox, Ellipse* ellipse, QWidget* parent = nullptr);
};

class MyPolygonShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyPolygonShapeMenu(BoundingBox* boundingBox, Polygon* polygon, QWidget* parent = nullptr);
};

class MyStrokeMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    MyStrokeMenu(GraphicalObject* graphicalObject, Style* style, QWidget* parent = nullptr);
    
signals:
    void isUpdated();
    
protected:
    MyParameterBase* _widthParameter;
    MyParameterBase* _colorParameter;
    MyParameterBase* _dashArrayParameter;
};

#endif
