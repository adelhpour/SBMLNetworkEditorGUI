#include "libsbml_ne_text.h"
#include "libsbml_ne_element_graphics_item.h"
#include "libsbml_ne_feature_menu.h"
#include <QGridLayout>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

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
    if (isSetText(_graphicalObject))
        plaintText = QString(getText(_graphicalObject).c_str());
    else if (isSetOriginOfTextId(_graphicalObject)) {
        SBase* entity = emit askForModelEntity(QString(getOriginOfTextId(_graphicalObject).c_str()));
        if (entity)
            plaintText = QString(entity->getId().c_str());
    }
    else if (isSetGraphicalObjectId(_graphicalObject)) {
        GraphicalObject* graphicalObject = emit askForGraphicalObject(QString(getGraphicalObjectId(_graphicalObject).c_str()));
        if (graphicalObject) {
            if (isSetName(graphicalObject))
                plaintText = QString(getName(graphicalObject).c_str());
            else
                plaintText = QString(LIBSBML_NETWORKEDITOR_CPP_NAMESPACE::getId(graphicalObject).c_str());
        }
    }
       
    if (!plaintText.isEmpty())
        ((MyElementGraphicsItem*)_graphicsItem)->addTextGraphicsItem(getRenderGroup(_style), getBoundingBox(_graphicalObject), plaintText);
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
        QWidget* boundingBoxMenu = new MyBoundingBoxMenu(getBoundingBox(_graphicalObject));
        connect(boundingBoxMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(boundingBoxMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(boundingBoxMenu, "BoundingBox");

        // text features
        QWidget* textFeaturesMenu = new MyTextFeatureMenu(getRenderGroup(_style));
        connect(textFeaturesMenu, SIGNAL(isUpdated()), this, SIGNAL(isUpdated()));
        connect(textFeaturesMenu, SIGNAL(isUpdated()), this, SLOT(updateGraphicsItem()));
        featureMenuTree->addBranchWidget(textFeaturesMenu, "Features");

        contentLayout->addWidget(featureMenuTree, contentLayout->rowCount(), 0, 1, 2);
    }

    elementFeatureMenu->setFixedWidth(400);

    return elementFeatureMenu;
}

QWidget* MyText::createPlainTextMenu() {
    if (isSetText(_graphicalObject))
        return new MyPlainTextMenu(_graphicalObject);
    if (isSetGraphicalObjectId(_graphicalObject)) {
        GraphicalObject* associatedGraphicalObject = askForGraphicalObject(QString(getGraphicalObjectId(_graphicalObject).c_str()));
        if (associatedGraphicalObject)
            return new MyPlainTextMenu(associatedGraphicalObject);
    }
    if (isSetOriginOfTextId(_graphicalObject)) {
        SBase* associatedModelEntity = askForModelEntity(QString(getOriginOfTextId(_graphicalObject).c_str()));
        if (associatedModelEntity)
            return new MyPlainTextMenu(associatedModelEntity);
    }

    return NULL;
}
