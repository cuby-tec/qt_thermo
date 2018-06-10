#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stddef.h>

#include "countertime_t.h"
#include "stepmotor.h"
#include "links/msmotor/msport.h"
#include "block_state_t.h"
#include "gparcer/coordinatus.h"
#include "ProfileData.h"
#include "trapeze_t.h"
#include "accelerationtable.h"

#define FREQUENCY  50000000 //;frequency = 50000000;


class Controller
{
public:
    Controller();
/*
    Controller(StepMotor* motor){
    	this->motor = motor;
    	frequency = FREQUENCY;
    }
*/
    ~Controller();

    /**
      Построение таблицы значений счётчика для заданного количества шагов.
     * @brief buildCounterValue
     * @param steps
     */
    void buildCounterValue(uint32_t steps, uint8_t axis);

    /**
     * Заполнение полей разгона, торможения, и т.д.
     */
    void buildBlock(Coordinatus* cord);


private:
    size_t frequency;

    CounterTime_t* pcountertime[N_AXIS];

    StepMotor* motor[M_AXIS];


    ProfileData_t profileData;

    void setupProfileData();

    Trapeze_t trapeze[M_AXIS];

    // Расчёт трапеций для каждой оси.
    void calculateTrapeze();

    AccelerationTable* acctable;

};

#endif // CONTROLLER_H
