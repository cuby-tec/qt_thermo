#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QTextStream>



class MyGlobal
{
public:
    MyGlobal();

    static int mglobal;

    static uint requestIndex;

    static QMutex mutex;

    static void mPrint(QString line);

};

#endif // MYGLOBAL_H
