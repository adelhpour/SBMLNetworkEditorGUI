#include "libsbml_ne_interactor.h"
#include "libsbml_ne_network_element_builder.h"
#include <QFileDialog>
#include <QMessageBox>

using namespace LIBSBML_NETWORKEDITOR_CPP_NAMESPACE;

// MyInteractor

MyInteractor::MyInteractor(QObject *parent) : QObject(parent) {
    _document = NULL;
    _isDocumentModified = false;
    
    connect(this, SIGNAL(loadedSuccessfully(const QString&)), this, SLOT(setCurrentFileName(const QString&)));
    connect(this, SIGNAL(savedSuccessfully(const QString&)), this, SLOT(setCurrentFileName(const QString&)));
    connect(this, SIGNAL(notLoadedSuccessfully(const QString&)), this, SLOT(displayFailedMessage(const QString&)));
    connect(this, SIGNAL(notSavedSuccessfully(const QString&)), this, SLOT(displayFailedMessage(const QString&)));
    connect(this, SIGNAL(documentIsModified(const bool&)), this, SLOT(setDocumentModified(const bool&)));
    connect(this, SIGNAL(documentIsModified(const bool&)), this, SIGNAL(askForSetSaveActionEnabled(const bool&)));
}

QList<QAction*> MyInteractor::createMenuActions() {
    QList<QAction*> actions;
    
    QAction* action = new QAction(tr("&Open"), this);
    action->setShortcuts(QKeySequence::Open);
    action->setStatusTip(tr("Open an XML file"));
    connect(action, &QAction::triggered, this, &MyInteractor::readFromFile);
    actions.push_back(action);
    
    action = new QAction(tr("&Save"), this);
    action->setShortcuts(QKeySequence::Save);
    action->setStatusTip(tr("Save the file with the enetered file name"));
    action->setEnabled(false);
    connect(action, &QAction::triggered, this, &MyInteractor::saveToFile);
    actions.push_back(action);
    
    action = new QAction(tr("Export as &PDF"), this);
    action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    action->setStatusTip(tr("Export a drawing of the model as a PDF file"));
    action->setEnabled(false);
    connect(action, &QAction::triggered, this, &MyInteractor::screenshot);
    actions.push_back(action);
    
    action = new QAction(tr("&Exit"), this);
    action->setShortcuts(QKeySequence::Quit);
    action->setStatusTip(tr("Exit the application"));
    //connect(action, &QAction::triggered, this, SLOT(askforExit()));
    actions.push_back(action);
    
    return actions;
}

void MyInteractor::readFromFile() {
    if (isReadyToLoad()) {
        QString fileName = QFileDialog::getOpenFileName(NULL, "Select the SBML File", ".", " xml files (*.xml)");
        if (!fileName.isEmpty()) {
            if (!createNetwork(fileName)) {
                emit loadedSuccessfully(fileName);
                emit askForSetExportActionEnabled(true);
                return;
            }
        }
        emit notLoadedSuccessfully("The model could not be opened");
        emit askForSetExportActionEnabled(false);
    }
}

bool MyInteractor::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File", getCurrentFileName(), tr("xml files (*.xml)"));
    if (!fileName.isEmpty()) {
        if (exportNetwork(fileName)) {
            emit savedSuccessfully(fileName);
            emit documentIsModified(false);
            return true;
        }
    }
    emit notSavedSuccessfully("The model could not be saved");
    
    return false;
}

void MyInteractor::screenshot() {
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save PDF File", QFileInfo(getCurrentFileName()).baseName() + "_drawing", "(*.pdf)");
    
    if (!fileName.isEmpty())
        emit askForExportSceneFigure(fileName);
}

bool MyInteractor::isReadyToLoad() {
    emit askForRemoveFeatureMenu();
    if (isDocumentModified())
        return displayAskForSaveMessage();
    
    return true;
}

const QString MyInteractor::getCurrentFileName() {
    return _currentFileName;
}

