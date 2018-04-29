#ifndef EXCHANGE_H
#define EXCHANGE_H

//#include <stdio.h>

//#include from FeeRTOS project.
#include "links/status.h"
#include "links/ComDataReq_t.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE    -1
#endif

#define EXIT_SUCCESS    0

class Exchange
{
public:
    Exchange();

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

private:
    QFile *fp;

    int sendBuffer(uint8_t* buffer, uint32_t size, QFile* fp);

    void buildProfile(sProfile *profile);

    ComDataReq_t comdata;

    Status_t* c_status;

    void print_status(Status_t* c_status);

    void load_defaults(struct sControl* pctl);

};



#endif // EXCHANGE_H
