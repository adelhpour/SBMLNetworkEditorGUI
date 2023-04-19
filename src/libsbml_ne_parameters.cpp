#include "libsbml_ne_parameters.h"
#include <QWidgetAction>
#include <QtMath>
#include <QPainter>
#include <QGridLayout>
#include <QFileDialog>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

// MySpacerItem

MySpacerItem::MySpacerItem(int w, int h) : QSpacerItem(w, h, QSizePolicy::Fixed, QSizePolicy::Fixed) {
    
}

// MyLabel

MyLabel::MyLabel(const QString& text, QWidget* parent) : QLabel(parent) {
    setContentsMargins(0, 0, 0, 0);
    QFont _font;
    _font.setBold(true);
    _font.setCapitalization(QFont::Capitalize);
    _font.setPointSize(12);
    setFont(_font);
    
    if (!text.isEmpty())
        setText(text);
    
    setFixedHeight(20);
}

// MyTitleLabel

MyTitleLabel::MyTitleLabel(const QString& text, QWidget* parent) : MyLabel(text, parent) {
    QFont _font = font();
    _font.setPointSize(18);
    setFont(_font);
    setFixedSize(800, 25);
    setAlignment(Qt::AlignCenter);
}

// MyLineEdit

MyLineEdit::MyLineEdit(const QString &contents, QWidget* parent) : QLineEdit(parent) {
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QLineEdit {border: 1px solid LightSlateGray; border-radius: 10px; padding: 0 8px; background: GhostWhite; selection-background-color: LightGray;} QLineEdit::read-only {color: gray}");
    setText(contents);
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(120, 20);
}

void MyLineEdit::setText(const QString &contents) {
    QLineEdit::setText(contents);
    setToolTip(contents);
    setCursorPosition(0);
}

// MyReadOnlyLineEdit

MyReadOnlyLineEdit::MyReadOnlyLineEdit(const QString &contents, QWidget* parent) : MyLineEdit(contents, parent) {
    setReadOnly(true);
}

// MySpinBox

MySpinBox::MySpinBox(QWidget* parent) : QSpinBox(parent) {
    setContentsMargins(0, 0, 0, 0);
    setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    setStyleSheet("QSpinBox { border: 1px solid LightSlateGray; border-radius: 5px; background-color: GhostWhite; margin-right: 15px }" "QSpinBox::up-button { background-color: transparent; }" "QSpinBox::down-button { background-color: transparent;}" "QSpinBox::up-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-bottom: 5px solid black; width: 0px; height: 0px; }" "QSpinBox::down-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-top: 5px solid black; width: 0px; height: 0px; }");
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(120, 20);
}

// MyDoubleSpinBox

MyDoubleSpinBox::MyDoubleSpinBox(QWidget* parent) : QDoubleSpinBox(parent) {
    setContentsMargins(0, 0, 0, 0);
    setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    setStyleSheet("QDoubleSpinBox { border: 1px solid LightSlateGray; border-radius: 5px; background-color: GhostWhite; margin-right: 15px }" "QDoubleSpinBox::up-button { background-color: transparent; }" "QDoubleSpinBox::down-button { background-color: transparent;}" "QDoubleSpinBox::up-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-bottom: 5px solid black; width: 0px; height: 0px; }" "QDoubleSpinBox::down-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-top: 5px solid black; width: 0px; height: 0px; }");
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(120, 20);
}

// MyComboBox

MyComboBox::MyComboBox(QWidget* parent) : QComboBox(parent) {
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QComboBox { border: 1px solid LightSlateGray; border-radius: 5px; background-color: GhostWhite; color: black; padding: 1px 18px 1px 3px; }" "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 15px; border-left-width: 1px; border-left-color: LightSlateGray;border-left-style: solid; border-top-right-radius: 5px; border-bottom-right-radius: 5px; }" "QComboBox::down-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-top: 5px solid black; width: 0px; height: 0px; } QComboBox::disabled { color: gray;} QComboBox QAbstractItemView { border: 1px solid LightSlateGray; background-color: white; min-width: 100px; }");
    
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(120, 20);
}

// MyGroupBox

MyGroupBox::MyGroupBox(QWidget* parent) : QGroupBox(parent) {
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setStyleSheet("QGroupBox { background-color: white; border: no-border;}");
    setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
}

// MyStandardItem

MyStandardItem::MyStandardItem(const QString& text, const qreal& fontsize, const bool& isbold, const QColor& color) {
    QFont font;
    font.setPointSize(fontsize);
    font.setBold(isbold);
    setEditable(false);
    setSelectable(false);
    setForeground(color);
    setFont(font);
    setText(text);
}

// MyDashArrayItemsBox

MyDashArrayItemsBox::MyDashArrayItemsBox(QWidget* parent) : MyComboBox(parent) {
    setIconSize(QSize(100, 10));
    setStyleSheet("QComboBox { border: 1px solid LightSlateGray; border-radius: 5px; color: black; padding: 1px 18px 1px 3px; min-width: 6em; }" "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 15px; border-left-width: 1px; border-left-color: LightSlateGray;border-left-style: solid; border-top-right-radius: 5px; border-bottom-right-radius: 5px; }" "QComboBox::down-arrow { border-left: 4px solid none;" "border-right: 4px solid none; border-top: 5px solid black; width: 0px; height: 0px; } QComboBox::disabled { color: gray;} QComboBox QAbstractItemView { border: 1px solid LightSlateGray; background-color: white; }");
    
    // solid line
    QPixmap solidLinePixmap(QSize(100, 10));
    solidLinePixmap.fill(Qt::transparent);
    QPainter solidLinePaint(&solidLinePixmap);
    solidLinePaint.setPen(QPen(QBrush(Qt::black), 3, Qt::SolidLine));
    solidLinePaint.drawLine(5, 5, 88, 5);
    solidLinePaint.end();
    addItem(solidLinePixmap, "");
    
    // dash line
    QPixmap dashLinePixmap(QSize(100, 10));
    dashLinePixmap.fill(Qt::transparent);
    QPainter dashLinePaint(&dashLinePixmap);
    dashLinePaint.setPen(QPen(QBrush(Qt::black), 3, Qt::DashLine));
    dashLinePaint.drawLine(5, 5, 88, 5);
    dashLinePaint.end();
    addItem(dashLinePixmap, "");
    
    // dot line
    QPixmap dotLinePixmap(QSize(100, 10));
    dotLinePixmap.fill(Qt::transparent);
    QPainter dotLinePaint(&dotLinePixmap);
    dotLinePaint.setPen(QPen(QBrush(Qt::black), 3, Qt::DotLine));
    dotLinePaint.drawLine(5, 5, 88, 5);
    dotLinePaint.end();
    addItem(dotLinePixmap, "");
    
    // dash dot line
    QPixmap dashDotLinePixmap(QSize(100, 10));
    dashDotLinePixmap.fill(Qt::transparent);
    QPainter dashDotLinePaint(&dashDotLinePixmap);
    dashDotLinePaint.setPen(QPen(QBrush(Qt::black), 3, Qt::DashDotLine));
    dashDotLinePaint.drawLine(5, 5, 88, 5);
    dashDotLinePaint.end();
    addItem(dashDotLinePixmap, "");
    
    // dash dot dot line
    QPixmap dashDotDotLinePixmap(QSize(100, 10));
    dashDotDotLinePixmap.fill(Qt::transparent);
    QPainter dashDotDotLinePaint(&dashDotDotLinePixmap);
    dashDotDotLinePaint.setPen(QPen(QBrush(Qt::black), 3, Qt::DashDotDotLine));
    dashDotDotLinePaint.drawLine(5, 5, 88, 5);
    dashDotDotLinePaint.end();
    addItem(dashDotDotLinePixmap, "");
    
    connect(this, QOverload<int>::of(&QComboBox::activated), this, [this] (const int& index) { emit dashArrayChosen(this->getDashArray(index)); });
    
    setFixedSize(120, 20);
}

const QList<unsigned int> MyDashArrayItemsBox::currentDashArray() {
    return getDashArray(currentIndex());
}

void MyDashArrayItemsBox::setCurrentDashArray(const QList<unsigned int>& dashArray) {
    if (dashArray.size() == 2) {
        if (dashArray.at(1) == 2) {
            if (dashArray.at(0) == 5)
                setCurrentIndex(1);
            else if (dashArray.at(0) == 2)
                setCurrentIndex(2);
        }
    }
    else if (dashArray.size() == 4 && dashArray.at(0) == 5 && dashArray.at(1) == 2 && dashArray.at(2) == 2 && dashArray.at(3) == 2)
        setCurrentIndex(3);
    else if (dashArray.size() == 6 && dashArray.at(0) == 5 && dashArray.at(1) == 2 && dashArray.at(2) == 2 && dashArray.at(3) == 2 && dashArray.at(4) == 2 && dashArray.at(5) == 2)
        setCurrentIndex(4);
}

const QList<unsigned int> MyDashArrayItemsBox::getDashArray(const unsigned int& index) {
    QList<unsigned int> dashArray;

    if (index == 1) {
        dashArray.push_back(5);
        dashArray.push_back(2);
    }
    else if (index == 2) {
        dashArray.push_back(2);
        dashArray.push_back(2);
    }
    else if (index == 3) {
        dashArray.push_back(5);
        dashArray.push_back(2);
        dashArray.push_back(2);
        dashArray.push_back(2);
    }
    else if (index == 4) {
        dashArray.push_back(5);
        dashArray.push_back(2);
        dashArray.push_back(2);
        dashArray.push_back(2);
        dashArray.push_back(2);
        dashArray.push_back(2);
    }
    
    return dashArray;
}

void MyDashArrayItemsBox::reset() {
    setCurrentIndex(0);
}

// MyColorPickerButton

MyColorPickerButton::MyColorPickerButton(QWidget *parent) : QToolButton(parent) {
    MyColorPickerMenu* colorPickerMenu = new MyColorPickerMenu();
    setMenu(colorPickerMenu);
    connect(colorPickerMenu, SIGNAL(colorChosen(const QString&)), this, SLOT(setCurrentColor(const QString&)));
    setArrowType(Qt::NoArrow);
    setPopupMode(QToolButton::InstantPopup);
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setStyleSheet("QToolButton { border: 1px solid LightSlateGray; border-radius: 6px; background-color: white} QToolButton::menu-indicator { image: none; }" );
    connect(this, SIGNAL(clicked()), this, SLOT(showMenu()));
    setFixedSize(QSize(20, 20));
}

void MyColorPickerButton::setBackgroundColor(const QString& color)  {
    if (!color.isEmpty())
        setStyleSheet("QToolButton { border: 1px solid LightSlateGray; border-radius: 5px; background-color:" + color + " } QToolButton::menu-indicator { image: none; } " );
}

void MyColorPickerButton::setCurrentColor(const QString& color)  {
    _currentColor = color;
    setBackgroundColor(color);
}

const QString& MyColorPickerButton::currentColor() const {
    return _currentColor;
}
 
// MyColorPickerMenu

