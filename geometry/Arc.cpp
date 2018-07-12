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
	alfa = 0.0;
	angle = 0.0;
	beta_start = 0.0;
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
	Point result;

/*
	//= D$5-ACOS((B$5-$B$3+B$7*A11)/B$4)
//	double_t alfa1 = beta_start - acos((start.x-center.x+precicion*number)/radious);
	Point alphaP = new Point(start.x + precicion*number,start.y);
	double_t alfa1 = beta_start - calcAngleX(alphaP,center);
	double_t beta1 = beta_start - asin((start.y - center.y+precicion*number)/radious);
*/
	result.x = center.x + radious*cos(beta_start - number*alfa);
	result.y = center.y + radious*sin(beta_start - number*alfa);
	return (result);
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
	alfa = 2.0*asin(precicion/(2.0*radious));

}

//TODO calculate
void Arc::calculate() {

    if((std::isnan(radious)) || (radious == 0)){
		calculateRadious();
	}

	Q_ASSERT((radious != qQNaN()) && (radious != 0) );


#define I9 		beta_startAbs
#define I10 	beta_endAbs
//#define H3 vector

	// start point angle
	Point startdistance = start - center;
	double_t beta_startAbs = atan(startdistance.y/startdistance.x);// I9
	double_t beta_startY = asin(startdistance.y/radious);

//		assert(enddistance.x <= radious);
//	Q_ASSERT(enddistance.x <= radious);

	Point enddistance = end - center;
	double_t beta_endAbs = atan(enddistance.y/enddistance.x);
	double_t beta_endY = acos(enddistance.y/radious);	//, beta_end;

	double_t K9;
	double_t K10;

	//Start
	uint8_t H3 = 0;
	if(startdistance.x < 0)
		H3 |= 0x01;
	if(startdistance.y < 0)
		H3 |= 0x02;
	//=IF(H3=1;180+I9;IF(H3=0 AND(G3=0);I9;IF(H3=0 AND(G3=1);360+I9;0)))

	// End
	uint8_t H4 = 0;
	if(enddistance.x < 0)
		H4 |= 0x01;
	if(enddistance.y < 0)
		H4 |= 0x02;
	//=IF(H5=1;180+I10;IF(H5=0 AND(G5=0);I10;IF(H5=0 AND(G5=1);360+I10;0)))


	if(H3 & 0x01){
		K9 = MyGlobal::PI + I9;
	}else if(H3 == 0){
		K9 = I9;
	}else if(H3 == 2){
		K9 = 2.0*MyGlobal::PI + I9;
	}
	beta_start = K9;

	if(H4 & 0x01){
		K10 = MyGlobal::PI + I10;
	}else if(H4 == 0){
		K10 = I10;
	}else if(H4 == 2){
		K10 = 2.0*MyGlobal::PI + I10;
	}

	beta_end = K10;

	double_t L10 = beta_start-beta_end;
	if(clockWise){
		//=IF((K9-K10)<0;360+(K9-K10);(K9-K10))
		if(L10 < 0){
			angle = 2.0*MyGlobal::PI + L10;
		}else{
			angle = L10;
		}


	}else{

		//=IF(L30>0;360-L30;L30)
		if(L10>0){
			angle = 2.0*MyGlobal::PI - L10;
		}else{
			angle = L10;
		}

	}

	angle = fabs(angle);

	//	angle = std::abs(beta_start - beta_end);

	assert(alfa!=0);
	points_number = std::floor( angle/alfa);

	/*
	qDebug()<<"Arc[164] beta_start:"<<MyGlobal::DEGREES(beta_start)<< "\tbeta_end:"<<MyGlobal::DEGREES(beta_end)<<"\tangle:"
			<<MyGlobal::DEGREES(angle)<<"\tpoints_number:"<<points_number ;
	 */

}

double_t Arc::calcAngleX(Point &start, Point &center) {
	double_t angle;

	Q_ASSERT((radious != qQNaN()) && (radious != 0) );

    Point startdistance = start - center;
	angle = acos(startdistance.x/radious);

	uint8_t vector = 0;
	if(startdistance.x < 0)
		vector |= 0x01;
	if(startdistance.y < 0)
		vector |= 0x02;

	switch(vector)
	{
	case 0:
	case 1:
		beta_start = angle;
		break;

	case 2:
	case 3:
		beta_start = 2.0*MyGlobal::PI - angle;
		break;
	}

	return angle;
}

double_t Arc::calcAngleY(Point &start, Point &center) {
	double_t angle;

	Q_ASSERT((radious != qQNaN()) && (radious != 0) );

    Point startdistance = start - center;
	angle = asin(startdistance.y/radious);

	uint8_t vector = 0;
	if(startdistance.x < 0)
		vector |= 0x01;
	if(startdistance.y < 0)
		vector |= 0x02;

	switch(vector)
	{
	case 0:
	case 1:
		beta_start = angle;
		break;

	case 2:
	case 3:
		beta_start = 2.0*MyGlobal::PI - angle;
		break;
	}

	return angle;

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
