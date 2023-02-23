#include "libsbml_ne_text.h"
#include "libsbml_ne_element_graphics_item.h"

MyText::MyText(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

const QString MyText::getType() {
    return QString("Text");
}

const QString MyText::getId() {
    return QString();
}

void MyText::updateGraphicsItem() {
    ((MyElementGraphicsItem*)_graphicsItem)->clear();
    QString plaintText;
    if (((TextGlyph*)_graphicalObject)->isSetText())
        plaintText = QString(((TextGlyph*)_graphicalObject)->getText().c_str());
    else if (((TextGlyph*)_graphicalObject)->isSetOriginOfTextId()) {
        SBase* entity = emit askForModelEntity(QString(((TextGlyph*)_graphicalObject)->getOriginOfTextId().c_str()));
        if (entity)
            plaintText = QString(entity->getId().c_str());
    }
    else if (((TextGlyph*)_graphicalObject)->isSetGraphicalObjectId()) {
        GraphicalObject* graphicalObject = emit askForGraphicalObject(QString(((TextGlyph*)_graphicalObject)->getGraphicalObjectId().c_str()));
        if (graphicalObject) {
            if (graphicalObject->isSetName())
                plaintText = QString(graphicalObject->getName().c_str());
            else
                plaintText = QString(graphicalObject->getId().c_str());
        }
    }
       
    if (!plaintText.isEmpty())
        ((MyElementGraphicsItem*)_graphicsItem)->addTextGraphicsItem(_style->getGroup(), _graphicalObject->getBoundingBox(), plaintText);
}
