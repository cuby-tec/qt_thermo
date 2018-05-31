#include "threadexchange.h"

#include <QScopedPointer>


ThreadExchange::ThreadExchange()
{
    QScopedPointer<UsbExchange> exch(new UsbExchange()) ;
    abort = false;
    restart = false;
//    start();

}

//TODO send/recieve status
void
ThreadExchange ::process()
{
    QMutexLocker locker(&mutex);
    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}


/**
  * @brief ThermoThread::run
  */
 void
 ThreadExchange::run(){

     int result_exch;
     forever {
//         mutex.lock();
         thermo_gmutex.lock();
//         MGlobal::M_mutex->lock();

         // TODO frameIndex
//         index++;

//         exch->buildComData(&request,eoState);

         result_exch = exch->sendRequest(request);

         if(!result_exch == EXIT_SUCCESS)
         {
             status = 0;
             if (!restart)
                 emit sg_failed_status();
         }else{
             status = exch->getStatus();
         }


//         mutex.unlock();
         thermo_gmutex.unlock();

         // do .... : timeout
//         msleep(200);

//         MGlobal::M_mutex->unlock();

         if (!restart && (result_exch == EXIT_SUCCESS ))
             emit sg_status_updated(status);

         mutex.lock();
         if (!restart)
             condition.wait(&mutex);
         restart = false;
         mutex.unlock();

     }// forever
 }

//TODO conversion ComDataReq_t to const ComDataReq_t
void
ThreadExchange::setRequest(const ComDataReq_t* request)
{
    this->request = (ComDataReq_t*)request;
}
