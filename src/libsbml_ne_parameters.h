#ifndef __LIBSBML_NE_PARAMETERS_H
#define __LIBSBML_NE_PARAMETERS_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include <QStandardItem>
#include <QTreeView>

class MySpacerItem : public QSpacerItem {
    
public:
    
    MySpacerItem(int w, int h);
};

class MyLabel : public QLabel {
    
public:
    
    MyLabel(const QString& text = "", QWidget* parent = nullptr);
};

class MyTitleLabel : public MyLabel {
    
public:
    
    MyTitleLabel(const QString& text = "", QWidget* parent = nullptr);
};

class MyLineEdit : public QLineEdit {
    
public:
    
    MyLineEdit(const QString &contents = "", QWidget* parent = nullptr);
    
    void setText(const QString &contents);
};

class MyReadOnlyLineEdit : public MyLineEdit {
    
public:
    
    MyReadOnlyLineEdit(const QString &contents = "", QWidget* parent = nullptr);
};

class MySpinBox : public QSpinBox {
    
public:
    
    MySpinBox(QWidget* parent = nullptr);
};

class MyDoubleSpinBox : public QDoubleSpinBox {
    
public:
    
    MyDoubleSpinBox(QWidget* parent = nullptr);
};

class MyComboBox : public QComboBox {
    
public:
    
    MyComboBox(QWidget* parent = nullptr);
};

class MyGroupBox : public QGroupBox {
    
public:
    
    MyGroupBox(QWidget* parent = nullptr);
};

class MyStandardItem : public QStandardItem {
    
public:
    MyStandardItem(const QString& text = "", const qreal& fontsize = qreal(12.0), const bool& isbold = false, const QColor& color = QColor(Qt::black));
};

class MyDashArrayItemsBox : public MyComboBox {
    Q_OBJECT
    
public:
    MyDashArrayItemsBox(QWidget* parent = nullptr);
    
    const QList<unsigned int> currentDashArray();
    
    void setCurrentDashArray(const QList<unsigned int>& dashArray);
    
    const QList<unsigned int> getDashArray(const unsigned int& index);
    
    void reset();
    
signals:
    void dashArrayChosen(const QList<unsigned int>& dashArray);
    
protected:
    QList<unsigned int> _currentDashArray;
};

class MyColorPickerButton : public QToolButton {
    Q_OBJECT
        
public:
    MyColorPickerButton(QWidget *parent = nullptr);
    
    const QString& currentColor() const;
    
    void setBackgroundColor(const QString& color);
    
public slots:
    
    void setCurrentColor(const QString& color);
    
protected:
    QMenu* _colorPickerMenu;
    QString _currentColor;
};

class MyColorPickerMenu : public QMenu {
    Q_OBJECT
    
public:
    MyColorPickerMenu();
    
signals:
    void colorChosen(const QString&);
        
private slots:
    void colorTileButtonPicked(QPushButton* colorTileButton);
};

class MyColorTileButton : public QPushButton {
        
public:
    MyColorTileButton(const QString& color, const QString& value, QWidget* parent = 0);
    
    const QString& color() const;
    
    const QString& value() const;
    
protected:
    QString _color;
    QString _value;
};

class MyTreeView : public QTreeView {
    
public:
    MyTreeView(QWidget* parent);
    
    void clearModel();
    
    /// Containers
    // branches
    typedef std::vector<std::pair<MyStandardItem*, MyStandardItem*>> branchVec;
    
    /// Iterators
    // branches
    typedef branchVec::iterator branchIt;
    typedef branchVec::const_iterator constBranchIt;
    
    /// Functions related to beginning and end of containers
    // branches
    const constBranchIt BranchesBegin() const { return _branches.begin(); }
    const constBranchIt BranchesEnd() const { return _branches.end(); }
    
    void addBranchWidget(QWidget* branchWidget = NULL, const QString& branchTitle = "", const QString& rootTitle= "");
    
    void removeBranches(const QString& rootTitle= "", const unsigned int& staticbranches = 0);
    
protected:
    QStandardItemModel* treeModel;
    branchVec _branches;
};

class MyParameterBase : public QObject {
    Q_OBJECT
    
public:
    
    MyParameterBase(const QString& name);
    
    MyParameterBase(const QString& name, GraphicalObject* graphicalObject);
    
    MyParameterBase(const QString& name, Transformation2D* styleFeatures);
    
    typedef enum {
        DOUBLE_PARAMETER_TYPE,
        INTEGER_PARAMETER_TYPE,
        BOOLEAN_PARAMETER_TYPE,
        STRING_PARAMETER_TYPE,
        NOMINAL_PARAMETER_TYPE,
        DASH_ARRAY_PARAMETER_TYPE,
        COLOR_PARAMETER_TYPE,
        REL_ABS_PARAMETER_TYPE,
    } PARAMETER_TYPE;
    
