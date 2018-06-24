/*
 * File: coordinatus.h
 *
*/

#include <QtGlobal>

#include "coordinatus.h"
#include <string.h>
#include "profiles/profile.h"
#include "step_motor/controller.h"

/*
Coordinatus::Coordinatus()
{

}
*/

void
Coordinatus::initWork()
{
    memcpy(work,current,sizeof(work)*sizeof(double_t) );
}

void
Coordinatus::moveWorkToNext()
{
    memcpy(next,work,sizeof(work)*sizeof(double_t));

}

void
Coordinatus::setWorkValue(size_t axis,double_t value)
{
    Q_ASSERT(axis < N_AXIS);
    work[axis] = value;
//    sendSignalCoord();
}

double_t
Coordinatus::getWorkvalue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (work[axis]);
}

double_t
Coordinatus::getCurrentValue(size_t axis)
{
    Q_ASSERT(axis < N_AXIS);

    return (current[axis]);
}

double_t
Coordinatus::getNextValue(size_t axis)
{
    Q_ASSERT(axis<N_AXIS);

    return (next[axis]);
}

void
Coordinatus::sendSignalCoord()
{
//    emit(sg_coordUpdated());
}


/**
 * Загрузка данных из профиля.
 */
void
Coordinatus::setupProfileData() {
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





//==================

