#include "comdata.h"
#include <string.h>
#include <QString>
#include <QDebug>

#include <QtGlobal>
#include <QWaitCondition>
#include <QVarLengthArray>

#include "myglobal.h"

#include "geometry/Arc.h"

#include <cmath>
//#include <thread>


//const QString msg3 = "Conversion error.";
//const QString msg4 = "Profile should be selected.";
const char* msg3 = "Conversion error.";
const char* msg4 = "Profile should be selected.";

ComData::ComData(QObject *parent) : QObject(parent)
{

    memset(&request,'\0',sizeof(ComDataReq_t));
//    request.requestNumber = 22;

    state = ecdOne;// отправка одного Сегмента.

    profile = Profile::instance();

    cord = Coordinatus::instance();
    cord->setupProfileData();

//    motor = new StepMotor();

    controller = new Controller();

    setupThread();

}

void
ComData::setupThread()
{
	acknowledge_flag = false;
    connect(&thread,SIGNAL(sg_status_updated(const Status_t*)),this,SLOT(updateStatus(const Status_t*)) );
    connect(&thread,SIGNAL(sg_failed_status()),this,SLOT(failedStatus())  );

    connect(&threadarc,SIGNAL(sg_status_updated(const Status_t*)),this,SLOT(updateStatus(const Status_t*)));
    connect(&threadarc,SIGNAL(sg_failed_status()),this,SLOT(failedStatus()) );

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

    cord->moveNextToCurrent();
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

		control->speedLevel = bstate->accelerate_until;// TODO Attention

		control->microsteps = bstate->microstep;

		for(int j=0;j<3;j++){
			control->schem[j] = bstate->schem[j];
		}

		control->steps = bstate->steps;

		control->axis = bstate->axis_mask;
	}

//TODOH build ComdataReq



}

