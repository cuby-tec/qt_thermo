#include "mainwindow.h"
#include <QApplication>


QMutex thermo_gmutex;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
