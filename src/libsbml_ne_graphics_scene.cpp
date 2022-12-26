#include "libsbml_ne_graphics_scene.h"
#include <QPainter>
#include <QPrinter>

// MyGraphicsScene

MyGraphicsScene::MyGraphicsScene(QWidget* parent) : QGraphicsScene(parent) {
    setSceneRect(30.0, 20.0, 840.0, 560.0);
}

void MyGraphicsScene::setSceneExtents(const QRectF& extents) {
    setSceneRect(extents.x(), extents.y(), extents.width(), extents.height());
}

void MyGraphicsScene::setSceneBackgroundColor(const QBrush& backgroundColor) {
    setBackgroundBrush(backgroundColor);
}

void MyGraphicsScene::addGraphicsItem(QGraphicsItem* item) {
    addItem(item);
}

void MyGraphicsScene::removeGraphicsItem(QGraphicsItem* item) {
    removeItem(item);
}

void MyGraphicsScene::exportSceneFigure(const QString& fileName) {
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPageSize(QSize(sceneRect().width(), sceneRect().height()), QPageSize::Point));
    printer.setPageMargins(QMarginsF(0.0, 0.0, 0.0, 0.0));
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QPainter painter(&printer);
    render(&painter);
}

void MyGraphicsScene::clearScene() {
    clear();
}
