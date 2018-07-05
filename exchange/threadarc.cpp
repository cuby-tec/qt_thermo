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
int a = 0;
}
