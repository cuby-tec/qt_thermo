#ifndef SGCODE_H
#define SGCODE_H


//#include <stdint.h>
//#include <stddef.h>
#include "sgparam.h"


struct sGcode{
    char group;
    char value[10];
    uint32_t line;
    char comment[80];
    char param_number;
    struct sGparam param[15];
};



#endif // SGCODE_H

