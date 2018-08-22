/*
 * Recalculate_flag.h
 *
 *  Created on: 18.06.2018
 *      Author: walery
 */

#ifndef THERMO_STEP_MOTOR_RECALCULATE_FLAG_H_
#define THERMO_STEP_MOTOR_RECALCULATE_FLAG_H_

#include <stdint.h>

#define byte uint8_t

struct Recalculate_flag{
	byte single:1;	//флог назначения одноразового сегмента: 0 - одноразовый, 1 - программный.
	byte reserv:7;
};



#endif /* THERMO_STEP_MOTOR_RECALCULATE_FLAG_H_ */
