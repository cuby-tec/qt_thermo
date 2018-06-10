

#include "stepmotor.h"

#include "math.h"

//--------- defs


StepMotor::StepMotor()
{
#ifdef _17HS4401

    angle = ANGLE;	//1.8;

    stepsPerRound = 360/ANGLE;

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

   getLineStep[X_AXIS] = &StepMotor::lineStep;
   getLineStep[Y_AXIS] = &StepMotor::lineStep;
   getLineStep[Z_AXIS] = &StepMotor::pulleyStep;

#endif

}

/*
double_t
StepMotor::getPulleyDiameter() const {
	return pulley_diameter;
}
*/

/*
void
StepMotor::setPulleyDiameter(double_t pulleyDiameter) {
	pulley_diameter = pulleyDiameter;
}
*/

double_t
StepMotor::angular_velocity_tan(double_t tangential_speed)
{
	return ((tangential_speed/pulley_diameter)*2);
}

double_t StepMotor::angular_velocity_rpm(double_t rpm) {
	return (rpm*MyGlobal::PI/30);
}

//double_t
//StepMotor::getAlfa(uint32_t axis) {
//	return (alfa/microstep[axis]);
//}

double_t StepMotor::steps_rpm(double_t rpm, double_t raccel) {
	double_t aps = angular_velocity_rpm(rpm); // angular per second
	return (pow(aps,2)/(2*alfa*raccel));
}

double_t StepMotor::linespeed(double_t rpm) {

	//Число оборотов (об/мин)		500
	double_t radianps = MyGlobal::PI/30*rpm;
	radianps *= pulley_diameter/2; // radius
	return radianps;
}

// для винта
double_t StepMotor::linespeed_pitch(double_t rpm) {
	double_t v;
	v = rpm/60;
	v*= SHAFT_PITCH;
	return v;
}

double_t StepMotor::lineStep(uint32_t axis) {
	double_t alfa = getAlfa(axis);
	alfa *= pulley_diameter/2;
	return alfa;
}


// Линейное ускорение для заданного
// максимального углового ускорения.
double_t StepMotor::getLinearAcceleration() {
	double_t result;
	result = acceleration*pulley_diameter/2; // 1250
	return result;
}

double_t StepMotor::pulleyStep(uint32_t axis) {
	double_t result;
	result = SHAFT_PITCH/(microstep[axis] * stepsPerRound);
	return result;
}


// EOF


