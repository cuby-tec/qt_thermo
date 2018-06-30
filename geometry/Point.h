/*
 * Point.h
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */

#ifndef THERMO_GEOMETRY_POINT_H_
#define THERMO_GEOMETRY_POINT_H_

#include <math.h>

class Point {
public:
	Point(double_t x = 0,double_t y = 0);
	virtual ~Point();

	// Overload '+' operator as member function of the class
    Point operator+(const Point & rhs) ;

    Point operator-(const Point & rhs) ;

    Point operator =(const Point & rhs);


	double_t x;
	double_t y;

};

#endif /* THERMO_GEOMETRY_POINT_H_ */
