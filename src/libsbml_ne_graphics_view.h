#ifndef __LIBSBML_NE_GRAPHICS_VIEW_H
#define __LIBSBML_NE_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPrinter>

class MyGraphicsView : public QGraphicsView {
    Q_OBJECT
    
public:
    
    MyGraphicsView(QWidget* parent = nullptr);
    
    const qreal currentScale() const;
    void setMinScale(const qreal& minScale);
    void setMaxScale(const qreal& maxScale);
    const qreal minScale() const;
    const qreal maxScale() const;
    
private slots:
    
    void exportFigure(const QString& fileName, QPrinter::OutputFormat outputFormat);
    void resetScale();
    void scalingTime(qreal x);
    void animFinished();
    
protected:
    
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    
    int _numScheduledScalings;
    qreal _minScale;
    qreal _maxScale;
    int _panStartX;
    int _panStartY;
    bool _panMode;
};

#endif
