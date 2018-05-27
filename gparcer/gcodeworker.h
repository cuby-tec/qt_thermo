/**
  File : gcodeworker.h
  Company: CUBY,Ltd
  date: 25.05.2018
 */


#ifndef GCODEWORKER_H
#define GCODEWORKER_H

//#include <cstdio>
#include <QFile>
#include <QString>


class GcodeWorker
{
public:
    GcodeWorker();

    void fileOpen(QString filename);


private:

//    std::FILE* fp;
//    std::FILE* flog;
    QFile fp;
    QFile flog;

};

#endif // GCODEWORKER_H
