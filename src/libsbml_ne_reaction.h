#ifndef __LIBSBML_NE_REACTION_H
#define __LIBSBML_NE_REACTION_H

#include "libsbml_ne_network_element.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>

class MyReaction : public MyNetworkElementBase {
Q_OBJECT

public:
    MyReaction(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    const QString getType() override;
    
    const QString getId() override;
    
    const QString getCompartmentId();
    
    QWidget* elementFeatureMenu() override;

    void setReactionFeaturesMenu(QGridLayout* layout);

    QWidget* createReactionFeaturesMenuTree();
    
public slots:
    
    void updateGraphicsItem() override;

protected:
    QWidget* _reactionBoundingBoxCurveSwitch;
    QWidget* _reactionFeaturesMenu;
};

class MyReactionBoundingBoxCurveSwitch: public QGroupBox {
Q_OBJECT

public:
    MyReactionBoundingBoxCurveSwitch(GraphicalObject* graphicalObject, QWidget* parent = nullptr);

    void initializeButtons();

    void addCurve();

    void removeCurve();

signals:

    void isUpdated();

public slots:

    void enableBoundingBox(bool checked);

    void enableCurve(bool checked);

protected:

    QRadioButton* _boundingBoxRadioButton;
    QRadioButton* _curveRadioButton;
    GraphicalObject* _graphicalObject;
};

#endif
