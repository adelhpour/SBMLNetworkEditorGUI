#include "libsbml_ne_main_window.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow* mainWindow = new MyMainWindow();
    mainWindow->show();
    return a.exec();
}

