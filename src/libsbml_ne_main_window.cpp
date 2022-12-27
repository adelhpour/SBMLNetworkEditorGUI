#include "libsbml_ne_main_window.h"
#include "libsbml_ne_interactor.h"
#include "libsbml_ne_graphics_view.h"
#include "libsbml_ne_graphics_scene.h"
#include <QGridLayout>
#include <QMenuBar>

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent) {
    setObjectName("main_window");
    setStyleSheet("QMainWindow {background-color : white}");
    
    setMinimumSize(120, 80);
    resize(1050, 700);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    setWidgets();
    setInteractions();
    
    QGridLayout* layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view(), 0, 2);
    
    QWidget* widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(layout);
}

MyMainWindow::~MyMainWindow() {
    
}

void MyMainWindow::setWidgets() {
    _view = new MyGraphicsView(this);
    _interactor = new MyInteractor(this);
    _featureMenu = NULL;
    
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    _menuActions = ((MyInteractor*)interactor())->createMenuActions();
    fileMenu->addActions(_menuActions);
}

void MyMainWindow::setInteractions() {
    // set save action enabled
    connect(interactor(), SIGNAL(askForSetSaveActionEnabled(const bool&)), this, SLOT(setSaveActionEnabled(const bool&)));
    
    // set export action enabled
    connect(interactor(), SIGNAL(askForSetExportActionEnabled(const bool&)), this, SLOT(setExportActionEnabled(const bool&)));
    
    // display feature menu
    connect((MyInteractor*)interactor(), SIGNAL(askForDisplayFeatureMenu(QWidget*)), this, SLOT(displayFeatureMenu(QWidget*)));
    
    // remove feature menu
    connect((MyInteractor*)interactor(), SIGNAL(askForRemoveFeatureMenu()), this, SLOT(removeFeatureMenu()));
    
    connect(((MyGraphicsView*)view())->scene(), SIGNAL(mouseLeftButtonIsPressed()), this, SLOT(removeFeatureMenu()));
    
    // export scene figure
    connect(interactor(), SIGNAL(askForExportSceneFigure(const QString&)), ((MyGraphicsView*)view())->scene(), SLOT(exportSceneFigure(const QString&)));
    
    // reset scene
    connect(interactor(), SIGNAL(askForClearScene()), ((MyGraphicsView*)view())->scene(), SLOT(clearScene()));
    
    // set scene extents
    connect(interactor(), SIGNAL(askForSetSceneExtents(const QRectF&)), ((MyGraphicsView*)view())->scene(), SLOT(setSceneExtents(const QRectF&)));
    
    // set scene background color
    connect(interactor(), SIGNAL(askForSetSceneBackgroundColor(const QBrush&)), ((MyGraphicsView*)view())->scene(), SLOT(setSceneBackgroundColor(const QBrush&)));
    
    // add graphics item to the scene
    connect(interactor(), SIGNAL(askForAddGraphicsItem(QGraphicsItem*)), ((MyGraphicsView*)view())->scene(), SLOT(addGraphicsItem(QGraphicsItem*)));
    
    // remove graphics item from the scene
    connect(interactor(), SIGNAL(askForRemoveGraphicsItem(QGraphicsItem*)), ((MyGraphicsView*)view())->scene(), SLOT(removeGraphicsItem(QGraphicsItem*)));
}

QWidget* MyMainWindow::view() {
    return _view;
}

QObject* MyMainWindow::interactor() {
    return _interactor;
}

void MyMainWindow::displayFeatureMenu(QWidget* featureMenu) {
    removeFeatureMenu();
    ((QGridLayout*)centralWidget()->layout())->addWidget(featureMenu, 0, 1);
    _featureMenu = featureMenu;
}

void MyMainWindow::removeFeatureMenu() {
    if (_featureMenu) {
        centralWidget()->layout()->removeWidget(_featureMenu);
        delete _featureMenu;
        _featureMenu = NULL;
    }
}

void MyMainWindow::setSaveActionEnabled(const bool& enabled) {
    QAction* action = getMenuBarAction("Save");
    if (action)
        action->setEnabled(enabled);
}

void MyMainWindow::setExportActionEnabled(const bool& enabled) {
    QAction* action = getMenuBarAction("Export as PDF");
    if (action)
        action->setEnabled(enabled);
}

QAction* MyMainWindow::getMenuBarAction(const QString& actionIconText) {
    for (QAction* action : _menuActions) {
        if (action->iconText() == actionIconText)
            return action;
    }
    
    return NULL;
}


