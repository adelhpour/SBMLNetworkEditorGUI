#ifndef __LIBSBML_NE_MAIN_WINDOW_H
#define __LIBSBML_NE_MAIN_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class MyMainWindow: public QMainWindow {
    Q_OBJECT
    
public:
    
    explicit MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    
    QWidget* view();
    QObject* interactor();
    QAction* getMenuBarAction(const QString& actionIconText);
    
private slots:
    
    void setSaveActionEnabled(const bool& enabled);
    
    void setExportActionEnabled(const bool& enabled);
    
protected:
    void setWidgets();
    void setInteractions();
    
    QWidget* _view;
    QObject* _interactor;
    QList<QAction*> _menuActions;
};

#endif
