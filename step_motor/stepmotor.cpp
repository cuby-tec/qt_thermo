

#include "stepmotor.h"

#include "myglobal.h"

//--------- defs


StepMotor::StepMotor()
{
#ifdef _17HS4401
    stepsPerRound = 200;

    angle = 1.8;

    alfa = MyGlobal::PI*angle/180;
#endif

   pulley_diameter = 12.1;
   
 }

/*
float_t
StepMotor::getPulleyDiameter() const {
	return pulley_diameter;
}
*/

/*
void
StepMotor::setPulleyDiameter(float_t pulleyDiameter) {
	pulley_diameter = pulleyDiameter;
}
*/

float_t
StepMotor::angular_velocity_tan(float_t tangential_speed)
{
	return ((tangential_speed/pulley_diameter)*2);
}

float_t StepMotor::angular_velocity_rpm(float_t rpm) {
	return (rpm*MyGlobal::PI/30);
}

float_t StepMotor::steps_rpm(float_t rpm, float_t raccel) {
	float_t aps = angular_velocity_rpm(rpm); // angular per second
	return (pow(aps,2)/(2*alfa*raccel));
}
