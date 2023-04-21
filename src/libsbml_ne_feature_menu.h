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
    MyBoundingBoxMenu(BoundingBox* boundingBox, QWidget* parent = nullptr);
    
signals:
    void isUpdated();
    
protected:
    MyParameterBase* _xParameter;
    MyParameterBase* _yParameter;
    MyParameterBase* _widthParameter;
    MyParameterBase* _heightParameter;
};

class MyCurveMenu : public MyGroupBox {
    Q_OBJECT

public:
    MyCurveMenu(GraphicalObject* graphicalObject, QWidget* parent = nullptr);

    void setCurveSegmentsMenuTree(GraphicalObject* graphicalObject);

    QWidget* createCurveSegmentsMenu(GraphicalObject* graphicalObject);

signals:

    void isUpdated();

protected:
    QDialogButtonBox* _addRemoveCurveSegmentsButtons;
    QWidget* _curveSegmentsMenuTree;
};

class MyGeometricShapesMenu : public MyGroupBox {
    Q_OBJECT
    
public:
    MyGeometricShapesMenu(RenderGroup* renderGroup, QWidget* parent = nullptr);

    void setGeometricShapesMenuTree(RenderGroup* renderGroup);
    
    QWidget* createGeometricShapesMenu(RenderGroup* renderGroup);
    
signals:
    void isUpdated();

protected:
    QDialogButtonBox* _addRemoveGeometricShapesButtons;
    QWidget* _geometricShapesMenuTree;
};

class MyGeometricShapeMenuItemBase : public MyGroupBox {
    Q_OBJECT

public:
    MyGeometricShapeMenuItemBase(QWidget* parent = nullptr);

signals:
    void isUpdated();
};

class My1DGeometricShapeMenu : public MyGeometricShapeMenuItemBase {
    Q_OBJECT
    
public:
    My1DGeometricShapeMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent = nullptr);
    
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

class MyImageShapeMenu : public MyGeometricShapeMenuItemBase {
    Q_OBJECT

public:
    MyImageShapeMenu(Image* image, QWidget* parent = nullptr);

protected:
    MyParameterBase* _hrefParameter;
    MyParameterBase* _xAbsParameter;
    MyParameterBase* _xRelParameter;
    MyParameterBase* _yAbsParameter;
    MyParameterBase* _yRelParameter;
    MyParameterBase* _widthAbsParameter;
    MyParameterBase* _widthRelParameter;
    MyParameterBase* _heightAbsParameter;
    MyParameterBase* _heightRelParameter;
};

class MyRenderCurveShapeMenu : public My1DGeometricShapeMenu {
    Q_OBJECT

public:
    MyRenderCurveShapeMenu(RenderCurve* renderCurve, QWidget* parent = nullptr);

    void setElementsMenuTree(RenderCurve* renderCurve);

    QWidget* createElementsMenuTree(RenderCurve* renderCurve);

protected:
    QDialogButtonBox* _addRemoveRenderCurveElementButtons;
    QWidget* _elementsMenuTree;
};

class MyPolygonShapeMenu : public My2DGeometricShapeMenu {
    Q_OBJECT

public:
    MyPolygonShapeMenu(Polygon* polygon, QWidget* parent = nullptr);

    void setElementsMenuTree(Polygon* polygon);

    QWidget* createElementsMenuTree(Polygon* polygon);

protected:
    QDialogButtonBox* _addRemovePolygonElementButtons;
    QWidget* _elementsMenuTree;
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

class MyElementTextsMenu : public MyGroupBox {
Q_OBJECT

public:
    MyElementTextsMenu(QList<QWidget*> textsMenu, QWidget* parent = nullptr);

    void setElementTextsMenuTree(QList<QWidget*> textsMenu);

    QWidget* createElementTextsMenu(QList<QWidget*> textsMenu);

signals:
    void isUpdated();

protected:
    QWidget* _elementTextsMenuTree;
};

class MyPlainTextMenu : public MyGroupBox {
    Q_OBJECT

public:
    MyPlainTextMenu(TextGlyph* textGlyph, QWidget* parent = nullptr);