void MyInteractor::setCurrentFileName(const QString& fileName) {
    _currentFileName = fileName;
}

bool MyInteractor::displayAskForSaveMessage() {
    QMessageBox* askForSaveMessageBox =  new QMessageBox();
    askForSaveMessageBox->setWindowTitle("Save Action");
    askForSaveMessageBox->setText("The current SBML document has been modified.");
    askForSaveMessageBox->setInformativeText("Do you want to save your changes?");
    askForSaveMessageBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    askForSaveMessageBox->setDefaultButton(QMessageBox::Save);
    int answer = askForSaveMessageBox->exec();
    if (answer == QMessageBox::Save)
        return saveToFile();
    else if (answer == QMessageBox::Discard)
        return true;
    
    return false;
}

void MyInteractor::displayFailedMessage(const QString& text) {
    QMessageBox* failedMessageBox = new QMessageBox();
    failedMessageBox->setWindowTitle("Failed");
    failedMessageBox->setText(text);
    failedMessageBox->setIcon(QMessageBox::Critical);
    failedMessageBox->exec();
}

int MyInteractor::createNetwork(const QString& fileName) {
    if (!loadSBMLDocument(fileName)) {
        updateNetwork();
        return 0;
    }
    
    return -1;
}

int MyInteractor::exportNetwork(const QString& fileName) {
    return writeSBMLToFile(document(), fileName.toStdString().c_str());
}

void MyInteractor::updateNetwork() {
    clearNetworkElements();
    emit askForClearScene();
    addElementsToNetwork();
    emit askForSetSceneExtents(networkExtents());
    emit askForSetSceneBackgroundColor(networkBackgroundColor());
}

QList<MyNetworkElementBase*> MyInteractor::networkElements() {
    return _networkElements;
}

void MyInteractor::clearNetworkElements() {
    MyNetworkElementBase* element = NULL;
    while(_networkElements.size()) {
        element = _networkElements.takeLast();
        emit askForRemoveGraphicsItem(element->graphicsItem());
        delete element;
    }
}

int MyInteractor::loadSBMLDocument(const QString& fileName) {
    _document = readSBMLFromFile(fileName.toStdString().c_str());
    if (_document && _document->getModel()) {
        setCurrentFileName(fileName);
        return 0;
    }
    
    return -1;
}

SBMLDocument* MyInteractor::document() {
    return _document;
}

void MyInteractor::setDocumentModified(const bool& isModified) {
    _isDocumentModified = isModified;
}

Layout* MyInteractor::layout() {
    Layout* layout = NULL;
    ListOfLayouts* listOfLayouts = getListOfLayouts(document());
    if (listOfLayouts && listOfLayouts->size())
        layout = listOfLayouts->get(0);
    else {
        layout = createLayout(_document);
        setDefaultLayoutFeatures(document(), layout);
        emit documentIsModified(true);
    }
    
    return layout;
}

GlobalRenderInformation* MyInteractor::globalRenderInformation() {
    GlobalRenderInformation* globalRenderInformation = NULL;
    ListOfGlobalRenderInformation* listOfGlobalRenderInformation =  getListOfGlobalRenderInformation(document());
    if (listOfGlobalRenderInformation && listOfGlobalRenderInformation->size())
        globalRenderInformation = listOfGlobalRenderInformation->get(0);
    else {
        globalRenderInformation = createGlobalRender(_document);
        setDefaultGlobalRenderFeatures(document(), globalRenderInformation);
        emit documentIsModified(true);
    }
    
    return globalRenderInformation;
}

LocalRenderInformation* MyInteractor::localRenderInformation() {
    LocalRenderInformation* localRenderInformation = NULL;
    ListOfLocalRenderInformation* listOfLocalRenderInformation = getListOfLocalRenderInformation(layout());
    if (listOfLocalRenderInformation && listOfLocalRenderInformation->size())
        localRenderInformation = listOfLocalRenderInformation->get(0);
    else {
        localRenderInformation = createLocalRender(layout());
        setDefaultLocalRenderFeatures(document(), layout(), localRenderInformation);
        emit documentIsModified(true);
    }
    
    return localRenderInformation;
}

