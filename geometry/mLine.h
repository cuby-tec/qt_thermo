/*
 * Line.h
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */

#ifndef THERMO_GEOMETRY_MLINE_H_
#define THERMO_GEOMETRY_MLINE_H_

#include "Point.h"

class mLine {
public:
	mLine();

	mLine(Point start, Point end);

	virtual ~mLine();

	const Point& getEnd() const {
		return end;
	}

	void setEnd(const Point& end) {
		this->end = end;
	}

	const Point& getStart() const {
		return start;
	}

	void setStart(const Point& start) {
		this->start = start;
	}

	double_t getLength();

	Point start;
	Point end;

};

#endif /* THERMO_GEOMETRY_MLINE_H_ */
