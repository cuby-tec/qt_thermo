#include "comdata.h"
#include <string.h>
#include <QString>
#include <QDebug>
#include <QtGlobal>
#include "myglobal.h"

#include <cmath>

//const QString msg3 = "Conversion error.";
//const QString msg4 = "Profile should be selected.";
const char* msg3 = "Conversion error.";
const char* msg4 = "Profile should be selected.";

ComData::ComData()
{

    memset(&request,'\0',sizeof(ComDataReq_t));
//    request.requestNumber = 22;

    profile = Profile::instance();
    cord = Coordinatus::instance();
//    motor = new StepMotor();

    controller = new Controller();


}

void
ComData::setWorkValue(QString value, size_t axis_num)
{
    int i;
    bool ok;
	QString str_val = QString( value );

    i = str_val.indexOf(',');
    if(i>0)
    {
        str_val = str_val.replace(i,1,'.');
    }

    float coord = str_val.toFloat(&ok);
//    if(!ok)
//    {
//        qFatal(msg3);
//    }
    Q_ASSERT(ok);

    if(cord->isAbsolute())
    {
        cord->setWorkValue(axis_num,coord);
    }else{
        float wv = cord->getWorkvalue(axis_num);
        wv += coord;
        cord->setWorkValue(axis_num,wv);
    }


}

void
ComData::setParam_coord(sGparam *param)
{
    size_t axis_num = N_AXIS;

    switch (param->group) {
    case 'X':
       axis_num = X_AXIS;
       setWorkValue(param->value,axis_num);
        break;
    case 'Y':
        axis_num = Y_AXIS;
        setWorkValue(param->value,axis_num);
        break;
    case 'Z':
        axis_num = Z_AXIS;
        setWorkValue(param->value,axis_num);
        break;
    case 'E':
        axis_num = E_AXIS;
        setWorkValue(param->value,axis_num);
        break;
    default:
        break;
    }



}

bool
ComData::isPlaneHasSteps()
{

    float sum = 0.0;

    for(int i=0; i<N_AXIS;i++)
    {
        sum +=  fabs(cord->getCurrentValue(i) - cord->getNextValue(i));
    }

    return (sum != 0);
}


void
ComData::setProfileValue()
{
//setSpeedLevel(block, psettings->seekSpeed);
//    float seekspeed;
    bool ok;

    QString fspeed; // rpm unit
    float speed;

    QString facceleration;
    float acceleration;

//QString fseek = MyGlobal::formatFloat(profile->getHOMING_SEEK_RATE());
//    seekspeed = fseek.toFloat(&ok);
//    Q_ASSERT(ok);


    for(int i=0;i<N_AXIS;i++)
    {
//        block_state* block = &blocks[i];
        block_state* block = &cord->nextBlocks[i];

        switch(i)
        {
        case X_AXIS:
            fspeed = MyGlobal::formatFloat(profile->getX_MAX_RATE());
            facceleration = MyGlobal::formatFloat(profile->getX_ACCELERATION());
            break;

        case Y_AXIS:
            fspeed = MyGlobal::formatFloat(profile->getY_MAX_RATE());
            facceleration = MyGlobal::formatFloat(profile->getY_ACCELERATION());
            break;

        case Z_AXIS:
            fspeed = MyGlobal::formatFloat(profile->getZ_MAX_RATE());
            facceleration = MyGlobal::formatFloat(profile->getZ_ACCELERATION());
            break;

        case E_AXIS:
            fspeed = MyGlobal::formatFloat(profile->getE_MAX_RATE());
            facceleration = MyGlobal::formatFloat(profile->getE_ACCELERATION());
            break;
        }

        speed = fspeed.toFloat(&ok);
        Q_ASSERT(ok);
        block->nominal_speed = speed;

        acceleration = facceleration.toFloat(&ok);
        Q_ASSERT(ok);
        block->acceleration = acceleration;

        qDebug()<<"ComData [171]"<< block->speedLevel;
    }

}


void
ComData::setDirection_bits()
{
    for(int i=0;i<N_AXIS;i++)
    {
//        block_state* block = &blocks[i];
        block_state* block = &cord->nextBlocks[i];
        float_t ds = cord->getNextValue(i) - cord->getCurrentValue(i);

        if(ds>0){
            block->direction_bits |= DIRECTION_BIT<<i;
            block->axis_mask |= STEP_BIT<<i;
        }else if(ds<0){
            block->direction_bits &= ~(DIRECTION_BIT<<i);
            block->axis_mask |= STEP_BIT<<i;
        }else{
            block->axis_mask &= ~(STEP_BIT<<i);
        }

    }
}