    MyPlainTextMenu(GraphicalObject* graphicalObject, QWidget* parent = nullptr);

    MyPlainTextMenu(SBase* modelEntity, QWidget* parent = nullptr);

    void setMenu();

signals:
    void isUpdated();

protected:
    MyParameterBase* _plainTextParameter;
};

class MyTextFeatureMenu : public MyGroupBox {
Q_OBJECT

public:
    MyTextFeatureMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent = nullptr);

signals:
    void isUpdated();

protected:

    MyParameterBase* _fontColorParameter;
    MyParameterBase* _fontFamilyParameter;
    MyParameterBase* _fontSizeAbsParameter;
    MyParameterBase* _fontSizeRelParameter;
    MyParameterBase* _fontWeightParameter;
    MyParameterBase* _fontStyleParameter;
    MyParameterBase* _textAnchorParameter;
    MyParameterBase* _textVAnchorParameter;
};

class MyLineEndingMenu : public MyGroupBox {
    Q_OBJECT

public:
    MyLineEndingMenu(LineEnding* lineEnding, QWidget* parent = nullptr);

signals:
        void isUpdated();

protected:
    QWidget* _lineEndingMenuTree;
    MyParameterBase* _enableRotationalMappingParameter;
};

class MyAddRemoveButtonsBase : public QDialogButtonBox {
Q_OBJECT

public:
    MyAddRemoveButtonsBase(QWidget* parent = nullptr);

    void setMenus() ;

    virtual void setAddingMenu() = 0;

private slots:

    virtual void setRemovingMenu() = 0;

signals:

    void isUpdated();

protected:
    QPushButton* _addPushButton;
    QPushButton* _removePushButton;
    QMenu* _addingMenu;
    QMenu* _removingMenu;
};

class MyAddRemoveCurveSegmentsButtons : public MyAddRemoveButtonsBase {
    Q_OBJECT

public:
    MyAddRemoveCurveSegmentsButtons(GraphicalObject* graphicalObject, QWidget* parent = nullptr);

    void setAddingMenu() override;

    void addLineSegment();

    void addCubicBezier();

    void removeSegment(const qint32 index);

    const bool hasEnoughCurveSegmentsLeft();

    unsigned int numberOfCurveSegments();

private slots:

    void setRemovingMenu() override;

protected:
    GraphicalObject* _graphicalObject;
};

class MyAddRemoveGeometricShapesButtons : public MyAddRemoveButtonsBase {
Q_OBJECT

public:
    MyAddRemoveGeometricShapesButtons(RenderGroup* renderGroup, QWidget* parent = nullptr);

    void setAddingMenu() override;

    void addShape(const QString& shape);

    void removeShape(const qint32 index);

private slots:

    void setRemovingMenu() override;

protected:
    RenderGroup* _renderGroup;
};

class MyAddRemoveShapeElementButtonsBase : public MyAddRemoveButtonsBase {
Q_OBJECT

public:
    MyAddRemoveShapeElementButtonsBase(Transformation2D* shape, QWidget* parent = nullptr);

    void setAddingMenu() override;

    void addRenderPoint();

    void removeElement(const qint32 index);

    virtual const bool hasEnoughElementsLeft() = 0;

    virtual unsigned int numberOfShapeElements() = 0;

private slots:

    void setRemovingMenu() override;

protected:
    Transformation2D* _shape;
};

class MyAddRemovePolygonElementButtons : public MyAddRemoveShapeElementButtonsBase {
Q_OBJECT

public:
    MyAddRemovePolygonElementButtons(Polygon* polygon, QWidget* parent = nullptr);

    const bool hasEnoughElementsLeft() override;

    unsigned int numberOfShapeElements() override;
};

class MyAddRemoveRenderCurveElementButtons : public MyAddRemoveShapeElementButtonsBase {
Q_OBJECT

public:
    MyAddRemoveRenderCurveElementButtons(RenderCurve* renderCurve, QWidget* parent = nullptr);

    void setAddingMenu() override;

    void addRenderCubicBezier();

    const bool hasEnoughElementsLeft() override;

    unsigned int numberOfShapeElements() override;
};

#endif
