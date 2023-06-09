#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

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

MyBoundingBoxMenu::MyBoundingBoxMenu(BoundingBox* boundingBox, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);

    // x
    _xParameter = new MyBoundingBoxXParameter(boundingBox);
    _xParameter->read();
    connect(_xParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // y
    _yParameter = new MyBoundingBoxYParameter(boundingBox);
    _yParameter->read();
    connect(_yParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // width
    _widthParameter = new MyBoundingBoxWidthParameter(boundingBox);
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    // height
    _heightParameter = new MyBoundingBoxHeightParameter(boundingBox);
    _heightParameter->read();
    connect(_heightParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
    
    setLayout(contentLayout);
}

// MyCurveMenu

MyCurveMenu::MyCurveMenu(GraphicalObject* graphicalObject, QWidget* parent) : MyGroupBox(parent) {
    _curveSegmentsMenuTree = NULL;
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    _addRemoveCurveSegmentsButtons = new MyAddRemoveCurveSegmentsButtons(graphicalObject, this);
    ((MyAddRemoveCurveSegmentsButtons*)_addRemoveCurveSegmentsButtons)->setMenus();
    connect(_addRemoveCurveSegmentsButtons, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect((MyAddRemoveCurveSegmentsButtons*)_addRemoveCurveSegmentsButtons, &MyAddRemoveCurveSegmentsButtons::isUpdated, this, [this, graphicalObject] () { setCurveSegmentsMenuTree(graphicalObject); });
    contentLayout->addWidget(_addRemoveCurveSegmentsButtons, contentLayout->rowCount(), 1);
    setCurveSegmentsMenuTree(graphicalObject);
    setLayout(contentLayout);
}

void MyCurveMenu::setCurveSegmentsMenuTree(GraphicalObject* graphicalObject) {
    QGridLayout* contentLayout = (QGridLayout*)layout();
    if (_curveSegmentsMenuTree != NULL) {
        contentLayout->removeWidget(_curveSegmentsMenuTree);
        _curveSegmentsMenuTree->deleteLater();
    }
    _curveSegmentsMenuTree = createCurveSegmentsMenu(graphicalObject);
    contentLayout->addWidget(_curveSegmentsMenuTree, contentLayout->rowCount(), 0);
}

QWidget* MyCurveMenu::createCurveSegmentsMenu(GraphicalObject* graphicalObject) {
    MyTreeView* curveSegmentsMenuTree = new MyTreeView(this);
    MyParameterBase* _curveStartPointXParameter = NULL;
    MyParameterBase* _curveStartPointYParameter = NULL;
    MyParameterBase* _curveEndPointXParameter = NULL;
    MyParameterBase* _curveEndPointYParameter = NULL;
    MyParameterBase* _curveBasePoint1XParameter = NULL;
    MyParameterBase* _curveBasePoint1YParameter = NULL;
    MyParameterBase* _curveBasePoint2XParameter = NULL;
    MyParameterBase* _curveBasePoint2YParameter = NULL;
    QWidget* curveSegmentMenu = NULL;
    QGridLayout* curveSegmentMenuLayout = NULL;
    for (unsigned int i = 0; i < getNumCurveSegments(graphicalObject); i++) {
        curveSegmentMenu = new QWidget(curveSegmentsMenuTree);
        curveSegmentMenuLayout = new QGridLayout(curveSegmentMenu);
        /// start
        // x
        _curveStartPointXParameter = new MyCurveStartPointXParameter(graphicalObject, i);
        _curveStartPointXParameter->read();
        connect(_curveStartPointXParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        curveSegmentMenuLayout->addWidget(new MyLabel(_curveStartPointXParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
        curveSegmentMenuLayout->addWidget(_curveStartPointXParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

        // y
        _curveStartPointYParameter = new MyCurveStartPointYParameter(graphicalObject, i);
        _curveStartPointYParameter->read();
        connect(_curveStartPointYParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        curveSegmentMenuLayout->addWidget(new MyLabel(_curveStartPointYParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
        curveSegmentMenuLayout->addWidget(_curveStartPointYParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

        /// end
        // x
        _curveEndPointXParameter = new MyCurveEndPointXParameter(graphicalObject, i);
        _curveEndPointXParameter->read();
        connect(_curveEndPointXParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        curveSegmentMenuLayout->addWidget(new MyLabel(_curveEndPointXParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
        curveSegmentMenuLayout->addWidget(_curveEndPointXParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

        // y
        _curveEndPointYParameter = new MyCurveEndPointYParameter(graphicalObject, i);
        _curveEndPointYParameter->read();
        connect(_curveEndPointYParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        curveSegmentMenuLayout->addWidget(new MyLabel(_curveEndPointYParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
        curveSegmentMenuLayout->addWidget(_curveEndPointYParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

        if (isCubicBezier(getCurveSegment(graphicalObject, i))) {
            // base point 1 x
            _curveBasePoint1XParameter = new MyCurveBasePoint1XParameter(graphicalObject, i);
            _curveBasePoint1XParameter->read();
            connect(_curveBasePoint1XParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            curveSegmentMenuLayout->addWidget(new MyLabel(_curveBasePoint1XParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
            curveSegmentMenuLayout->addWidget(_curveBasePoint1XParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

            // base point 1 y
            _curveBasePoint1YParameter = new MyCurveBasePoint1YParameter(graphicalObject, i);
            _curveBasePoint1YParameter->read();
            connect(_curveBasePoint1YParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            curveSegmentMenuLayout->addWidget(new MyLabel(_curveBasePoint1YParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
            curveSegmentMenuLayout->addWidget(_curveBasePoint1YParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

            // base point 2 x
            _curveBasePoint2XParameter = new MyCurveBasePoint2XParameter(graphicalObject, i);
            _curveBasePoint2XParameter->read();
            connect(_curveBasePoint2XParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            curveSegmentMenuLayout->addWidget(new MyLabel(_curveBasePoint2XParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
            curveSegmentMenuLayout->addWidget(_curveBasePoint2XParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);

            // base point 2 y
            _curveBasePoint2YParameter = new MyCurveBasePoint2YParameter(graphicalObject, i);
            _curveBasePoint2YParameter->read();
            connect(_curveBasePoint2YParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            curveSegmentMenuLayout->addWidget(new MyLabel(_curveBasePoint2YParameter->name()), curveSegmentMenuLayout->rowCount(), 0);
            curveSegmentMenuLayout->addWidget(_curveBasePoint2YParameter->inputWidget(), curveSegmentMenuLayout->rowCount() - 1, 1);
        }

        curveSegmentMenu->setLayout(curveSegmentMenuLayout);
        curveSegmentsMenuTree->addBranchWidget(curveSegmentMenu, "Segment " + QString::number(i + 1));
    }

    return curveSegmentsMenuTree;
}

// MyGeometricShapesMenu

MyGeometricShapesMenu::MyGeometricShapesMenu(RenderGroup* renderGroup, QWidget* parent) : MyGroupBox(parent) {
    _geometricShapesMenuTree = NULL;
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    _addRemoveGeometricShapesButtons = new MyAddRemoveGeometricShapesButtons(renderGroup, this);
    ((MyAddRemoveGeometricShapesButtons*)_addRemoveGeometricShapesButtons)->setMenus();
    connect(_addRemoveGeometricShapesButtons, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    connect((MyAddRemoveGeometricShapesButtons*)_addRemoveGeometricShapesButtons, &MyAddRemoveGeometricShapesButtons::isUpdated, this, [this, renderGroup] () { setGeometricShapesMenuTree(renderGroup); });
    contentLayout->addWidget(_addRemoveGeometricShapesButtons, contentLayout->rowCount(), 1);
    setGeometricShapesMenuTree(renderGroup);
    setLayout(contentLayout);
}

void MyGeometricShapesMenu::setGeometricShapesMenuTree(RenderGroup* renderGroup) {
    QGridLayout* contentLayout = (QGridLayout*)layout();
    if (_geometricShapesMenuTree != NULL) {
        contentLayout->removeWidget(_geometricShapesMenuTree);
        _geometricShapesMenuTree->deleteLater();
    }
    _geometricShapesMenuTree = createGeometricShapesMenu(renderGroup);
    contentLayout->addWidget(_geometricShapesMenuTree, contentLayout->rowCount(), 0);
}

QWidget* MyGeometricShapesMenu::createGeometricShapesMenu(RenderGroup* renderGroup) {
    MyTreeView* geometricShapesMenuTree = new MyTreeView(this);
    for (unsigned int i = 0; i < getNumGeometricShapes(renderGroup); i++) {
        Transformation2D* shape = getGeometricShape(renderGroup, i);
        QWidget* geometricShapeMenu = NULL;
        if (isRectangle(shape)) {
            geometricShapeMenu = new MyRectangleShapeMenu((Rectangle*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, QString::number(i + 1) + ": Rectangle");
        }
        else if (isEllipse(shape)) {
            geometricShapeMenu = new MyEllipseShapeMenu((Ellipse*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, QString::number(i + 1) + ": Ellipse");
        }
        else if (isPolygon(shape)) {
            geometricShapeMenu = new MyPolygonShapeMenu((Polygon*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, QString::number(i + 1) + ": Polygon");
        }
        else if (isRenderCurve(shape)) {
            geometricShapeMenu = new MyRenderCurveShapeMenu((RenderCurve*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, QString::number(i + 1) + ": RenderCurve");
        }
        else if (isImage(shape)) {
            geometricShapeMenu = new MyImageShapeMenu((Image*)shape, this);
            geometricShapesMenuTree->addBranchWidget(geometricShapeMenu, QString::number(i + 1) + ": Image");
        }
        connect(geometricShapeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    }

    return geometricShapesMenuTree;
}

// MyGeometricShapeMenuItemBase

MyGeometricShapeMenuItemBase::MyGeometricShapeMenuItemBase(QWidget* parent) : MyGroupBox(parent) {
    setLayout(new QGridLayout(this));
}

// My1DGeometricShapeMenu

My1DGeometricShapeMenu::My1DGeometricShapeMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent) : MyGeometricShapeMenuItemBase(parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
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
}

// My2DGeometricShapeMenu

My2DGeometricShapeMenu::My2DGeometricShapeMenu(GraphicalPrimitive2D* graphicalPrimitive2D, QWidget* parent) : My1DGeometricShapeMenu(graphicalPrimitive2D, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    
    // fill
    _fillParameter = new MyFillParameter(graphicalPrimitive2D);
    _fillParameter->read();
    connect(_fillParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fillParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fillParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyImageShapeMenu

MyImageShapeMenu::MyImageShapeMenu(Image* image, QWidget* parent) : MyGeometricShapeMenuItemBase(parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    // href
    _hrefParameter = new MyImageShapeHrefParameter(image);
    _hrefParameter->read();
    connect(_hrefParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_hrefParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_hrefParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // x
    _xAbsParameter = new MyImageShapeXAbsoluteParameter(image);
    _xAbsParameter->read();
    connect(_xAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    _xRelParameter = new MyImageShapeXRelativeParameter(image);
    _xRelParameter->read();
    connect(_xRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_xRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_xRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // y
    _yAbsParameter = new MyImageShapeYAbsoluteParameter(image);
    _yAbsParameter->read();
    connect(_yAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    _yRelParameter = new MyImageShapeYRelativeParameter(image);
    _yRelParameter->read();
    connect(_yRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_yRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_yRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // width
    _widthAbsParameter = new MyImageShapeWidthAbsoluteParameter(image);
    _widthAbsParameter->read();
    connect(_widthAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    _widthRelParameter = new MyImageShapeWidthRelativeParameter(image);
    _widthRelParameter->read();
    connect(_widthRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // height
    _heightAbsParameter = new MyImageShapeHeightAbsoluteParameter(image);
    _heightAbsParameter->read();
    connect(_heightAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    _heightRelParameter = new MyImageShapeHeightRelativeParameter(image);
    _heightRelParameter->read();
    connect(_heightRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_heightRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_heightRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);
}

// MyRenderCurveShapeMenu

MyRenderCurveShapeMenu::MyRenderCurveShapeMenu(RenderCurve* renderCurve, QWidget* parent) : My1DGeometricShapeMenu(renderCurve, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    _elementsMenuTree = NULL;

    _addRemoveRenderCurveElementButtons = new MyAddRemoveRenderCurveElementButtons(renderCurve, this);
    ((MyAddRemoveRenderCurveElementButtons*)_addRemoveRenderCurveElementButtons)->setMenus();
    connect(_addRemoveRenderCurveElementButtons, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(_addRemoveRenderCurveElementButtons, contentLayout->rowCount(), 1);
    connect((MyAddRemoveRenderCurveElementButtons*)_addRemoveRenderCurveElementButtons, &MyAddRemoveRenderCurveElementButtons::isUpdated, this, [this, renderCurve] () { setElementsMenuTree(renderCurve); });
    setElementsMenuTree(renderCurve);
}

void MyRenderCurveShapeMenu::setElementsMenuTree(RenderCurve* renderCurve) {
    QGridLayout* contentLayout = (QGridLayout*)layout();
    if (_elementsMenuTree != NULL) {
        contentLayout->removeWidget(_elementsMenuTree);
        _elementsMenuTree->deleteLater();
    }
    _elementsMenuTree = createElementsMenuTree(renderCurve);
    contentLayout->addWidget(_elementsMenuTree, contentLayout->rowCount(), 0);
}

QWidget* MyRenderCurveShapeMenu::createElementsMenuTree(RenderCurve* renderCurve) {
    MyTreeView* elementsMenuTree = new MyTreeView(this);
    MyParameterBase* _vertexXAbsParameter = NULL;
    MyParameterBase* _vertexXRelParameter = NULL;
    MyParameterBase* _vertexYAbsParameter = NULL;
    MyParameterBase* _vertexYRelParameter = NULL;
    MyParameterBase* _vertexBasePoint1XAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint1XRelParameter = NULL;
    MyParameterBase* _vertexBasePoint1YAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint1YRelParameter = NULL;
    MyParameterBase* _vertexBasePoint2XAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint2XRelParameter = NULL;
    MyParameterBase* _vertexBasePoint2YAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint2YRelParameter = NULL;
    QWidget* elementMenu = NULL;
    QGridLayout* elementMenuLayout = NULL;
    for (unsigned int i = 0; i < renderCurve->getNumElements(); i++) {
        elementMenu = new QWidget(elementsMenuTree);
        elementMenuLayout = new QGridLayout(elementMenu);
        // x
        _vertexXAbsParameter = new MyRenderCurveShapePointXAbsoluteParameter(renderCurve, i);
        _vertexXAbsParameter->read();
        connect(_vertexXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexXAbsParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexXAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        _vertexXRelParameter = new MyRenderCurveShapePointXRelativeParameter(renderCurve, i);
        _vertexXRelParameter->read();
        connect(_vertexXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexXRelParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexXRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        // y
        _vertexYAbsParameter = new MyRenderCurveShapePointYAbsoluteParameter(renderCurve, i);
        _vertexYAbsParameter->read();
        connect(_vertexYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexYAbsParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexYAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        _vertexYRelParameter = new MyRenderCurveShapePointYRelativeParameter(renderCurve, i);
        _vertexYRelParameter->read();
        connect(_vertexYRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexYRelParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexYRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        if (isRenderCubicBezier(renderCurve, i)) {
            // base point 1 x
            _vertexBasePoint1XAbsParameter = new MyRenderCurveShapeBasePoint1XAbsoluteParameter(renderCurve, i);
            _vertexBasePoint1XAbsParameter->read();
            connect(_vertexBasePoint1XAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1XAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1XAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint1XRelParameter = new MyRenderCurveShapeBasePoint1XRelativeParameter(renderCurve, i);
            _vertexBasePoint1XRelParameter->read();
            connect(_vertexBasePoint1XRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1XRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1XRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 1 y
            _vertexBasePoint1YAbsParameter = new MyRenderCurveShapeBasePoint1YAbsoluteParameter(renderCurve, i);
            _vertexBasePoint1YAbsParameter->read();
            connect(_vertexBasePoint1YAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1YAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1YAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint1YRelParameter = new MyRenderCurveShapeBasePoint1YRelativeParameter(renderCurve, i);
            _vertexBasePoint1YRelParameter->read();
            connect(_vertexBasePoint1YRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1YRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1YRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 2 x
            _vertexBasePoint2XAbsParameter = new MyRenderCurveShapeBasePoint2XAbsoluteParameter(renderCurve, i);
            _vertexBasePoint2XAbsParameter->read();
            connect(_vertexBasePoint2XAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2XAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2XAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint2XRelParameter = new MyRenderCurveShapeBasePoint2XRelativeParameter(renderCurve, i);
            _vertexBasePoint2XRelParameter->read();
            connect(_vertexBasePoint2XRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2XRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2XRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 2 y
            _vertexBasePoint2YAbsParameter = new MyRenderCurveShapeBasePoint2YAbsoluteParameter(renderCurve, i);
            _vertexBasePoint2YAbsParameter->read();
            connect(_vertexBasePoint2YAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2YAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2YAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint2YRelParameter = new MyRenderCurveShapeBasePoint2YRelativeParameter(renderCurve, i);
            _vertexBasePoint2YRelParameter->read();
            connect(_vertexBasePoint2YRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2YRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2YRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);
        }

        elementMenu->setLayout(elementMenuLayout);
        elementsMenuTree->addBranchWidget(elementMenu, "Element " + QString::number(i + 1));
    }

    return elementsMenuTree;
}

// MyPolygonShapeMenu

MyPolygonShapeMenu::MyPolygonShapeMenu(Polygon* polygon, QWidget* parent) : My2DGeometricShapeMenu(polygon, parent) {
    QGridLayout* contentLayout = (QGridLayout*)(layout());
    _elementsMenuTree = NULL;

    _addRemovePolygonElementButtons = new MyAddRemovePolygonElementButtons(polygon, this);
    ((MyAddRemovePolygonElementButtons*)_addRemovePolygonElementButtons)->setMenus();
    connect(_addRemovePolygonElementButtons, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(_addRemovePolygonElementButtons, contentLayout->rowCount(), 1);
    connect((MyAddRemovePolygonElementButtons*)_addRemovePolygonElementButtons, &MyAddRemovePolygonElementButtons::isUpdated, this, [this, polygon] () { setElementsMenuTree(polygon); });
    setElementsMenuTree(polygon);
}

void MyPolygonShapeMenu::setElementsMenuTree(Polygon* polygon) {
    QGridLayout* contentLayout = (QGridLayout*)layout();
    if (_elementsMenuTree != NULL) {
        contentLayout->removeWidget(_elementsMenuTree);
        _elementsMenuTree->deleteLater();
    }
    _elementsMenuTree = createElementsMenuTree(polygon);
    contentLayout->addWidget(_elementsMenuTree, contentLayout->rowCount(), 0);
}

QWidget* MyPolygonShapeMenu::createElementsMenuTree(Polygon* polygon) {
    MyTreeView* elementsMenuTree = new MyTreeView(this);
    MyParameterBase* _vertexXAbsParameter = NULL;
    MyParameterBase* _vertexXRelParameter = NULL;
    MyParameterBase* _vertexYAbsParameter = NULL;
    MyParameterBase* _vertexYRelParameter = NULL;
    MyParameterBase* _vertexBasePoint1XAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint1XRelParameter = NULL;
    MyParameterBase* _vertexBasePoint1YAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint1YRelParameter = NULL;
    MyParameterBase* _vertexBasePoint2XAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint2XRelParameter = NULL;
    MyParameterBase* _vertexBasePoint2YAbsParameter = NULL;
    MyParameterBase* _vertexBasePoint2YRelParameter = NULL;
    QWidget* elementMenu = NULL;
    QGridLayout* elementMenuLayout = NULL;
    for (unsigned int i = 0; i < getGeometricShapeNumElements(polygon); i++) {
        elementMenu = new QWidget(elementsMenuTree);
        elementMenuLayout = new QGridLayout(elementMenu);
        // x
        _vertexXAbsParameter = new MyPolygonShapeVertexXAbsoluteParameter(polygon, i);
        _vertexXAbsParameter->read();
        connect(_vertexXAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexXAbsParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexXAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        _vertexXRelParameter = new MyPolygonShapeVertexXRelativeParameter(polygon, i);
        _vertexXRelParameter->read();
        connect(_vertexXRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexXRelParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexXRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        // y
        _vertexYAbsParameter = new MyPolygonShapeVertexYAbsoluteParameter(polygon, i);
        _vertexYAbsParameter->read();
        connect(_vertexYAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexYAbsParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexYAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        _vertexYRelParameter = new MyPolygonShapeVertexYRelativeParameter(polygon, i);
        _vertexYRelParameter->read();
        connect(_vertexYRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        elementMenuLayout->addWidget(new MyLabel(_vertexYRelParameter->name()), elementMenuLayout->rowCount(), 0);
        elementMenuLayout->addWidget(_vertexYRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

        if (isRenderCubicBezier(polygon, i)) {
            // base point 1 x
            _vertexBasePoint1XAbsParameter = new MyPolygonShapeBasePoint1XAbsoluteParameter(polygon, i);
            _vertexBasePoint1XAbsParameter->read();
            connect(_vertexBasePoint1XAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1XAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1XAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint1XRelParameter = new MyPolygonShapeBasePoint1XRelativeParameter(polygon, i);
            _vertexBasePoint1XRelParameter->read();
            connect(_vertexBasePoint1XRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1XRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1XRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 1 y
            _vertexBasePoint1YAbsParameter = new MyPolygonShapeBasePoint1YAbsoluteParameter(polygon, i);
            _vertexBasePoint1YAbsParameter->read();
            connect(_vertexBasePoint1YAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1YAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1YAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint1YRelParameter = new MyPolygonShapeBasePoint1YRelativeParameter(polygon, i);
            _vertexBasePoint1YRelParameter->read();
            connect(_vertexBasePoint1YRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint1YRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint1YRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 2 x
            _vertexBasePoint2XAbsParameter = new MyPolygonShapeBasePoint2XAbsoluteParameter(polygon, i);
            _vertexBasePoint2XAbsParameter->read();
            connect(_vertexBasePoint2XAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2XAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2XAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint2XRelParameter = new MyPolygonShapeBasePoint2XRelativeParameter(polygon, i);
            _vertexBasePoint2XRelParameter->read();
            connect(_vertexBasePoint2XRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2XRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2XRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            // base point 2 y
            _vertexBasePoint2YAbsParameter = new MyPolygonShapeBasePoint2YAbsoluteParameter(polygon, i);
            _vertexBasePoint2YAbsParameter->read();
            connect(_vertexBasePoint2YAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2YAbsParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2YAbsParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);

            _vertexBasePoint2YRelParameter = new MyPolygonShapeBasePoint2YRelativeParameter(polygon, i);
            _vertexBasePoint2YRelParameter->read();
            connect(_vertexBasePoint2YRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
            elementMenuLayout->addWidget(new MyLabel(_vertexBasePoint2YRelParameter->name()), elementMenuLayout->rowCount(), 0);
            elementMenuLayout->addWidget(_vertexBasePoint2YRelParameter->inputWidget(), elementMenuLayout->rowCount() - 1, 1);
        }

        elementMenu->setLayout(elementMenuLayout);
        elementsMenuTree->addBranchWidget(elementMenu, "Element " + QString::number(i + 1));
    }

    return elementsMenuTree;
}

// MyRectangleShapeMenu

MyRectangleShapeMenu::MyRectangleShapeMenu(Rectangle* rectangle, QWidget* parent) : My2DGeometricShapeMenu(rectangle, parent) {
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

MyEllipseShapeMenu::MyEllipseShapeMenu(Ellipse* ellipse, QWidget* parent) : My2DGeometricShapeMenu(ellipse, parent) {
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

// MyStrokeMenu

MyStrokeMenu::MyStrokeMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);

    // width
    _widthParameter = new MyStrokeWidthParameter(graphicalPrimitive1D);
    _widthParameter->read();
    connect(_widthParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_widthParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_widthParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // color
    _colorParameter = new MyStrokeColorParameter(graphicalPrimitive1D);
    _colorParameter->read();
    connect(_colorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_colorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_colorParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);

    // dasharray
    _dashArrayParameter = new MyStrokeDashArrayParameter(graphicalPrimitive1D);
    _dashArrayParameter->read();
    connect(_dashArrayParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_dashArrayParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_dashArrayParameter->inputWidget(), contentLayout->rowCount() - 1, 1, Qt::AlignLeft);

    setLayout(contentLayout);
}

// MyElementTextsMenu

MyElementTextsMenu::MyElementTextsMenu(QList<QWidget*> textsMenu, QWidget* parent) : MyGroupBox(parent) {
    _elementTextsMenuTree = NULL;
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);
    setElementTextsMenuTree(textsMenu);
    setLayout(contentLayout);
}

void MyElementTextsMenu::setElementTextsMenuTree(QList<QWidget*> textsMenu) {
    QGridLayout* contentLayout = (QGridLayout*)layout();
    if (_elementTextsMenuTree != NULL) {
        contentLayout->removeWidget(_elementTextsMenuTree);
        _elementTextsMenuTree->deleteLater();
    }
    _elementTextsMenuTree = createElementTextsMenu(textsMenu);
    contentLayout->addWidget(_elementTextsMenuTree, contentLayout->rowCount(), 0);
}

QWidget* MyElementTextsMenu::createElementTextsMenu(QList<QWidget*> textsMenu) {
    MyTreeView* elementTextsMenuTree = new MyTreeView(this);
    for (unsigned int i = 0; i < textsMenu.size(); i++)
        elementTextsMenuTree->addBranchWidget(textsMenu.at(i), ": Text " + QString::number(i + 1));
    return elementTextsMenuTree;
}

// MyPlainTextMenu

MyPlainTextMenu::MyPlainTextMenu(TextGlyph* textGlyph, QWidget* parent) : MyGroupBox(parent) {
    _plainTextParameter = new MyTextPlainTextFromTextGlyphParameter(textGlyph);
    setMenu();
}

MyPlainTextMenu::MyPlainTextMenu(GraphicalObject* graphicalObject, QWidget* parent) : MyGroupBox(parent) {
    _plainTextParameter = new MyTextPlainTextFromGraphicalObjectParameter(graphicalObject);
    setMenu();
}

MyPlainTextMenu::MyPlainTextMenu(SBase* modelEntity, QWidget* parent) : MyGroupBox(parent) {
    _plainTextParameter = new MyTextPlainTextFromModelEntityParameter(modelEntity);
    setMenu();
}

void MyPlainTextMenu::setMenu() {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);

    _plainTextParameter->read();
    connect(_plainTextParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_plainTextParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_plainTextParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    setLayout(contentLayout);
}

// MyTextFeatureMenu

MyTextFeatureMenu::MyTextFeatureMenu(GraphicalPrimitive1D* graphicalPrimitive1D, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    // font color
    _fontColorParameter = new MyTextFontColorParameter(graphicalPrimitive1D);
    _fontColorParameter->read();
    connect(_fontColorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontColorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontColorParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // font family
    _fontFamilyParameter = new MyTextFontFamilyParameter(graphicalPrimitive1D);
    _fontFamilyParameter->read();
    connect(_fontFamilyParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontFamilyParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontFamilyParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // font size
    _fontSizeAbsParameter = new MyTextFontSizeAbsoluteParameter(graphicalPrimitive1D);
    _fontSizeAbsParameter->read();
    connect(_fontSizeAbsParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontSizeAbsParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontSizeAbsParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    _fontSizeRelParameter = new MyTextFontSizeRelativeParameter(graphicalPrimitive1D);
    _fontSizeRelParameter->read();
    connect(_fontSizeRelParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontSizeRelParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontSizeRelParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // font weight
    _fontWeightParameter = new MyTextFontWeightParameter(graphicalPrimitive1D);
    _fontWeightParameter->read();
    connect(_fontWeightParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontWeightParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontWeightParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // font style
    _fontStyleParameter = new MyTextFontStyleParameter(graphicalPrimitive1D);
    _fontStyleParameter->read();
    connect(_fontStyleParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_fontStyleParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_fontStyleParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // text horizontal anchor
    _textAnchorParameter = new MyTextAnchorParameter(graphicalPrimitive1D);
    _textAnchorParameter->read();
    connect(_textAnchorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_textAnchorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_textAnchorParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    // text vertical anchor
    _textVAnchorParameter = new MyTextVAnchorParameter(graphicalPrimitive1D);
    _textVAnchorParameter->read();
    connect(_textVAnchorParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_textVAnchorParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_textVAnchorParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    setLayout(contentLayout);
}

// MyLineEndingMenu

MyLineEndingMenu::MyLineEndingMenu(LineEnding* lineEnding, QWidget* parent) : MyGroupBox(parent) {
    QGridLayout* contentLayout = new QGridLayout(this);
    contentLayout->setAlignment(Qt::AlignTop);

    _enableRotationalMappingParameter = new MyEnableRotationalMappingParameter(lineEnding);
    _enableRotationalMappingParameter->read();
    connect(_enableRotationalMappingParameter, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    contentLayout->addWidget(new MyLabel(_enableRotationalMappingParameter->name()), contentLayout->rowCount(), 0);
    contentLayout->addWidget(_enableRotationalMappingParameter->inputWidget(), contentLayout->rowCount() - 1, 1);

    MyTreeView* lineEndingMenuTree = new MyTreeView(this);
    // bounding box
    QWidget* boundingBoxMenu = new MyBoundingBoxMenu(lineEnding->getBoundingBox());
    connect(boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    lineEndingMenuTree->addBranchWidget(boundingBoxMenu, "BoundingBox");

    // geometric shapes
    QWidget* geometricShapeMenu = new MyGeometricShapesMenu(lineEnding->getGroup());
    connect(geometricShapeMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
    lineEndingMenuTree->addBranchWidget(geometricShapeMenu, "Geometric Shapes");
    contentLayout->addWidget(lineEndingMenuTree, contentLayout->rowCount(), 0);

    setLayout(contentLayout);
}

// MyAddRemoveButtonsBase

MyAddRemoveButtonsBase::MyAddRemoveButtonsBase(QWidget* parent) : QDialogButtonBox(parent) {
    setContentsMargins(0, 0, 0, 0);
    setOrientation(Qt::Horizontal);
    setFixedSize(150.0, 50.0);

    // add button
    _addPushButton = addButton(QString("+"), QDialogButtonBox::YesRole);
    _addingMenu = new QMenu(_addPushButton);
    _addPushButton->setMenu(_addingMenu);
    // remove button
    _removePushButton = addButton(QString("-"), QDialogButtonBox::NoRole);
    _removingMenu = new QMenu(_removePushButton);
    _removePushButton->setMenu(_removingMenu);
    connect(this, SIGNAL(isUpdated()), this, SLOT(setRemovingMenu()));
}

void MyAddRemoveButtonsBase::setMenus() {
    setAddingMenu();
    setRemovingMenu();
}

// MyAddRemoveCurveSegmentsButtons

MyAddRemoveCurveSegmentsButtons::MyAddRemoveCurveSegmentsButtons(GraphicalObject* graphicalObject, QWidget* parent) : MyAddRemoveButtonsBase(parent) {
    _graphicalObject = graphicalObject;
}

void MyAddRemoveCurveSegmentsButtons::setAddingMenu() {
    _addPushButton->setEnabled(true);
    connect(_addingMenu->addAction("Point"), &QAction::triggered, this, [this] () { addLineSegment(); });
    connect(_addingMenu->addAction("CubicBezier"), &QAction::triggered, this, [this] () { addCubicBezier(); });
}

void MyAddRemoveCurveSegmentsButtons::setRemovingMenu() {
    _removingMenu->clear();
    _removePushButton->setEnabled(false);
    if (hasEnoughCurveSegmentsLeft()) {
        _removePushButton->setEnabled(true);
        for (unsigned int i = 0; i < numberOfCurveSegments(); i++)
            connect(_removingMenu->addAction("Element " + QString::number(i + 1)), &QAction::triggered, this, [this, i] () { removeSegment(i); });
    }
}

void MyAddRemoveCurveSegmentsButtons::addLineSegment() {
    createLineCurveSegment(_graphicalObject);
    emit isUpdated();
}

void MyAddRemoveCurveSegmentsButtons::addCubicBezier() {
    createCubicBezierCurveSegment(_graphicalObject);
    emit isUpdated();
}

void MyAddRemoveCurveSegmentsButtons::removeSegment(const qint32 index) {
    removeCurveSegment(_graphicalObject, index);
    emit isUpdated();
}

const bool MyAddRemoveCurveSegmentsButtons::hasEnoughCurveSegmentsLeft() {
    if (getNumCurveSegments(_graphicalObject) > 1)
        return true;

    return false;
}

unsigned int MyAddRemoveCurveSegmentsButtons::numberOfCurveSegments() {
    return getNumCurveSegments(_graphicalObject);
}

// MyAddRemoveGeometricShapesButtons

MyAddRemoveGeometricShapesButtons::MyAddRemoveGeometricShapesButtons(RenderGroup* renderGroup, QWidget* parent) : MyAddRemoveButtonsBase(parent) {
    _renderGroup = renderGroup;
}

void MyAddRemoveGeometricShapesButtons::setAddingMenu() {
    _addPushButton->setEnabled(true);
    connect(_addingMenu->addAction("Rectangle"), &QAction::triggered, this, [this] () { addShape("Rectangle"); });
    connect(_addingMenu->addAction("Ellipse"), &QAction::triggered, this, [this] () { addShape("Ellipse"); });
    connect(_addingMenu->addAction("Image"), &QAction::triggered, this, [this] () { addShape("Image"); });
    QMenu* polygonsMenu = _addingMenu->addMenu("Polygons");
    connect(polygonsMenu->addAction("Triangle"), &QAction::triggered, this, [this] () { addShape("Triangle"); });
    connect(polygonsMenu->addAction("Diamond"), &QAction::triggered, this, [this] () { addShape("Diamond"); });
    connect(polygonsMenu->addAction("Pentagon"), &QAction::triggered, this, [this] () { addShape("Pentagon"); });
    connect(polygonsMenu->addAction("Hexagon"), &QAction::triggered, this, [this] () { addShape("Hexagon"); });
    connect(polygonsMenu->addAction("Octagon"), &QAction::triggered, this, [this] () { addShape("Octagon"); });
    connect(_addingMenu->addAction("RenderCurve"), &QAction::triggered, this, [this] () { addShape("RenderCurve"); });
}

void MyAddRemoveGeometricShapesButtons::setRemovingMenu() {
    _removingMenu->clear();
    _removePushButton->setEnabled(false);
    if (getNumGeometricShapes(_renderGroup) > 1) {
        _removePushButton->setEnabled(true);
        for (unsigned int i = 0; i < getNumGeometricShapes(_renderGroup); i++) {
            if (isImage(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "Image"), &QAction::triggered, this, [this, i] () { removeShape(i); });
            else if (isRenderCurve(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "RenderCurve"), &QAction::triggered, this, [this, i] () { removeShape(i); });
            else if (isText(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "Text"), &QAction::triggered, this, [this, i] () { removeShape(i); });
            else if (isRectangle(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "Rectangle"), &QAction::triggered, this, [this, i] () { removeShape(i); });
            else if (isEllipse(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "Ellipse"), &QAction::triggered, this, [this, i] () { removeShape(i); });
            else if (isPolygon(getGeometricShape(_renderGroup, i)))
                connect(_removingMenu->addAction(QString::number(i + 1) + ": " + "Polygon"), &QAction::triggered, this, [this, i] () { removeShape(i); });
        }
    }
}

void MyAddRemoveGeometricShapesButtons::addShape(const QString& shape) {
    addGeometricShape(_renderGroup, shape.toStdString());
    emit isUpdated();
}

void MyAddRemoveGeometricShapesButtons::removeShape(const qint32 index) {
    _renderGroup->removeElement(index);
    emit isUpdated();
}

// MyAddRemoveShapeElementButtonsBase

MyAddRemoveShapeElementButtonsBase::MyAddRemoveShapeElementButtonsBase(Transformation2D* shape, QWidget* parent) : MyAddRemoveButtonsBase(parent) {
    _shape = shape;
}

void MyAddRemoveShapeElementButtonsBase::setAddingMenu() {
    _addPushButton->setEnabled(true);
    connect(_addingMenu->addAction("RenderPoint"), &QAction::triggered, this, [this] () { addRenderPoint(); });
}

void MyAddRemoveShapeElementButtonsBase::setRemovingMenu() {
    _removingMenu->clear();
    _removePushButton->setEnabled(false);
    if (hasEnoughElementsLeft()) {
        _removePushButton->setEnabled(true);
        for (unsigned int i = 0; i < numberOfShapeElements(); i++)
            connect(_removingMenu->addAction("Element " + QString::number(i + 1)), &QAction::triggered, this, [this, i] () { removeElement(i); });
    }
}

void MyAddRemoveShapeElementButtonsBase::addRenderPoint() {
   addRenderPointToShape(_shape);
    emit isUpdated();
}

void MyAddRemoveShapeElementButtonsBase::removeElement(const qint32 index) {
    removeElementFromShape(_shape, index);
    emit isUpdated();
}

// MyAddRemovePolygonElementButtons

MyAddRemovePolygonElementButtons::MyAddRemovePolygonElementButtons(Polygon* polygon, QWidget* parent) : MyAddRemoveShapeElementButtonsBase(polygon, parent) {

}

const bool MyAddRemovePolygonElementButtons::hasEnoughElementsLeft() {
    if (getGeometricShapeNumElements((Polygon*)_shape) > 3)
        return true;

    return false;
}

unsigned int MyAddRemovePolygonElementButtons::numberOfShapeElements() {
    return getGeometricShapeNumElements((Polygon*)_shape);
}

// MyAddRemoveRenderCurveElementButtons

MyAddRemoveRenderCurveElementButtons::MyAddRemoveRenderCurveElementButtons(RenderCurve* renderCurve, QWidget* parent) : MyAddRemoveShapeElementButtonsBase(renderCurve, parent) {

}

void MyAddRemoveRenderCurveElementButtons::setAddingMenu() {
    MyAddRemoveShapeElementButtonsBase::setAddingMenu();
    connect(_addingMenu->addAction("RenderCubicBezier"), &QAction::triggered, this, [this] () { addRenderCubicBezier(); });
}

const bool MyAddRemoveRenderCurveElementButtons::hasEnoughElementsLeft() {
    if (getGeometricShapeNumElements((RenderCurve*)_shape) > 2)
        return true;

    return false;
}

unsigned int MyAddRemoveRenderCurveElementButtons::numberOfShapeElements() {
    return getGeometricShapeNumElements((RenderCurve*)_shape);
}

void MyAddRemoveRenderCurveElementButtons::addRenderCubicBezier() {
    addRenderCubicBezierToShape(_shape);
    emit isUpdated();
}