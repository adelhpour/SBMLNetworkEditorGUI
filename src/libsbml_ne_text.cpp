#include "libsbml_ne_text.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

MyText::MyText(GraphicalObject* graphicalObject, Style* style, const qreal& graphicsItemZValue) : MyNetworkElementBase(graphicalObject, style, graphicsItemZValue) {
    
}

const QString MyText::getType() {
    return QString("Text");
}

const QString MyText::getId() {
    return QString();
}

bool MyText::hasAssociatedModelEntity() {
    return false;
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

QWidget* MyText::elementFeatureMenu() {
    QWidget* elementFeatureMenu = MyNetworkElementBase::elementFeatureMenu();
    QGridLayout* contentLayout = (QGridLayout*)(elementFeatureMenu->layout());

    contentLayout->addItem(new MySpacerItem(0, 20), contentLayout->rowCount(), 0, 1, 2);

    // plain text
    QWidget* plainTextMenu = createPlainTextMenu();
    if (plainTextMenu) {
        MyTreeView* featureMenuTree = new MyTreeView(elementFeatureMenu);

        connect(plainTextMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(plainTextMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(plainTextMenu, "PlainText");

        // bounding box
        QWidget* boundingBoxMenu = new MyBoundingBoxMenu(_graphicalObject);
        connect(boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(boundingBoxMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(boundingBoxMenu, "BoundingBox");

        // text features
        QWidget* textFeaturesMenu = new MyTextFeatureMenu(_style->getGroup());
        connect(textFeaturesMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(textFeaturesMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(textFeaturesMenu, "Features");

        contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);
    }

    elementFeatureMenu->setFixedWidth(400);

    return elementFeatureMenu;
}

QWidget* MyText::createPlainTextMenu() {
    if (((TextGlyph*)_graphicalObject)->isSetText())
        return new MyPlainTextMenu((TextGlyph*)_graphicalObject);
    if (((TextGlyph*)_graphicalObject)->isSetGraphicalObjectId()) {
        GraphicalObject* associatedGraphicalObject = askForGraphicalObject(QString(((TextGlyph*)_graphicalObject)->getGraphicalObjectId().c_str()));
        if (associatedGraphicalObject)
            return new MyPlainTextMenu(associatedGraphicalObject);
    }
    if (((TextGlyph*)_graphicalObject)->isSetOriginOfTextId()) {
        SBase* associatedModelEntity = askForModelEntity(QString(((TextGlyph*)_graphicalObject)->getOriginOfTextId().c_str()));
        if (associatedModelEntity)
            return new MyPlainTextMenu(associatedModelEntity);
    }

    return NULL;
}
