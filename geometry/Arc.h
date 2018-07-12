/*
 * Arc.h
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */

#ifndef THERMO_GEOMETRY_ARC_H_
#define THERMO_GEOMETRY_ARC_H_

#include "Point.h"

#include <inttypes.h>

#include <QString>


class Arc {
public:
	Arc();
	virtual ~Arc();

	void setStart(QString x, QString y);

	void setStart(Point start) {this->start = start; }

	Point getStart() const {return (this->start);}

	void setEnd(QString x, QString y);

	Point getEnd() const {return this->end;}

	void setEnd(Point point){this->end = point; }

	// I,J parameters
	void setCenter(QString x, QString y);

	void setCenter(Point point){ this->center = point; }

	Point getCenter() const {return (this->center);}

	double_t getStartAngle() const {return beta_start;}

	double_t getAlfa(){return alfa;}

	double_t getRadious() const {
		return radious;
	}

	uint32_t getPointsNumber() const {
		return points_number;
	}

	//R parameter
	void setRadious(QString r);

	void setRadious(double_t radious) {
		this->radious = radious;
	}


	void calculateRadious();

	double_t getPrecicion() const {
		return precicion;
	}


	Point getPoint(size_t number);

	void setPrecicion(double_t precicion);

	void setPrecicion(QString pstr);


	bool isClockWise() const {
		return clockWise;
	}

	void setClockWise(bool clockWise) {
		this->clockWise = clockWise;
	}

	// Вычисление угла между вектором и осью X.
	double_t calcAngleX(Point &start, Point &center);

	//Вычисление угла междду вектором и осью Y
	double_t calcAngleY(Point &start, Point &center);

	/*
	 * Построить массив точек траектории
	 */
	void calculate();

private:
	Point start;
	Point end;
	Point center;
	// Минимальная длина дуги.
	double_t precicion;
	double_t radious;

	// Начальный угол дуги.
	double_t beta_start;

	double_t beta_end;//, beta_end;

	//Раствор дуги
	double_t angle; // radian

	// минимальный шаг дуги;определяется микрошагом, конструкцией привода оси.
	double_t alfa; // radian

	uint32_t points_number;

	bool clockWise;// clockWise

	void calculateAlfa();

};

#endif /* THERMO_GEOMETRY_ARC_H_ */
