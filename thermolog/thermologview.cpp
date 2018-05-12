#include "thermologview.h"
#include <QDebug>
#include "myglobal.h"

ThermoLogView::ThermoLogView()
{

}


ThermoLogView::ThermoLogView(QCustomPlot* plot)
{
    this->plot = plot;
    setupPlot(plot);
//    drawLogData();
}




void ThermoLogView::setupPlot(QCustomPlot *customPlot)
{
//    plotName = "Hotend temperature";

//    customPlot->addGraph(); // blue line
//    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//    customPlot->addGraph(); // red line
//    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
//    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);

}


QStringList
ThermoLogView::parse (QString str)
{
    QStringList list;

    str.remove(QChar(' '),Qt::CaseInsensitive);
// TODO
    if(!str.contains("#"))
    {
        list = str.split(MyGlobal::logfileDelimiter,QString::SkipEmptyParts);
    }
    return list;
}


#define PLOT_V1
void
ThermoLogView::drawLogData(QStringList *lst)
{
    qDebug() << "ThermoLogView::drawData[13]"<< lst->size();

    double_t maxValue = 0;

    this->strdata = lst;

#ifdef PLOT_V2
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
    }


//    plot->graph(0)->setData(x,y);
    for(int i=0;i<101;++i)
    {
        plot->graph(0)->addData(x[i],y[i]);
        plot->replot();
    }
#endif

#ifdef PLOT_V1
    // generate some data:



    QVector<double> x(strdata->size()), y(strdata->size()); // initialize with entries 0..100
    bool ok;

    QString line;
    QStringList  dataList;

    if( strdata->size())
    {
        for(int i=0;i<strdata->size();++i){
            x[i] = i;
            line = strdata->at(i);
            dataList = parse(line);
            if(!dataList.isEmpty())
            {
                y[i] = dataList.at(1).toDouble(&ok);
                if(maxValue<y[i])
                    maxValue = y[i];
            }else{
                y[i] = 0;
            }

        }
    }


/*
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
*/

    plot->graph(0)->setData(x, y);

    // set axes ranges, so we see all data:
    plot->xAxis->setRange(-2, strdata->size());
    plot->yAxis->setRange(0, maxValue*1.1);
    plot->replot();
#endif

}



