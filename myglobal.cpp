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

QString MyGlobal::msg_absolute("Abs");
QString MyGlobal::msg_relative("Rel");

QString MyGlobal::msg_abs_title("Absolute positioning.");
QString MyGlobal::msg_rel_title("Relative positioning.");


QString MyGlobal::logfileDelimiter(";");

QString MyGlobal::comment("#");

uint32_t MyGlobal::commandIndex = 1;

double_t const MyGlobal::PI = 3.1415926536 ;	//3.1415;


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

/*
 *
 *     int i;

    QString str_val = QString( param->value );

    i = str_val.indexOf(',');

    if(i>0)
    {
        str_val = str_val.replace(i,1,'.');
    }
 *
*/
QString
MyGlobal::formatFloat(QString fl)
{
    int i;

    i = fl.indexOf(',');
    if(i>0)
    {
        fl = fl.replace(i,1,'.');
    }
    return fl;
}
