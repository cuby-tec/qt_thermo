/*
 * ProfileData.h
 *
 *  Created on: 07.06.2018
 *      Author: walery
 */

#ifndef THERMO_STEP_MOTOR_PROFILEDATA_H_
#define THERMO_STEP_MOTOR_PROFILEDATA_H_

#include <math.h>
#include "links/msmotor/msport.h"


struct ProfileData_t{

	float_t acceleration[N_AXIS];

	float_t speed_rpm[N_AXIS];
};


#endif /* THERMO_STEP_MOTOR_PROFILEDATA_H_ */