    virtual ~MyParameterBase() {
        delete _inputWidget;
    };
    
    const QString& name();
    
    void setGraphicalObject(GraphicalObject* graphicalObject);
    
    GraphicalObject* graphicalObject();
    
    void setStyleFeatures(Transformation2D* styleFeatures);
    
    Transformation2D* styleFeatures();
    
    // get type of parameter
    virtual PARAMETER_TYPE type() = 0;
    
    // set the dafault value using the input widget value
    virtual void setDefaultValue() = 0;
    
    // get the user input widget
    virtual QWidget* inputWidget() = 0;
    
    // reset the values of the parameter
    virtual void reset() = 0;
    
    // read the parameter info from the graphical object and style
    virtual void read() = 0;
    
signals:
    void isUpdated();
    
public slots:
    // set the value of parameter info to the graphical object and style
    virtual void write() = 0;
    
protected:
    QString _name;
    QWidget* _inputWidget;
    GraphicalObject* _graphicalObject;
    Transformation2D* _styleFeatures;
};

class MyDoubleParameter : public MyParameterBase {
public:
    
    MyDoubleParameter(const QString& name);
    
    MyDoubleParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyDoubleParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const qreal& value);
    
    // get default value
    const qreal& defaultValue() const;
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // set min
    void setMin(const qreal& min);
    
    // get min
    const qreal& min() const;
    
    // show whether the min is set
    const bool isSetMin() const { return _isSetMin; }
    
    // set max
    void setMax(const qreal& max);
    
    // get max
    const qreal& max() const;
    
    // show whether the max is set
    const bool isSetMax() const { return _isSetMax; }
    
    // set step
    void setStep(const qreal& step);
    
    // get step
    const qreal& step() const;
    
    // show whether the step is set
    const bool isSetStep() const { return _isSetStep; }
    
    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;

protected:
    qreal _defaultValue;
    qreal _min;
    qreal _max;
    qreal _step;
    bool _isSetDefaultValue;
    bool _isSetMin;
    bool _isSetMax;
    bool _isSetStep;
};

class MyIntegerParameter : public MyParameterBase {
public:
    
    MyIntegerParameter(const QString& name);
    
    MyIntegerParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyIntegerParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const qint32& value);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const qint32& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // set min
    void setMin(const qint32& min);
    
    // get min
    const qint32& min() const;
    
    // show whether the min is set
    const bool isSetMin() const { return _isSetMin; }
    
    // set max
    void setMax(const qint32& max);
    
    // get max
    const qint32& max() const;
    
    // show whether the max is set
    const bool isSetMax() const { return _isSetMax; }
    
    // set step
    void setStep(const qint32& step);
    
    // get step
    const qint32& step() const;
    
    // show whether the step is set
    const bool isSetStep() const { return _isSetStep; }
    
    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;

protected:
    qint32 _defaultValue;
    qint32 _min;
    qint32 _max;
    qint32 _step;
    bool _isSetDefaultValue;
    bool _isSetMin;
    bool _isSetMax;
    bool _isSetStep;
};

class MyBooleanParameter : public MyParameterBase {
public:
    
    MyBooleanParameter(const QString& name);
    
    MyBooleanParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyBooleanParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const bool& value);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const bool& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;

protected:
    bool _defaultValue;
    bool _isSetDefaultValue;
};

class MyStringParameter : public MyParameterBase {
public:
    
    MyStringParameter(const QString& name);
    
    MyStringParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyStringParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const QString& value);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const QString& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;

protected:
    QString _defaultValue;
    bool _isSetDefaultValue;
};

class MyNominalParameter : public MyParameterBase {
public:
    
    MyNominalParameter(const QString& name);
    
    MyNominalParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyNominalParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const QString& value);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const QString& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // get the user input widget
    QWidget* inputWidget() override;
    
    // get the items of the nominal parameter
    const QStringList& items() const;
    
    // reset the values of the parameter
    void reset() override;

protected:
    QString _defaultValue;
    QStringList _items;
    bool _isSetDefaultValue;
};

class MyPositionalParameter : public MyDoubleParameter {
public:
    
    MyPositionalParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyPositionalParameter(const QString& name, Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
};

class MyDimensionalParameter : public MyDoubleParameter {
public:
    
    MyDimensionalParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyDimensionalParameter(const QString& name, Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
};

class MyRelativePositionalParameter : public MyPositionalParameter {
public:
    
    MyRelativePositionalParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyRelativePositionalParameter(const QString& name, Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
};

class MyRelativeDimensionalParameter : public MyDimensionalParameter {
public:
    
    MyRelativeDimensionalParameter(const QString& name, GraphicalObject* graphicalObject);
    