void MyInteractor::addElementsToNetwork() {
    for (unsigned int i = 0; i < layout()->getNumCompartmentGlyphs(); i++)
        addComparmtent(layout()->getCompartmentGlyph(i));
    for (unsigned int i = 0; i < layout()->getNumSpeciesGlyphs(); i++)
        addSpecies(layout()->getSpeciesGlyph(i));
    for (unsigned int i = 0; i < layout()->getNumReactionGlyphs(); i++) {
        ReactionGlyph* reactionGlyph = layout()->getReactionGlyph(i);
        addReaction(reactionGlyph);
        for (unsigned int j = 0; j < reactionGlyph->getNumSpeciesReferenceGlyphs(); j++)
            addSpeciesReference(reactionGlyph->getSpeciesReferenceGlyph(j));
    }
    for (unsigned int i = 0; i < layout()->getNumTextGlyphs(); i++)
        addText(layout()->getTextGlyph(i));
}

void MyInteractor::addComparmtent(GraphicalObject* graphicalObject) {
    Style* style = findStyle(localRenderInformation(), graphicalObject);
    if (!style)
        style = findStyle(globalRenderInformation(), graphicalObject, "COMPARTMENTGLYPH");
    
    if (style)
        addNetworkElement(createCompartment(graphicalObject, style));
}

void MyInteractor::addSpecies(GraphicalObject* graphicalObject) {
    Style* style = findStyle(localRenderInformation(), graphicalObject);
    if (!style)
        style = findStyle(globalRenderInformation(), graphicalObject, "SPECIESGLYPH");
    
    if (style)
        addNetworkElement(createSpecies(graphicalObject, style));
}

void MyInteractor::addReaction(GraphicalObject* graphicalObject) {
    Style* style = findStyle(localRenderInformation(), graphicalObject);
    if (!style)
        style = findStyle(globalRenderInformation(), graphicalObject, "REACTIONGLYPH");
    
    if (style)
        addNetworkElement(createReaction(graphicalObject, style));
}

void MyInteractor::addSpeciesReference(GraphicalObject* graphicalObject) {
    Style* style = findStyle(localRenderInformation(), graphicalObject);
    if (!style)
        style = findStyle(globalRenderInformation(), graphicalObject, "SPECIESREFERENCEGLYPH");
    
    if (style) {
        MyNetworkElementBase* element = createSpeciesReference(graphicalObject, style);
        connect(element, SIGNAL(askForLineEnding(const QString&)), this, SLOT(getLineEnding(const QString&)));
        addNetworkElement(element);
    }
}

void MyInteractor::addText(GraphicalObject* graphicalObject) {
    Style* style = findStyle(localRenderInformation(), graphicalObject);
    if (!style)
        style = findStyle(globalRenderInformation(), graphicalObject, "TEXTGLYPH");
    
    if (style) {
        MyNetworkElementBase* element = createText(graphicalObject, style);
        connect(element, SIGNAL(askForGraphicalObject(const QString&)), this, SLOT(getGraphicalObject(const QString&)));
        connect(element, SIGNAL(askForModelEntity(const QString&)), this, SLOT(getModelEntity(const QString&)));
        addNetworkElement(element);
    }
}

void MyInteractor::addNetworkElement(MyNetworkElementBase* element) {
    connect(element, SIGNAL(askForColorDefinition(const QString&)), this, SLOT(getColorDefinition(const QString&)));
    connect(element, SIGNAL(askForGradientDefinition(const QString&)), this, SLOT(getGradientDefinition(const QString&)));
    connect(element, SIGNAL(askForDisplayFeatureMenu(QWidget*)), this, SIGNAL(askForDisplayFeatureMenu(QWidget*)));
    
    element->updateGraphicsItem();
    emit askForAddGraphicsItem(element->graphicsItem());
    _networkElements.push_back(element);
}

