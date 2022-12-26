#include "libsbml_ne_network_element_builder.h"
#include "libsbml_ne_compartment.h"
#include "libsbml_ne_species.h"
#include "libsbml_ne_reaction.h"
#include "libsbml_ne_species_reference.h"
#include "libsbml_ne_text.h"

MyNetworkElementBase* createCompartment(GraphicalObject* graphicalObject, Style* style) {
    return new MyCompartment(graphicalObject, style, 0);
}

MyNetworkElementBase* createSpecies(GraphicalObject* graphicalObject, Style* style) {
    return new MySpecies(graphicalObject, style, 3);
}

MyNetworkElementBase* createReaction(GraphicalObject* graphicalObject, Style* style) {
    return new MyReaction(graphicalObject, style, 2);
}

MyNetworkElementBase* createSpeciesReference(GraphicalObject* graphicalObject, Style* style) {
    return new MySpeciesReference(graphicalObject, style, 1);
}

MyNetworkElementBase* createText(GraphicalObject* graphicalObject, Style* style) {
    return new MyText(graphicalObject, style, 4);
}
