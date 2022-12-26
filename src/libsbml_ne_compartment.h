#ifndef __LIBSBML_NE_COMPARTMENT_H
#define __LIBSBML_NE_COMPARTMENT_H

#include "libsbml_ne_network_element.h"

class MyCompartment : public MyNetworkElementBase {
    
public:
    MyCompartment(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateGraphicsItem() override;
    
};

#endif
