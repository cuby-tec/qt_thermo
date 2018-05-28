#include "thermothread.h"

ThermoThread::ThermoThread()
{
    abort = false;
    restart = false;
//    symbol = "O";
//    symbol.append("%1");
//    slp = 1;
//    start();
    exch = new UsbExchange();

}


//TODO send/recieve status
void
ThermoThread::process()
{
    QMutexLocker locker(&mutex);
    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}


// TODO : emit sg_temperature_updated
 void
 ThermoThread::run(){

     int result_exch;
     forever {
//         mutex.lock();
         thermo_gmutex.lock();
//         MGlobal::M_mutex->lock();

         // TODO frameIndex
         index++;

         exch->buildComData(&request,eoState);

         result_exch = exch->sendRequest(&request);

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
             emit sg_temperature_updated(status);

         mutex.lock();
         if (!restart)
             condition.wait(&mutex);
         restart = false;
         mutex.unlock();

     }// forever
 }
