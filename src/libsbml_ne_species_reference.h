#ifndef __LIBSBML_NE_SPECIES_REFERENCE_H
#define __LIBSBML_NE_SPECIES_REFERENCE_H

#include "libsbml_ne_network_element.h"

class MySpeciesReference : public MyNetworkElementBase {
    
public:
    MySpeciesReference(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateLineEndingsGraphicsItem();
    
    void addLineEndingGraphicsItem(const QString& lineEndingId, const QPointF& position, const qreal rotation);
    
    const QPointF getStartPoint();
    
    const QPointF getEndPoint();
    
    const qreal getStartSlope();
    
    const qreal getEndSlope();
    
    const QString getType() override;
    
    const QString getId() override;
    
    const QString getSpeciesGlyphId();
    
    const QString getRole();
    
    QWidget* elementFeatureMenu() override;

    const QString getStartHeadId();

    const QString getEndHeadId();
    
public slots:
        
    void updateGraphicsItem() override;
};

#endif
