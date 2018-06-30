/*
 * Line.cpp
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */

#include "mLine.h"


mLine::mLine() {
	// TODO Auto-generated constructor stub

}

mLine::mLine(Point start, Point end)
{
//    :start(start), end(end)
    this->start = start;
    this->end = end;
}


mLine::~mLine() {
	// TODO Auto-generated destructor stub
}

double_t mLine::getLength() {

	Point dp = end - start;

	double_t len = sqrt(pow(dp.x,2)+pow(dp.y,2));

	return len;
}


