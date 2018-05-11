#ifndef THERMOTHREAD_H
#define THERMOTHREAD_H

#include <QMutex>
#include <QThread>
#include <QString>
#include <QTextStream>
#include <QWaitCondition>

#include "usbexchange.h"
#include "links/Status_t.h"
#include "usbexchange.h"
#include "myglobal.h"

extern QMutex thermo_gmutex;

class ThermoThread : public QThread
{
    Q_OBJECT

public:
    ThermoThread();

    ~ThermoThread()
    {
        free(exch);

    }

    void process();


signals:
    void sg_temperature_updated(const Status_t* status);
    void sg_failed_status();


public slots:


protected:
    void run();

private:
    bool abort;
    bool restart;
    uint32_t index;

    const Status_t* status;

    ComDataReq_t request;


    QMutex mutex;
    QWaitCondition condition;

    UsbExchange* exch;

};


#endif // THERMOTHREAD_H
