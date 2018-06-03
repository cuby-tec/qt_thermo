#ifndef COMDATA_H
#define COMDATA_H

#include "links/ComDataReq_t.h"
#include "gparcer/sgcode.h"

#include "profiles/profile.h"
#include "coordinatus.h"
#include "step_motor/stepmotor.h"
#include "step_motor/controller.h"
#include "step_motor/block_state_t.h"

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

    block_state blocks[N_AXIS];

    StepMotor* motor;


    void calculateAccel();

    void buildGgroup();

    void buildMgroup();

    void buildG0command();

    void setParam_coord(sGparam* param);

    void initWorkAray();

    bool isPlaneHasSteps();

    void setSpeedLeve();

};

#endif // COMDATA_H
