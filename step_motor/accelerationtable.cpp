#include "accelerationtable.h"

#include <QtGlobal>

AccelerationTable::AccelerationTable()
{
    steps = NULL;
    table = NULL;
}

AccelerationTable::AccelerationTable(uint32_t steps) {

	table = (AccelerationTable_t*)malloc(sizeof(AccelerationTable_t)*steps);
	this->steps = steps;
	Q_ASSERT(table!=NULL);

}

AccelerationTable::~AccelerationTable() {
    if(steps != NULL)
		free(table);
}

void AccelerationTable::buildTale(uint32_t startCount) {

	for(int i=0;i<steps;i++){
		switch(i){

		case 0:
			table[i].counter = startCount;
			break;
		case 1:
			table[i].counter = table[i-1].counter*COUNTER_COEFFICIENT;
			break;

		default:
            table[i].counter = table[i-1].counter - table[i-1].counter*2/( 4*i + 1 );
			break;
		}

	}

}

double_t AccelerationTable::getAccelerationTime(uint32_t frequency) {
	float_t result = 0;

	for (int i=0;i<steps;i++){
        result += (float_t)table[i].counter/(float_t)frequency;
	}

	return result;


}

double_t AccelerationTable::getCounter(uint32_t step) {
	Q_ASSERT(step<steps);
    return (table[step].counter);
}




