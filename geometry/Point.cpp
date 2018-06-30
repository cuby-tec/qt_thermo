/*
 * Point.cpp
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */

#include "Point.h"

#include <QtGlobal>


Point::Point(double_t x, double_t y):x(x),y(y)
{
	// TODO Auto-generated constructor stub

}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point Point::operator +(const Point& rhs)  {
	return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator -(const Point& rhs)  {
	return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator =(const Point& rhs)  {
	return Point(x = rhs.x, y = rhs.y);
}
