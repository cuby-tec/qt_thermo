#include "myglobal.h"

#include "qcustomplot.h"


///----------------- vars


int MyGlobal::mglobal = 0;

uint MyGlobal::requestIndex = 0;

QMutex MyGlobal::mutex;

bool MyGlobal::useTermoLog = true;

//const QString G_logfileDir(QDir::homePath()+"/tmp");

QString MyGlobal::logfileDir = QString(QDir::homePath()+"/tmp");

QString MyGlobal::profilefileDir = QString(QDir::currentPath());


QString MyGlobal::message4("File dos't selected.");

QString MyGlobal::message5("File corrupted.");

QString MyGlobal::logfileDelimiter(";");

QString MyGlobal::comment("#");

uint32_t MyGlobal::commandIndex = 1;


MyGlobal::MyGlobal()
{
//    MyGlobal::mglobal = 0;
//    sglobal.logfileDir = G_logfileDir;
}
void
MyGlobal::mPrint(QString line)
{
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin
    print << line;
}
