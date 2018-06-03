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
    motor = new StepMotor();

}


void
ComData::setParam_coord(sGparam *param)
{
    bool ok;
    int i;
    size_t axis_num;

    QString str_val = QString( param->value );

    sSegment* segment = &request.payload.instrument1_parameter;

    i = str_val.indexOf(',');


    if(i>0)
    {
        str_val = str_val.replace(i,1,'.');
    }

    switch (param->group) {
    case 'X':
       axis_num = X_AXIS;
        break;
    case 'Y':
        axis_num = Y_AXIS;
        break;
    case 'Z':
        axis_num = Z_AXIS;
        break;
    case 'E':
        axis_num = E_AXIS;
        break;
    default:
        break;
    }


    float coord = str_val.toFloat(&ok);
    if(!ok)
    {
        qFatal(msg3);
    }


    if(cord->isAbsolute())
    {
        cord->setWorkValue(axis_num,coord);
    }else{
        float wv = cord->getWorkvalue(axis_num);
        wv += coord;
        cord->setWorkValue(axis_num,wv);
    }


/*
    QString steps = profile->getX_STEPS();

    i = steps.indexOf(',');

    if(i>0)
    {
        steps.replace(i,1,'.');
    }

//    float_t steps_per_mm = QString( profile->getX_STEPS()).toFloat(&ok);
    float_t steps_per_mm = steps.toFloat(&ok);
    if(!(ok && steps_per_mm>0)){
        qFatal(msg3 + msg4);
    }
    else{
        segment->axis[X_AXIS].steps = coord/steps_per_mm;
    }
*/

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
ComData::setSpeedLeve()
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
        block_state* block = &blocks[i];

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

        // ступень скорости
        block->speedLevel = motor->steps_rpm(speed,block->acceleration);
        qDebug()<<"ComData [171]"<< block->speedLevel;
    }
    //================



//    dt = motor->steps_rpm(500.0,1250);

}

/**
 * @brief ComData::buildG0command
 */
void
ComData::buildG0command()
{

//    float coord;
//    bool ok;
    sGparam* gparam;


    for(int i=0;i<sgCode->param_number;i++)
    {
        gparam = &sgCode->param[i];

//        coord = QString(gparam->value).toFloat(&ok);

//        switch (gparam->group) {
//        case 'X':
            setParam_coord(gparam);
//            break;
//        case 'Y':

//            break;
//        default:
//            break;
//        }

    }

    cord->moveWorkToNext();
    //TODO calculate acceleration.
    if(!isPlaneHasSteps())
    {
        return;
    }

    setSpeedLeve();


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