    MyRelativeDimensionalParameter(const QString& name, Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
};

class MyDashArrayParameter : public MyParameterBase {
    Q_OBJECT
    
public:
    MyDashArrayParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const QList<unsigned int>& dashArray);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const QList<unsigned int>& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;
    
protected:
    QList<unsigned int> _defaultValue;
    bool _isSetDefaultValue;
};

class MyColorParameter : public MyParameterBase {
public:
    
    MyColorParameter(const QString& name, Transformation2D* styleFeatures);
    
    // get type of parameter
    PARAMETER_TYPE type() override;
    
    // set default value
    void setDefaultValue(const QString& value);
    
    // set the dafault value using the input widget value
    void setDefaultValue() override;
    
    // get default value
    const QString& defaultValue() const;
    
    // show whether the default value is set
    const bool isSetDefaultValue() const { return _isSetDefaultValue; }

    // get the user input widget
    QWidget* inputWidget() override;
    
    // reset the values of the parameter
    void reset() override;

protected:
    QString _defaultValue;
    bool _isSetDefaultValue;
};

class MyBoundingBoxXParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyBoundingBoxXParameter(GraphicalObject* graphicalObject);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyBoundingBoxYParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyBoundingBoxYParameter(GraphicalObject* graphicalObject);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyBoundingBoxWidthParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyBoundingBoxWidthParameter(GraphicalObject* graphicalObject);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyBoundingBoxHeightParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyBoundingBoxHeightParameter(GraphicalObject* graphicalObject);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyStrokeWidthParameter : public MyDoubleParameter {
    Q_OBJECT
    
public:
    
    MyStrokeWidthParameter(Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyStrokeColorParameter : public MyColorParameter {
    Q_OBJECT
    
public:
    
    MyStrokeColorParameter(Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyStrokeDashArrayParameter : public MyDashArrayParameter {
    Q_OBJECT
    
public:
    
    MyStrokeDashArrayParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyFillParameter : public MyColorParameter {
    Q_OBJECT
    
public:
    
    MyFillParameter(Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyFontFamilyParameter : public MyStringParameter {
    Q_OBJECT
    
public:
    
    MyFontFamilyParameter(Transformation2D* styleFeatures);
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyFontSizeParameter : public MyNominalParameter {
    Q_OBJECT
    
public:
    
    MyFontSizeParameter(Transformation2D* styleFeatures);
    
    // get the value of default size
    const qint32 defaultSize() const;
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyFontWeightParameter : public MyNominalParameter {
    Q_OBJECT
    
public:
    
    MyFontWeightParameter(Transformation2D* styleFeatures);
    
    // get the value of default weight
    const bool defaultWeight() const;
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyFontStyleParameter : public MyNominalParameter {
    Q_OBJECT
    
public:
    
    MyFontStyleParameter(Transformation2D* styleFeatures);
    
    // get the value of default style
    const bool defaultStyle() const;
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyTextAnchorParameter : public MyNominalParameter {
    Q_OBJECT
    
public:
    
    MyTextAnchorParameter(Transformation2D* styleFeatures);
    
    // get the value of default alignment
    const Qt::Alignment defaultAlignment() const;
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyVTextAnchorParameter : public MyNominalParameter {
    Q_OBJECT
    
public:
    
    MyVTextAnchorParameter(Transformation2D* styleFeatures);
    
    // get the value of default alignment
    const Qt::Alignment defaultAlignment() const;
    
    // reset the values of the parameter
    void reset() override;
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeXAbsoluteParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeXAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeXRelativeParameter : public MyRelativePositionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeXRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeYAbsoluteParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeYAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeYRelativeParameter : public MyRelativePositionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeYRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeWidthAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeWidthAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeWidthRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeWidthRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeHeightAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeHeightAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeHeightRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeHeightRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeRatioParameter : public MyDoubleParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeRatioParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
    void reset() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeRXAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeRXAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeRXRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeRXRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeRYAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeRYAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyRectangleShapeRYRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyRectangleShapeRYRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeCXAbsoluteParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeCXAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeCXRelativeParameter : public MyRelativePositionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeCXRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeCYAbsoluteParameter : public MyPositionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeCYAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeCYRelativeParameter : public MyRelativePositionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeCYRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeRXAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeRXAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeRXRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeRXRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeRYAbsoluteParameter : public MyDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeRYAbsoluteParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeRYRelativeParameter : public MyRelativeDimensionalParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeRYRelativeParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};

class MyEllipseShapeRatioParameter : public MyDoubleParameter {
    Q_OBJECT
    
public:
    
    MyEllipseShapeRatioParameter(Transformation2D* styleFeatures);
    
    // read the parameter info from the graphical object and style
    void read() override;
    
    void reset() override;
    
protected slots:
    
    // set the value of parameter info to the graphical object and style
    void write() override;
};
#endif
