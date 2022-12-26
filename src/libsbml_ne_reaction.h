#ifndef __LIBSBML_NE_REACTION_H
#define __LIBSBML_NE_REACTION_H

#include "libsbml_ne_network_element.h"

class MyReaction : public MyNetworkElementBase {
    
public:
    MyReaction(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateGraphicsItem() override;
    
};

#endif
