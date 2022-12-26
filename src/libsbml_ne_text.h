#ifndef __LIBSBML_NE_TEXT_H
#define __LIBSBML_NE_TEXT_H

#include "libsbml_ne_network_element.h"

class MyText : public MyNetworkElementBase {
    
public:
    MyText(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue);
    
    void updateGraphicsItem() override;
    
};

#endif
