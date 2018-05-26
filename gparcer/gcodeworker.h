/**
  File : gcodeworker.h
  Company: CUBY,Ltd
  date: 25.05.2018
 */


#ifndef GCODEWORKER_H
#define GCODEWORKER_H

#include <cstdio>

#include <QString>


class GcodeWorker
{
public:
    GcodeWorker();

    void fileOpen(QString filename);


private:

    std::FILE* fp;
    std::FILE* flog;

};

#endif // GCODEWORKER_H