MyColorPickerMenu::MyColorPickerMenu() {
    /// all colors
    QWidgetAction* allColors = new QWidgetAction(this);
    QWidget* allColorsWidget = new QWidget(this);
    QGridLayout* allColorsContentLayout = new QGridLayout(allColorsWidget);
    allColorsContentLayout->setSpacing(1);
    int rowCount = 2;
    int columnCount = 0;
    
    // label
    allColorsContentLayout->addWidget(new MyLabel("Colors"), allColorsContentLayout->rowCount() - 1, 0, 1, 14, Qt::AlignLeft);
    
    allColorsContentLayout->addItem(new QSpacerItem(1, 10), allColorsContentLayout->rowCount(), 0, 1, 14);

    // black
    MyColorTileButton* blackButton = new MyColorTileButton("Black", "#000000");
    allColorsContentLayout->addWidget(blackButton, rowCount++, columnCount);
    connect(blackButton, &QPushButton::clicked, this, [this, blackButton] () { this->colorTileButtonPicked(blackButton); });
    
    // darkslategray
    MyColorTileButton* darkslategrayButton = new MyColorTileButton("DarkSlateGray", "#2F4F4F");
    allColorsContentLayout->addWidget(darkslategrayButton, rowCount++, columnCount);
    connect(darkslategrayButton, &QPushButton::clicked, this, [this, darkslategrayButton] () { this->colorTileButtonPicked(darkslategrayButton); });
    
    // dimgray
    MyColorTileButton* dimgrayButton = new MyColorTileButton("DimGray" , "#696969");
    allColorsContentLayout->addWidget(dimgrayButton, rowCount++, columnCount);
    connect(dimgrayButton, &QPushButton::clicked, this, [this, dimgrayButton] () { this->colorTileButtonPicked(dimgrayButton); });
    
    // slategray
    MyColorTileButton* slategrayButton = new MyColorTileButton("SlateGray", "#708090");
    allColorsContentLayout->addWidget(slategrayButton, rowCount++, columnCount);
    connect(slategrayButton, &QPushButton::clicked, this, [this, slategrayButton] () { this->colorTileButtonPicked(slategrayButton); });
    
    // gray
    MyColorTileButton* grayButton = new MyColorTileButton("Gray", "#808080");
    allColorsContentLayout->addWidget(grayButton, rowCount++, columnCount);
    connect(grayButton, &QPushButton::clicked, this, [this, grayButton] () { this->colorTileButtonPicked(grayButton); });
    
    // lightslategray
    MyColorTileButton* lightslategrayButton = new MyColorTileButton("LightSlateGray", "#778899");
    allColorsContentLayout->addWidget(lightslategrayButton, rowCount++, columnCount);
    connect(lightslategrayButton, &QPushButton::clicked, this, [this, lightslategrayButton] () { this->colorTileButtonPicked(lightslategrayButton); });
    
    // darkgray
    MyColorTileButton* darkgrayButton = new MyColorTileButton("DarkGray", "#A9A9A9");
    allColorsContentLayout->addWidget(darkgrayButton, rowCount++, columnCount);
    connect(darkgrayButton, &QPushButton::clicked, this, [this, darkgrayButton] () { this->colorTileButtonPicked(darkgrayButton); });
    
    // silver
    MyColorTileButton* silverButton = new MyColorTileButton("Silver", "#C0C0C0");
    allColorsContentLayout->addWidget(silverButton, rowCount++, columnCount);
    connect(silverButton, &QPushButton::clicked, this, [this, silverButton] () { this->colorTileButtonPicked(silverButton); });
    
    // lightgray
    MyColorTileButton* lightgrayButton = new MyColorTileButton("LightGray", "#D3D3D3");
    allColorsContentLayout->addWidget(lightgrayButton, rowCount++, columnCount);
    connect(lightgrayButton, &QPushButton::clicked, this, [this, lightgrayButton] () { this->colorTileButtonPicked(lightgrayButton); });
    
    // gainsboro
    MyColorTileButton* gainsboroButton = new MyColorTileButton("Gainsboro", "#DCDCDC");
    allColorsContentLayout->addWidget(gainsboroButton, rowCount++, columnCount);
    connect(gainsboroButton, &QPushButton::clicked, this, [this, gainsboroButton] () { this->colorTileButtonPicked(gainsboroButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // maroon
    MyColorTileButton* maroonButton = new MyColorTileButton("Maroon", "#800000");
    allColorsContentLayout->addWidget(maroonButton, rowCount++, columnCount);
    connect(maroonButton, &QPushButton::clicked, this, [this, maroonButton] () { this->colorTileButtonPicked(maroonButton); });
    
    // brown
    MyColorTileButton* brownButton = new MyColorTileButton("Brown", "#A52A2A");
    allColorsContentLayout->addWidget(brownButton, rowCount++, columnCount);
    connect(brownButton, &QPushButton::clicked, this, [this, brownButton] () { this->colorTileButtonPicked(brownButton); });
    
    // saddlebrown
    MyColorTileButton* saddlebrownButton = new MyColorTileButton("SaddleBrown", "#8B4513");
    allColorsContentLayout->addWidget(saddlebrownButton, rowCount++, columnCount);
    connect(saddlebrownButton, &QPushButton::clicked, this, [this, saddlebrownButton] () { this->colorTileButtonPicked(saddlebrownButton); });
    
    // sienna
    MyColorTileButton* siennaButton = new MyColorTileButton("Sienna", "#A0522D");
    allColorsContentLayout->addWidget(siennaButton, rowCount++, columnCount);
    connect(siennaButton, &QPushButton::clicked, this, [this, siennaButton] () { this->colorTileButtonPicked(siennaButton); });
    
    // chocolate
    MyColorTileButton* chocolateButton = new MyColorTileButton("Chocolate", "#D2691E");
    allColorsContentLayout->addWidget(chocolateButton, rowCount++, columnCount);
    connect(chocolateButton, &QPushButton::clicked, this, [this, chocolateButton] () { this->colorTileButtonPicked(chocolateButton); });
    
    // darkgoldenrod
    MyColorTileButton* darkgoldenrodButton = new MyColorTileButton("DarkGoldenrod", "#B8860B");
    allColorsContentLayout->addWidget(darkgoldenrodButton, rowCount++, columnCount);
    connect(darkgoldenrodButton, &QPushButton::clicked, this, [this, darkgoldenrodButton] () { this->colorTileButtonPicked(darkgoldenrodButton); });
    
    // peru
    MyColorTileButton* peruButton = new MyColorTileButton("Peru", "#CD853F");
    allColorsContentLayout->addWidget(peruButton, rowCount++, columnCount);
    connect(peruButton, &QPushButton::clicked, this, [this, peruButton] () { this->colorTileButtonPicked(peruButton); });
    
    // rosybrown
    MyColorTileButton* rosybrownButton = new MyColorTileButton("RosyBrown", "#BC8F8F");
    allColorsContentLayout->addWidget(rosybrownButton, rowCount++, columnCount);
    connect(rosybrownButton, &QPushButton::clicked, this, [this, rosybrownButton] () { this->colorTileButtonPicked(rosybrownButton); });
    
    // goldenrod
    MyColorTileButton* goldenrodButton = new MyColorTileButton("Goldenrod", "#DAA520");
    allColorsContentLayout->addWidget(goldenrodButton, rowCount++, columnCount);
    connect(goldenrodButton, &QPushButton::clicked, this, [this, goldenrodButton] () { this->colorTileButtonPicked(goldenrodButton); });
    
    // sandybrown
    MyColorTileButton* sandybrownButton = new MyColorTileButton("SandyBrown", "#F4A460");
    allColorsContentLayout->addWidget(sandybrownButton, rowCount++, columnCount);
    connect(sandybrownButton, &QPushButton::clicked, this, [this, sandybrownButton] () { this->colorTileButtonPicked(sandybrownButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // tan
    MyColorTileButton* tanButton = new MyColorTileButton("Tan", "#D2B48C");
    allColorsContentLayout->addWidget(tanButton, rowCount++, columnCount);
    connect(tanButton, &QPushButton::clicked, this, [this, tanButton] () { this->colorTileButtonPicked(tanButton); });
    
    // burlywood
    MyColorTileButton* burlywoodButton = new MyColorTileButton("Burlywood", "#DEB887");
    allColorsContentLayout->addWidget(burlywoodButton, rowCount++, columnCount);
    connect(burlywoodButton, &QPushButton::clicked, this, [this, burlywoodButton] () { this->colorTileButtonPicked(burlywoodButton); });
    
    // wheat
    MyColorTileButton* wheatButton = new MyColorTileButton("Wheat", "#F5DEB3");
    allColorsContentLayout->addWidget(wheatButton, rowCount++, columnCount);
    connect(wheatButton, &QPushButton::clicked, this, [this, wheatButton] () { this->colorTileButtonPicked(wheatButton); });
    
    // navajowhite
    MyColorTileButton* navajowhiteButton = new MyColorTileButton("NavajoWhite", "#FFDEAD");
    allColorsContentLayout->addWidget(navajowhiteButton, rowCount++, columnCount);
    connect(navajowhiteButton, &QPushButton::clicked, this, [this, navajowhiteButton] () { this->colorTileButtonPicked(navajowhiteButton); });
    
    // bisque
    MyColorTileButton* bisqueButton = new MyColorTileButton("Bisque", "#FFE4C4");
    allColorsContentLayout->addWidget(bisqueButton, rowCount++, columnCount);
    connect(bisqueButton, &QPushButton::clicked, this, [this, bisqueButton] () { this->colorTileButtonPicked(bisqueButton); });
    
    // blanchedalmond
    MyColorTileButton* blanchedalmondButton = new MyColorTileButton("BlanchedAlmond", "#FFEBCD");
    allColorsContentLayout->addWidget(blanchedalmondButton, rowCount++, columnCount);
    connect(blanchedalmondButton, &QPushButton::clicked, this, [this, blanchedalmondButton] () { this->colorTileButtonPicked(blanchedalmondButton); });
    
    // cornsilk
    MyColorTileButton* cornsilkButton = new MyColorTileButton("Cornsilk", "#FFF8DC");
    allColorsContentLayout->addWidget(cornsilkButton, rowCount++, columnCount);
    connect(cornsilkButton, &QPushButton::clicked, this, [this, cornsilkButton] () { this->colorTileButtonPicked(cornsilkButton); });
    
    // darkred
    MyColorTileButton* darkredButton = new MyColorTileButton("DarkRed", "#8B0000");
    allColorsContentLayout->addWidget(darkredButton, rowCount++, columnCount);
    connect(darkredButton, &QPushButton::clicked, this, [this, darkredButton] () { this->colorTileButtonPicked(darkredButton); });
    
    // red
    MyColorTileButton* redButton = new MyColorTileButton("Red", "#FF0000");
    allColorsContentLayout->addWidget(redButton, rowCount++, columnCount);
    connect(redButton, &QPushButton::clicked, this, [this, redButton] () { this->colorTileButtonPicked(redButton); });
    
    // firebrick
    MyColorTileButton* firebrickButton = new MyColorTileButton("Firebrick", "#B22222");
    allColorsContentLayout->addWidget(firebrickButton, rowCount++, columnCount);
    connect(firebrickButton, &QPushButton::clicked, this, [this, firebrickButton] () { this->colorTileButtonPicked(firebrickButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // crimson
    MyColorTileButton* crimsonButton = new MyColorTileButton("Crimson", "#DC143C");
    allColorsContentLayout->addWidget(crimsonButton, rowCount++, columnCount);
    connect(crimsonButton, &QPushButton::clicked, this, [this, crimsonButton] () { this->colorTileButtonPicked(crimsonButton); });
    
    // indianred
    MyColorTileButton* indianredButton = new MyColorTileButton("IndianRed", "#CD5C5C");
    allColorsContentLayout->addWidget(indianredButton, rowCount++, columnCount);
    connect(indianredButton, &QPushButton::clicked, this, [this, indianredButton] () { this->colorTileButtonPicked(indianredButton); });
    
    // lightcoral
    MyColorTileButton* lightcoralButton = new MyColorTileButton("LightCoral", "#F08080");
    allColorsContentLayout->addWidget(lightcoralButton, rowCount++, columnCount);
    connect(lightcoralButton, &QPushButton::clicked, this, [this, lightcoralButton] () { this->colorTileButtonPicked(lightcoralButton); });
    
    // salmon
    MyColorTileButton* salmonButton = new MyColorTileButton("Salmon", "#FA8072");
    allColorsContentLayout->addWidget(salmonButton, rowCount++, columnCount);
    connect(salmonButton, &QPushButton::clicked, this, [this, salmonButton] () { this->colorTileButtonPicked(salmonButton); });
    
    // darksalmon
    MyColorTileButton* darksalmonButton = new MyColorTileButton("DarkSalmon", "#E9967A");
    allColorsContentLayout->addWidget(darksalmonButton, rowCount++, columnCount);
    connect(darksalmonButton, &QPushButton::clicked, this, [this, darksalmonButton] () { this->colorTileButtonPicked(darksalmonButton); });
    
    // lightsalmon
    MyColorTileButton* lightsalmonButton = new MyColorTileButton("LightSalmon", "#FFA07A");
    allColorsContentLayout->addWidget(lightsalmonButton, rowCount++, columnCount);
    connect(lightsalmonButton, &QPushButton::clicked, this, [this, lightsalmonButton] () { this->colorTileButtonPicked(lightsalmonButton); });
    
    // orangered
    MyColorTileButton* orangeredButton = new MyColorTileButton("OrangeRed", "#FF4500");
    allColorsContentLayout->addWidget(orangeredButton, rowCount++, columnCount);
    connect(orangeredButton, &QPushButton::clicked, this, [this, orangeredButton] () { this->colorTileButtonPicked(orangeredButton); });
    
    // tomato
    MyColorTileButton* tomatoButton = new MyColorTileButton("Tomato", "#FF6347");
    allColorsContentLayout->addWidget(tomatoButton, rowCount++, columnCount);
    connect(tomatoButton, &QPushButton::clicked, this, [this, tomatoButton] () { this->colorTileButtonPicked(tomatoButton); });
    
    // darkorange
    MyColorTileButton* darkorangeButton = new MyColorTileButton("DarkOrange", "#FF8C00");
    allColorsContentLayout->addWidget(darkorangeButton, rowCount++, columnCount);
    connect(darkorangeButton, &QPushButton::clicked, this, [this, darkorangeButton] () { this->colorTileButtonPicked(darkorangeButton); });
    
    // coral
    MyColorTileButton* coralButton = new MyColorTileButton("Coral", "#FF7F50");
    allColorsContentLayout->addWidget(coralButton, rowCount++, columnCount);
    connect(coralButton, &QPushButton::clicked, this, [this, coralButton] () { this->colorTileButtonPicked(coralButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // orange
    MyColorTileButton* orangeButton = new MyColorTileButton("Orange", "#FFA500");
    allColorsContentLayout->addWidget(orangeButton, rowCount++, columnCount);
    connect(orangeButton, &QPushButton::clicked, this, [this, orangeButton] () { this->colorTileButtonPicked(orangeButton); });
    
    // mediumvioletred
    MyColorTileButton* mediumvioletredButton = new MyColorTileButton("MediumVioletRed", "#C71585");
    allColorsContentLayout->addWidget(mediumvioletredButton, rowCount++, columnCount);
    connect(mediumvioletredButton, &QPushButton::clicked, this, [this, mediumvioletredButton] () { this->colorTileButtonPicked(mediumvioletredButton); });
    
    // deeppink
    MyColorTileButton* deeppinkButton = new MyColorTileButton("DeepPink", "#FF1493");
    allColorsContentLayout->addWidget(deeppinkButton, rowCount++, columnCount);
    connect(deeppinkButton, &QPushButton::clicked, this, [this, deeppinkButton] () { this->colorTileButtonPicked(deeppinkButton); });
    
    // palevioletred
    MyColorTileButton* palevioletredButton = new MyColorTileButton("PaleVioletRed", "#DB7093");
    allColorsContentLayout->addWidget(palevioletredButton, rowCount++, columnCount);
    connect(palevioletredButton, &QPushButton::clicked, this, [this, palevioletredButton] () { this->colorTileButtonPicked(palevioletredButton); });
    
    // hotpink
    MyColorTileButton* hotpinkButton = new MyColorTileButton("HotPink", "#DB7093");
    allColorsContentLayout->addWidget(hotpinkButton, rowCount++, columnCount);
    connect(hotpinkButton, &QPushButton::clicked, this, [this, hotpinkButton] () { this->colorTileButtonPicked(hotpinkButton); });
    
    // lightpink
    MyColorTileButton* lightpinkButton = new MyColorTileButton("LightPink", "#FFB6C1");
    allColorsContentLayout->addWidget(lightpinkButton, rowCount++, columnCount);
    connect(lightpinkButton, &QPushButton::clicked, this, [this, lightpinkButton] () { this->colorTileButtonPicked(lightpinkButton); });
    
    // pink
    MyColorTileButton* pinkButton = new MyColorTileButton("Pink", "#FFC0CB");
    allColorsContentLayout->addWidget(pinkButton, rowCount++, columnCount);
    connect(pinkButton, &QPushButton::clicked, this, [this, pinkButton] () { this->colorTileButtonPicked(pinkButton); });
    
    // indigo
    MyColorTileButton* indigoButton = new MyColorTileButton("Indigo", "#4B0082");
    allColorsContentLayout->addWidget(indigoButton, rowCount++, columnCount);
    connect(indigoButton, &QPushButton::clicked, this, [this, indigoButton] () { this->colorTileButtonPicked(indigoButton); });
    
    // purple
    MyColorTileButton* purpleButton = new MyColorTileButton("Purple", "#800080");
    allColorsContentLayout->addWidget(purpleButton, rowCount++, columnCount);
    connect(purpleButton, &QPushButton::clicked, this, [this, purpleButton] () { this->colorTileButtonPicked(purpleButton); });
    
    // rebeccapurple
    //MyColorTileButton* rebeccapurpleButton = new MyColorTileButton("RebeccaPurple", "#663399");
    //allColorsContentLayout->addWidget(rebeccapurpleButton, rowCount++, columnCount);
    //connect(rebeccapurpleButton, &QPushButton::clicked, this, [this, rebeccapurpleButton] () { this->colorTileButtonPicked(rebeccapurpleButton); });
    
    // darkmagenta
    MyColorTileButton* darkmagentaButton = new MyColorTileButton("DarkMagenta", "#800080");
    allColorsContentLayout->addWidget(darkmagentaButton, rowCount++, columnCount);
    connect(darkmagentaButton, &QPushButton::clicked, this, [this, darkmagentaButton] () { this->colorTileButtonPicked(darkmagentaButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // darkviolet
    MyColorTileButton* darkvioletButton = new MyColorTileButton("DarkViolet", "#9400D3");
    allColorsContentLayout->addWidget(darkvioletButton, rowCount++, columnCount);
    connect(darkvioletButton, &QPushButton::clicked, this, [this, darkvioletButton] () { this->colorTileButtonPicked(darkvioletButton); });
    
    // darkslateblue
    MyColorTileButton* darkslateblueButton = new MyColorTileButton("DarkSlateBlue", "#483D8B");
    allColorsContentLayout->addWidget(darkslateblueButton, rowCount++, columnCount);
    connect(darkslateblueButton, &QPushButton::clicked, this, [this, darkslateblueButton] () { this->colorTileButtonPicked(darkslateblueButton); });
    
    // blueviolet
    MyColorTileButton* bluevioletButton = new MyColorTileButton("BlueViolet", "#8A2BE2");
    allColorsContentLayout->addWidget(bluevioletButton, rowCount++, columnCount);
    connect(bluevioletButton, &QPushButton::clicked, this, [this, bluevioletButton] () { this->colorTileButtonPicked(bluevioletButton); });
    
    // darkorchid
    MyColorTileButton* darkorchidButton = new MyColorTileButton("DarkOrchid", "#9932CC");
    allColorsContentLayout->addWidget(darkorchidButton, rowCount++, columnCount);
    connect(darkorchidButton, &QPushButton::clicked, this, [this, darkorchidButton] () { this->colorTileButtonPicked(darkorchidButton); });
    
    // fuchsia
    MyColorTileButton* fuchsiaButton = new MyColorTileButton("Fuchsia", "#FF00FF");
    allColorsContentLayout->addWidget(fuchsiaButton, rowCount++, columnCount);
    connect(fuchsiaButton, &QPushButton::clicked, this, [this, fuchsiaButton] () { this->colorTileButtonPicked(fuchsiaButton); });
    
    // magenta
    MyColorTileButton* magentaButton = new MyColorTileButton("Magenta", "#FF00FF");
    allColorsContentLayout->addWidget(magentaButton, rowCount++, columnCount);
    connect(magentaButton, &QPushButton::clicked, this, [this, magentaButton] () { this->colorTileButtonPicked(magentaButton); });
    
    // slateblue
    MyColorTileButton* slateblueButton = new MyColorTileButton("SlateBlue", "#6A5ACD");
    allColorsContentLayout->addWidget(slateblueButton, rowCount++, columnCount);
    connect(slateblueButton, &QPushButton::clicked, this, [this, slateblueButton] () { this->colorTileButtonPicked(slateblueButton); });
    
    // mediumslateblue
    MyColorTileButton* mediumslateblueButton = new MyColorTileButton("MediumSlateBlue", "#7B68EE");
    allColorsContentLayout->addWidget(mediumslateblueButton, rowCount++, columnCount);
    connect(mediumslateblueButton, &QPushButton::clicked, this, [this, mediumslateblueButton] () { this->colorTileButtonPicked(mediumslateblueButton); });
    
    // mediumorchid
    MyColorTileButton* mediumorchidButton = new MyColorTileButton("MediumOrchid", "#BA55D3");
    allColorsContentLayout->addWidget(mediumorchidButton, rowCount++, columnCount);
    connect(mediumorchidButton, &QPushButton::clicked, this, [this, mediumorchidButton] () { this->colorTileButtonPicked(mediumorchidButton); });
    
    // mediumpurple
    MyColorTileButton* mediumpurpleButton = new MyColorTileButton("MediumPurple", "#9370DB");
    allColorsContentLayout->addWidget(mediumpurpleButton, rowCount++, columnCount);
    connect(mediumpurpleButton, &QPushButton::clicked, this, [this, mediumpurpleButton] () { this->colorTileButtonPicked(mediumpurpleButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // orchid
    MyColorTileButton* orchidButton = new MyColorTileButton("Orchid", "#DA70D6");
    allColorsContentLayout->addWidget(orchidButton, rowCount++, columnCount);
    connect(orchidButton, &QPushButton::clicked, this, [this, orchidButton] () { this->colorTileButtonPicked(orchidButton); });
    
    // violet
    MyColorTileButton* violetButton = new MyColorTileButton("Violet", "#EE82EE");
    allColorsContentLayout->addWidget(violetButton, rowCount++, columnCount);
    connect(violetButton, &QPushButton::clicked, this, [this, violetButton] () { this->colorTileButtonPicked(violetButton); });
    
    // plum
    MyColorTileButton* plumButton = new MyColorTileButton("Plum", "#DDA0DD");
    allColorsContentLayout->addWidget(plumButton, rowCount++, columnCount);
    connect(plumButton, &QPushButton::clicked, this, [this, plumButton] () { this->colorTileButtonPicked(plumButton); });
    
    // thistle
    MyColorTileButton* thistleButton = new MyColorTileButton("Thistle", "#D8BFD8");
    allColorsContentLayout->addWidget(thistleButton, rowCount++, columnCount);
    connect(thistleButton, &QPushButton::clicked, this, [this, thistleButton] () { this->colorTileButtonPicked(thistleButton); });
    
    // lavender
    MyColorTileButton* lavenderButton = new MyColorTileButton("Lavender", "#E6E6FA");
    allColorsContentLayout->addWidget(lavenderButton, rowCount++, columnCount);
    connect(lavenderButton, &QPushButton::clicked, this, [this, lavenderButton] () { this->colorTileButtonPicked(lavenderButton); });
    
    // navy
    MyColorTileButton* navyButton = new MyColorTileButton("Navy", "#000080");
    allColorsContentLayout->addWidget(navyButton, rowCount++, columnCount);
    connect(navyButton, &QPushButton::clicked, this, [this, navyButton] () { this->colorTileButtonPicked(navyButton); });
    
    // darkblue
    MyColorTileButton* darkblueButton = new MyColorTileButton("DarkBlue", "#00008B");
    allColorsContentLayout->addWidget(darkblueButton, rowCount++, columnCount);
    connect(darkblueButton, &QPushButton::clicked, this, [this, darkblueButton] () { this->colorTileButtonPicked(darkblueButton); });
    
    // mediumblue
    MyColorTileButton* mediumblueButton = new MyColorTileButton("MediumBlue", "#0000CD");
    allColorsContentLayout->addWidget(mediumblueButton, rowCount++, columnCount);
    connect(mediumblueButton, &QPushButton::clicked, this, [this, mediumblueButton] () { this->colorTileButtonPicked(mediumblueButton); });
    
    // blue
    MyColorTileButton* blueButton = new MyColorTileButton("Blue", "#0000FF");
    allColorsContentLayout->addWidget(blueButton, rowCount++, columnCount);
    connect(blueButton, &QPushButton::clicked, this, [this, blueButton] () { this->colorTileButtonPicked(blueButton); });
    
    // midnightblue
    MyColorTileButton* midnightblueButton = new MyColorTileButton("MidnightBlue", "#191970");
    allColorsContentLayout->addWidget(midnightblueButton, rowCount++, columnCount);
    connect(midnightblueButton, &QPushButton::clicked, this, [this, midnightblueButton] () { this->colorTileButtonPicked(midnightblueButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // royalblue
    MyColorTileButton* royalblueButton = new MyColorTileButton("RoyalBlue", "#4169E1");
    allColorsContentLayout->addWidget(royalblueButton, rowCount++, columnCount);
    connect(royalblueButton, &QPushButton::clicked, this, [this, royalblueButton] () { this->colorTileButtonPicked(royalblueButton); });
    
    // steelblue
    MyColorTileButton* steelblueButton = new MyColorTileButton("SteelBlue", "#4682B4");
    allColorsContentLayout->addWidget(steelblueButton, rowCount++, columnCount);
    connect(steelblueButton, &QPushButton::clicked, this, [this, steelblueButton] () { this->colorTileButtonPicked(steelblueButton); });
    
    // dodgerblue
    MyColorTileButton* dodgerblueButton = new MyColorTileButton("DodgerBlue", "#1E90FF");
    allColorsContentLayout->addWidget(dodgerblueButton, rowCount++, columnCount);
    connect(dodgerblueButton, &QPushButton::clicked, this, [this, dodgerblueButton] () { this->colorTileButtonPicked(dodgerblueButton); });
    
    // deepskyblue
    MyColorTileButton* deepskyblueButton = new MyColorTileButton("DeepSkyBlue", "#00BFFF");
    allColorsContentLayout->addWidget(deepskyblueButton, rowCount++, columnCount);
    connect(deepskyblueButton, &QPushButton::clicked, this, [this, deepskyblueButton] () { this->colorTileButtonPicked(deepskyblueButton); });
    
    // cornflowerblue
    MyColorTileButton* cornflowerblueButton = new MyColorTileButton("CornflowerBlue", "#6495ED");
    allColorsContentLayout->addWidget(cornflowerblueButton, rowCount++, columnCount);
    connect(cornflowerblueButton, &QPushButton::clicked, this, [this, cornflowerblueButton] () { this->colorTileButtonPicked(cornflowerblueButton); });
    
    // skyblue
    MyColorTileButton* skyblueButton = new MyColorTileButton("SkyBlue", "#87CEEB");
    allColorsContentLayout->addWidget(skyblueButton, rowCount++, columnCount);
    connect(skyblueButton, &QPushButton::clicked, this, [this, skyblueButton] () { this->colorTileButtonPicked(skyblueButton); });
    
    // lightskyblue
    MyColorTileButton* lightskyblueButton = new MyColorTileButton("LightSkyBlue", "#87CEFA");
    allColorsContentLayout->addWidget(lightskyblueButton, rowCount++, columnCount);
    connect(lightskyblueButton, &QPushButton::clicked, this, [this, lightskyblueButton] () { this->colorTileButtonPicked(lightskyblueButton); });
    
    // lightsteelblue
    MyColorTileButton* lightsteelblueButton = new MyColorTileButton("LightSteelBlue", "#B0C4DE");
    allColorsContentLayout->addWidget(lightsteelblueButton, rowCount++, columnCount);
    connect(lightsteelblueButton, &QPushButton::clicked, this, [this, lightsteelblueButton] () { this->colorTileButtonPicked(lightsteelblueButton); });
    
    // lightblue
    MyColorTileButton* lightblueButton = new MyColorTileButton("LightBlue", "#ADD8E6");
    allColorsContentLayout->addWidget(lightblueButton, rowCount++, columnCount);
    connect(lightblueButton, &QPushButton::clicked, this, [this, lightblueButton] () { this->colorTileButtonPicked(lightblueButton); });
    
    // powderblue
    MyColorTileButton* powderblueButton = new MyColorTileButton("PowderBlue", "#B0E0E6");
    allColorsContentLayout->addWidget(powderblueButton, rowCount++, columnCount);
    connect(powderblueButton, &QPushButton::clicked, this, [this, powderblueButton] () { this->colorTileButtonPicked(powderblueButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // teal
    MyColorTileButton* tealButton = new MyColorTileButton("Teal", "#008080");
    allColorsContentLayout->addWidget(tealButton, rowCount++, columnCount);
    connect(tealButton, &QPushButton::clicked, this, [this, tealButton] () { this->colorTileButtonPicked(tealButton); });
    
    // darkcyan
    MyColorTileButton* darkcyanButton = new MyColorTileButton("DarkCyan", "#008B8B");
    allColorsContentLayout->addWidget(darkcyanButton, rowCount++, columnCount);
    connect(darkcyanButton, &QPushButton::clicked, this, [this, darkcyanButton] () { this->colorTileButtonPicked(darkcyanButton); });
    
    // lightseagreen
    MyColorTileButton* lightseagreenButton = new MyColorTileButton("LightSeaGreen", "#20B2AA");
    allColorsContentLayout->addWidget(lightseagreenButton, rowCount++, columnCount);
    connect(lightseagreenButton, &QPushButton::clicked, this, [this, lightseagreenButton] () { this->colorTileButtonPicked(lightseagreenButton); });
    
    // cadetblue
    MyColorTileButton* cadetblueButton = new MyColorTileButton("CadetBlue", "#5F9EA0");
    allColorsContentLayout->addWidget(cadetblueButton, rowCount++, columnCount);
    connect(cadetblueButton, &QPushButton::clicked, this, [this, cadetblueButton] () { this->colorTileButtonPicked(cadetblueButton); });
    
    // darkturquoise
    MyColorTileButton* darkturquoiseButton = new MyColorTileButton("DarkTurquoise", "#00CED1");
    allColorsContentLayout->addWidget(darkturquoiseButton, rowCount++, columnCount);
    connect(darkturquoiseButton, &QPushButton::clicked, this, [this, darkturquoiseButton] () { this->colorTileButtonPicked(darkturquoiseButton); });
    
    // mediumturquoise
    MyColorTileButton* mediumturquoiseButton = new MyColorTileButton("MediumTurquoise", "#48D1CC");
    allColorsContentLayout->addWidget(mediumturquoiseButton, rowCount++, columnCount);
    connect(mediumturquoiseButton, &QPushButton::clicked, this, [this, mediumturquoiseButton] () { this->colorTileButtonPicked(mediumturquoiseButton); });
    
    // turquoise
    MyColorTileButton* turquoiseButton = new MyColorTileButton("Turquoise", "#40E0D0");
    allColorsContentLayout->addWidget(turquoiseButton, rowCount++, columnCount);
    connect(turquoiseButton, &QPushButton::clicked, this, [this, turquoiseButton] () { this->colorTileButtonPicked(turquoiseButton); });
    
    // aqua
    MyColorTileButton* aquaButton = new MyColorTileButton("Aqua", "#00FFFF");
    allColorsContentLayout->addWidget(aquaButton, rowCount++, columnCount);
    connect(aquaButton, &QPushButton::clicked, this, [this, aquaButton] () { this->colorTileButtonPicked(aquaButton); });
    
    // cyan
    MyColorTileButton* cyanButton = new MyColorTileButton("Cyan", "#00FFFF");
    allColorsContentLayout->addWidget(cyanButton, rowCount++, columnCount);
    connect(cyanButton, &QPushButton::clicked, this, [this, cyanButton] () { this->colorTileButtonPicked(cyanButton); });
    
    // aquamarine
    MyColorTileButton* aquamarineButton = new MyColorTileButton("Aquamarine", "#7FFFD4");
    allColorsContentLayout->addWidget(aquamarineButton, rowCount++, columnCount);
    connect(aquamarineButton, &QPushButton::clicked, this, [this, aquamarineButton] () { this->colorTileButtonPicked(aquamarineButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // paleturquoise
    MyColorTileButton* paleturquoiseButton = new MyColorTileButton("PaleTurquoise", "#AFEEEE");
    allColorsContentLayout->addWidget(paleturquoiseButton, rowCount++, columnCount);
    connect(paleturquoiseButton, &QPushButton::clicked, this, [this, paleturquoiseButton] () { this->colorTileButtonPicked(paleturquoiseButton); });
    
    // lightcyan
    MyColorTileButton* lightcyanButton = new MyColorTileButton("LightCyan", "#E0FFFF");
    allColorsContentLayout->addWidget(lightcyanButton, rowCount++, columnCount);
    connect(lightcyanButton, &QPushButton::clicked, this, [this, lightcyanButton] () { this->colorTileButtonPicked(lightcyanButton); });
    
    // darkgreen
    MyColorTileButton* darkgreenButton = new MyColorTileButton("DarkGreen", "#006400");
    allColorsContentLayout->addWidget(darkgreenButton, rowCount++, columnCount);
    connect(darkgreenButton, &QPushButton::clicked, this, [this, darkgreenButton] () { this->colorTileButtonPicked(darkgreenButton); });
    
    // green
    MyColorTileButton* greenButton = new MyColorTileButton("Green", "#008000");
    allColorsContentLayout->addWidget(greenButton, rowCount++, columnCount);
    connect(greenButton, &QPushButton::clicked, this, [this, greenButton] () { this->colorTileButtonPicked(greenButton); });
    
    // darkolivegreen
    MyColorTileButton* darkolivegreenButton = new MyColorTileButton("DarkOliveGreen", "#556B2F");
    allColorsContentLayout->addWidget(darkolivegreenButton, rowCount++, columnCount);
    connect(darkolivegreenButton, &QPushButton::clicked, this, [this, darkolivegreenButton] () { this->colorTileButtonPicked(darkolivegreenButton); });
    
    // forestgreen
    MyColorTileButton* forestgreenButton = new MyColorTileButton("ForestGreen", "#228B22");
    allColorsContentLayout->addWidget(forestgreenButton, rowCount++, columnCount);
    connect(forestgreenButton, &QPushButton::clicked, this, [this, forestgreenButton] () { this->colorTileButtonPicked(forestgreenButton); });
    
    // seagreen
    MyColorTileButton* seagreenButton = new MyColorTileButton("SeaGreen", "#2E8B57");
    allColorsContentLayout->addWidget(seagreenButton, rowCount++, columnCount);
    connect(seagreenButton, &QPushButton::clicked, this, [this, seagreenButton] () { this->colorTileButtonPicked(seagreenButton); });
    
    // olive
    MyColorTileButton* oliveButton = new MyColorTileButton("Olive", "#808000");
    allColorsContentLayout->addWidget(oliveButton, rowCount++, columnCount);
    connect(oliveButton, &QPushButton::clicked, this, [this, oliveButton] () { this->colorTileButtonPicked(oliveButton); });
    
    // olivedrab
    MyColorTileButton* olivedrabButton = new MyColorTileButton("OliveDrab", "#6B8E23");
    allColorsContentLayout->addWidget(olivedrabButton, rowCount++, columnCount);
    connect(olivedrabButton, &QPushButton::clicked, this, [this, olivedrabButton] () { this->colorTileButtonPicked(olivedrabButton); });
    
    // mediumseagreen
    MyColorTileButton* mediumseagreenButton = new MyColorTileButton("MediumSeaGreen", "#3CB371");
    allColorsContentLayout->addWidget(mediumseagreenButton, rowCount++, columnCount);
    connect(mediumseagreenButton, &QPushButton::clicked, this, [this, mediumseagreenButton] () { this->colorTileButtonPicked(mediumseagreenButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // limegreen
    MyColorTileButton* limegreenButton = new MyColorTileButton("LimeGreen", "#32CD32");
    allColorsContentLayout->addWidget(limegreenButton, rowCount++, columnCount);
    connect(limegreenButton, &QPushButton::clicked, this, [this, limegreenButton] () { this->colorTileButtonPicked(limegreenButton); });
    
    // lime
    MyColorTileButton* limeButton = new MyColorTileButton("Lime", "#00FF00");
    allColorsContentLayout->addWidget(limeButton, rowCount++, columnCount);
    connect(limeButton, &QPushButton::clicked, this, [this, limeButton] () { this->colorTileButtonPicked(limeButton); });
    
    // springgreen
    MyColorTileButton* springgreenButton = new MyColorTileButton("SpringGreen", "#00FF7F");
    allColorsContentLayout->addWidget(springgreenButton, rowCount++, columnCount);
    connect(springgreenButton, &QPushButton::clicked, this, [this, springgreenButton] () { this->colorTileButtonPicked(springgreenButton); });
    
    // mediumspringgreen
    MyColorTileButton* mediumspringgreenButton = new MyColorTileButton("MediumSpringGreen", "#00FA9A");
    allColorsContentLayout->addWidget(mediumspringgreenButton, rowCount++, columnCount);
    connect(mediumspringgreenButton, &QPushButton::clicked, this, [this, mediumspringgreenButton] () { this->colorTileButtonPicked(mediumspringgreenButton); });
    
    // darkseagreen
    MyColorTileButton* darkseagreenButton = new MyColorTileButton("DarkSeaGreen", "#8FBC8F");
    allColorsContentLayout->addWidget(darkseagreenButton, rowCount++, columnCount);
    connect(darkseagreenButton, &QPushButton::clicked, this, [this, darkseagreenButton] () { this->colorTileButtonPicked(darkseagreenButton); });
    
    // mediumaquamarine
    MyColorTileButton* mediumaquamarineButton = new MyColorTileButton("MediumAquamarine", "#66CDAA");
    allColorsContentLayout->addWidget(mediumaquamarineButton, rowCount++, columnCount);
    connect(mediumaquamarineButton, &QPushButton::clicked, this, [this, mediumaquamarineButton] () { this->colorTileButtonPicked(mediumaquamarineButton); });
    
    // yellowgreen
    MyColorTileButton* yellowgreenButton = new MyColorTileButton("YellowGreen", "#9ACD32");
    allColorsContentLayout->addWidget(yellowgreenButton, rowCount++, columnCount);
    connect(yellowgreenButton, &QPushButton::clicked, this, [this, yellowgreenButton] () { this->colorTileButtonPicked(yellowgreenButton); });
    
    // lawngreen
    MyColorTileButton* lawngreenButton = new MyColorTileButton("LawnGreen", "#7CFC00");
    allColorsContentLayout->addWidget(lawngreenButton, rowCount++, columnCount);
    connect(lawngreenButton, &QPushButton::clicked, this, [this, lawngreenButton] () { this->colorTileButtonPicked(lawngreenButton); });
    
    // chartreuse
    MyColorTileButton* chartreuseButton = new MyColorTileButton("Chartreuse", "#7FFF00");
    allColorsContentLayout->addWidget(chartreuseButton, rowCount++, columnCount);
    connect(chartreuseButton, &QPushButton::clicked, this, [this, chartreuseButton] () { this->colorTileButtonPicked(chartreuseButton); });
    
    // lightgreen
    MyColorTileButton* lightgreenButton = new MyColorTileButton("LightGreen", "#90EE90");
    allColorsContentLayout->addWidget(lightgreenButton, rowCount++, columnCount);
    connect(lightgreenButton, &QPushButton::clicked, this, [this, lightgreenButton] () { this->colorTileButtonPicked(lightgreenButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // greenyellow
    MyColorTileButton* greenyellowButton = new MyColorTileButton("GreenYellow", "#ADFF2F");
    allColorsContentLayout->addWidget(greenyellowButton, rowCount++, columnCount);
    connect(greenyellowButton, &QPushButton::clicked, this, [this, greenyellowButton] () { this->colorTileButtonPicked(greenyellowButton); });
    
    // palegreen
    MyColorTileButton* palegreenButton = new MyColorTileButton("PaleGreen", "#98FB98");
    allColorsContentLayout->addWidget(palegreenButton, rowCount++, columnCount);
    connect(palegreenButton, &QPushButton::clicked, this, [this, palegreenButton] () { this->colorTileButtonPicked(palegreenButton); });
    
    // darkkhaki
    MyColorTileButton* darkkhakiButton = new MyColorTileButton("DarkKhaki", "#BDB76B");
    allColorsContentLayout->addWidget(darkkhakiButton, rowCount++, columnCount);
    connect(darkkhakiButton, &QPushButton::clicked, this, [this, darkkhakiButton] () { this->colorTileButtonPicked(darkkhakiButton); });
    
    // gold
    MyColorTileButton* goldButton = new MyColorTileButton("Gold", "#FFD700");
    allColorsContentLayout->addWidget(goldButton, rowCount++, columnCount);
    connect(goldButton, &QPushButton::clicked, this, [this, goldButton] () { this->colorTileButtonPicked(goldButton); });
    
    // khaki
    MyColorTileButton* khakiButton = new MyColorTileButton("Khaki", "#F0E68C");
    allColorsContentLayout->addWidget(khakiButton, rowCount++, columnCount);
    connect(khakiButton, &QPushButton::clicked, this, [this, khakiButton] () { this->colorTileButtonPicked(khakiButton); });
    
    // peachpuff
    MyColorTileButton* peachpuffButton = new MyColorTileButton("PeachPuff", "#FFDAB9");
    allColorsContentLayout->addWidget(peachpuffButton, rowCount++, columnCount);
    connect(peachpuffButton, &QPushButton::clicked, this, [this, peachpuffButton] () { this->colorTileButtonPicked(peachpuffButton); });
    
    // yellow
    MyColorTileButton* yellowButton = new MyColorTileButton("Yellow", "#FFFF00");
    allColorsContentLayout->addWidget(yellowButton, rowCount++, columnCount);
    connect(yellowButton, &QPushButton::clicked, this, [this, yellowButton] () { this->colorTileButtonPicked(yellowButton); });
    
    // palegoldenrod
    MyColorTileButton* palegoldenrodButton = new MyColorTileButton("PaleGoldenrod", "#EEE8AA");
    allColorsContentLayout->addWidget(palegoldenrodButton, rowCount++, columnCount);
    connect(palegoldenrodButton, &QPushButton::clicked, this, [this, palegoldenrodButton] () { this->colorTileButtonPicked(palegoldenrodButton); });
    
    // moccasin
    MyColorTileButton* moccasinButton = new MyColorTileButton("Moccasin", "#FFE4B5");
    allColorsContentLayout->addWidget(moccasinButton, rowCount++, columnCount);
    connect(moccasinButton, &QPushButton::clicked, this, [this, moccasinButton] () { this->colorTileButtonPicked(moccasinButton); });
    
    // papayawhip
    MyColorTileButton* papayawhipButton = new MyColorTileButton("PapayaWhip", "#FFEFD5");
    allColorsContentLayout->addWidget(papayawhipButton, rowCount++, columnCount);
    connect(papayawhipButton, &QPushButton::clicked, this, [this, papayawhipButton] () { this->colorTileButtonPicked(papayawhipButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // lightgoldenrodyellow
    MyColorTileButton* lightgoldenrodyellowButton = new MyColorTileButton("LightGoldenrodYellow", "#FAFAD2");
    allColorsContentLayout->addWidget(lightgoldenrodyellowButton, rowCount++, columnCount);
    connect(lightgoldenrodyellowButton, &QPushButton::clicked, this, [this, lightgoldenrodyellowButton] () { this->colorTileButtonPicked(lightgoldenrodyellowButton); });
    
    // lemonchiffon
    MyColorTileButton* lemonchiffonButton = new MyColorTileButton("LemonChiffon", "#FFFACD");
    allColorsContentLayout->addWidget(lemonchiffonButton, rowCount++, columnCount);
    connect(lemonchiffonButton, &QPushButton::clicked, this, [this, lemonchiffonButton] () { this->colorTileButtonPicked(lemonchiffonButton); });
    
    // lightyellow
    MyColorTileButton* lightyellowButton = new MyColorTileButton("LightYellow", "#FFFFE0");
    allColorsContentLayout->addWidget(lightyellowButton, rowCount++, columnCount);
    connect(lightyellowButton, &QPushButton::clicked, this, [this, lightyellowButton] () { this->colorTileButtonPicked(lightyellowButton); });
    
    // mistyrose
    MyColorTileButton* mistyroseButton = new MyColorTileButton("MistyRose", "#FFE4E1");
    allColorsContentLayout->addWidget(mistyroseButton, rowCount++, columnCount);
    connect(mistyroseButton, &QPushButton::clicked, this, [this, mistyroseButton] () { this->colorTileButtonPicked(mistyroseButton); });
    
    // antiquewhite
    MyColorTileButton* antiquewhiteButton = new MyColorTileButton("AntiqueWhite", "#FAEBD7");
    allColorsContentLayout->addWidget(antiquewhiteButton, rowCount++, columnCount);
    connect(antiquewhiteButton, &QPushButton::clicked, this, [this, antiquewhiteButton] () { this->colorTileButtonPicked(antiquewhiteButton); });
    
    // linen
    MyColorTileButton* linenButton = new MyColorTileButton("Linen", "#FAF0E6");
    allColorsContentLayout->addWidget(linenButton, rowCount++, columnCount);
    connect(linenButton, &QPushButton::clicked, this, [this, linenButton] () { this->colorTileButtonPicked(linenButton); });
    
    // beige
    MyColorTileButton* beigeButton = new MyColorTileButton("Beige", "#F5F5DC");
    allColorsContentLayout->addWidget(beigeButton, rowCount++, columnCount);
    connect(beigeButton, &QPushButton::clicked, this, [this, beigeButton] () { this->colorTileButtonPicked(beigeButton); });
    
    // whitesmoke
    MyColorTileButton* whitesmokeButton = new MyColorTileButton("WhiteSmoke", "#F5F5F5");
    allColorsContentLayout->addWidget(whitesmokeButton, rowCount++, columnCount);
    connect(whitesmokeButton, &QPushButton::clicked, this, [this, whitesmokeButton] () { this->colorTileButtonPicked(whitesmokeButton); });
    
    // lavenderblush
    MyColorTileButton* lavenderblushButton = new MyColorTileButton("LavenderBlush", "#FFF0F5");
    allColorsContentLayout->addWidget(lavenderblushButton, rowCount++, columnCount);
    connect(lavenderblushButton, &QPushButton::clicked, this, [this, lavenderblushButton] () { this->colorTileButtonPicked(lavenderblushButton); });
    
    // oldlace
    MyColorTileButton* oldlaceButton = new MyColorTileButton("OldLace", "#FDF5E6");
    allColorsContentLayout->addWidget(oldlaceButton, rowCount++, columnCount);
    connect(oldlaceButton, &QPushButton::clicked, this, [this, oldlaceButton] () { this->colorTileButtonPicked(oldlaceButton); });
    
    rowCount = 2;
    ++columnCount;
    
    // aliceblue
    MyColorTileButton* aliceblueButton = new MyColorTileButton("AliceBlue", "#F0F8FF");
    allColorsContentLayout->addWidget(aliceblueButton, rowCount++, columnCount);
    connect(aliceblueButton, &QPushButton::clicked, this, [this, aliceblueButton] () { this->colorTileButtonPicked(aliceblueButton); });
    
    // seashell
    MyColorTileButton* seashellButton = new MyColorTileButton("Seashell", "#FFF5EE");
    allColorsContentLayout->addWidget(seashellButton, rowCount++, columnCount);
    connect(seashellButton, &QPushButton::clicked, this, [this, seashellButton] () { this->colorTileButtonPicked(seashellButton); });
    
    // ghostwhite
    MyColorTileButton* ghostwhiteButton = new MyColorTileButton("GhostWhite", "#F8F8FF");
    allColorsContentLayout->addWidget(ghostwhiteButton, rowCount++, columnCount);
    connect(ghostwhiteButton, &QPushButton::clicked, this, [this, ghostwhiteButton] () { this->colorTileButtonPicked(ghostwhiteButton); });
    
    // honeydew
    MyColorTileButton* honeydewButton = new MyColorTileButton("Honeydew", "#F0FFF0");
    allColorsContentLayout->addWidget(honeydewButton, rowCount++, columnCount);
    connect(honeydewButton, &QPushButton::clicked, this, [this, honeydewButton] () { this->colorTileButtonPicked(honeydewButton); });
    
    // floralwhite
    MyColorTileButton* floralwhiteButton = new MyColorTileButton("FloralWhite", "#FFFAF0");
    allColorsContentLayout->addWidget(floralwhiteButton, rowCount++, columnCount);
    connect(floralwhiteButton, &QPushButton::clicked, this, [this, floralwhiteButton] () { this->colorTileButtonPicked(floralwhiteButton); });
    
    // azure
    MyColorTileButton* azureButton = new MyColorTileButton("Azure", "#F0FFFF");
    allColorsContentLayout->addWidget(azureButton, rowCount++, columnCount);
    connect(azureButton, &QPushButton::clicked, this, [this, azureButton] () { this->colorTileButtonPicked(azureButton); });
    
    // mintcream
    MyColorTileButton* mintcreamButton = new MyColorTileButton("MintCream", "#F5FFFA");
    allColorsContentLayout->addWidget(mintcreamButton, rowCount++, columnCount);
    connect(mintcreamButton, &QPushButton::clicked, this, [this, mintcreamButton] () { this->colorTileButtonPicked(mintcreamButton); });
    
    // snow
    MyColorTileButton* snowButton = new MyColorTileButton("Snow", "#FFFAFA");
    allColorsContentLayout->addWidget(snowButton, rowCount++, columnCount);
    connect(snowButton, &QPushButton::clicked, this, [this, snowButton] () { this->colorTileButtonPicked(snowButton); });
    
    // ivory
    MyColorTileButton* ivoryButton = new MyColorTileButton("Ivory", "#FFFFF0");
    allColorsContentLayout->addWidget(ivoryButton, rowCount++, columnCount);
    connect(ivoryButton, &QPushButton::clicked, this, [this, ivoryButton] () { this->colorTileButtonPicked(ivoryButton); });
    
    // white
    MyColorTileButton* whiteButton = new MyColorTileButton("White", "#FFFFFF");
    allColorsContentLayout->addWidget(whiteButton, rowCount++, columnCount);
    connect(whiteButton, &QPushButton::clicked, this, [this, whiteButton] () { this->colorTileButtonPicked(whiteButton); });
    
    allColorsWidget->setLayout(allColorsContentLayout);
    allColorsWidget->setContentsMargins(0, 0, 0, 0);
    allColors->setDefaultWidget(allColorsWidget);
    addAction(allColors);
    
    /// frequent colors
    QWidgetAction* frequentColors = new QWidgetAction(this);
    QWidget* frequentColorsWidget = new QWidget(this);
    QGridLayout* frequentColorsContentLayout = new QGridLayout(frequentColorsWidget);
    frequentColorsContentLayout->setSpacing(1);
    
    // label
    frequentColorsContentLayout->addWidget(new MyLabel("Frequent Colors"), frequentColorsContentLayout->rowCount() - 1, 0, 1, 14, Qt::AlignLeft);
    
    frequentColorsContentLayout->addItem(new QSpacerItem(1, 10), frequentColorsContentLayout->rowCount(), 0, 1, 14);
    
    rowCount = 2;
    columnCount = 0;
    
    // black
    MyColorTileButton* balckMainButton = new MyColorTileButton("Black", "#000000");
    frequentColorsContentLayout->addWidget(balckMainButton, rowCount, columnCount++);
    connect(balckMainButton, &QPushButton::clicked, this, [this, balckMainButton] () { this->colorTileButtonPicked(balckMainButton); });
    
    // gray
    MyColorTileButton* grayMainButton = new MyColorTileButton("Gray", "#808080");
    frequentColorsContentLayout->addWidget(grayMainButton, rowCount, columnCount++);
    connect(grayMainButton, &QPushButton::clicked, this, [this, grayMainButton] () { this->colorTileButtonPicked(grayMainButton); });
    
    // brown
    MyColorTileButton* brownMainButton = new MyColorTileButton("Brown", "#A52A2A");
    frequentColorsContentLayout->addWidget(brownMainButton, rowCount, columnCount++);
    connect(brownMainButton, &QPushButton::clicked, this, [this, brownMainButton] () { this->colorTileButtonPicked(brownMainButton); });
    
    // red
    MyColorTileButton* redMainButton = new MyColorTileButton("Red", "#FF0000");
    frequentColorsContentLayout->addWidget(redMainButton, rowCount, columnCount++);
    connect(redMainButton, &QPushButton::clicked, this, [this, redMainButton] () { this->colorTileButtonPicked(redMainButton); });
    
    // orange
    MyColorTileButton* orangeMainButton = new MyColorTileButton("Orange", "#FFA500");
    frequentColorsContentLayout->addWidget(orangeMainButton, rowCount, columnCount++);
    connect(orangeMainButton, &QPushButton::clicked, this, [this, orangeMainButton] () { this->colorTileButtonPicked(orangeMainButton); });
    
    // pink
    MyColorTileButton* pinkMainButton = new MyColorTileButton("Pink", "#FFC0CB");
    frequentColorsContentLayout->addWidget(pinkMainButton, rowCount, columnCount++);
    connect(pinkMainButton, &QPushButton::clicked, this, [this, pinkMainButton] () { this->colorTileButtonPicked(pinkMainButton); });
    
    // purple
    MyColorTileButton* purpleMainButton = new MyColorTileButton("Purple", "#800080");
    frequentColorsContentLayout->addWidget(purpleMainButton, rowCount, columnCount++);
    connect(purpleMainButton, &QPushButton::clicked, this, [this, purpleMainButton] () { this->colorTileButtonPicked(purpleMainButton); });
    
    // magenta
    MyColorTileButton* magentaMainButton = new MyColorTileButton("Magenta", "#FF00FF");
    frequentColorsContentLayout->addWidget(magentaMainButton, rowCount, columnCount++);
    connect(magentaMainButton, &QPushButton::clicked, this, [this, magentaMainButton] () { this->colorTileButtonPicked(magentaMainButton); });
    
    // violet
    MyColorTileButton* violetMainButton = new MyColorTileButton("Violet", "#EE82EE");
    frequentColorsContentLayout->addWidget(violetMainButton, rowCount, columnCount++);
    connect(violetMainButton, &QPushButton::clicked, this, [this, violetMainButton] () { this->colorTileButtonPicked(violetMainButton); });
    
    // blue
    MyColorTileButton* blueMainButton = new MyColorTileButton("Blue", "#0000FF");
    frequentColorsContentLayout->addWidget(blueMainButton, rowCount, columnCount++);
    connect(blueMainButton, &QPushButton::clicked, this, [this, blueMainButton] () { this->colorTileButtonPicked(blueMainButton); });
    
    // cyan
    MyColorTileButton* cyanMainButton = new MyColorTileButton("Cyan", "#00FFFF");
    frequentColorsContentLayout->addWidget(cyanMainButton, rowCount, columnCount++);
    connect(cyanMainButton, &QPushButton::clicked, this, [this, cyanMainButton] () { this->colorTileButtonPicked(cyanMainButton); });
    
    // green
    MyColorTileButton* greenMainButton = new MyColorTileButton("Green", "#008000");
    frequentColorsContentLayout->addWidget(greenMainButton, rowCount, columnCount++);
    connect(greenMainButton, &QPushButton::clicked, this, [this, greenMainButton] () { this->colorTileButtonPicked(greenMainButton); });
    
    // yellow
    MyColorTileButton* yellowMainButton = new MyColorTileButton("Yellow", "#FFFF00");
    frequentColorsContentLayout->addWidget(yellowMainButton, rowCount, columnCount++);
    connect(yellowMainButton, &QPushButton::clicked, this, [this, yellowMainButton] () { this->colorTileButtonPicked(yellowMainButton); });
    
    // white
    MyColorTileButton* whiteMainButton = new MyColorTileButton("White", "#FFFFFF");
    frequentColorsContentLayout->addWidget(whiteMainButton, rowCount, columnCount++);
    connect(whiteMainButton, &QPushButton::clicked, this, [this, whiteMainButton] () { this->colorTileButtonPicked(whiteMainButton); });
    
    frequentColorsWidget->setLayout(frequentColorsContentLayout);
    frequentColorsWidget->setContentsMargins(0, 0, 0, 0);
    frequentColors->setDefaultWidget(frequentColorsWidget);
    addAction(frequentColors);
}

void MyColorPickerMenu::colorTileButtonPicked(QPushButton* colorTileButton) {
    if (colorTileButton) {
        close();
        emit colorChosen(((MyColorTileButton*)colorTileButton)->color());
    }
}

// MyColorTileButton

MyColorTileButton::MyColorTileButton(const QString& color, const QString& value, QWidget* parent) : QPushButton(parent) {
    _color = color;
    _value = value;
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet(" QPushButton {background-color: " + _color + "; border-radius: 1px;} QToolTip { background-color: white;}");
    setToolTip(_color);
    setFixedWidth(12);
    setFixedHeight(12);
}

const QString& MyColorTileButton::color() const {
    return _color;
}

const QString& MyColorTileButton::value() const {
    return _value;
}

// MyFilePathButton

MyFilePathButton::MyFilePathButton(QWidget *parent) : QPushButton(parent) {
    connect(this, SIGNAL(clicked()), this, SLOT(getFilePath()));
    setFixedSize(120, 30);
}

void MyFilePathButton::getFilePath() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select an image file", ".", tr("Image Files (*.png *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        setToolTip(filePath);
        setText(filePath);
        emit isUpdated();
    }
}

// MyTreeView

MyTreeView::MyTreeView(QWidget* parent) : QTreeView(parent) {
    setHeaderHidden(true);
    setStyleSheet("QTreeView { background-color: white; border: no-border;}" "QTreeView::item:selected { background-color: white; border: no-border;}" "QTreeView::item:hover { background-color: white; border: no-border;}");
    setContentsMargins(0, 0, 0, 0);
    
    treeModel = new QStandardItemModel(this);
    setModel(treeModel);
    
    connect(this, QOverload<const QModelIndex&>::of(&QTreeView::expanded), this, [this] (const QModelIndex& index) {
        QList<QStandardItem*> familyItems;
        QList<QStandardItem*> items;
        QStandardItem* root = treeModel->invisibleRootItem();;
        QStandardItem* item = treeModel->itemFromIndex(index);
        int n = 0;
        int m = 0;
        
        familyItems.push_back(item);
        while (item->parent()) {
            item = item->parent();
            familyItems.push_back(item);
        }
        
        for (unsigned int i = 0; i < root->rowCount(); ++i) {
            items.push_back(root->child(i));
            
            while (!items.empty()) {
                n = items.size();
                
                while (n > 0) {
                    item = items.front();
                    items.pop_front();
                    
                    m = 0;
                    for (m = 0; m < familyItems.size(); ++m) {
                        if (item->text() == familyItems.at(m)->text())
                            break;
                    }
                    
                    if (m == familyItems.size())
                        this->collapse(treeModel->indexFromItem(item));
                    
                    //if (!item->hasChildren())
                        //break;
                    
                    for (int j = 0; j < item->rowCount(); ++j)
                        items.push_back(item->child(j));
                    
                    n--;
                }
            }
        }
        
        this->scrollTo(index, QAbstractItemView::PositionAtTop);
    });
}

void MyTreeView::addBranchWidget(QWidget* branchWidget, const QString& branchTitle, const QString& rootTitle) {
    MyStandardItem* branch = new MyStandardItem(branchTitle, 12.0, true);
    if (treeModel->findItems(rootTitle).empty())
        treeModel->invisibleRootItem()->appendRow(branch);
    else
        treeModel->findItems(rootTitle).first()->appendRow(branch);
    
    if (branchWidget) {
        MyStandardItem* branchContent = new MyStandardItem();
        branch->appendRow(branchContent);
        setIndexWidget(branchContent->index(), branchWidget);
        _branches.push_back(std::pair<MyStandardItem*, MyStandardItem*>(branch, branchContent));
    }
    else
        _branches.push_back(std::pair<MyStandardItem*, MyStandardItem*>(branch, NULL));
}

void MyTreeView::clearModel() {
    for (constBranchIt bIt = BranchesBegin(); bIt != BranchesEnd(); ++bIt) {
        if ((*bIt).second) {
            (*bIt).second->removeRows(0, (*bIt).second->rowCount());
            delete (*bIt).second;
        }
        delete (*bIt).first;
    }
    _branches.clear();
    treeModel->clear();
}

void MyTreeView::removeBranches(const QString& rootTitle, const unsigned int& staticbranches) {
    QList<QStandardItem *> roots;
    if (!rootTitle.isEmpty())
        roots = treeModel->findItems(rootTitle);
    else
        roots.push_back(treeModel->invisibleRootItem());
    for (int i = 0; i < roots.size(); ++i) {
        while (roots.at(i)->rowCount() > staticbranches) {
            for (constBranchIt bIt = BranchesBegin(); bIt != BranchesEnd(); ++bIt) {
                if ((*bIt).first->text() == roots.at(i)->child(staticbranches)->text()) {
                    if ((*bIt).second) {
                        (*bIt).second->clearData();
                        (*bIt).second->removeRows(0, (*bIt).second->rowCount());
                        delete (*bIt).second;
                    }
                    (*bIt).first->clearData();
                    (*bIt).first->removeRows(0, (*bIt).first->rowCount());
                    delete (*bIt).first;
                    _branches.erase(bIt);
                    roots.at(i)->removeRow(staticbranches);
                    break;
                }
            }
        }
    }
}

// MyParameterBase

MyParameterBase::MyParameterBase(const QString& name) {
    _name = name;
    _graphicalObject = NULL;
    _styleFeatures = NULL;
    _inputWidget = NULL;
}

const QString& MyParameterBase::name() {
    return _name;
}

void MyParameterBase::setGraphicalObject(GraphicalObject* graphicalObject) {
    _graphicalObject = graphicalObject;
}

GraphicalObject* MyParameterBase::graphicalObject() {
    return _graphicalObject;
}

void MyParameterBase::setStyleFeatures(Transformation2D* styleFeatures) {
    _styleFeatures = styleFeatures;
}

Transformation2D* MyParameterBase::styleFeatures() {
    return _styleFeatures;
}

// MyDoubleParameter

MyDoubleParameter::MyDoubleParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MyDoubleSpinBox();
    connect(_inputWidget, SIGNAL(editingFinished()), SLOT(write()));
    reset();
}

MyDoubleParameter::MyDoubleParameter(const QString& name, GraphicalObject* graphicalObject) : MyDoubleParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyDoubleParameter::MyDoubleParameter(const QString& name, Transformation2D* styleFeatures) : MyDoubleParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyParameterBase::PARAMETER_TYPE MyDoubleParameter::type() {
    return DOUBLE_PARAMETER_TYPE;
}

void MyDoubleParameter::setDefaultValue(const qreal& value) {
    if (value >= min() && value <= max()) {
        _defaultValue = value;
        _isSetDefaultValue = true;
    }
}

void MyDoubleParameter::setDefaultValue() {
    setDefaultValue(((MyDoubleSpinBox*)_inputWidget)->value());
}

const qreal& MyDoubleParameter::defaultValue() const {
    return _defaultValue;
}

void MyDoubleParameter::setMin(const qreal& min) {
    _min = min;
    _isSetMin = true;
}

const qreal& MyDoubleParameter::min() const {
    return _min;
}

void MyDoubleParameter::setMax(const qreal& max) {
    _max = max;
    _isSetMax = true;
}

const qreal& MyDoubleParameter::max() const {
    return _max;
}

void MyDoubleParameter::setStep(const qreal& step) {
    _step = step;
    _isSetStep = true;
}

const qreal& MyDoubleParameter::step() const {
    return _step;
}

QWidget* MyDoubleParameter::inputWidget() {
    ((MyDoubleSpinBox*)_inputWidget)->setMinimum(min());
    ((MyDoubleSpinBox*)_inputWidget)->setMaximum(max());
    ((MyDoubleSpinBox*)_inputWidget)->setSingleStep(step());
    ((MyDoubleSpinBox*)_inputWidget)->setValue(defaultValue());
    QStringList stepNumbers = QString::number(step()).split('.');
    if (stepNumbers.size() == 2)
        ((MyDoubleSpinBox*)_inputWidget)->setDecimals(stepNumbers.at(1).size());
    
    return _inputWidget;
}

void MyDoubleParameter::reset() {
    _defaultValue = 0.0;
    _min = 0.0;
    _max = 1.0;
    _step = 1.0;
    _isSetDefaultValue = false;
    _isSetMin = false;
    _isSetMax = false;
    _isSetStep = false;
}

// MyIntegerParameter

MyIntegerParameter::MyIntegerParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MySpinBox();
    connect(_inputWidget, SIGNAL(editingFinished()), SLOT(write()));
    reset();
}

MyIntegerParameter::MyIntegerParameter(const QString& name, GraphicalObject* graphicalObject) : MyIntegerParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyIntegerParameter::MyIntegerParameter(const QString& name, Transformation2D* styleFeatures) : MyIntegerParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyParameterBase::PARAMETER_TYPE MyIntegerParameter::type() {
    return INTEGER_PARAMETER_TYPE;
}

void MyIntegerParameter::setDefaultValue(const qint32& value) {
    if (value >= min() && value <= max()) {
        _defaultValue = value;
        _isSetDefaultValue = true;
    }
}

void MyIntegerParameter::setDefaultValue() {
    setDefaultValue(((MySpinBox*)_inputWidget)->value());
}

const qint32& MyIntegerParameter::defaultValue() const {
    return _defaultValue;
}

void MyIntegerParameter::setMin(const qint32& min) {
    _min = min;
    _isSetMin = true;
}

const qint32& MyIntegerParameter::min() const {
    return _min;
}

void MyIntegerParameter::setMax(const qint32& max) {
    _max = max;
    _isSetMax = true;
}

const qint32& MyIntegerParameter::max() const {
    return _max;
}

void MyIntegerParameter::setStep(const qint32& step) {
    _step = step;
    _isSetStep = true;
}

const qint32& MyIntegerParameter::step() const {
    return _step;
}

QWidget* MyIntegerParameter::inputWidget() {
    ((MySpinBox*)_inputWidget)->setMinimum(min());
    ((MySpinBox*)_inputWidget)->setMaximum(max());
    ((MySpinBox*)_inputWidget)->setSingleStep(step());
    ((MySpinBox*)_inputWidget)->setValue(defaultValue());
    
    return _inputWidget;
}

void MyIntegerParameter::reset() {
    _defaultValue = 0;
    _min = 0;
    _max = 1;
    _step = 1;
    _isSetDefaultValue = false;
    _isSetMin = false;
    _isSetMax = false;
    _isSetStep = false;
}

// MyBooleanParameter

MyBooleanParameter::MyBooleanParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MyComboBox();
    connect(_inputWidget, SIGNAL(editingFinished()), SLOT(write()));
    reset();
}

MyBooleanParameter::MyBooleanParameter(const QString& name, GraphicalObject* graphicalObject) : MyBooleanParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyBooleanParameter::MyBooleanParameter(const QString& name, Transformation2D* styleFeatures) : MyBooleanParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyParameterBase::PARAMETER_TYPE MyBooleanParameter::type() {
    return BOOLEAN_PARAMETER_TYPE;
}

void MyBooleanParameter::setDefaultValue(const bool& value) {
    _defaultValue = value;
    _isSetDefaultValue = true;
}

void MyBooleanParameter::setDefaultValue() {
    if (((MyComboBox*)_inputWidget)->currentText() == "true")
        setDefaultValue(true);
    else
        setDefaultValue(false);
}

const bool& MyBooleanParameter::defaultValue() const {
    return _defaultValue;
}

QWidget* MyBooleanParameter::inputWidget() {
    ((MyComboBox*)_inputWidget)->clear();
    ((MyComboBox*)_inputWidget)->addItem("true");
    ((MyComboBox*)_inputWidget)->addItem("false");
    if (defaultValue())
        ((MyComboBox*)_inputWidget)->setCurrentText("true");
    else
        ((MyComboBox*)_inputWidget)->setCurrentText("false");
    
    return _inputWidget;
}

void MyBooleanParameter::reset() {
    _defaultValue = true;
    _isSetDefaultValue = false;
}

// MyStringParameter

MyStringParameter::MyStringParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MyLineEdit();
    connect(_inputWidget, SIGNAL(editingFinished()), SLOT(write()));
    reset();
}

MyStringParameter::MyStringParameter(const QString& name, GraphicalObject* graphicalObject) : MyStringParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyStringParameter::MyStringParameter(const QString& name, Transformation2D* styleFeatures) : MyStringParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyParameterBase::PARAMETER_TYPE MyStringParameter::type() {
    return STRING_PARAMETER_TYPE;
}

void MyStringParameter::setDefaultValue(const QString& value) {
    _defaultValue = value;
    _isSetDefaultValue = true;
}

void MyStringParameter::setDefaultValue() {
    setDefaultValue(((MyLineEdit*)_inputWidget)->text());
}

const QString& MyStringParameter::defaultValue() const {
    return _defaultValue;
}

QWidget* MyStringParameter::inputWidget() {
    ((MyLineEdit*)_inputWidget)->setText(defaultValue());

    return _inputWidget;
}

void MyStringParameter::reset() {
    _defaultValue = "";
    _isSetDefaultValue = false;
}

// MyNominalParameter

MyNominalParameter::MyNominalParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MyComboBox();
    connect(_inputWidget, SIGNAL(editingFinished()), SLOT(write()));
    reset();
}

MyNominalParameter::MyNominalParameter(const QString& name, GraphicalObject* graphicalObject) : MyNominalParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyNominalParameter::MyNominalParameter(const QString& name, Transformation2D* styleFeatures) : MyNominalParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyParameterBase::PARAMETER_TYPE MyNominalParameter::type() {
    return NOMINAL_PARAMETER_TYPE;
}

void MyNominalParameter::setDefaultValue(const QString& value) {
    for (QString item : qAsConst(items())) {
        if (value == item) {
            _defaultValue = value;
            _isSetDefaultValue = true;
            break;
        }
    }
}

void MyNominalParameter::setDefaultValue() {
    setDefaultValue(((MyComboBox*)_inputWidget)->currentText());
}

const QString& MyNominalParameter::defaultValue() const {
    return _defaultValue;
}

const QStringList& MyNominalParameter::items() const {
    return _items;
}

QWidget* MyNominalParameter::inputWidget() {
    ((MyComboBox*)_inputWidget)->clear();
    ((MyComboBox*)_inputWidget)->addItems(items());
    ((MyComboBox*)_inputWidget)->setCurrentText(defaultValue());
    
    return _inputWidget;
}

void MyNominalParameter::reset() {
    _defaultValue = "";
    _isSetDefaultValue = false;
    _items.clear();
}

// MyPositionalParameter

MyPositionalParameter::MyPositionalParameter(const QString& name, GraphicalObject* graphicalObject) : MyDoubleParameter(name, graphicalObject) {
    reset();
}

MyPositionalParameter::MyPositionalParameter(const QString& name, Transformation2D* styleFeatures) : MyDoubleParameter(name, styleFeatures) {
    reset();
}

void MyPositionalParameter::reset() {
    setDefaultValue(0.0);
    setMin(-1000.0);
    setMax(1000.0);
    setStep(1.0);
}

// MyDimensionalParameter

MyDimensionalParameter::MyDimensionalParameter(const QString& name, GraphicalObject* graphicalObject) : MyDoubleParameter(name, graphicalObject) {
    reset();
}

MyDimensionalParameter::MyDimensionalParameter(const QString& name, Transformation2D* styleFeatures) : MyDoubleParameter(name, styleFeatures) {
    reset();
}

void MyDimensionalParameter::reset() {
    setDefaultValue(20.0);
    setMin(0.0);
    setMax(2000.0);
    setStep(1.0);
}

// MyRelativePositionalParameter

MyRelativePositionalParameter::MyRelativePositionalParameter(const QString& name, GraphicalObject* graphicalObject) : MyPositionalParameter(name, graphicalObject) {
    reset();
}

MyRelativePositionalParameter::MyRelativePositionalParameter(const QString& name, Transformation2D* styleFeatures) : MyPositionalParameter(name, styleFeatures) {
    reset();
}

void MyRelativePositionalParameter::reset() {
    setDefaultValue(0);
    setMin(-100);
    setMax(100);
    setStep(1.0);
}

// MyRelativeDimensionalParameter

MyRelativeDimensionalParameter::MyRelativeDimensionalParameter(const QString& name, GraphicalObject* graphicalObject) : MyDimensionalParameter(name, graphicalObject) {
    reset();
}

MyRelativeDimensionalParameter::MyRelativeDimensionalParameter(const QString& name, Transformation2D* styleFeatures) : MyDimensionalParameter(name, styleFeatures) {
    reset();
}

void MyRelativeDimensionalParameter::reset() {
    setDefaultValue(0);
    setMin(0);
    setMax(100);
    setStep(1.0);
}

// MyDashArrayParameter

MyDashArrayParameter::MyDashArrayParameter(const QString& name, Transformation2D* styleFeatures) : MyParameterBase(name) {
    setStyleFeatures(styleFeatures);
    _inputWidget = new MyDashArrayItemsBox();
    connect((MyDashArrayItemsBox*)_inputWidget, &MyDashArrayItemsBox::dashArrayChosen, this, [this] (const QList<unsigned int>& dashArray) {this->write(); });
    reset();
}

MyParameterBase::PARAMETER_TYPE MyDashArrayParameter::type() {
    return DASH_ARRAY_PARAMETER_TYPE;
}

void MyDashArrayParameter::setDefaultValue(const QList<unsigned int>& dashArray) {
    _defaultValue = dashArray;
}

void MyDashArrayParameter::setDefaultValue() {
    setDefaultValue(((MyDashArrayItemsBox*)_inputWidget)->currentDashArray());
}

const QList<unsigned int>& MyDashArrayParameter::defaultValue() const {
    return _defaultValue;
}

QWidget* MyDashArrayParameter::inputWidget() {
    ((MyDashArrayItemsBox*)_inputWidget)->setCurrentDashArray(defaultValue());
    
    return _inputWidget;
}

void MyDashArrayParameter::reset() {
    ((MyDashArrayItemsBox*)_inputWidget)->reset();
}

// MyColorParameter

MyColorParameter::MyColorParameter(const QString& name, Transformation2D* styleFeatures) : MyParameterBase(name) {
    setStyleFeatures(styleFeatures);
    _inputWidget = new MyColorPickerButton();
    connect(((MyColorPickerMenu*)((MyColorPickerButton*)_inputWidget)->menu()), &MyColorPickerMenu::colorChosen, this, [this] (const QString& color) {this->write(); });
    reset();
}

MyParameterBase::PARAMETER_TYPE MyColorParameter::type() {
    return COLOR_PARAMETER_TYPE;
}

void MyColorParameter::setDefaultValue(const QString& value) {
    _defaultValue = value;
}

void MyColorParameter::setDefaultValue() {
    setDefaultValue(((MyColorPickerButton*)_inputWidget)->currentColor());
}

const QString& MyColorParameter::defaultValue() const {
    return _defaultValue;
}

QWidget* MyColorParameter::inputWidget() {
    ((MyColorPickerButton*)_inputWidget)->setCurrentColor(defaultValue());
    
    return _inputWidget;
}

void MyColorParameter::reset() {
    setDefaultValue("black");
}

// MyFilePathParameter

MyFilePathParameter::MyFilePathParameter(const QString& name) : MyParameterBase(name) {
    _inputWidget = new MyFilePathButton();
    connect(_inputWidget, SIGNAL(isUpdated()), SLOT(write()));
    reset();
}

MyFilePathParameter::MyFilePathParameter(const QString& name, GraphicalObject* graphicalObject) : MyFilePathParameter(name) {
    setGraphicalObject(graphicalObject);
}

MyFilePathParameter::MyFilePathParameter(const QString& name, Transformation2D* styleFeatures) : MyFilePathParameter(name) {
    setStyleFeatures(styleFeatures);
}

MyFilePathParameter::PARAMETER_TYPE MyFilePathParameter::type() {
    return FILE_PATH_PARAMETER_TYPE;
}

void MyFilePathParameter::setDefaultValue(const QString& value) {
    _defaultValue = value;
    _isSetDefaultValue = true;
}

void MyFilePathParameter::setDefaultValue() {
    setDefaultValue(((MyFilePathButton*)_inputWidget)->text());
}

const QString& MyFilePathParameter::defaultValue() const {
    return _defaultValue;
}

QWidget* MyFilePathParameter::inputWidget() {
    ((MyFilePathButton*)_inputWidget)->setText(defaultValue());

    return _inputWidget;
}

void MyFilePathParameter::reset() {
    _defaultValue = "ImagePath";
    _isSetDefaultValue = false;
}

// MyBoundingBoxXParameter

MyBoundingBoxXParameter::MyBoundingBoxXParameter(GraphicalObject* graphicalObject) : MyPositionalParameter("X", graphicalObject) {
    
}

void MyBoundingBoxXParameter::read() {
    setDefaultValue(getPositionX(_graphicalObject));
}

void MyBoundingBoxXParameter::write() {
    setPositionX(_graphicalObject, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyBoundingBoxYParameter

MyBoundingBoxYParameter::MyBoundingBoxYParameter(GraphicalObject* graphicalObject) : MyPositionalParameter("Y", graphicalObject) {
    
}

void MyBoundingBoxYParameter::read() {
    setDefaultValue(getPositionY(_graphicalObject));
}

void MyBoundingBoxYParameter::write() {
    setPositionY(_graphicalObject, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyBoundingBoxWidthParameter

MyBoundingBoxWidthParameter::MyBoundingBoxWidthParameter(GraphicalObject* graphicalObject) : MyDimensionalParameter("Width", graphicalObject) {
    
}

void MyBoundingBoxWidthParameter::read() {
    setDefaultValue(getDimensionWidth(_graphicalObject));
}

void MyBoundingBoxWidthParameter::write() {
    setDimensionWidth(_graphicalObject, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyBoundingBoxHeightParameter

MyBoundingBoxHeightParameter::MyBoundingBoxHeightParameter(GraphicalObject* graphicalObject) : MyDimensionalParameter("Height", graphicalObject) {
    
}

void MyBoundingBoxHeightParameter::read() {
    setDefaultValue(getDimensionHeight(_graphicalObject));
}

void MyBoundingBoxHeightParameter::write() {
    setDimensionHeight(_graphicalObject, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurvePointParameterBase

MyCurvePointParameterBase::MyCurvePointParameterBase(const unsigned int& segmentIndex) {
    _segmentIndex = segmentIndex;
}

// MyCurveStartPointXParameter

MyCurveStartPointXParameter::MyCurveStartPointXParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("startX", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveStartPointXParameter::read() {
    setDefaultValue(getCurveSegmentStartPointX(_graphicalObject, _segmentIndex));
}

void MyCurveStartPointXParameter::write() {
    setCurveSegmentStartPointX(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveStartPointYParameter

MyCurveStartPointYParameter::MyCurveStartPointYParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("startY", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveStartPointYParameter::read() {
    setDefaultValue(getCurveSegmentStartPointY(_graphicalObject, _segmentIndex));
}

void MyCurveStartPointYParameter::write() {
    setCurveSegmentStartPointY(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveEndPointXParameter

MyCurveEndPointXParameter::MyCurveEndPointXParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("endX", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveEndPointXParameter::read() {
    setDefaultValue(getCurveSegmentEndPointX(_graphicalObject, _segmentIndex));
}

void MyCurveEndPointXParameter::write() {
    setCurveSegmentEndPointX(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveEndPointYParameter

MyCurveEndPointYParameter::MyCurveEndPointYParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("endY", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveEndPointYParameter::read() {
    setDefaultValue(getCurveSegmentEndPointY(_graphicalObject, _segmentIndex));
}

void MyCurveEndPointYParameter::write() {
    setCurveSegmentEndPointY(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveBasePoint1XParameter

MyCurveBasePoint1XParameter::MyCurveBasePoint1XParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("BasePoint1X", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveBasePoint1XParameter::read() {
    setDefaultValue(getCurveSegmentBasePoint1X(_graphicalObject, _segmentIndex));
}

void MyCurveBasePoint1XParameter::write() {
    setCurveSegmentBasePoint1X(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveBasePoint1YParameter

MyCurveBasePoint1YParameter::MyCurveBasePoint1YParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("BasePoint1Y", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveBasePoint1YParameter::read() {
    setDefaultValue(getCurveSegmentBasePoint1Y(_graphicalObject, _segmentIndex));
}

void MyCurveBasePoint1YParameter::write() {
    setCurveSegmentBasePoint1Y(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveBasePoint2XParameter

MyCurveBasePoint2XParameter::MyCurveBasePoint2XParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("BasePoint2X", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveBasePoint2XParameter::read() {
    setDefaultValue(getCurveSegmentBasePoint2X(_graphicalObject, _segmentIndex));
}

void MyCurveBasePoint2XParameter::write() {
    setCurveSegmentBasePoint2X(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyCurveBasePoint2YParameter

MyCurveBasePoint2YParameter::MyCurveBasePoint2YParameter(GraphicalObject* graphicalObject, const unsigned int& segmentIndex) : MyPositionalParameter("BasePoint2Y", graphicalObject), MyCurvePointParameterBase(segmentIndex) {

}

void MyCurveBasePoint2YParameter::read() {
    setDefaultValue(getCurveSegmentBasePoint2Y(_graphicalObject, _segmentIndex));
}

void MyCurveBasePoint2YParameter::write() {
    setCurveSegmentBasePoint2Y(_graphicalObject, _segmentIndex, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyStrokeWidthParameter

MyStrokeWidthParameter::MyStrokeWidthParameter(Transformation2D* styleFeatures) : MyDoubleParameter("stroke-width", styleFeatures) {
    reset();
}

void MyStrokeWidthParameter::reset() {
    setDefaultValue(2.0);
    setMin(1.0);
    setMax(20.0);
    setStep(1.0);
}

void MyStrokeWidthParameter::read() {
    setDefaultValue(getStrokeWidth((GraphicalPrimitive1D*)_styleFeatures));
}

void MyStrokeWidthParameter::write() {
    setStrokeWidth((GraphicalPrimitive1D*)_styleFeatures, ((MyDoubleSpinBox*)_inputWidget)->value());
    emit isUpdated();
}

// MyStrokeColorParameter

MyStrokeColorParameter::MyStrokeColorParameter(Transformation2D* styleFeatures) : MyColorParameter("stroke", styleFeatures) {
    reset();
}

void MyStrokeColorParameter::reset() {
    setDefaultValue("black");
}

void MyStrokeColorParameter::read() {
    setDefaultValue(QString(getStrokeColor((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyStrokeColorParameter::write() {
    setStrokeColor((GraphicalPrimitive1D*)_styleFeatures, ((MyColorPickerButton*)_inputWidget)->currentColor().toStdString());
    emit isUpdated();
}

// MyStrokeDashArrayParameter

MyStrokeDashArrayParameter::MyStrokeDashArrayParameter(Transformation2D* styleFeatures) : MyDashArrayParameter("stroke-dasharray", styleFeatures) {
    reset();
}

void MyStrokeDashArrayParameter::read() {
    setDefaultValue(QList<unsigned int>::fromVector(QVector<unsigned int>::fromStdVector(getStrokeDashArray((GraphicalPrimitive1D*)_styleFeatures))));
}

void MyStrokeDashArrayParameter::write() {
    setStrokeDashArray((GraphicalPrimitive1D*)_styleFeatures, ((MyDashArrayItemsBox*)_inputWidget)->currentDashArray().toVector().toStdVector());
    emit isUpdated();
}

// MyFillParameter

MyFillParameter::MyFillParameter(Transformation2D* styleFeatures) : MyColorParameter("fill", styleFeatures) {
    reset();
}

void MyFillParameter::reset() {
    setDefaultValue("white");
}

void MyFillParameter::read() {
    setDefaultValue(QString(getFillColor((GraphicalPrimitive2D*)_styleFeatures).c_str()));
}

void MyFillParameter::write() {
    setFillColor((GraphicalPrimitive2D*)_styleFeatures, ((MyColorPickerButton*)_inputWidget)->currentColor().toStdString());
    emit isUpdated();
}

// MyRectangleShapeXAbsoluteParameter

MyRectangleShapeXAbsoluteParameter::MyRectangleShapeXAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("X (abs)", styleFeatures) {
    
}

void MyRectangleShapeXAbsoluteParameter::read() {
    if (isSetRectangleShapeX((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeX((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeXAbsoluteParameter::write() {
    RelAbsVector x = getRectangleShapeX((Rectangle*)_styleFeatures);
    x.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeX((Rectangle*)_styleFeatures, x);
    emit isUpdated();
}

// MyRectangleShapeXRelativeParameter

MyRectangleShapeXRelativeParameter::MyRectangleShapeXRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("X (rel %)", styleFeatures) {
    
}

void MyRectangleShapeXRelativeParameter::read() {
    if (isSetRectangleShapeX((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeX((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeXRelativeParameter::write() {
    RelAbsVector x = getRectangleShapeX((Rectangle*)_styleFeatures);
    x.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeX((Rectangle*)_styleFeatures, x);
    emit isUpdated();
}

// MyRectangleShapeYAbsoluteParameter

MyRectangleShapeYAbsoluteParameter::MyRectangleShapeYAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("Y (abs)", styleFeatures) {
    
}

void MyRectangleShapeYAbsoluteParameter::read() {
    if (isSetRectangleShapeY((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeY((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeYAbsoluteParameter::write() {
    RelAbsVector y = getRectangleShapeY((Rectangle*)_styleFeatures);
    y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeY((Rectangle*)_styleFeatures, y);
    emit isUpdated();
}

// MyRectangleShapeYRelativeParameter

MyRectangleShapeYRelativeParameter::MyRectangleShapeYRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("Y (rel %)", styleFeatures) {
    
}

void MyRectangleShapeYRelativeParameter::read() {
    if (isSetRectangleShapeY((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeY((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeYRelativeParameter::write() {
    RelAbsVector y = getRectangleShapeY((Rectangle*)_styleFeatures);
    y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeY((Rectangle*)_styleFeatures, y);
    emit isUpdated();
}

// MyRectangleShapeWidthAbsoluteParameter

MyRectangleShapeWidthAbsoluteParameter::MyRectangleShapeWidthAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("Width (abs)", styleFeatures) {
    
}

void MyRectangleShapeWidthAbsoluteParameter::read() {
    if (isSetRectangleShapeWidth((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeWidth((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeWidthAbsoluteParameter::write() {
    RelAbsVector width = getRectangleShapeWidth((Rectangle*)_styleFeatures);
    width.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeWidth((Rectangle*)_styleFeatures, width);
    emit isUpdated();
}

// MyRectangleShapeWidthRelativeParameter

MyRectangleShapeWidthRelativeParameter::MyRectangleShapeWidthRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("Width (rel %)", styleFeatures) {
    
}

void MyRectangleShapeWidthRelativeParameter::read() {
    if (isSetRectangleShapeWidth((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeWidth((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeWidthRelativeParameter::write() {
    RelAbsVector width = getRectangleShapeWidth((Rectangle*)_styleFeatures);
    width.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeWidth((Rectangle*)_styleFeatures, width);
    emit isUpdated();
}

// MyRectangleShapeHeightAbsoluteParameter

MyRectangleShapeHeightAbsoluteParameter::MyRectangleShapeHeightAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("Height (abs)", styleFeatures) {
    
}

void MyRectangleShapeHeightAbsoluteParameter::read() {
    if (isSetRectangleShapeHeight((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeHeight((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeHeightAbsoluteParameter::write() {
    RelAbsVector height = getRectangleShapeHeight((Rectangle*)_styleFeatures);
    height.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeHeight((Rectangle*)_styleFeatures, height);
    emit isUpdated();
}

// MyRectangleShapeHeightRelativeParameter

MyRectangleShapeHeightRelativeParameter::MyRectangleShapeHeightRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("Height (rel %)", styleFeatures) {
    
}

void MyRectangleShapeHeightRelativeParameter::read() {
    if (isSetRectangleShapeHeight((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeHeight((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeHeightRelativeParameter::write() {
    RelAbsVector height = getRectangleShapeHeight((Rectangle*)_styleFeatures);
    height.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeHeight((Rectangle*)_styleFeatures, height);
    emit isUpdated();
}

// MyRectangleShapeRatioParameter

MyRectangleShapeRatioParameter::MyRectangleShapeRatioParameter(Transformation2D* styleFeatures) : MyDoubleParameter("Ratio", styleFeatures) {
    reset();
}

void MyRectangleShapeRatioParameter::read() {
    if (isSetRectangleShapeRatio((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeRatio((Rectangle*)_styleFeatures));
}

void MyRectangleShapeRatioParameter::write() {
    if (((MyDoubleSpinBox*)_inputWidget)->value() > 0.0) {
        setRectangleShapeRatio((Rectangle*)_styleFeatures, ((MyDoubleSpinBox*)_inputWidget)->value());
        emit isUpdated();
    }
}

void MyRectangleShapeRatioParameter::reset() {
    setDefaultValue(0.0);
    setMin(0.0);
    setMax(5.0);
    setStep(0.1);
}

// MyRectangleShapeRXAbsoluteParameter

MyRectangleShapeRXAbsoluteParameter::MyRectangleShapeRXAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("RX (abs)", styleFeatures) {
    
}

void MyRectangleShapeRXAbsoluteParameter::read() {
    if (isSetRectangleShapeRX((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeRX((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeRXAbsoluteParameter::write() {
    RelAbsVector rx = getRectangleShapeRX((Rectangle*)_styleFeatures);
    rx.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeRX((Rectangle*)_styleFeatures, rx);
    emit isUpdated();
}

// MyRectangleShapeRXRelativeParameter

MyRectangleShapeRXRelativeParameter::MyRectangleShapeRXRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("RX (rel %)", styleFeatures) {
    
}

void MyRectangleShapeRXRelativeParameter::read() {
    if (isSetRectangleShapeRX((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeRX((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeRXRelativeParameter::write() {
    RelAbsVector rx = getRectangleShapeRX((Rectangle*)_styleFeatures);
    rx.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeRX((Rectangle*)_styleFeatures, rx);
    emit isUpdated();
}

// MyRectangleShapeRYAbsoluteParameter

MyRectangleShapeRYAbsoluteParameter::MyRectangleShapeRYAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("RY (abs)", styleFeatures) {
    
}

void MyRectangleShapeRYAbsoluteParameter::read() {
    if (isSetRectangleShapeRY((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeRY((Rectangle*)_styleFeatures).getAbsoluteValue());
}

void MyRectangleShapeRYAbsoluteParameter::write() {
    RelAbsVector ry = getRectangleShapeRY((Rectangle*)_styleFeatures);
    ry.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeRY((Rectangle*)_styleFeatures, ry);
    emit isUpdated();
}

// MyRectangleShapeRYRelativeParameter

MyRectangleShapeRYRelativeParameter::MyRectangleShapeRYRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("RY (rel %)", styleFeatures) {
    
}

void MyRectangleShapeRYRelativeParameter::read() {
    if (isSetRectangleShapeRY((Rectangle*)_styleFeatures))
        setDefaultValue(getRectangleShapeRY((Rectangle*)_styleFeatures).getRelativeValue());
}

void MyRectangleShapeRYRelativeParameter::write() {
    RelAbsVector ry = getRectangleShapeRY((Rectangle*)_styleFeatures);
    ry.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRectangleShapeRY((Rectangle*)_styleFeatures, ry);
    emit isUpdated();
}

// MyEllipseShapeCXAbsoluteParameter

MyEllipseShapeCXAbsoluteParameter::MyEllipseShapeCXAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("CX (abs)", styleFeatures) {
    
}

void MyEllipseShapeCXAbsoluteParameter::read() {
    if (isSetEllipseShapeCX((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeCX((Ellipse*)_styleFeatures).getAbsoluteValue());
}

void MyEllipseShapeCXAbsoluteParameter::write() {
    RelAbsVector cx = getEllipseShapeCX((Ellipse*)_styleFeatures);
    cx.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeCX((Ellipse*)_styleFeatures, cx);
    emit isUpdated();
}

// MyEllipseShapeCXRelativeParameter

MyEllipseShapeCXRelativeParameter::MyEllipseShapeCXRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("CX (rel %)", styleFeatures) {
    
}

void MyEllipseShapeCXRelativeParameter::read() {
    if (isSetEllipseShapeCX((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeCX((Ellipse*)_styleFeatures).getRelativeValue());
}

void MyEllipseShapeCXRelativeParameter::write() {
    RelAbsVector cx = getEllipseShapeCX((Ellipse*)_styleFeatures);
    cx.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeCX((Ellipse*)_styleFeatures, cx);
    emit isUpdated();
}

// MyEllipseShapeCYAbsoluteParameter

MyEllipseShapeCYAbsoluteParameter::MyEllipseShapeCYAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("CY (abs)", styleFeatures) {
    
}

void MyEllipseShapeCYAbsoluteParameter::read() {
    if (isSetEllipseShapeCY((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeCY((Ellipse*)_styleFeatures).getAbsoluteValue());
}

void MyEllipseShapeCYAbsoluteParameter::write() {
    RelAbsVector cy = getEllipseShapeCY((Ellipse*)_styleFeatures);
    cy.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeCY((Ellipse*)_styleFeatures, cy);
    emit isUpdated();
}

// MyEllipseShapeCYRelativeParameter

MyEllipseShapeCYRelativeParameter::MyEllipseShapeCYRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("CY (rel %)", styleFeatures) {
    
}

void MyEllipseShapeCYRelativeParameter::read() {
    if (isSetEllipseShapeCY((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeCY((Ellipse*)_styleFeatures).getRelativeValue());
}

void MyEllipseShapeCYRelativeParameter::write() {
    RelAbsVector cy = getEllipseShapeCY((Ellipse*)_styleFeatures);
    cy.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeCY((Ellipse*)_styleFeatures, cy);
    emit isUpdated();
}

// MyEllipseShapeRXAbsoluteParameter

MyEllipseShapeRXAbsoluteParameter::MyEllipseShapeRXAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("RX (abs)", styleFeatures) {
    
}

void MyEllipseShapeRXAbsoluteParameter::read() {
    if (isSetEllipseShapeRX((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeRX((Ellipse*)_styleFeatures).getAbsoluteValue());
}

void MyEllipseShapeRXAbsoluteParameter::write() {
    RelAbsVector rx = getEllipseShapeRX((Ellipse*)_styleFeatures);
    rx.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeRX((Ellipse*)_styleFeatures, rx);
    emit isUpdated();
}

// MyEllipseShapeRXRelativeParameter

MyEllipseShapeRXRelativeParameter::MyEllipseShapeRXRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("RX (rel %)", styleFeatures) {
    
}

void MyEllipseShapeRXRelativeParameter::read() {
    if (isSetEllipseShapeRX((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeRX((Ellipse*)_styleFeatures).getRelativeValue());
}

void MyEllipseShapeRXRelativeParameter::write() {
    RelAbsVector rx = getEllipseShapeRX((Ellipse*)_styleFeatures);
    rx.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeRX((Ellipse*)_styleFeatures, rx);
    emit isUpdated();
}

// MyEllipseShapeRYAbsoluteParameter

MyEllipseShapeRYAbsoluteParameter::MyEllipseShapeRYAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("RY (abs)", styleFeatures) {
    
}

void MyEllipseShapeRYAbsoluteParameter::read() {
    if (isSetEllipseShapeRY((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeRY((Ellipse*)_styleFeatures).getAbsoluteValue());
}

void MyEllipseShapeRYAbsoluteParameter::write() {
    RelAbsVector ry = getEllipseShapeRY((Ellipse*)_styleFeatures);
    ry.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeRY((Ellipse*)_styleFeatures, ry);
    emit isUpdated();
}

// MyEllipseShapeRYRelativeParameter

MyEllipseShapeRYRelativeParameter::MyEllipseShapeRYRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("RY (rel %)", styleFeatures) {
    
}

void MyEllipseShapeRYRelativeParameter::read() {
    if (isSetEllipseShapeRY((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeRY((Ellipse*)_styleFeatures).getRelativeValue());
}

void MyEllipseShapeRYRelativeParameter::write() {
    RelAbsVector ry = getEllipseShapeRY((Ellipse*)_styleFeatures);
    ry.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setEllipseShapeRY((Ellipse*)_styleFeatures, ry);
    emit isUpdated();
}

// MyEllipseShapeRatioParameter

MyEllipseShapeRatioParameter::MyEllipseShapeRatioParameter(Transformation2D* styleFeatures) : MyDoubleParameter("Ratio", styleFeatures) {
    reset();
}

void MyEllipseShapeRatioParameter::read() {
    if (isSetEllipseShapeRatio((Ellipse*)_styleFeatures))
        setDefaultValue(getEllipseShapeRatio((Ellipse*)_styleFeatures));
}

void MyEllipseShapeRatioParameter::write() {
    if (((MyDoubleSpinBox*)_inputWidget)->value() > 0.0) {
        setEllipseShapeRatio((Ellipse*)_styleFeatures, ((MyDoubleSpinBox*)_inputWidget)->value());
        emit isUpdated();
    }
}

void MyEllipseShapeRatioParameter::reset() {
    setDefaultValue(0.0);
    setMin(0.0);
    setMax(5.0);
    setStep(0.1);
}

// MyPolygonShapeVertexParameterBase

MyPolygonShapeVertexParameterBase::MyPolygonShapeVertexParameterBase(const unsigned int& elementIndex) {
    _elementIndex = elementIndex;
}

// MyPolygonShapeVertexXAbsoluteParameter

MyPolygonShapeVertexXAbsoluteParameter::MyPolygonShapeVertexXAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("X (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeVertexXAbsoluteParameter::read() {
    RelAbsVector elementX = getPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(elementX.getAbsoluteValue());
}

void MyPolygonShapeVertexXAbsoluteParameter::write() {
    RelAbsVector elementX = getPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex);
    elementX.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex, elementX);
    emit isUpdated();
}

// MyPolygonShapeVertexXRelativeParameter

MyPolygonShapeVertexXRelativeParameter::MyPolygonShapeVertexXRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("X (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeVertexXRelativeParameter::read() {
    RelAbsVector elementX = getPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(elementX.getRelativeValue());
}

void MyPolygonShapeVertexXRelativeParameter::write() {
    RelAbsVector elementX = getPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex);
    elementX.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeElementX((Polygon*)_styleFeatures, _elementIndex, elementX);
    emit isUpdated();
}

// MyPolygonShapeVertexYAbsoluteParameter

MyPolygonShapeVertexYAbsoluteParameter::MyPolygonShapeVertexYAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("Y (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeVertexYAbsoluteParameter::read() {
    RelAbsVector elementY = getPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(elementY.getAbsoluteValue());
}

void MyPolygonShapeVertexYAbsoluteParameter::write() {
    RelAbsVector elementY = getPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex);
    elementY.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex, elementY);
    emit isUpdated();
}

// MyPolygonShapeVertexYRelativeParameter

MyPolygonShapeVertexYRelativeParameter::MyPolygonShapeVertexYRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("Y (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex)
{

}

void MyPolygonShapeVertexYRelativeParameter::read() {
    RelAbsVector elementY = getPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(elementY.getRelativeValue());
}

void MyPolygonShapeVertexYRelativeParameter::write() {
    RelAbsVector elementY = getPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex);
    elementY.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeElementY((Polygon*)_styleFeatures, _elementIndex, elementY);
    emit isUpdated();
}

// MyPolygonShapeBasePoint1XAbsoluteParameter

MyPolygonShapeBasePoint1XAbsoluteParameter::MyPolygonShapeBasePoint1XAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint1X (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint1XAbsoluteParameter::read() {
    RelAbsVector basePoint1X = getPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1X.getAbsoluteValue());
}

void MyPolygonShapeBasePoint1XAbsoluteParameter::write() {
    RelAbsVector basePoint1X = getPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex);
    basePoint1X.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex, basePoint1X);
    emit isUpdated();
}

// MyPolygonShapeBasePoint1XRelativeParameter

MyPolygonShapeBasePoint1XRelativeParameter::MyPolygonShapeBasePoint1XRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint1X (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint1XRelativeParameter::read() {
    RelAbsVector basePoint1X = getPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1X.getRelativeValue());
}

void MyPolygonShapeBasePoint1XRelativeParameter::write() {
    RelAbsVector basePoint1X = getPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex);
    basePoint1X.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint1X((Polygon*)_styleFeatures, _elementIndex, basePoint1X);
    emit isUpdated();
}

// MyPolygonShapeBasePoint1YAbsoluteParameter

MyPolygonShapeBasePoint1YAbsoluteParameter::MyPolygonShapeBasePoint1YAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint1Y (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint1YAbsoluteParameter::read() {
    RelAbsVector basePoint1Y = getPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1Y.getAbsoluteValue());
}

void MyPolygonShapeBasePoint1YAbsoluteParameter::write() {
    RelAbsVector basePoint1Y = getPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex);
    basePoint1Y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex, basePoint1Y);
    emit isUpdated();
}

// MyPolygonShapeBasePoint1YRelativeParameter

MyPolygonShapeBasePoint1YRelativeParameter::MyPolygonShapeBasePoint1YRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint1 Y (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint1YRelativeParameter::read() {
    RelAbsVector basePoint1Y = getPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1Y.getRelativeValue());
}

void MyPolygonShapeBasePoint1YRelativeParameter::write() {
    RelAbsVector basePoint1Y = getPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex);
    basePoint1Y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint1Y((Polygon*)_styleFeatures, _elementIndex, basePoint1Y);
    emit isUpdated();
}

// MyPolygonShapeBasePoint2XAbsoluteParameter

MyPolygonShapeBasePoint2XAbsoluteParameter::MyPolygonShapeBasePoint2XAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint2X (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint2XAbsoluteParameter::read() {
    RelAbsVector basePoint2X = getPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2X.getAbsoluteValue());
}

void MyPolygonShapeBasePoint2XAbsoluteParameter::write() {
    RelAbsVector basePoint2X = getPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex);
    basePoint2X.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex, basePoint2X);
    emit isUpdated();
}

// MyPolygonShapeBasePoint2XRelativeParameter

MyPolygonShapeBasePoint2XRelativeParameter::MyPolygonShapeBasePoint2XRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint2X (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint2XRelativeParameter::read() {
    RelAbsVector basePoint2X = getPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2X.getRelativeValue());
}

void MyPolygonShapeBasePoint2XRelativeParameter::write() {
    RelAbsVector basePoint2X = getPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex);
    basePoint2X.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint2X((Polygon*)_styleFeatures, _elementIndex, basePoint2X);
    emit isUpdated();
}

// MyPolygonShapeBasePoint2YAbsoluteParameter

MyPolygonShapeBasePoint2YAbsoluteParameter::MyPolygonShapeBasePoint2YAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint2Y (abs)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint2YAbsoluteParameter::read() {
    RelAbsVector basePoint2Y = getPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex);
    (basePoint2Y.getAbsoluteValue());
}

void MyPolygonShapeBasePoint2YAbsoluteParameter::write() {
    RelAbsVector basePoint2Y = getPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex);
    basePoint2Y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex, basePoint2Y);
    emit isUpdated();
}

// MyPolygonShapeBasePoint2YRelativeParameter

MyPolygonShapeBasePoint2YRelativeParameter::MyPolygonShapeBasePoint2YRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint2Y (rel %)", styleFeatures), MyPolygonShapeVertexParameterBase(elementIndex) {

}

void MyPolygonShapeBasePoint2YRelativeParameter::read() {
    RelAbsVector basePoint2Y = getPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2Y.getRelativeValue());
}

void MyPolygonShapeBasePoint2YRelativeParameter::write() {
    RelAbsVector basePoint2Y = getPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex);
    basePoint2Y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setPolygonShapeBasePoint2Y((Polygon*)_styleFeatures, _elementIndex, basePoint2Y);
    emit isUpdated();
}

// MyRenderCurveShapePointParameterBase

MyRenderCurveShapePointParameterBase::MyRenderCurveShapePointParameterBase(const unsigned int& elementIndex) {
    _elementIndex = elementIndex;
}

// MyRenderCurveShapePointXAbsoluteParameter

MyRenderCurveShapePointXAbsoluteParameter::MyRenderCurveShapePointXAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("X (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapePointXAbsoluteParameter::read() {
    RelAbsVector elementX = getRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(elementX.getAbsoluteValue());
}

void MyRenderCurveShapePointXAbsoluteParameter::write() {
    RelAbsVector elementX = getRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex);
    elementX.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex, elementX);
    emit isUpdated();
}

// MyRenderCurveShapePointXRelativeParameter

MyRenderCurveShapePointXRelativeParameter::MyRenderCurveShapePointXRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("X (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapePointXRelativeParameter::read() {
    RelAbsVector elementX = getRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(elementX.getRelativeValue());
}

void MyRenderCurveShapePointXRelativeParameter::write() {
    RelAbsVector elementX = getRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex);
    elementX.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeElementX((RenderCurve*)_styleFeatures, _elementIndex, elementX);
    emit isUpdated();
}

// MyRenderCurveShapePointYAbsoluteParameter

MyRenderCurveShapePointYAbsoluteParameter::MyRenderCurveShapePointYAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("Y (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapePointYAbsoluteParameter::read() {
    RelAbsVector elementY = getRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(elementY.getAbsoluteValue());
}

void MyRenderCurveShapePointYAbsoluteParameter::write() {
    RelAbsVector elementY = getRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex);
    elementY.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex, elementY);
    emit isUpdated();
}

// MyRenderCurveShapePointYRelativeParameter

MyRenderCurveShapePointYRelativeParameter::MyRenderCurveShapePointYRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("Y (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapePointYRelativeParameter::read() {
    RelAbsVector elementY = getRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(elementY.getRelativeValue());
}

void MyRenderCurveShapePointYRelativeParameter::write() {
    RelAbsVector elementY = getRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex);
    elementY.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeElementY((RenderCurve*)_styleFeatures, _elementIndex, elementY);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint1XAbsoluteParameter

MyRenderCurveShapeBasePoint1XAbsoluteParameter::MyRenderCurveShapeBasePoint1XAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint1X (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint1XAbsoluteParameter::read() {
    RelAbsVector basePoint1X = getRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1X.getAbsoluteValue());
}

void MyRenderCurveShapeBasePoint1XAbsoluteParameter::write() {
    RelAbsVector basePoint1X = getRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint1X.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex, basePoint1X);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint1XRelativeParameter

MyRenderCurveShapeBasePoint1XRelativeParameter::MyRenderCurveShapeBasePoint1XRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint1X (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint1XRelativeParameter::read() {
    RelAbsVector basePoint1X = getRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1X.getRelativeValue());
}

void MyRenderCurveShapeBasePoint1XRelativeParameter::write() {
    RelAbsVector basePoint1X = getRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint1X.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint1X((RenderCurve*)_styleFeatures, _elementIndex, basePoint1X);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint1YAbsoluteParameter

MyRenderCurveShapeBasePoint1YAbsoluteParameter::MyRenderCurveShapeBasePoint1YAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint1Y (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint1YAbsoluteParameter::read() {
    RelAbsVector basePoint1Y = getRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1Y.getAbsoluteValue());
}

void MyRenderCurveShapeBasePoint1YAbsoluteParameter::write() {
    RelAbsVector basePoint1Y = getRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint1Y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex, basePoint1Y);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint1YRelativeParameter

MyRenderCurveShapeBasePoint1YRelativeParameter::MyRenderCurveShapeBasePoint1YRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint1Y (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint1YRelativeParameter::read() {
    RelAbsVector basePoint1Y = getRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint1Y.getRelativeValue());
}

void MyRenderCurveShapeBasePoint1YRelativeParameter::write() {
    RelAbsVector basePoint1Y = getRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint1Y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint1Y((RenderCurve*)_styleFeatures, _elementIndex, basePoint1Y);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint2XAbsoluteParameter

MyRenderCurveShapeBasePoint2XAbsoluteParameter::MyRenderCurveShapeBasePoint2XAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint2X (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint2XAbsoluteParameter::read() {
    RelAbsVector basePoint2X = getRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2X.getAbsoluteValue());
}

void MyRenderCurveShapeBasePoint2XAbsoluteParameter::write() {
    RelAbsVector basePoint2X = getRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint2X.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex, basePoint2X);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint2XRelativeParameter

MyRenderCurveShapeBasePoint2XRelativeParameter::MyRenderCurveShapeBasePoint2XRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint2X (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint2XRelativeParameter::read() {
    RelAbsVector basePoint2X = getRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2X.getRelativeValue());
}

void MyRenderCurveShapeBasePoint2XRelativeParameter::write() {
    RelAbsVector basePoint2X = getRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint2X.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint2X((RenderCurve*)_styleFeatures, _elementIndex, basePoint2X);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint2YAbsoluteParameter

MyRenderCurveShapeBasePoint2YAbsoluteParameter::MyRenderCurveShapeBasePoint2YAbsoluteParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyPositionalParameter("BasePoint2Y (abs)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint2YAbsoluteParameter::read() {
    RelAbsVector basePoint2Y = getRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2Y.getAbsoluteValue());
}

void MyRenderCurveShapeBasePoint2YAbsoluteParameter::write() {
    RelAbsVector basePoint2Y = getRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint2Y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex, basePoint2Y);
    emit isUpdated();
}

// MyRenderCurveShapeBasePoint2YRelativeParameter

MyRenderCurveShapeBasePoint2YRelativeParameter::MyRenderCurveShapeBasePoint2YRelativeParameter(Transformation2D* styleFeatures, const unsigned int& elementIndex) : MyRelativePositionalParameter("BasePoint2Y (rel %)", styleFeatures), MyRenderCurveShapePointParameterBase(elementIndex) {

}

void MyRenderCurveShapeBasePoint2YRelativeParameter::read() {
    RelAbsVector basePoint2Y = getRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex);
    setDefaultValue(basePoint2Y.getRelativeValue());
}

void MyRenderCurveShapeBasePoint2YRelativeParameter::write() {
    RelAbsVector basePoint2Y = getRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex);
    basePoint2Y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setRenderCurveShapeBasePoint2Y((RenderCurve*)_styleFeatures, _elementIndex, basePoint2Y);
    emit isUpdated();
}

// MyImageShapeHrefParameter

MyImageShapeHrefParameter::MyImageShapeHrefParameter(Transformation2D* styleFeatures) : MyFilePathParameter("href", styleFeatures) {
    reset();
}

void MyImageShapeHrefParameter::getImagePath() {
    ((MyFilePathButton*)_inputWidget)->getFilePath();
}

void MyImageShapeHrefParameter::read() {
    if (isSetImageShapeHref((Image*)_styleFeatures))
        setDefaultValue(getImageShapeHref((Image*)_styleFeatures).c_str());
}

void MyImageShapeHrefParameter::write() {
    setImageShapeHref((Image*)_styleFeatures, ((MyFilePathButton*)_inputWidget)->text().toStdString());
    emit isUpdated();
}

// MyImageShapeXAbsoluteParameter

MyImageShapeXAbsoluteParameter::MyImageShapeXAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("X (abs)", styleFeatures) {

}

void MyImageShapeXAbsoluteParameter::read() {
    if (isSetImageShapeX((Image*)_styleFeatures))
        setDefaultValue(getImageShapeX((Image*)_styleFeatures).getAbsoluteValue());
}

void MyImageShapeXAbsoluteParameter::write() {
    RelAbsVector x = getImageShapeX((Image*)_styleFeatures);
    x.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeX((Image*)_styleFeatures, x);
    emit isUpdated();
}

// MyImageShapeXRelativeParameter

MyImageShapeXRelativeParameter::MyImageShapeXRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("X (rel %)", styleFeatures) {

}

void MyImageShapeXRelativeParameter::read() {
    if (isSetImageShapeX((Image*)_styleFeatures))
        setDefaultValue(getImageShapeX((Image*)_styleFeatures).getRelativeValue());
}

void MyImageShapeXRelativeParameter::write() {
    RelAbsVector x = getImageShapeX((Image*)_styleFeatures);
    x.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeX((Image*)_styleFeatures, x);
    emit isUpdated();
}

// MyImageShapeYAbsoluteParameter

MyImageShapeYAbsoluteParameter::MyImageShapeYAbsoluteParameter(Transformation2D* styleFeatures) : MyPositionalParameter("Y (abs)", styleFeatures) {

}

void MyImageShapeYAbsoluteParameter::read() {
    if (isSetImageShapeY((Image*)_styleFeatures))
        setDefaultValue(getImageShapeY((Image*)_styleFeatures).getAbsoluteValue());
}

void MyImageShapeYAbsoluteParameter::write() {
    RelAbsVector y = getImageShapeY((Image*)_styleFeatures);
    y.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeY((Image*)_styleFeatures, y);
    emit isUpdated();
}

// MyImageShapeYRelativeParameter

MyImageShapeYRelativeParameter::MyImageShapeYRelativeParameter(Transformation2D* styleFeatures) : MyRelativePositionalParameter("Y (rel %)", styleFeatures) {

}

void MyImageShapeYRelativeParameter::read() {
    if (isSetImageShapeY((Image*)_styleFeatures))
        setDefaultValue(getImageShapeY((Image*)_styleFeatures).getRelativeValue());
}

void MyImageShapeYRelativeParameter::write() {
    RelAbsVector y = getImageShapeY((Image*)_styleFeatures);
    y.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeY((Image*)_styleFeatures, y);
    emit isUpdated();
}

// MyImageShapeWidthAbsoluteParameter

MyImageShapeWidthAbsoluteParameter::MyImageShapeWidthAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("Width (abs)", styleFeatures) {

}

void MyImageShapeWidthAbsoluteParameter::read() {
    if (isSetImageShapeWidth((Image*)_styleFeatures))
        setDefaultValue(getImageShapeWidth((Image*)_styleFeatures).getAbsoluteValue());
}

void MyImageShapeWidthAbsoluteParameter::write() {
    RelAbsVector width = getImageShapeWidth((Image*)_styleFeatures);
    width.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeWidth((Image*)_styleFeatures, width);
    emit isUpdated();
}

// MyImageShapeWidthRelativeParameter

MyImageShapeWidthRelativeParameter::MyImageShapeWidthRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("Width (rel %)", styleFeatures) {

}

void MyImageShapeWidthRelativeParameter::read() {
    if (isSetImageShapeWidth((Image*)_styleFeatures))
        setDefaultValue(getImageShapeWidth((Image*)_styleFeatures).getRelativeValue());
}

void MyImageShapeWidthRelativeParameter::write() {
    RelAbsVector width = getImageShapeWidth((Image*)_styleFeatures);
    width.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeWidth((Image*)_styleFeatures, width);
    emit isUpdated();
}

// MyImageShapeHeightAbsoluteParameter

MyImageShapeHeightAbsoluteParameter::MyImageShapeHeightAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("Height (abs)", styleFeatures) {

}

void MyImageShapeHeightAbsoluteParameter::read() {
    if (isSetImageShapeHeight((Image*)_styleFeatures))
        setDefaultValue(getImageShapeHeight((Image*)_styleFeatures).getAbsoluteValue());
}

void MyImageShapeHeightAbsoluteParameter::write() {
    RelAbsVector height = getImageShapeHeight((Image*)_styleFeatures);
    height.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeHeight((Image*)_styleFeatures, height);
    emit isUpdated();
}

// MyImageShapeHeightRelativeParameter

MyImageShapeHeightRelativeParameter::MyImageShapeHeightRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("Height (rel %)", styleFeatures) {

}

void MyImageShapeHeightRelativeParameter::read() {
    if (isSetImageShapeHeight((Image*)_styleFeatures))
        setDefaultValue(getImageShapeHeight((Image*)_styleFeatures).getRelativeValue());
}

void MyImageShapeHeightRelativeParameter::write() {
    RelAbsVector height = getImageShapeHeight((Image*)_styleFeatures);
    height.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    setImageShapeHeight((Image*)_styleFeatures, height);
    emit isUpdated();
}

// MyTextFontColorParameter

MyTextFontColorParameter::MyTextFontColorParameter(Transformation2D* styleFeatures) : MyColorParameter("font-color", styleFeatures) {
    reset();
}

void MyTextFontColorParameter::reset() {
    setDefaultValue("black");
}

void MyTextFontColorParameter::read() {
    //setDefaultValue(QString(getStrokeColor((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextFontColorParameter::write() {
    //setStrokeColor((GraphicalPrimitive1D*)_styleFeatures, ((MyColorPickerButton*)_inputWidget)->currentColor().toStdString());
    emit isUpdated();
}

// MyTextFontFamilyParameter

MyTextFontFamilyParameter::MyTextFontFamilyParameter(Transformation2D* styleFeatures) : MyStringParameter("font-family", styleFeatures) {
    reset();
}

void MyTextFontFamilyParameter::reset() {
    setDefaultValue("monospace");
}

void MyTextFontFamilyParameter::read() {
    //setDefaultValue(QString(getFontFamily((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextFontFamilyParameter::write() {
    //setFontFamily((GraphicalPrimitive1D*)_styleFeatures, ((MyLineEdit*)_inputWidget)->text().toStdString());
    emit isUpdated();
}

// MyTextFontSizeAbsoluteParameter

MyTextFontSizeAbsoluteParameter::MyTextFontSizeAbsoluteParameter(Transformation2D* styleFeatures) : MyDimensionalParameter("font-size (abs)", styleFeatures) {

}

void MyTextFontSizeAbsoluteParameter::read() {
    //setDefaultValue(getTextFontSize((GraphicalPrimitive1D*)_styleFeatures).getAbsoluteValue());
}

void MyTextFontSizeAbsoluteParameter::write() {
    //RelAbsVector fontSize = getTextFontSize((GraphicalPrimitive1D*)_styleFeatures);
    //fontSize.setAbsoluteValue(((MyDoubleSpinBox*)_inputWidget)->value());
    //setTextFontSize((GraphicalPrimitive1D*)_styleFeatures, fontSize);
    emit isUpdated();
}

// MyTextFontSizeRelativeParameter

MyTextFontSizeRelativeParameter::MyTextFontSizeRelativeParameter(Transformation2D* styleFeatures) : MyRelativeDimensionalParameter("font-size (rel %)", styleFeatures) {

}

void MyTextFontSizeRelativeParameter::read() {
    //setDefaultValue(getTextFontSize((GraphicalPrimitive1D*)_styleFeatures).getRelativeValue());
}

void MyTextFontSizeRelativeParameter::write() {
    //RelAbsVector fontSize = getTextFontSize((GraphicalPrimitive1D*)_styleFeatures);
    //fontSize.setRelativeValue(((MyDoubleSpinBox*)_inputWidget)->value());
    //setTextFontSize((GraphicalPrimitive1D*)_styleFeatures, fontSize);
    emit isUpdated();
}

// MyTextFontWeightParameter

MyTextFontWeightParameter::MyTextFontWeightParameter(Transformation2D* styleFeatures) : MyNominalParameter("font-weight", styleFeatures) {
    _items.push_back("normal");
    _items.push_back("bold");
    reset();
}

const bool MyTextFontWeightParameter::defaultWeight() const {
    if (defaultValue() == "bold")
        return true;

    return false;
}

void MyTextFontWeightParameter::reset() {
    setDefaultValue("normal");
}

void MyTextFontWeightParameter::read() {
    //setDefaultValue(QString(getFontWeight((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextFontWeightParameter::write() {
    //setFontWeight((GraphicalPrimitive1D*)_styleFeatures, ((MyComboBox*)_inputWidget)->currentText().toStdString());
    emit isUpdated();
}

// MyTextFontStyleParameter

MyTextFontStyleParameter::MyTextFontStyleParameter(Transformation2D* styleFeatures) : MyNominalParameter("font-style", styleFeatures) {
    _items.push_back("normal");
    _items.push_back("italic");
    reset();
}

const bool MyTextFontStyleParameter::defaultStyle() const {
    if (defaultValue() == "italic")
        return true;

    return false;
}

void MyTextFontStyleParameter::reset() {
    setDefaultValue("normal");
}

void MyTextFontStyleParameter::read() {
    //setDefaultValue(QString(getFontStyle((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextFontStyleParameter::write() {
    //setFontStyle((GraphicalPrimitive1D*)_styleFeatures, ((MyComboBox*)_inputWidget)->currentText().toStdString());
    emit isUpdated();
}

// MyTextAnchorParameter

MyTextAnchorParameter::MyTextAnchorParameter(Transformation2D* styleFeatures) : MyNominalParameter("text-anchor", styleFeatures) {
    _items.push_back("start");
    _items.push_back("middle");
    _items.push_back("end");
    reset();
}

const Qt::Alignment MyTextAnchorParameter::defaultAlignment() const {
    if (defaultValue() == "start")
        return Qt::AlignLeft;
    else if (defaultValue() == "middle")
        return Qt::AlignHCenter;
    else if (defaultValue() == "end")
        return Qt::AlignRight;

    return Qt::AlignHCenter;
}

void MyTextAnchorParameter::reset() {
    setDefaultValue("middle");
}

void MyTextAnchorParameter::read() {
    //setDefaultValue(QString(getTextAnchor((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextAnchorParameter::write() {
    //setTextAnchor((GraphicalPrimitive1D*)_styleFeatures, ((MyComboBox*)_inputWidget)->currentText().toStdString());
    emit isUpdated();
}

// MyTextVAnchorParameter

MyTextVAnchorParameter::MyTextVAnchorParameter(Transformation2D* styleFeatures) : MyNominalParameter("vtext-anchor", styleFeatures) {
    _items.push_back("top");
    _items.push_back("middle");
    _items.push_back("baseline");
    _items.push_back("bottom");
    reset();
}

const Qt::Alignment MyTextVAnchorParameter::defaultAlignment() const {
    if (defaultValue() == "top")
        return Qt::AlignTop;
    else if (defaultValue() == "middle")
        return Qt::AlignVCenter;
    else if (defaultValue() == "baseline")
        return Qt::AlignBaseline;
    else if (defaultValue() == "bottom")
        return Qt::AlignBottom;

    return Qt::AlignVCenter;
}

void MyTextVAnchorParameter::reset() {
    setDefaultValue("middle");
}

void MyTextVAnchorParameter::read() {
    //setDefaultValue(QString(getVTextAnchor((GraphicalPrimitive1D*)_styleFeatures).c_str()));
}

void MyTextVAnchorParameter::write() {
    //setVTextAnchor((GraphicalPrimitive1D*)_styleFeatures, ((MyComboBox*)_inputWidget)->currentText().toStdString());
    emit isUpdated();
}