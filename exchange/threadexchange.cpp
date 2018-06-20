#include "threadexchange.h"

#include <QScopedPointer>
#include <string.h>

ThreadExchange::ThreadExchange()
{
// QScopedPointer<UsbExchange> exch(new UsbExchange()) ;
    abort = false;
    restart = false;
    exch = new UsbExchange();
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
//         thermo_gmutex.try_lock();

         request.requestNumber = ++MyGlobal::requestIndex;

         result_exch = exch->sendRequest(&request);

         if(!result_exch == EXIT_SUCCESS)
         {
             status.frameNumber = 0;
             if (!restart)
                 emit sg_failed_status();
         }else{
//             status = exch->getStatus();
             memcpy(&status,exch->getStatus(),sizeof(Status_t));
         }


//         mutex.unlock();
         thermo_gmutex.unlock();

         // do .... : timeout
//         msleep(200);

//         MGlobal::M_mutex->unlock();

         if (!restart && (result_exch == EXIT_SUCCESS ))
             emit sg_status_updated(&status);

         mutex.lock();
         if (!restart)
             condition.wait(&mutex);
         restart = false;
         mutex.unlock(); //Debug mode

     }// forever
 }

//TODO conversion ComDataReq_t to const ComDataReq_t
void
ThreadExchange::setRequest(const ComDataReq_t* request)
{
//    this->request = (ComDataReq_t*)request;
	memcpy(&this->request,request,sizeof(ComDataReq_t));
}

ThreadExchange::~ThreadExchange()
{
	delete(exch);
}
