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

    double_t getPath_mm(uint8_t axis,int32_t steps);


private:
    size_t frequency;

    CounterTime_t* pcountertime[N_AXIS];

    StepMotor* motor[M_AXIS];


    ProfileData_t* profileData;

    void setupProfileData();

    Trapeze_t trapeze[M_AXIS];

    // Расчёт трапеций для каждой оси.
    uint32_t calculateTrapeze();

    AccelerationTable* acctable;

    void splinePath(block_state_t* privBlock, block_state_t* nextBlock);

    // пересчёт ускорений для одной оси.
    void planner_recalculate(block_state* prev, block_state* curr);


    /**
     * Загрузка данных(Угловое ускорение) из профиля.
     */
    void uploadMotorData();
};

#endif // CONTROLLER_H
