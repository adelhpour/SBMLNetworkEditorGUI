#ifndef __LIBSBML_NE_GRAPHICS_SCENE_H
#define __LIBSBML_NE_GRAPHICS_SCENE_H

#include <QWidget>
#include <QGraphicsScene>

class MyGraphicsScene : public QGraphicsScene {
    Q_OBJECT
    
public:
    
    MyGraphicsScene(QWidget* parent = nullptr);

public slots:
    
    void setSceneExtents(const QRectF& extents);
    void setSceneBackgroundColor(const QBrush& backgroundColor);
    void addGraphicsItem(QGraphicsItem* item);
    void removeGraphicsItem(QGraphicsItem* item);
    void exportSceneFigure(const QString& fileName);
    void clearScene();
};

#endif
