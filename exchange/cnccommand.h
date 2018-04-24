#ifndef CNCCOMMAND_H
#define CNCCOMMAND_H

#include "exchange.h"

class CncCommand
{
public:
    CncCommand(Exchange* exch);

    Status_t* getstatus(void);

    void sendHotendControl(sHotendControl_t control);

private:

    Exchange* exchange;

};

#endif // CNCCOMMAND_H
