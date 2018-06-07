/*
 *
 * Характеристики двигателя.
 *
 */

#ifndef STEPMOTOR_H
#define STEPMOTOR_H

//#include <QString>
#include <stdint.h>
#include <stddef.h>

#include <math.h>
#include "links/msmotor/msport.h"
#include "myglobal.h"


// "Крутящий момент(Н. см)" 40
//"Фиксированный крутящий момент(Н. см)" 2.2
//"Инерция ротора (Г. см2)" 54
//"Фаза индуктивность (Mh)" 2.8
//"Сопротивление фаза (Ом)" 1.5
//"Номинальный ток (A)"     1.7
//"Двигатель Длина (Мм)"    40
//"Шаг угол (Град)"         1.8
//"Двигатель Вес (G)"       280






#define _17HS4401

#define PULLEY_DIAMETER	12.1 // pulley_diameter

#define SHAFT_PITCH	1.25 // Шаг винта[mm]

#define MENDEL	1

class StepMotor;

typedef float_t (StepMotor::*convert)(float_t param);


class StepMotor
{
public:
    StepMotor();

    size_t getStepsPerRound() {return stepsPerRound;}

    void setStepsPerRound(size_t steps) {this->stepsPerRound = steps;}

	float_t getPulleyDiameter() {
		return pulley_diameter;
	}

	void setPulleyDiameter(float_t pulleyDiameter) {
		pulley_diameter = pulleyDiameter;
	}

	float_t getAngle() {
		return angle;
	}

	/**
	 * Для каждой оси может быть назначен свой микрошаг.
	 */
	float_t getAlfa(uint32_t axis){
		return (alfa/microstep[axis]);
	}

	/**
	 * linear velocity to angular_velocity
	 * in: mm/second
	 * out: radian/second
	 */
	float_t angular_velocity_tan(float_t tangential_speed);

	/**
	 * Round per min to angular velocity
	 * in: Round per min
	 * out: rad/sec
	 */
	float_t angular_velocity_rpm(float_t rpm);

	/**
	 * in: Round per min
	 * in: raccel rad/sec^2
	 * out: steps to achieve rpm.
	 */
	float_t steps_rpm(float_t rpm, float_t raccel);


	/**
	 * Преобразование вращательной скорости(об/мин) в линейную.
	 */
	float_t linespeed(float_t rpm);

	/**
	 * Для винта.
	 */
	float_t linespeed_pitch(float_t rpm);


    uint32_t getMicrostep(uint32_t axis) {
		return microstep[axis];
	}


    void setMicrostep(uint32_t axis, uint32_t _microstep){
        microstep[axis] = _microstep;
	}

	float_t getAcceleration() const {
		return acceleration;
	}

	void setAcceleration(float_t acceleration) {
		this->acceleration = acceleration;
	}

    convert m_struct[M_AXIS];

private:

    size_t stepsPerRound;
    
    float_t pulley_diameter; // 12.1
    
    float_t angle; /// 1.8


    uint32_t microstep[N_AXIS];

    float_t alfa;

    float_t acceleration;



};

#endif // STEPMOTOR_H

/*
 *
 *
*/
