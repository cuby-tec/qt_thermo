#ifndef THREADARC_H
#define THREADARC_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QVarLengthArray>

#include "links/Status_t.h"
#include "usbexchange.h"
#include "myglobal.h"
#include "links/ComDataReq_t.h"


extern QMutex thermo_gmutex;

class ThreadArc : public QThread
{
    Q_OBJECT

public:
    ThreadArc();

    void process();

//    QVarLengthArray<ComDataReq_t> getArray(){return array; }
    int putInArray(ComDataReq_t *src);

    void clear() { array.clear();}

signals:
    void sg_status_updated(const Status_t* status);
    void sg_failed_status();

protected:
    void run();


private:
    bool abort;
    bool restart;

    Status_t status;
    QVarLengthArray<ComDataReq_t,1024> array;


//    ComDataReq_t* request;
//    ComDataReq_t request;

    QMutex mutex;
    QWaitCondition condition;
    UsbExchange* exch;

};

#endif // THREADARC_H
