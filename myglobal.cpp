#include "myglobal.h"

int MyGlobal::mglobal = 0;

uint MyGlobal::requestIndex = 0;

QMutex MyGlobal::mutex;


MyGlobal::MyGlobal()
{
//    MyGlobal::mglobal = 0;
}
void
MyGlobal::mPrint(QString line)
{
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin
    print << line;
}
