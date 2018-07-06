#include "threadarc.h"
#include <QDebug>

ThreadArc::ThreadArc()
{
    abort = false;
    restart = false;
    exch = new UsbExchange();
    array.clear();
}

void ThreadArc::process()
{
//    QMutexLocker locker(&mutex);
    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
    qDebug()<<"ThreadArc[21]";
}

int ThreadArc::putInArray(ComDataReq_t *src)
{
    array.append(*src);
    int sz = array.size();


//    const ComDataReq_t* req = array.constData();
    const ComDataReq_t* req = &array.at(0);

    const ComDataReq_t* reqsz = &array.at(sz-1);

//    qDebug()<<"ThreadArc[27]:x:"<<req->payload.instrument1_parameter.axis[0].steps<<"\ty:"<<req->payload.instrument1_parameter.axis[1].steps;
//    qDebug()<<"ThreadArc[28]:x:"<<reqsz->payload.instrument1_parameter.axis[0].steps<<"\ty:"<<reqsz->payload.instrument1_parameter.axis[1].steps;

    return array.size();
}

void ThreadArc::run()
{
    int result_exch;
    int index;
    forever{
        index = 0;
        for(index=0;index<array.size();index++){
//==============
        thermo_gmutex.lock();

        qDebug()<<"ThreadArc[17]";

        ComDataReq_t* request = &array[index];

        request->requestNumber = ++MyGlobal::requestIndex;

        result_exch = exch->sendRequest(request);

        if(result_exch != EXIT_SUCCESS)
        {
            status.frameNumber = 0;
            if (!restart)
                emit sg_failed_status();
            qDebug()<<"ThreadExchange[38]"<<" failed.";
        }else{
            //             status = exch->getStatus();
            memcpy(&status,exch->getStatus(),sizeof(Status_t));
        }

        thermo_gmutex.unlock();
        qDebug()<<"ThreadArc[42]: free segments:"<<status.freeSegments<<"\t busy:"<<status.modelState.reserved1;

//=================
        }

        if (!restart && (result_exch == EXIT_SUCCESS ))
            emit sg_status_updated(&status);

        mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock(); //Debug mode

    }// forever
}
