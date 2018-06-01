#include "comdata.h"
#include <string.h>
#include <QString>
#include <QDebug>
#include <QtGlobal>

//const QString msg3 = "Conversion error.";
//const QString msg4 = "Profile should be selected.";
const char* msg3 = "Conversion error.";
const char* msg4 = "Profile should be selected.";

ComData::ComData()
{

    memset(&request,'\0',sizeof(ComDataReq_t));
//    request.requestNumber = 22;

    profile = Profile::instance();

}


void
ComData::setParam_X(sGparam *param)
{
    bool ok;
    int i;

    QString str_val = QString( param->value );

    sSegment* segment = &request.payload.instrument1_parameter;

    i = str_val.indexOf(',');


    if(i>0)
    {
        str_val = str_val.replace(i,1,'.');
    }

    float coord = str_val.toFloat(&ok);
    if(!ok)
    {
        qFatal(msg3);
    }


    if(cord->isAbsolute())
    {
        cord->setWorkValue(X_AXIS,coord);
    }else{
        float wv = cord->getWorkvalue(X_AXIS);
        wv += coord;
        cord->setWorkValue(X_AXIS,wv);
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

        switch (gparam->group) {
        case 'X':
            setParam_X(gparam);
            break;
        default:
            break;
        }

    }

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

    initWorkAray();

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
    cord = Coordinatus::instance();
    cord->initWork();
}
