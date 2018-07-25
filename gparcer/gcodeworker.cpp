/**
  File : gcodeworker.c
  Company: CUBY,Ltd
  date: 25.05.2018
 */


#include "gcodeworker.h"

#include <string.h>
//#include <cstring>

#include <QDebug>

//#include "gParcer.h"
//#include <QByteArray>
#include <QFile>
#include <QFileInfo>

#include <QTextStream>

#include <QtGlobal>
#include "lexer.h"
#include "gparcer/comdata.h"



GcodeWorker::GcodeWorker()
{

}




void
GcodeWorker::fileOpen(QString filename)
{

	char buffer[128];
	int result;

    uint linecounter = 0;

	sGcode gcode;
	sGcode* dst = &gcode;

	Lexer* lexer = new Lexer(dst);

	ComData* req_builder = new ComData();

	QFile file(filename);

	// Прочитать файл для проверки на наличие ошибок.

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {

        memset(dst,0,sizeof(sGcode));

    	QString line = in.readLine();
        result = lexer->parcer(line);

         qDebug()<<__FILE__<<":"<<__LINE__<<": line:"<<line;

        if(result<=0){
            Q_ASSERT(result>=0);
            continue;
        }
        //checkBox_immediately
        req_builder->buildComData(dst,true);


        linecounter++;
    }
qDebug()<<__FILE__<<":"<<__LINE__ <<"\tlines:"<<linecounter;


    delete(lexer);
//    delete(req_builder);

    fileClose();
//---------------------------- exit parcing

//     fclose(flog);

// /home/walery/Документы/3d-printer/ragel/exmple.gcode


/*
    QFileInfo floginfo(__log);
    qDebug() << "Scanning finished. Log file size:" << floginfo.size() ;
*/

}

void
GcodeWorker::fileClose()
{
    fp.close();
     qDebug() << "File closed.";

}


