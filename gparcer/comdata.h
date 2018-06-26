#ifndef COMDATA_H
#define COMDATA_H

#include "links/ComDataReq_t.h"
#include "gparcer/sgcode.h"

#include "profiles/profile.h"
#include "coordinatus.h"
//#include "step_motor/stepmotor.h"
#include "step_motor/controller.h"
#include "step_motor/block_state_t.h"

#include <QChar>

#define DIRECTION_BIT    	1  // Port X Pin X
#define STEP_BIT         	2  // Port X pin X


#define X_DIRECTION_BIT    	0  // Port X Pin X
#define X_STEP_BIT         	1  // Port X pin X

#define Y_DIRECTION_BIT    	2  // Port Y Pin Y
#define Y_STEP_BIT         	3  // Port Y pin Y

#define Z_DIRECTION_BIT    	4  // Port Z Pin Z
#define Z_STEP_BIT         	5  // Port Z pin Z

#define E_DIRECTION_BIT    	6  // Port Z Pin Z
#define E_STEP_BIT         	7  // Port Z pin Z


#define X_DIRECTION_MASK 		(1<<Y_DIRECTION_BIT) // All direction bits
#define X_STEP_MASK 			(1<<Y_STEP_BIT) // All step bits

#define Y_DIRECTION_MASK 		(1<<Y_DIRECTION_BIT) // All direction bits
#define Y_STEP_MASK 			(1<<Y_STEP_BIT) // All step bits

#define Z_DIRECTION_MASK 		(1<<Y_DIRECTION_BIT) // All direction bits
#define Z_STEP_MASK 			(1<<Y_STEP_BIT) // All step bits

#define E_DIRECTION_MASK 		(1<<Y_DIRECTION_BIT) // All direction bits
#define E_STEP_MASK 			(1<<Y_STEP_BIT) // All step bits




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

    double_t getPath_mm(uint8_t axis, int32_t steps) { return (controller->getPath_mm(axis, steps)); }

    Controller* getController(){ return controller; }


private:

    ComDataReq_t request;


    Controller* controller;


    int a;

    sGcode* sgCode;

    Profile* profile;

    Coordinatus* cord;

//    block_state blocks[N_AXIS];

//    StepMotor* motor;


    void calculateAccel();

    void buildGgroup();

    void buildMgroup();

    void buildG0command();

    void setParam_coord(sGparam* param);

    void setWorkValue(QString value, size_t axis_num);

    void initWorkAray();

    bool isPlaneHasSteps();

    void setProfileValue();

    void setDirection_bits();

    void planner_recalculate();

    void buildComdata();




};

#endif // COMDATA_H
