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
    layout->addWidget(view(), 2, 0);
    
    
    QWidget* widget = new QWidget;
    setCentralWidget(widget);
    widget->setLayout(layout);
}

MyMainWindow::~MyMainWindow() {
    
}

void MyMainWindow::setWidgets() {
    _view = new MyGraphicsView(this);
    _interactor = new MyInteractor(this);
    
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    _menuActions = ((MyInteractor*)interactor())->createMenuActions();
    fileMenu->addActions(_menuActions);
}

void MyMainWindow::setInteractions() {
    // set save action enabled
    connect((MyInteractor*)interactor(), SIGNAL(askForSetSaveActionEnabled(const bool&)), this, SLOT(setSaveActionEnabled(const bool&)));
    
    // set export action enabled
    connect((MyInteractor*)interactor(), SIGNAL(askForSetExportActionEnabled(const bool&)), this, SLOT(setExportActionEnabled(const bool&)));
    
    // export scene figure
    connect((MyInteractor*)interactor(), SIGNAL(askForExportSceneFigure(const QString&)), ((MyGraphicsScene*)((MyGraphicsView*)view())->scene()), SLOT(exportSceneFigure(const QString&)));
    
    // reset scene
    connect((MyInteractor*)interactor(), SIGNAL(askForClearScene()), ((MyGraphicsScene*)((MyGraphicsView*)view())->scene()), SLOT(clearScene()));
    
    // set scene extents
    connect((MyInteractor*)interactor(), SIGNAL(askForSetSceneExtents(const QRectF&)), (MyGraphicsScene*)((MyGraphicsView*)view())->scene(), SLOT(setSceneExtents(const QRectF&)));
    
    // set scene background color
    connect((MyInteractor*)interactor(), SIGNAL(askForSetSceneBackgroundColor(const QBrush&)), (MyGraphicsScene*)((MyGraphicsView*)view())->scene(), SLOT(setSceneBackgroundColor(const QBrush&)));
    
    // add graphics item to the scene
    connect((MyInteractor*)interactor(), SIGNAL(askForAddGraphicsItem(QGraphicsItem*)), (MyGraphicsScene*)((MyGraphicsView*)view())->scene(), SLOT(addGraphicsItem(QGraphicsItem*)));
    
    // remove graphics item from the scene
    connect((MyInteractor*)interactor(), SIGNAL(askForRemoveGraphicsItem(QGraphicsItem*)), (MyGraphicsScene*)((MyGraphicsView*)view())->scene(), SLOT(removeGraphicsItem(QGraphicsItem*)));
}

QWidget* MyMainWindow::view() {
    return _view;
}

QObject* MyMainWindow::interactor() {
    return _interactor;
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



