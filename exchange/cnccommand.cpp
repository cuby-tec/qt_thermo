#include "cnccommand.h"

CncCommand::CncCommand(Exchange* exch)
{
    exchange = exch;
}

Status_t*
CncCommand::getstatus(void)
{
    return exchange->getStatus();
}



void
CncCommand::sendHotendControl(sHotendControl_t control)
{
    // Build request
    ComDataReq_t request;
    int value;

    value = exchange->sendRequest(&request);

    // TODO Exception
    // if(value < 0){
    // Данные небыли переданы.
    //}

}
