#ifndef __LIBSBML_NE_NETWORK_ELEMENT_BUILDER_H
#define __LIBSBML_NE_NETWORK_ELEMENT_BUILDER_H

#include "libsbml_ne_network_element.h"

MyNetworkElementBase* createCompartment(GraphicalObject* graphicalObject, Style* style);

MyNetworkElementBase* createSpecies(GraphicalObject* graphicalObject, Style* style);

MyNetworkElementBase* createReaction(GraphicalObject* graphicalObject, Style* style);

MyNetworkElementBase* createSpeciesReference(GraphicalObject* graphicalObject, Style* style);

MyNetworkElementBase* createText(GraphicalObject* graphicalObject, Style* style);

#endif
