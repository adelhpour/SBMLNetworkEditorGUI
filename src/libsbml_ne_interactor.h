#ifndef __LIBSBML_NE_INTERACTOR_H
#define __LIBSBML_NE_INTERACTOR_H

#include "src/libsbml_ne_layout.h"
#include "src/libsbml_ne_render.h"
#include "libsbml_ne_network_element.h"
#include <QObject>
#include <QAction>
#include <QGraphicsItem>

class MyInteractor : public QObject {
    Q_OBJECT
    
public:

    MyInteractor(QObject *parent = nullptr);
    
    QList<QAction*> createMenuActions();
    
    bool isReadyToLoad();
    
    const QString getCurrentFileName();
    
    bool displayAskForSaveMessage();
    
    int createNetwork(const QString& fileName);
    
    int exportNetwork(const QString& fileName);
    
    void updateNetwork();
    
    QList<MyNetworkElementBase*> networkElements();
    
    void clearNetworkElements();
    
    int loadSBMLDocument(const QString& fileName);
    
    SBMLDocument* document();
    
    const bool& isDocumentModified() {return _isDocumentModified; };
    
    Layout* layout();
    
    GlobalRenderInformation* globalRenderInformation();
    
    LocalRenderInformation* localRenderInformation();
    
    void addElementsToNetwork();
    
    void addComparmtent(GraphicalObject* graphicalObject);
    
    void addSpecies(GraphicalObject* graphicalObject);
    
    void addReaction(GraphicalObject* graphicalObject);
    
    void addSpeciesReference(GraphicalObject* graphicalObject);
    
    void addText(GraphicalObject* graphicalObject);
    
    void addNetworkElement(MyNetworkElementBase* element);
    
signals:
    
    void loadedSuccessfully(const QString&);
    
    void notLoadedSuccessfully(const QString&);
    
    void askForSetSaveActionEnabled(const bool&);
    
    void askForSetExportActionEnabled(const bool&);
    
    void askForSetSceneExtents(const QRectF&);
    
    void askForSetSceneBackgroundColor(const QBrush&);
    
    void askForAddGraphicsItem(QGraphicsItem* item);
    
    void askForRemoveGraphicsItem(QGraphicsItem* item);
    
    void askForExportSceneFigure(const QString&);
    
    void askForClearScene();
    
    void savedSuccessfully(const QString&);
    
    void notSavedSuccessfully(const QString&);
    
    void documentIsModified();
    
    void askForDisplayFeatureMenu(QWidget*);
    
    void askForRemoveFeatureMenu();
    
private slots:
    
    void readFromFile();
    
    bool saveToFile();
    
    void screenshot();
    
    void setCurrentFileName(const QString& fileName);
    
    void displayFailedMessage(const QString& text);
    
    void setDocumentModified(const bool& isModified);
    
    const QRectF networkExtents();
    
    const QBrush networkBackgroundColor();
    
    SBase* getModelEntity(const QString& enitityId);
    
    GraphicalObject* getGraphicalObject(const QString& graphicalObjectId);

    QList<QWidget*> getAssociatedTextsMenu(const QString& graphicalObjectId);
    
    ColorDefinition* getColorDefinition(const QString& colorId);
    
    GradientBase* getGradientDefinition(const QString& gradientId);
    
    LineEnding* getLineEnding(const QString& lineEndingId);
    
protected:
    QList<QAction*> _menuActions;
    QString _currentFileName;
    QList<MyNetworkElementBase*> _networkElements;
    SBMLDocument* _document;
    bool _isDocumentModified;
    
};

void updateExtents(QRectF& extents, const QRectF& elementExtents);

#endif