const QRectF MyInteractor::networkExtents() {
    QRectF extents;
    for (MyNetworkElementBase* element : networkElements())
        updateExtents(extents, element->getExtents());
    
    return extents;
}

const QBrush MyInteractor::networkBackgroundColor() {
    if (globalRenderInformation() && globalRenderInformation()->isSetBackgroundColor())
        return QBrush(QColor(globalRenderInformation()->getBackgroundColor().c_str()));
    
    return Qt::NoBrush;
}

SBase* MyInteractor::getModelEntity(const QString& enitityId) {
    Model* model = document()->getModel();
    if (document()->getModel()->getCompartment(enitityId.toStdString()))
        return document()->getModel()->getCompartment(enitityId.toStdString());
    else if (document()->getModel()->getSpecies(enitityId.toStdString()))
        return document()->getModel()->getSpecies(enitityId.toStdString());
    else if (document()->getModel()->getReaction(enitityId.toStdString()))
        return document()->getModel()->getReaction(enitityId.toStdString());
    
    return NULL;
}

GraphicalObject* MyInteractor::getGraphicalObject(const QString& graphicalObjectId) {
    if (layout()->getCompartmentGlyph(graphicalObjectId.toStdString()))
        return layout()->getCompartmentGlyph(graphicalObjectId.toStdString());
    else if (layout()->getSpeciesGlyph(graphicalObjectId.toStdString()))
        return layout()->getSpeciesGlyph(graphicalObjectId.toStdString());
    else if (layout()->getReactionGlyph(graphicalObjectId.toStdString()))
        return layout()->getReactionGlyph(graphicalObjectId.toStdString());
    
    return NULL;
}

ColorDefinition* MyInteractor::getColorDefinition(const QString& colorId) {
    ColorDefinition* colorDefinition = NULL;
    if (globalRenderInformation()->getColorDefinition(colorId.toStdString()))
        colorDefinition =  globalRenderInformation()->getColorDefinition(colorId.toStdString());
    if (localRenderInformation()->getColorDefinition(colorId.toStdString()))
        colorDefinition = localRenderInformation()->getColorDefinition(colorId.toStdString());
    
    return colorDefinition;
}

GradientBase* MyInteractor::getGradientDefinition(const QString& gradientId) {
    GradientBase* gradientBase = NULL;
    if (globalRenderInformation()->getGradientDefinition(gradientId.toStdString()))
        gradientBase = globalRenderInformation()->getGradientDefinition(gradientId.toStdString());
    if (localRenderInformation()->getGradientDefinition(gradientId.toStdString()))
        gradientBase = localRenderInformation()->getGradientDefinition(gradientId.toStdString());
    
    return gradientBase;
}

LineEnding* MyInteractor::getLineEnding(const QString& lineEndingId) {
    LineEnding* lineEnding = NULL;
    if (globalRenderInformation()->getLineEnding(lineEndingId.toStdString()))
        lineEnding = globalRenderInformation()->getLineEnding(lineEndingId.toStdString());
    if (localRenderInformation()->getLineEnding(lineEndingId.toStdString()))
        lineEnding = localRenderInformation()->getLineEnding(lineEndingId.toStdString());
    
    return lineEnding;
}

void updateExtents(QRectF& extents, const QRectF& elementExtents) {
    if (elementExtents.x() < extents.x())
        extents.setX(elementExtents.x());
    if (elementExtents.y() < extents.y())
        extents.setY(elementExtents.y());
    if (extents.x() + extents.width() < elementExtents.x() + elementExtents.width())
        extents.setWidth(extents.width() + (elementExtents.x() + elementExtents.width() - extents.x() - extents.width()));
    if (extents.y() + extents.height() < elementExtents.y() + elementExtents.height())
        extents.setHeight(extents.height() + (elementExtents.y() + elementExtents.height() - extents.y() - extents.height()));
}