//TODOH Circle G2 G3 (Clockwise Arc)
void
ComData::buildG2Command()
{
    bool ok;

    sGparam* gparam;

//    Arc* arc = new Arc();
    arc = new Arc();

    QString xstr,ystr,istr,jstr,rstr;


    sSegment* segment = &request.payload.instrument1_parameter;


    for(int i=0;i<sgCode->param_number;i++)
    {
        gparam = &sgCode->param[i];

//        coord = QString(gparam->value).toFloat(&ok);

        switch (gparam->group)
        {
        case 'X':
        	xstr = gparam->value;
        	break;
        case 'Y':
//            setParam_coord(gparam);
        	ystr = gparam->value;
            break;

        case 'I':
        	istr = gparam->value;
        	break;

        case 'J':
        	jstr = gparam->value;
        	break;

        case 'R':
        	rstr = gparam->value;
        	break;

        case 'E':
        	// TODOH Extruder
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

    // G2 X90.6 Y13.8 I5 J10 E22.4
    //77,2317745639	56,0908965345 30 grad

    // G2 X90.6 Y13.8 I15 J10 E22.4
    //52,8477211996	-55,5541760683 300 grad
    //56,0908965344	-53,5715205261 302,88°

    QString startX("77,2317745639");

    QString startY("56,0908965345");

//    arc->setStart(Point(cord->getCurrentValue(X_AXIS),cord->getCurrentValue(Y_AXIS))); // TODO current value
    arc->setStart(startX,startY);

    Q_ASSERT(xstr.count()>0 && ystr.count()>0);

    arc->setEnd(xstr,ystr);

    Q_ASSERT(istr.count()>0 && jstr.count()>0);// TODO set radious

    arc->setCenter(istr,jstr);

    QString tstr = profile->getARC_TOLERANCE();

    Q_ASSERT(tstr.count()>0);

    double_t precicion = controller->getPrecicion(X_AXIS,1);

    //TODO correct precicion from Controller.
    arc->setPrecicion(precicion);

    arc->calculate();

    cord->moveNextToCurrent();
    cord->initWork();

//  QVarLengthArray<int, 1024> array(n + 1);

    size_t num = arc->getPointsNumber();

//    QVarLengthArray<ComDataReq_t,1024> array(num);
    ThreadArc *pthreadarc = &threadarc;
//    QVarLengthArray<ComDataReq_t> array = threadarc->getArray();

    bool send = false;
    Point p0 = arc->getPoint(0);
    for(int i=1;i<arc->getPointsNumber();i++){
        Point p = arc->getPoint(i);

//        cord->initWork();
        Point dp = p-p0;
        if(abs(dp.x/precicion)>=1){
        	cord->setWorkValue(X_AXIS,p.x);
        	send = true;
        	p0.x = p.x;

        }
        if(abs(dp.y/precicion) >= 1){
        	cord->setWorkValue(Y_AXIS,p.y);
        	send = true;
        	p0.y = p.y;
        }


        if(send == false)
        	continue;

        cord->moveWorkToNext();

        controller->buildBlock(cord);

        buildComdata();


//        ComDataReq_t* dst = &array[i];
//        memcpy(dst,&request,sizeof(ComDataReq_t));

        int s = pthreadarc->putInArray(&request);
//        qDebug()<<"ComData[507] array size:"<<s;
        //TODOH send comdata
        bool ACK = true;
        while(ACK)
        {

            sSegment* segment = &request.payload.instrument1_parameter;
            sControl* control = &segment->axis[X_AXIS];
            sControl* controly= &segment->axis[Y_AXIS];

//            qDebug()<<"ComData[517] ";
//            qDebug()<<"i:"<<i<<"\tpoint.x:"<<dp.x<<"\tpoint.y:"<<dp.y;
//            qDebug()<<"current_x:"<< cord->getCurrentValue(X_AXIS)<<"\tnext:"<<cord->getNextValue(X_AXIS)<<"\tdx:"<<(cord->getCurrentValue(X_AXIS)-cord->getNextValue(X_AXIS));
//            qDebug()<<"current y:"<<cord->getCurrentValue(Y_AXIS)<<"\tnext y:"<<cord->getNextValue(Y_AXIS)<<"\tdy:"<<(cord->getCurrentValue(Y_AXIS)-cord->getNextValue(Y_AXIS));

//            qDebug()<<"stepsX:"<<control->steps<<"\tinitial rate:"<<control->initial_rate<<"\tstepsY:"<<controly->steps;


//            thread.setRequest(&request);

//                thread.process();

            //    return result;
//                while(ACK){
//                    sleep(1);
//                }



        	ACK = false;
        }
        send = false;
        cord->moveNextToCurrent();

    }

    // sending

    threadarc.process();

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
    	state = ecdOne;
        buildG0command();
        break;

    case 2:
    case 3:
    	state = ecdCircle;
    	buildG2Command();
        break;

    case 4:
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

// from GConsole
void ComData::buildComData(sGcode *sgcode, bool checkBox_immediately)
{
	setRequestNumber(++MyGlobal::commandIndex);

	//    ComDataReq_t* req = getRequest();
	ComDataReq_t* req = build(sgcode);
	switch(state){

	case ecdOne:
		// immediately execute
		if(checkBox_immediately)
			req->command.reserved |= EXECUTE_IMMEDIATELY;
		else
			req->command.reserved &= ~EXECUTE_IMMEDIATELY;

		req->payload.instrument1_parameter.head.reserved &= ~EXIT_CONTINUE;

		thread.setRequest(req);
		thread.process();
		break;

	case ecdCircle:

		for(int i = 1; i<arc->getPointsNumber();i++)
		{
			Point p = arc->getPoint(i);

			cord->moveNextToCurrent();
			cord->initWork();
			cord->setWorkValue(X_AXIS,p.x);
			cord->setWorkValue(Y_AXIS,p.y);

		    cord->moveWorkToNext();
		    if(!isPlaneHasSteps())
		    {
		        continue;
		    }

		    controller->buildBlock(cord);

			buildComdata();

		}

		break;
	}


}

void ComData::updateStatus(const Status_t *status)
{
	acknowledge_flag = true;
    emit sg_updateStatus(status);

    qDebug()<<"ComData[694] updateStatus";
}

void ComData::failedStatus()
{
 //TODO failed Status
	qDebug()<<"ComData::failedStatus[700].";

}

void
ComData::initWorkAray()
{
//    cord = Coordinatus::instance();
    cord->initWork();
}
