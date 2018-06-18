
#include "controller.h"

#include <QScopedPointer>
#include <QtGlobal>
#include <QDebug>
#include <math.h>
#include <stdbool.h>

#include "profiles/profile.h"

#include <algorithm>


Controller::Controller()
{
    frequency = FREQUENCY;
    for(int i=0;i<N_AXIS;i++)
    {
        pcountertime[i] = NULL;
    }

    setupProfileData();

    motor[X_AXIS] = new StepMotor(e17HS4401_pulley);
    motor[X_AXIS]->setAcceleration(profileData.acceleration[X_AXIS]);

    motor[Y_AXIS] = new StepMotor(e17HS4401_pulley);
    motor[Y_AXIS]->setAcceleration(profileData.acceleration[Y_AXIS]);

    motor[Z_AXIS] = new StepMotor(e17HS4401_shuft);
    motor[Z_AXIS]->setAcceleration(profileData.acceleration[Z_AXIS]);

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

    Q_ASSERT(motor[X_AXIS]->getAcceleration() != NULL);

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
		path[i] = cord->getNextValue(i) - cord->getCurrentValue(i);
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

//        convert pf = motor->getLineSpeed[i];
//        v[i] = fabs((motor->*pf)(profileData.speed_rpm[i]));
        StepMotor* m = motor[i];
        convert pm = m->getLineSpeed;
        v[i] = fabs((m->*pm)(profileData.speed_rpm[i]));


//varant 2:     v[i] = (motor->*motor->m_struct[i])(profileData.speed_rpm[i]);

		//	v = cord->nextBlocks[X_AXIS].nominal_speed; // Число оборотов/мин
	}

    //Максимальная скорость для сегмента
    double_t maxs = *std::max_element(v,v+M_AXIS);	//E13

    //[3] Синусы направлений					C18
    double_t sins[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
        sins[i] = fabs(path[i]/s);
    }

    //[4] Длина линии в шагах						C23
