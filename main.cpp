#include "mainwindow.h"
#include <QApplication>
#include "myglobal.h"


QMutex thermo_gmutex;

MyGlobal mglobal;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
