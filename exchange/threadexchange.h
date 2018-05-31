#ifndef THREAEXCHANGE_H
#define THREAEXCHANGE_H

#include <QMutex>
#include <QThread>
//#include <QString>
//#include <QTextStream>
#include <QWaitCondition>


#include "links/Status_t.h"
#include "usbexchange.h"
#include "myglobal.h"

extern QMutex thermo_gmutex;

class ThreadExchange : public QThread
{
    Q_OBJECT

public:
    ThreadExchange();

    void process();

    void setRequest(const ComDataReq_t* request);


signals:
    void sg_status_updated(const Status_t* status);
    void sg_failed_status();


protected:
    void run();


private:
    bool abort;
    bool restart;
//    uint32_t index;

    const Status_t* status;

    ComDataReq_t* request;


    QMutex mutex;
    QWaitCondition condition;

    UsbExchange* exch;


};

#endif // THREAEXCHANGE_H
