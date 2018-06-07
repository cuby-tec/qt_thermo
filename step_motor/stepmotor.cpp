

#include "stepmotor.h"

#include "math.h"

//--------- defs


StepMotor::StepMotor()
{
#ifdef _17HS4401
    stepsPerRound = 200;

    angle = 1.8;


#endif

    for(int i=0;i<N_AXIS;i++)
    {
    	microstep[i] = 1;
    }

    alfa = 2*MyGlobal::PI/stepsPerRound;

   pulley_diameter = PULLEY_DIAMETER;
   
   this->acceleration = NULL;

#if MENDEL == 1
   m_struct[X_AXIS] = &StepMotor::linespeed;
   m_struct[Y_AXIS] = &StepMotor::linespeed;
   m_struct[Z_AXIS] = &StepMotor::linespeed_pitch;
#endif

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

//float_t
//StepMotor::getAlfa(uint32_t axis) {
//	return (alfa/microstep[axis]);
//}

float_t StepMotor::steps_rpm(float_t rpm, float_t raccel) {
	float_t aps = angular_velocity_rpm(rpm); // angular per second
	return (pow(aps,2)/(2*alfa*raccel));
}

float_t StepMotor::linespeed(float_t rpm) {

	//Число оборотов (об/мин)		500
	float_t radianps = MyGlobal::PI/30*rpm;
	radianps *= pulley_diameter/2; // radius
	return radianps;
}

// для винта
float_t StepMotor::linespeed_pitch(float_t rpm) {
	float_t v;
	v = rpm/60;
	v*= SHAFT_PITCH;
	return v;
}


// EOF


