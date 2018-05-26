/**
  File : gcodeworker.c
  Company: CUBY,Ltd
  date: 25.05.2018
 */




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
    char tmpbuffer[256];

    int state;

    std::string fname = filename.toStdString();
    strncpy(buffer,fname.data(),sizeof(buffer)-1);

    QString __log = QString("/home/walery/tmp/gParcer.log");
    std::string _log = __log.toStdString();

    initGparcer();

    fp = std::fopen(buffer, "r");
    if(fp!=NULL)
    {

        clear_sgcode();

        //------------

        state = scanner();

        switch (state)
        {
        case 4:
            //fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
            fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
//            qDebug() << "gcodeworker.c[63] buf:"<< fsm.buf;
            state = scanner();

            qDebug() <<"sGcode.comment:"<< sgcode.comment;
            qDebug() << "sGcode.group:" << sgcode.group;
            qDebug() << "sGcode.line:" << sgcode.line ;
            qDebug() << "fsm.cs:" <<fsm.cs ;
            qDebug() << "fsm.space :" <<fsm.space ;
            qDebug() << "fsm.have :" <<fsm.have ;
            qDebug() << "fsm.buf :" <<fsm.buf[0] ;
            qDebug() << "=============================";


            break;
        }


        //---------------


        fclose(fp);

        qDebug() << "File opened and closed." ;
    }else{
        qDebug()<< "File error:"<<buffer;
        return;
    }


    // debug
    fp = std::fopen(buffer, "r");
    if(fp != NULL)
    {
        int len_t = fread(tmpbuffer,1,sizeof(tmpbuffer),fp);

        qDebug() << "tmp.buf :" <<tmpbuffer[0] ;

        fclose(fp);
    }

/*
    QFile file(buffer);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qint64 tmplen = file.read(tmpbuffer,sizeof(tmpbuffer));

      qDebug() << "tmp.buf :" <<tmpbuffer[0] ;

      file.close();

    }
*/
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


//     fclose(fp);
//     fclose(flog);

// /home/walery/Документы/3d-printer/ragel/exmple.gcode
/*    // not working.
     if(parcerFileOpen(buffer))
     {
         parcerFileClose();
         qDebug() << "Opened:" << __LC_NAME;

     }
*/
/*
    QFileInfo floginfo(__log);


     qDebug() << "Scanning finished. Log file size:" << floginfo.size() ;
*/


//     parcerFileClose();

}

