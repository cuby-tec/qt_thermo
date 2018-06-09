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
    memcpy(work,current,sizeof(work)*sizeof(double_t) );
}

void
Coordinatus::moveWorkToNext()
{
    memcpy(next,work,sizeof(work)*sizeof(double_t));

}

void
Coordinatus::setWorkValue(size_t axis,double_t value)
{
    Q_ASSERT(axis < N_AXIS);
    work[axis] = value;
    sendSignalCoord();
}

double_t
Coordinatus::getWorkvalue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (work[axis]);
}

double_t
Coordinatus::getCurrentValue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (current[axis]);
}

double_t
Coordinatus::getNextValue(size_t axis)
{
    Q_ASSERT(axis<N_AXIS);

    return (next[axis]);
}

void
Coordinatus::sendSignalCoord()
{
    emit(sg_coordUpdated());
}
