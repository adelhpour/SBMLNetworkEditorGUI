#ifndef __LIBSBML_NE_SPECIES_H
#define __LIBSBML_NE_SPECIES_H

#include "libsbml_ne_network_element.h"

class MySpecies : public MyNetworkElementBase {
    
public:
    MySpecies(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateGraphicsItem() override;
    
};

#endif
