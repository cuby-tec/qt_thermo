/*
 *
 * Характеристики двигателя.
 *
 */

#ifndef STEPMOTOR_H
#define STEPMOTOR_H

//#include <QString>
#include <stddef.h>
#include <math.h>

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


class StepMotor
{
public:
    StepMotor();

    size_t getStepsPerRound() {return stepsPerRound;}

    void setStepsPerRound(size_t steps) {this->stepsPerRound = steps;}

	float_t getPulleyDiameter() const {
		return pulley_diameter;
	}

	void setPulleyDiameter(float_t pulleyDiameter) {
		pulley_diameter = pulleyDiameter;
	}

	float_t getAngle() const {
		return angle;
	}

	float_t getAlfa() const {
		return alfa;
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

private:

    size_t stepsPerRound;
    
    float_t pulley_diameter; // 12.1
    
    float_t angle; /// 1.8

    float_t alfa;
};

#endif // STEPMOTOR_H

/*
 *
 *
*/
