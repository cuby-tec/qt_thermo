#ifndef COMDATA_H
#define COMDATA_H

#include "links/ComDataReq_t.h"
#include "gparcer/sgcode.h"

#include "profiles/profile.h"
#include "coordinatus.h"

#include <QChar>

class ComData
{
public:
    ComData();

    ComDataReq_t* getRequest()
    {
        return &request;
    }

    void setRequestNumber(uint32_t num){
        a = 5;
        request.requestNumber = num;
    }


    ComDataReq_t* build(sGcode* sgcode);

private:

    ComDataReq_t request;

    int a;

    sGcode* sgCode;

    Profile* profile;

    Coordinatus* cord;

    void buildGgroup();

    void buildMgroup();

    void buildG0command();

    void setParam_coord(sGparam* param);

    void initWorkAray();

};

#endif // COMDATA_H
