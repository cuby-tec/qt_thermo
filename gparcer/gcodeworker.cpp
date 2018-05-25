/**
  File : gcodeworker.c
  Company: CUBY,Ltd
  date: 25.05.2018
 */


#include <cstdio>

#include <string.h>
//#include <cstring>

#include <QDebug>


#include "gcodeworker.h"
#include "gParcer.h"

#include <QByteArray>
//#include <QFile>
#include <QFileInfo>

GcodeWorker::GcodeWorker()
{

}

void
GcodeWorker::fileOpen(QString filename)
{
    /*
     *     pFile = std::fopen(fname,"r+");
    if (pFile!=NULL)
    {
     * */
    char buffer[128];

    std::string fname = filename.toStdString();
    strncpy(buffer,fname.data(),sizeof(buffer)-1);

    QString __log = QString("/home/walery/tmp/gParcer.log");
    std::string _log = __log.toStdString();



    fp = std::fopen(buffer, "r");
    if(fp!=NULL)
    {

//        fclose(fp);

        qDebug() << "File opened and closed.";
    }else{
        qDebug()<< "File error:"<<buffer;
        return;
    }

/*
    strncpy(buffer,_log.data(),sizeof(buffer));


    flog = std::fopen(buffer,"w");
    if(flog != NULL)
    {
//        fclose(flog);

        qDebug() << "Log file oopened and closed.";
    }else{
        qDebug()<< "Log file error:"<<buffer;
        return;
    }
*/
    //scanner();


     fclose(fp);
//     fclose(flog);

// /home/walery/Документы/3d-printer/ragel/exmple.gcode
     if(parcerFileOpen(buffer))
     {
         parcerFileClose();
         qDebug() << "Opened:" << __LC_NAME;

     }


    QFileInfo floginfo(__log);


     qDebug() << "Scanning finished. Log file size:" << floginfo.size() ;

}

