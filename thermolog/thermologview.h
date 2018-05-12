#ifndef THERMOLOGVIEW_H
#define THERMOLOGVIEW_H


#include <QStringList>


#include "qcustomplot.h"




/*
 * Чтение лог-файла и отображение его на графике.
 * Company: CUBY,Ltd
 *
*/

class ThermoLogView
{
public:
    ThermoLogView();

    ThermoLogView(QCustomPlot* plot);

    void setStrData(QStringList * lst){ this->strdata = lst;  }


public slots:
    void drawLogData(QStringList *lst);



private:
    QCustomPlot* plot;

    QStringList* strdata;


    QStringList parse(QString str);

    void setupPlot(QCustomPlot *customPlot);

};

#endif // THERMOLOGVIEW_H
