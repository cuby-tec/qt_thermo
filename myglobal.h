#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QTextStream>
#include <QDir>



class MyGlobal
{
public:
    MyGlobal();

    static int mglobal;

    static uint requestIndex;

    static QMutex mutex;

    static bool useTermoLog;    // Вести или не вести лог температурного датчика Hotend.

    static QString logfileDir;

    static QString logfileDelimiter;

    static QString comment;

    static void mPrint(QString line);

    static QString profilefileDir;


    static QString message4;

    static QString message5;

    //-------- exchange

    static u_int32_t commandIndex;

};

#endif // MYGLOBAL_H
