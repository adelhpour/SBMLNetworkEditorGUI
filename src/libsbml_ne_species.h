#ifndef __LIBSBML_NE_SPECIES_H
#define __LIBSBML_NE_SPECIES_H

#include "libsbml_ne_network_element.h"

class MySpecies : public MyNetworkElementBase {
    
public:
    MySpecies(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    const QString getType() override;
    
    const QString getId() override;
    
    const QString getCompartmentId();
    
    QWidget* elementFeatureMenu() override;
    
public slots:
        
    void updateGraphicsItem() override;
};

#endif