//TODO planner_recalculate
void
ComData::planner_recalculate()
{

}


/**
 * @brief ComData::buildG0command
 */
void
ComData::buildG0command()
{

//    float coord;
    bool ok;

    sGparam* gparam;

    sSegment* segment = &request.payload.instrument1_parameter;


    for(int i=0;i<sgCode->param_number;i++)
    {
        gparam = &sgCode->param[i];

//        coord = QString(gparam->value).toFloat(&ok);

        switch (gparam->group)
        {
        case 'X':
        case 'Y':
        case 'Z':
            setParam_coord(gparam);
            break;

        case 'N': // Номер строки
            uint32_t number = QString(gparam->value).toInt(&ok);
            Q_ASSERT(ok);
            segment->head.linenumber = number;
        	break;

//        default:
//            break;
        }

    }

    cord->moveWorkToNext();
    if(!isPlaneHasSteps())
    {
        return;
    }

//    setProfileValue();

//in controller build model acceleration/deceleration
    Recalculate_flag* flag;

    for(int i=0;i<M_AXIS;i++){
    	byte* fl = &cord->nextBlocks[i].recalculate_flag;
    	*fl |= true; // Одиночная команда.
    }


    controller->buildBlock(cord);
        // ступень скорости
//        block->speedLevel = motor->steps_rpm(speed,block->acceleration);

// build ComDataReq_t
    buildComdata();

    //TODO Send Data

}



void
ComData::buildComdata()
{
	ComDataReq_t* req = &request;
	sSegment* segment;
	sControl* control;
    block_state_t* bstates = cord->nextBlocks;

    memset(req,0,sizeof(ComDataReq_t));

	req->requestNumber = 0;//++MyGlobal::requestIndex;// TODO get request number
	req->instruments = 1;

	req->command.order = eoSegment;
	req->command.instrument = 1;
	req->command.reserved = 0;

	segment = &req->payload.instrument1_parameter;

	//------------ payload =============================
	segment->head.linenumber = sgCode->line ;
	segment->head.axis_number = M_AXIS;//0;

	//if(segment->head.reserved == EXIT_CONTINUE)
	//    ms_finBlock = continueBlock;
	//else
	//    ms_finBlock = exitBlock;
	segment->head.reserved &= ~EXIT_CONTINUE;

	for(int i=0;i<M_AXIS;i++)
	{
//		segment->head.axis_mask = 0;
		if(bstates[i].steps>0)
			segment->head.axis_mask |= (1<<i);
		else
			segment->head.axis_mask &= ~(1<<i);
	}
	//======== sControl =========

	for(int i =0;i<M_AXIS;i++){
		control = &segment->axis[i];
		block_state_t* bstate = &bstates[i];

		control->accelerate_until = bstate->accelerate_until;
		control->decelerate_after = bstate->decelerate_after;

		if(bstate->path>0)
			control->direction = forward;
		else
			control->direction = backward;

		control->final_rate = bstate->final_rate;
		control->initial_rate = bstate->initial_rate;
		control->nominal_rate = bstate->nominal_rate;
		control->final_speedLevel = bstate->final_speedLevel;

		control->microsteps = bstate->microstep;

		for(int j=0;j<3;j++){
			control->schem[j] = bstate->schem[j];
		}

		control->steps = bstate->steps;
	}

//TODOH build ComdataReq



}


void
ComData::buildGgroup()
{
    int groupnumber;
    bool ok;

    groupnumber = QString(sgCode->value).toInt(&ok);

    switch (groupnumber) {

    case 0:
    case 1:
        buildG0command();
        break;

    case 2:
        break;

    case 3:
        break;



    default:
        break;
    }

}


void
ComData::buildMgroup()
{
    int groupnumber;
    bool ok;
    groupnumber = QString(sgCode->value).toInt(&ok);

    switch (groupnumber) {
    case 104:

        break;
    case 108:
        break;

    default:
        break;
    }

}

//void
//ComData::buildMgroup()
//{
//    int groupnumber;
//    bool ok;

//    groupnumber = 2;
//}


ComDataReq_t*
ComData::build(sGcode *sgcode)
{
    this->sgCode = sgcode;

//    initWorkAray();
    cord->initWork();

    switch (sgCode->group) {
    case 'G':
        buildGgroup();
        break;

    case 'M':
        buildMgroup();
        break;

    default:
        // somthing wrong.
        break;
    }
    return(&request);
}

void
ComData::initWorkAray()
{
//    cord = Coordinatus::instance();
    cord->initWork();
}
