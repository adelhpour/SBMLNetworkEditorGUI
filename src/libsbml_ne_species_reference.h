#ifndef __LIBSBML_NE_SPECIES_REFERENCE_H
#define __LIBSBML_NE_SPECIES_REFERENCE_H

#include "libsbml_ne_network_element.h"

class MySpeciesReference : public MyNetworkElementBase {
    
public:
    MySpeciesReference(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateGraphicsItem() override;
    
    void updateLineEndingsGraphicsItem();
    
    void addLineEndingGraphicsItem(const QString& lineEndingId, const QPointF& position, const qreal rotation);
    
    const QPointF getStartPoint();
    
    const QPointF getEndPoint();
    
    const qreal getStartSlope();
    
    const qreal getEndSlope();
};

#endif
