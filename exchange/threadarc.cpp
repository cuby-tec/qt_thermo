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
}

int ThreadArc::putInArray(ComDataReq_t *src)
{
    queue.enqueue(*src);
    return queue.size();
}

void ThreadArc::run()
{
    int result_exch;
    size_t try_counter;
    forever{

        while(!queue.isEmpty())
        {
            if(!queue.isEmpty()){
                buffer = queue.dequeue();
            }

            ComDataReq_t* request = &buffer;

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

                // check flag, and wait and resend if needed
                if(!status.modelState.reserved1&COMMAND_ACKNOWLEDGED)
                {
                    try_counter++;
                    msleep(mdelay);
                }
                if(try_counter>=max_tryCounter){
                    break;
                }

            }while(!status.modelState.reserved1&COMMAND_ACKNOWLEDGED);

            if(try_counter>=max_tryCounter){
                break;
            }

        }// while()

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
