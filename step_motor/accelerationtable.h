#ifndef ACCELERATIONTABLE_H
#define ACCELERATIONTABLE_H

#include "AccelerationTable_t.h"

//=K$64*0,4056

#define COUNTER_COEFFICIENT	0.4056

class AccelerationTable
{
public:
    AccelerationTable();

    AccelerationTable(uint32_t steps);

    ~AccelerationTable();

    void buildTale(uint32_t startCount);

    double_t getAccelerationTime(uint32_t frequency);

    double_t getCounter(uint32_t step);

private:

    uint32_t steps;

    AccelerationTable_t* table;

};

#endif // ACCELERATIONTABLE_H
