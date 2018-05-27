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
    int state;

#ifdef STD
    char buffer[128];
    char tmpbuffer[256];


    std::string fname = filename.toStdString();
    strncpy(buffer,fname.data(),sizeof(buffer)-1);

    QString __log = QString("/home/walery/tmp/gParcer.log");
    std::string _log = __log.toStdString();
#endif

    initGparcer();

//------------------------- begen parcing
    fp.setFileName(filename);
    if(!fp.open(QIODevice::ReadOnly | QIODevice::Text)){
        //TODO Exception
        qDebug() << "File Error:" << filename;
        return;
    }

    clear_sgcode();


    state = scanner();

    while(state!=3 && !fsm.eofile)
    {
        if(sgcode.line != 0){
            clear_sgcode();
        }
        switch (state)
        {
        case 4:
            fsm.lenfile = fp.read(fsm.buf+fsm.have,fsm.space);
            state = scanner();
            break;

        case 1:
            state = scanner();
            break;

        case 3:
            if ( fsm.eofile ){
                qDebug() << "End of file: lenfile:" << fsm.lenfile << "  have:" << fsm.have;
                break;
            }
            break;

        }// switch
    }


    fp.close();
     qDebug() << "File closed.";
//---------------------------- exn parcing

#ifdef STD
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
            if(sgcode.param_number>0)
                qDebug() << "sGcode.param_number:" << sgcode.param_number;
            else
                qDebug() << "sGcode.param_number:" << "0";

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
#endif



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

