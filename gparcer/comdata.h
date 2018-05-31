#ifndef COMDATA_H
#define COMDATA_H

#include "links/ComDataReq_t.h"
#include "gparcer/sgcode.h"

#include "profiles/profile.h"


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

    void buildGgroup();

    void buildMgroup();

    void buildG0command();

    void setParam_X(sGparam* param);

};

#endif // COMDATA_H
