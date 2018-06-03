#ifndef COORDINATUS_H
#define COORDINATUS_H

#include "links/msmotor/msport.h"
#include <QString>
#include <QObject>
#include "step_motor/block_state_t.h"


// Singleton
class Coordinatus:public QObject
{
    Q_OBJECT

public:
    static Coordinatus* instance()
    {
        static Coordinatus p;
        return &p;
    }

    // coping from current array to work array.
    void initWork();

    void setWorkValue(size_t axis,float value);

    float getWorkvalue(size_t axis);

    float getCurrentValue(size_t axis);

    float getNextValue(size_t axis);

    bool isAbsolute() {return absrel;}

    void setAbsolute(bool value){absrel = value;}

    void moveWorkToNext();

    block_state_t currentBlocks[N_AXIS];

    block_state_t nextBlocks[N_AXIS];


signals:
    void sg_coordUpdated();


private:
    float current[N_AXIS];

    float next[N_AXIS];

    float work[N_AXIS];

    bool absrel;

    void sendSignalCoord();

    Coordinatus()
    {
        absrel = false;
    }

    ~Coordinatus() {}

    Coordinatus(Coordinatus const&) = delete;
    void operator = (Coordinatus const&) = delete;

};

#endif // COORDINATUS_H
