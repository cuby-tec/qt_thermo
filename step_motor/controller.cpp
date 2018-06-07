
#include "controller.h"

#include <QScopedPointer>
#include <QtGlobal>

#include <math.h>

#include "profiles/profile.h"

#include <algorithm>


Controller::Controller()
{
    frequency = FREQUENCY;
    for(int i=0;i<N_AXIS;i++)
    {
        pcountertime[i] = NULL;
    }
    motor = new StepMotor();
    setupProfileData();
}




Controller::~Controller()
{
        free(pcountertime);
}



void
Controller::buildCounterValue(uint32_t steps,uint8_t axis)
{
    if(pcountertime[axis]!=NULL)
    {
        free(pcountertime[axis]);
        pcountertime[axis] = NULL;
    }

    pcountertime[axis] = (CounterTime_t*)(malloc(steps * sizeof(CounterTime_t)) );

    Q_ASSERT(pcountertime!=NULL);

    Q_ASSERT(motor->getAcceleration() != NULL);

    for(int i =0;i<steps;i++)
    {
        if(i == 0)
        {
            //=SQRT(2*alfa/acceleration)*timer_frequency


        }
    }

}

/**
 * Заполнение полей разгона, торможения, и т.д.
 */
void Controller::buildBlock(Coordinatus* cord) {

// Длина вектора.
  float_t s = 0;

    for(int i=0; i<N_AXIS;i++){
		s += powf( cord->getCurrentValue(i)-cord->getNextValue(i),2);
	}
	s = sqrt(s);

// Максимальная скорость по осям(линейная)
    float v[M_AXIS];

    for(int i=0;i<M_AXIS;++i){
//		v[i] = motor->linespeed(profileData.speed_rpm[i]);
//        v[i] = (motor->*m_struct[i])(profileData.speed_rpm[i]);
        convert pf = motor->m_struct[i];
        v[i] = (motor->*pf)(profileData.speed_rpm[i]);
//varant 2:     v[i] = (motor->*motor->m_struct[i])(profileData.speed_rpm[i]);

		//	v = cord->nextBlocks[X_AXIS].nominal_speed; // Число оборотов/мин
	}

    //Максимальная скорость для сегмента
    float_t maxs = *std::max_element(v,v+M_AXIS);

    //TODOH [3] Синусы направлений



}

/**
 * Загрузка данных из профиля.
 */
void Controller::setupProfileData() {
	Profile* profile = Profile::instance();
	if(!profile->isProfileActive())
		profile->init_profile();

	//setSpeedLevel(block, psettings->seekSpeed);
	//    float seekspeed;
	    bool ok;

	    QString fspeed; // rpm unit
	    float speed;

	    QString facceleration;
	    float acceleration;


	    for(int i=0;i<N_AXIS;i++)
	    {
	//        block_state* block = &blocks[i];
//	        block_state* block = &cord->nextBlocks[i];

	        switch(i)
	        {
	        case X_AXIS:
	            fspeed = MyGlobal::formatFloat(profile->getX_MAX_RATE());
	            facceleration = MyGlobal::formatFloat(profile->getX_ACCELERATION());
	            break;

	        case Y_AXIS:
	            fspeed = MyGlobal::formatFloat(profile->getY_MAX_RATE());
	            facceleration = MyGlobal::formatFloat(profile->getY_ACCELERATION());
	            break;

	        case Z_AXIS:
	            fspeed = MyGlobal::formatFloat(profile->getZ_MAX_RATE());
	            facceleration = MyGlobal::formatFloat(profile->getZ_ACCELERATION());
	            break;

	        case E_AXIS:
	            fspeed = MyGlobal::formatFloat(profile->getE_MAX_RATE());
	            facceleration = MyGlobal::formatFloat(profile->getE_ACCELERATION());
	            break;
	        }

	        speed = fspeed.toFloat(&ok);
	        Q_ASSERT(ok);
//	        block->nominal_speed = speed;
	        profileData.speed_rpm[i] = speed;

	        acceleration = facceleration.toFloat(&ok);
	        Q_ASSERT(ok);
//	        block->acceleration = acceleration;
	        profileData.acceleration[i] = acceleration;

	    }
}
