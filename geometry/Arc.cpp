/*
 * Arc.cpp
 *
 *  Created on: 28.06.2018
 *      Author: walery
 */


#include "Arc.h"
#include <QtGlobal>
#include <QDebug>
#include "mLine.h"
#include <cmath>
#include "myglobal.h"

Arc::Arc() {
	// TODO Auto-generated constructor stub
	this->radious = qQNaN();
	this->precicion = qQNaN();
	this->points_number = NULL;
	clockWise = true;
}

Arc::~Arc() {
	// TODO Auto-generated destructor stub
}

void
Arc::setStart(QString x, QString y)
{
	bool ok;

    x.replace(',','.');

	start.x = x.toDouble(&ok);
	Q_ASSERT(ok);

    y.replace(',','.');
	start.y = y.toDouble(&ok);
	Q_ASSERT(ok);
}

void
Arc::setEnd(QString x, QString y)
{
	bool ok;
	end.x = x.toDouble(&ok);
	Q_ASSERT(ok);

	end.y = y.toDouble(&ok);
	Q_ASSERT(ok);
}

void
Arc::setCenter(QString x, QString y) {
	bool ok;

	center.x = x.toDouble(&ok);
	Q_ASSERT(ok);

	center.y = y.toDouble(&ok);
	Q_ASSERT(ok);

    mLine* line = new mLine();

	this->radious = line->getLength();

}

void Arc::setRadious(QString r) {
	bool ok;

	radious = r.toDouble(&ok);

	Q_ASSERT(ok);
}

void Arc::calculateRadious() {

	radious = sqrt(pow((start.x-center.x),2.0)+pow((start.y - center.y),2.0));

	calculateAlfa();

}

Point Arc::getPoint(size_t number) {
// TODOH Arc::getPoint


}

void
Arc::setPrecicion(QString pstr)
{
	bool ok;
    QString tstr = pstr.replace(',','.');

    double_t precicion = tstr.toDouble(&ok);
	Q_ASSERT(ok);

	setPrecicion(precicion);
}


void
Arc::setPrecicion(double_t precicion) {

	this->precicion = precicion;

}

//TODO calculate
void Arc::calculate() {

    if((std::isnan(radious)) || (radious == 0)){
		calculateRadious();
	}

	Q_ASSERT((radious != qQNaN()) && (radious != 0) );



	// start point angle
	Point startdistance = start - center;
	double_t beta_startX = acos(startdistance.x/radious);
//	double_t beta_startY = asin(startdistance.y/radious);


	double_t beta_start, beta_end;

	uint8_t vector = 0;
	if(startdistance.x < 0)
		vector |= 0x01;
	if(startdistance.y < 0)
		vector |= 0x02;

	switch(vector)
	{
	case 0:
	case 1:
		beta_start = beta_startX;
		break;

	case 2:
	case 3:
		beta_start = 2.0*MyGlobal::PI - beta_startX;
		break;
	}

	Point enddistance = end - center;
	double_t beta_endX = acos(enddistance.x/radious);
	if(enddistance.x < 0)
		vector |= 0x01;
	if(enddistance.y < 0)
		vector |= 0x02;
	switch(vector)
	{
	case 0:
	case 1:
		beta_end = beta_endX;
		break;

	case 2:
	case 3:
		beta_end = 2.0*MyGlobal::PI - beta_endX;
		break;
	}

	angle = std::abs(beta_start - beta_end);

	qDebug()<<"Arc[164] beta_start:"<<MyGlobal::DEGREES(beta_start)<< "\tbeta_end:"<<MyGlobal::DEGREES(beta_end)<<"\tangle:"<<MyGlobal::DEGREES(angle) ;



}

void Arc::calculateAlfa() {

    Q_ASSERT((radious != qQNaN()) && (radious != 0) );

	// Угол сегмента
	alfa = 2.0 * asin(precicion/(radious*2.0));

	//=SQRT(SUMSQ(B3-B4;C3-C4))
//	double_t chorda = 0;
//	mLine* dl = new mLine(start,end);
//	chorda = dl->getLength();

//	angle = 2.0 * asin(chorda/(radious*2.0));//TODOH angle +180
}
