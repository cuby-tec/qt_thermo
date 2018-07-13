#include "threadarc.h"
#include <QDebug>

ThreadArc::ThreadArc()
{
    abort = false;
    restart = false;
    exch = new UsbExchange();
    array.clear();
    max_tryCounter = MAX_TRY_COUNTER;
    mdelay = DEFAULT_DELAY;
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

    queue.enqueue(*src);

//    const ComDataReq_t* req = array.constData();
//    const ComDataReq_t* req = &array.at(0);
//    const ComDataReq_t* reqsz = &array.at(sz-1);
//    qDebug()<<"ThreadArc[27]:x:"<<req->payload.instrument1_parameter.axis[0].steps<<"\ty:"<<req->payload.instrument1_parameter.axis[1].steps;
//    qDebug()<<"ThreadArc[28]:x:"<<reqsz->payload.instrument1_parameter.axis[0].steps<<"\ty:"<<reqsz->payload.instrument1_parameter.axis[1].steps;

    return array.size();
}

void ThreadArc::run()
{
    int result_exch;
    int index;
    size_t try_counter;
    forever{
        index = 0;
        for(index=0;index<array.size();index++){
            //==============

//            qDebug()<<"ThreadArc[51]";

            if(!queue.isEmpty()){
                buffer = queue.dequeue();
                qDebug()<<"ThreadArc[56]:"<<" reqNumber:"<<buffer.requestNumber
                       <<"\tqueue:"<<queue.count();
            }

            ComDataReq_t* request = &array[index];

//            request->requestNumber = ++MyGlobal::requestIndex;
            try_counter = 0;
            //
            do{

                thermo_gmutex.lock();

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
/*
                qDebug()<<"ThreadArc[77]: free segments:"<<status.freeSegments
                        <<"\t ready:"<<status.modelState.reserved1
//                        <<"frameNumber:"<<status.frameNumber
                        <<"\tcoun:"<<try_counter
                       <<"\tContCnt:"<<status.instrument2_parameter //счётчик входов continue
//                      <<"\t number:"<<request->requestNumber
                      <<"\treqCmd:"<<request->command.reserved
                     <<"\trateX:Y:"<<request->payload.instrument1_parameter.axis[X_AXIS].initial_rate<<":"<<request->payload.instrument1_parameter.axis[Y_AXIS].initial_rate
                     <<"\tPMS:"<<status.modelState.modelState;
*/
                // check flag, and wait and resend if needed
                if(!status.modelState.reserved1&COMMAND_ACKNOWLEDGED)
                {
                    try_counter++;
                    msleep(mdelay);
//                    qDebug()<<"ThreadArc[83] try_counter:"<<try_counter;
                }
                if(try_counter>=max_tryCounter){
                    break;
                }

            }while(!status.modelState.reserved1&COMMAND_ACKNOWLEDGED);

            if(try_counter>=max_tryCounter){
                break;
            }
            //=================
        }

        if(try_counter<max_tryCounter){
            if (!restart && (result_exch == EXIT_SUCCESS ))
                emit sg_status_updated(&status);
        }else{
            emit sg_failed_status();
        }

        mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock(); //Debug mode

    }// forever
}

size_t ThreadArc::getMdelay() const
{
    return mdelay;
}

void ThreadArc::setMdelay(const size_t &value)
{
    mdelay = value;
}

size_t ThreadArc::getMax_tryCounter() const
{
    return max_tryCounter;
}

void ThreadArc::setMax_tryCounter(const size_t &value)
{
    max_tryCounter = value;
}
