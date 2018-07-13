#ifndef THREADARC_H
#define THREADARC_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QVarLengthArray>
#include <QQueue>


#include "links/Status_t.h"
#include "usbexchange.h"
#include "myglobal.h"
#include "links/ComDataReq_t.h"

#define MAX_TRY_COUNTER     20
#define DEFAULT_DELAY       100


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

    size_t getMax_tryCounter() const;
    void setMax_tryCounter(const size_t &value);

    size_t getMdelay() const;
    void setMdelay(const size_t &value);

signals:
    void sg_status_updated(const Status_t* status);
    void sg_failed_status();

protected:
    void run();


private:
    bool abort;
    bool restart;

    uint max_tryCounter;

    uint mdelay;// milliseconds delay

    Status_t status;
    QVarLengthArray<ComDataReq_t,1024> array;

    QQueue<ComDataReq_t> queue;

    ComDataReq_t buffer;

//    ComDataReq_t* request;
//    ComDataReq_t request;

    QMutex mutex;
    QWaitCondition condition;
    UsbExchange* exch;

};

#endif // THREADARC_H
