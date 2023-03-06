#ifndef __LIBSBML_NE_FEATURE_MENU_H
#define __LIBSBML_NE_FEATURE_MENU_H
#include "libsbml_ne_parameters.h"

#include <QDialogButtonBox>

class MyFeatureMenu : public MyGroupBox {
    
public:
    MyFeatureMenu(QWidget* elementFeatureMenu, QWidget* parent = nullptr);
    
};

class MyBoundingBoxMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    MyBoundingBoxMenu(GraphicalObject* graphicalObject, QWidget* parent = nullptr);
    
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
    MyGeometricShapesMenu(RenderGroup* renderGroup, QWidget* parent = nullptr);
    
    QWidget* createGeometricShapesMenu(RenderGroup* renderGroup);
    
signals:
    void isUpdated();
};

class My1DGeometricShapeMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    My1DGeometricShapeMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent = nullptr);
    
signals:
    void isUpdated();
    
protected:
    MyParameterBase* _strokeWidthParameter;
    MyParameterBase* _strokeColorParameter;
    MyParameterBase* _strokeDashArrayParameter;
};

class My2DGeometricShapeMenu : public My1DGeometricShapeMenu {
    Q_OBJECT
    
public:
    My2DGeometricShapeMenu(GraphicalPrimitive2D* graphicalPrimitive2D, QWidget* parent = nullptr);
    
protected:
    MyParameterBase* _fillParameter;
};

class MyRectangleShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyRectangleShapeMenu(Rectangle* rectangle, QWidget* parent = nullptr);
    
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
    MyParameterBase* _ratioParameter;
};

class MyEllipseShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyEllipseShapeMenu(Ellipse* ellipse, QWidget* parent = nullptr);
    
protected:
    MyParameterBase* _cXAbsParameter;
    MyParameterBase* _cXRelParameter;
    MyParameterBase* _cYAbsParameter;
    MyParameterBase* _cYRelParameter;
    MyParameterBase* _rXAbsParameter;
    MyParameterBase* _rXRelParameter;
    MyParameterBase* _rYAbsParameter;
    MyParameterBase* _rYRelParameter;
    MyParameterBase* _ratioParameter;
};

class MyPolygonShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT
    
public:
    MyPolygonShapeMenu(Polygon* polygon, QWidget* parent = nullptr);
};

class MyStrokeMenu : public MyGroupBox {
    Q_OBJECT

public:
    MyStrokeMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent = nullptr);

    signals:
            void isUpdated();

protected:
    MyParameterBase* _widthParameter;
    MyParameterBase* _colorParameter;
    MyParameterBase* _dashArrayParameter;
};

class MyAddRemoveGeometricShapesButtons : public QDialogButtonBox {
    Q_OBJECT

public:
    MyAddRemoveGeometricShapesButtons(QWidget* parent = nullptr);

    void setAddingMenu();

signals:
    void shapeIsChosen(const QString&);

protected:
    QPushButton* _addPushButton;
    QPushButton* _removePushButton;
    QMenu* _addingMenu;
    QMenu* _removingMenu;
};

#endif