//    uint32_t lenline[M_AXIS];
    for(int i=0;i<M_AXIS;++i){

        StepMotor* m = motor[i];
        lines lm = m->getLineStep;
//    	lines pstep = motor->getLineStep[i];
//        cord->nextBlocks[i].steps = fabs(path[i])/( motor->*pstep)(i);
        cord->nextBlocks[i].steps = fabs(path[i])/( m->*lm)(i);//TODO в сборку блока

//    	lenline[i] = cord->nextBlocks[i].steps;
//    	double_t ps = (motor->*pstep)(i);
        double_t ps = (m->*lm)(i);

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
    	cord->nextBlocks[i].acceleration = profileData.acceleration[i];// TODO в сборку блокаS
    }


    //[4] velocity for every axis, line		313.16 47.7 	C54
    double_t velocity[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	velocity[i] = maxs * sins[i];
    }


    //[5] Угловая скорость							C59
    double_t tSpeed[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
        tSpeed[i] = (velocity[i]/motor[i]->getPulleyDiameter())*2;
    	qDebug()<<"Controller[142] "<< "speed:"<<tSpeed[i];
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
        accelSteps[i] = pow(tSpeed[i],2)/( 2 * motor[i]->getAlfa(i) * profileData.acceleration[i] );
        trapeze[i].accPath = pow(tSpeed[i],2)/( 2 * motor[i]->getAlfa(i) * profileData.acceleration[i] );
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

    // Построение трапеций для осей
    uint32_t index = calculateTrapeze();

    // motor[X_AXIS]
    double_t maxLineAccel = motor[index]->getLinearAcceleration();

    // Время разгона для оси X
    double_t minimeAccelerationTime = velocity[index]/maxLineAccel;

#define ACCELERTION_BY_TIME
// 0,0002%

    //[12] Угловое ускорения для осей					C64
    double_t accel[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
        if(trapeze[i].accPath!=0 && trapeze[i].length!=0){
#ifdef ACCELERTION_BY_TIME
            accel[i] = (2 * motor[i]->getAlfa(i)*(trapeze[i].accPath))/pow(minimeAccelerationTime,2); //  trapeze[i].accPath
#else
            accel[i] = pow(tSpeed[i],2)/(2 * motor[i]->getAlfa(i)* fabs(trapeze[i].accPath)); //  trapeze[i].accPath
#endif

        }else{

    		accel[i] = 0;

        }
    	qDebug()<<"Controller[182"<< "  accel:"<<accel[i]<< "\taccPath:"<<trapeze[i].accPath;
    }

    //[13] Начальный счётчик
    uint32_t start_counter[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	if(accel[i]!=0){
            start_counter[i] = sqrt(2*motor[i]->getAlfa(i)/accel[i])*frequency;
    	    qDebug() << "buildBlock[180]"<< "  axis:"<< i << " counter:"<<start_counter[i]<< "acc:"<< trapeze[i].accPath;

    	}
    	else
    		start_counter[i] = 0;
    }

    //[14] Счётчик номинальной скорости		C90
    uint32_t norm_counter[M_AXIS];
    for(int i=0;i<M_AXIS;i++){
    	if(tSpeed!=0)
            norm_counter[i] = frequency * motor[i]->getAlfa(i)/fabs(tSpeed[i]);
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

    // Сборка============>>>>>>>>>>

    block_state_t* blocks = cord->nextBlocks;
//    block->steps
//    block->accelerate_until
//    block->decelerate_after
//    block->initial_rate
//    block->nominal_rate
//    block->final_rate
//    block->axis_mask;
//    block->direction_bits
//    block->initial_speedLevel
//    block->final_speedLevel
//    block->schem

//TODO build block

    for(int i=0;i<M_AXIS;++i){
    	block_state_t block = blocks[i];
    	block.steps = trapeze[i].length;
    	block.speedLevel = trapeze[i].accPath;
    	block.accelerate_until = trapeze[i].accPath;
    	block.decelerate_after = block.steps-(word)trapeze[i].accPath;
    	block.initial_rate = start_counter[i];
    	block.nominal_rate = norm_counter[i];
    	block.final_rate = start_counter[i];
    	block.entry_speed = 0;
    	block.nominal_speed = tSpeed[i];
    	block.path = path[i];
    	block.schem[0] = 0;	// Разгон
    	block.schem[1] = 1;	// равномерно
    	block.schem[2] = 2;	// торможение
    	block.microstep = 0; //TODO Micro-step

    }

    splinePath(cord->currentBlocks,blocks);

} //


/**
 * Выравнивание скоростей в смежных сегментах.
 * Для одноразовой команды это не требуется.
 */
void Controller::splinePath(block_state_t* privBlock, block_state_t* currBlock) {
	double_t dif;

	 Recalculate_flag* flag;
	 flag = (Recalculate_flag*)&currBlock[X_AXIS].recalculate_flag;

	 if(flag->single == true)
		 return;


	dif = currBlock[X_AXIS].nominal_speed - privBlock[X_AXIS].nominal_speed;


	//TODO set scheme

}

/*                             STEPPER RATE DEFINITION
		                                     +--------+   <- nominal_rate
		                                    /          \
		    nominal_rate*entry_factor ->   +            \
		                                   |             + <- nominal_rate*exit_factor
		                                   +-------------+
		                                       time -->


	  	                              PLANNER SPEED DEFINITION
		                                     +--------+   <- current->nominal_speed
		                                    /          \
		         current->entry_speed ->   +            \
		                                   |             + <- next->entry_speed
		                                   +-------------+
		                                       time -->
 */
//#define CO		psettings->initial_rate/0.676
void
Controller::planner_recalculate(block_state* prev, block_state* curr)
{
	int16_t dlevel,d2;
	word meanlevel;
	word tmp_rate;

	double_t CO = 1.0;//TODO temporary value for debug.

	if(prev->speedLevel == curr->speedLevel) return;

	meanlevel = ((int64_t)prev->nominal_rate + curr->nominal_rate)/2;

	if(prev->speedLevel>curr->speedLevel){
		// Снижение скорости
		dlevel = prev->speedLevel - curr->speedLevel;
		d2 = dlevel/2;
		dlevel -= d2;
		prev->decelerate_after = prev->steps - d2;
		curr->accelerate_until = dlevel;	// todo if dlevel/2 > accelerate_until
		prev->schem[2] = 3;
		curr->schem[0] = 4;

		d2 = prev->speedLevel-d2;
		if(d2){
			prev->final_speedLevel = d2;
			tmp_rate = (word)(CO)*(sqrtf(d2+1)-sqrtf(d2));
			prev->final_rate = (tmp_rate>meanlevel)?(tmp_rate):(meanlevel);
		}
		dlevel += curr->speedLevel;
		if(dlevel){
			curr->initial_speedLevel = dlevel;
			tmp_rate = (word)CO*(sqrtf(dlevel+1)-sqrtf(dlevel));
			curr->initial_rate = (tmp_rate>meanlevel)?(tmp_rate):(meanlevel);

		}
	}else{
		// Увеличение скорости
		dlevel = curr->speedLevel - prev->speedLevel;
		word rest = prev->steps - prev->decelerate_after;
		if(rest>dlevel){
			d2 = dlevel/2;
		}else{
			d2 = rest;
		}
		dlevel -= d2;

		prev->decelerate_after = prev->steps - d2;
		curr->accelerate_until = dlevel;	// todo if dlevel/2 > accelerate_until
		prev->schem[2] = 6;
		curr->schem[0] = 1;
		d2 +=prev->speedLevel;
		if(d2){
			prev->final_speedLevel = d2;
			prev->final_rate = (word)CO*(sqrtf(d2+1)-sqrtf(d2));
		}
		dlevel = curr->speedLevel - dlevel;
		if(dlevel){
			curr->initial_rate = (word)CO*(sqrtf(dlevel+1)-sqrtf(dlevel));
			curr->initial_speedLevel = dlevel;
		}
	}
	//------------------------- check state go

}




#define TRAPEZE_V1
// Длина участка принимается как целое число
// Расчёт трапеций для каждой оси.
/**
 * @brief Controller::calculateTrapeze
 * @return Индекс приоритетной оси.
 */
uint32_t
Controller::calculateTrapeze() {
	double_t lenline[M_AXIS];
	uint32_t index; 			//Главная трапеция.
	double_t coeffic;

	for(int i=0;i<M_AXIS;i++)
		lenline[i] = trapeze[i].length;
    // Наибольшая длина линии						C26
    double_t* pmaxLenLine = std::max_element(lenline,lenline+M_AXIS);
    index = (pmaxLenLine - lenline)/sizeof(uint32_t);

    //Построение трапеции
#ifdef TRAPEZE_V1
    coeffic = trapeze[index].accPath/ floor(trapeze[index].length) ;
#else
    coeffic = trapeze[index].accPath/trapeze[index].length;
#endif
    // Есть трапеция Pass#1
    for(uint i=0;i<M_AXIS;++i)
    {
        if(i!=index){
#ifdef TRAPEZE_V1
            trapeze[i].accPath = floor(trapeze[i].length) * coeffic;
#else
            trapeze[i].accPath = trapeze[i].length * coeffic;
#endif
        }
    	// Pass#2
        if(trapeze[i].accPath*2>trapeze[i].length){
#ifdef TRAPEZE_V1
            trapeze[i].accPath = floor( trapeze[i].length )/2;
#else
            trapeze[i].accPath = trapeze[i].length/2;
#endif

        }
    }

    return index;
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

