
#include "controller.h"

#include <QScopedPointer>
#include <QtGlobal>
#include <QDebug>
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

	//  Путь по X
	//	Путь по Y
	//	Путь по Z
	double_t path[M_AXIS];						//	B2

	for(int i=0;i<M_AXIS;i++){
		path[i] = cord->getCurrentValue(i) - cord->getNextValue(i);
		qDebug()<<"Controller[74]"<<" path:"<< path[i];
	}


// Длина вектора.
  double_t s = 0;

    for(int i=0; i<M_AXIS;i++){
        s += pow( cord->getCurrentValue(i)-cord->getNextValue(i),2);
	}
	s = sqrt(s);

// Максимальная скорость по осям(линейная)
    double_t v[M_AXIS];

    for(int i=0;i<M_AXIS;++i){
//		v[i] = motor->linespeed(profileData.speed_rpm[i]);
//        v[i] = (motor->*m_struct[i])(profileData.speed_rpm[i]);
        convert pf = motor->m_struct[i];
        v[i] = fabs((motor->*pf)(profileData.speed_rpm[i]));
//varant 2:     v[i] = (motor->*motor->m_struct[i])(profileData.speed_rpm[i]);

		//	v = cord->nextBlocks[X_AXIS].nominal_speed; // Число оборотов/мин
	}

    //Максимальная скорость для сегмента
    float_t maxs = *std::max_element(v,v+M_AXIS);	//E13

    //[3] Синусы направлений					C18
    double_t sins[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
        sins[i] = fabs(path[i]/s);
    }

    //[4] Длина линии в шагах						C23
//    uint32_t lenline[M_AXIS];
    for(int i=0;i<M_AXIS;++i){
    	lines pstep = motor->getLineStep[i];
        cord->nextBlocks[i].steps = fabs(path[i])/( motor->*pstep)(i);
//    	lenline[i] = cord->nextBlocks[i].steps;
    	double_t ps = (motor->*pstep)(i);
//        trapeze[i].length = abs(path[i])/( motor->*pstep)(i);
    	double_t pa = path[i];
    	if(pa<0){
            pa = fabs(path[i]);
    	}
    	trapeze[i].length = pa/ps;
    }

    // Наибольшая длина линии						C26
//    uint32_t maxLenLine = *std::max_element(lenline,lenline+M_AXIS);

    //[5] Максимальное Угловое ускорение			C28
    for(int i=0;i<M_AXIS;++i){
    	cord->nextBlocks[i].acceleration = profileData.acceleration[i];
    }


    //[4] velocity for every axis, line		313.16 47.7
    double_t velocity[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	velocity[i] = maxs * sins[i];
    }

    //[5] Угловая скорость							C59
    double_t tSpeed[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	tSpeed[i] = (velocity[i]/motor->getPulleyDiameter())*2;
    }

    //[6] Определяющая координата					C33
/*
    bool isLongest[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	isLongest[i] = (lenline[i] == maxLenLine);
    }
*/

    //[7] Число шагов разгона	34.11 0.79			C38
    double_t accelSteps[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	accelSteps[i] = pow(tSpeed[i],2)/( 2 * motor->getAlfa(i) * profileData.acceleration[i] );
        trapeze[i].accPath = pow(tSpeed[i],2)/( 2 * motor->getAlfa(i) * profileData.acceleration[i] );
    }

    //Максимальное число шагов разгона				D41
    double_t maxAccelSteps = *std::max_element(accelSteps,accelSteps+M_AXIS);

/*
    //[8] Прверка трапеции
    bool isTrapecia[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	isTrapecia[i] = maxAccelSteps*2 < cord->nextBlocks[i].steps;
    }
*/

    // [9] Число шагов разгона пересчёт				C49

    // Построение трапций для осей
    calculateTrapeze();

    //[12] Угловое ускорения для осей					C64
    double_t accel[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	if(trapeze[i].accPath!=0 && trapeze[i].length!=0)
    		accel[i] = pow(tSpeed[i],2)/(2 * motor->getAlfa(i)* fabs(trapeze[i].accPath)); //  trapeze[i].accPath
    	else
    		accel[i] = 0;
    }

    //[13] Начальный счётчик
    uint32_t start_counter[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	if(accel[i]!=0){
    		start_counter[i] = sqrt(2*motor->getAlfa(i)/accel[i])*frequency;
    	    qDebug() << "buildBlock[180]"<< "  axis:"<< i << " counter:"<<start_counter[i]<< "acc:"<< trapeze[i].accPath;

    	}
    	else
    		start_counter[i] = 0;
    }

    //[14] Счётчик номинальной скорости		C90
    uint32_t norm_counter[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	if(tSpeed!=0)
    		norm_counter[i] = frequency * motor->getAlfa(i)/fabs(tSpeed[i]);
    	else
    		norm_counter[i] = 0;
    }


    // calculate acceleration Построение таблицы шагов разгона.
    AccelerationTable* tableX = new AccelerationTable(trapeze[X_AXIS].accPath + 1);
    tableX->buildTale(start_counter[X_AXIS]);
    float_t accTime = tableX->getAccelerationTime(FREQUENCY);

/*
    	qDebug()<<" buildBlock[192] =========";
    for(int i=0;i<trapeze[X_AXIS].accPath;i++)
    {
    	qDebug()<<" step:"<<i <<"\tcount:"<< tableX->getCounter(i);
    }
*/
    AccelerationTable* accY = new AccelerationTable(trapeze[Y_AXIS].accPath+1);
    accY->buildTale(start_counter[Y_AXIS]);

    qDebug()<< "buildBlock[192]";
    qDebug()<< " acc:"<< trapeze[X_AXIS].accPath << " \t path:"<< trapeze[X_AXIS].length
    		<<"\tstart:"<<start_counter[X_AXIS]
    		<<"\tspeed:"<<tableX->getCounter(trapeze[X_AXIS].accPath)
			<<"\tflat:"<<norm_counter[X_AXIS];

    qDebug()<< " acc:"<< trapeze[Y_AXIS].accPath << " \t path:"<< trapeze[Y_AXIS].length
    		<<"\tstart:"<<start_counter[Y_AXIS]
    		<< "\tspeed:"<< accY->getCounter(trapeze[Y_AXIS].accPath)
			<<"\tflat:"<<norm_counter[Y_AXIS];

    qDebug()<< " acc:"<< trapeze[Z_AXIS].accPath << " \t path:"<< trapeze[Z_AXIS].length
    		<<"\t\tflat:"<<norm_counter[Z_AXIS];


} //

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




// Расчёт трапеций для каждой оси.
void Controller::calculateTrapeze() {
	double_t lenline[M_AXIS];
	uint32_t index; 			//Главная трапеция.
	double_t coeffic;

	for(int i=0;i<M_AXIS;i++)
		lenline[i] = trapeze[i].length;
    // Наибольшая длина линии						C26
    double_t* pmaxLenLine = std::max_element(lenline,lenline+M_AXIS);
    index = (pmaxLenLine - lenline)/sizeof(uint32_t);

    //Построение трапеции
    coeffic = (float_t)trapeze[index].accPath/(float_t)trapeze[index].length;

    // Есть трапеция Pass#1
    for(int i=0;i<M_AXIS;++i)
    {
    	if(i!=index)
    		trapeze[i].accPath = trapeze[i].length*coeffic;
    	// Pass#2
    	if(trapeze[i].accPath*2>trapeze[i].length)
    		trapeze[i].accPath = trapeze[i].length/2;
    }

}











