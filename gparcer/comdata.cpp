#include "comdata.h"
#include <string.h>
#include <QString>
#include <QDebug>

const QString msg3 = "Conversion error.";
ComData::ComData()
{

    memset(&request,'\0',sizeof(ComDataReq_t));
//    request.requestNumber = 22;
}


void
ComData::setParam_X(sGparam *param)
{
    bool ok;
    sSegment* segment = &request.payload.instrument1_parameter;
    float coord = QString(param->value).toFloat(&ok);
    if(!ok)
    {
        qDebug()<<"Error ComData[23]:"<< msg3;
        exit(1);
    }

    profile = Profile::instance();

    QString value = profile->getX_STEPS();

    int a = value.indexOf(',');

    if(a>0)
    {
        value.replace(a,1,'.');
    }

//    float_t steps_per_mm = QString( profile->getX_STEPS()).toFloat(&ok);
    float_t steps_per_mm = value.toFloat(&ok);
    if(ok && steps_per_mm>0)
        segment->axis[X_AXIS].steps = coord/steps_per_mm;
    else{
        qDebug()<<"ERROR ComData[32]:"<< msg3<< "Profile should be selected." ;
        exit(1);
    }


}

void
ComData::buildG0command()
{

    float coord;
    bool ok;
    sGparam* gparam;


    for(int i=0;i<sgCode->param_number;i++)
    {
        gparam = &sgCode->param[i];

        coord = QString(gparam->value).toFloat(&ok);

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

}
