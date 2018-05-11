/**
  Только обмен даными с Контроллером(Сервером).
 */


#ifndef UUSBEXCHANGE_H
#define UUSBEXCHANGE_H


#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <cstdio>

#include <QDebug>
#include <QMessageBox>

#include <QMutex>

#include "links/status.h"
#include "links/ComDataReq_t.h"
#include "links/profiles/profile.h"

#include <myglobal.h>

extern uint rIndex;

class UsbExchange
{
public:

    UsbExchange();

    ~UsbExchange();

    void buildComData(struct ComDataReq_t* comdata);

     void buildComData(ComDataReq_t *comdata, eOrder order);

     /**
      * params:
      * 	psc - data to be filled.
      * 	i - offset for line number.
      */
     void build_segment_default(struct sSegment* psc, uint32_t i);

     int sendRequest(ComDataReq_t* request);

     void NoOperation();

     Status_t* getStatus() { return c_status; }

     void print_status(Status_t* c_status);

private:
     QFile *fp;

      int sendBuffer(uint8_t* buffer, uint32_t size, QFile* fp);

      int sendBuffer(uint8_t* buffer, uint32_t size, std::FILE* fp);

      void buildProfile(sProfile *sprofile_dst);

      ComDataReq_t comdata;

      Status_t* c_status;

      char buffer2[64];


      void load_defaults(struct sControl* pctl);


};

#endif // UUSBEXCHANGE_H
