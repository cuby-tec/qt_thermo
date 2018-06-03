/*
 * File: coordinatus.h
 *
*/

#include <QtGlobal>

#include "coordinatus.h"
#include <string.h>



/*
Coordinatus::Coordinatus()
{

}
*/

void
Coordinatus::initWork()
{
    memcpy(work,current,sizeof(work)*sizeof(float) );
}

void
Coordinatus::moveWorkToNext()
{
    memcpy(next,work,sizeof(work)*sizeof(float));

}

void
Coordinatus::setWorkValue(size_t axis,float value)
{
    Q_ASSERT(axis < N_AXIS);
    work[axis] = value;
    sendSignalCoord();
}

float
Coordinatus::getWorkvalue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (work[axis]);
}

float
Coordinatus::getCurrentValue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (current[axis]);
}

float Coordinatus::getNextValue(size_t axis)
{
    Q_ASSERT(axis<N_AXIS);

    return (next[axis]);
}

void
Coordinatus::sendSignalCoord()
{
    emit(sg_coordUpdated());
}
