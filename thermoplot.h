/**
  Company: CUBY,Ltd
    Класс управления процессом отображения данных
    Термодатчика и управления запросами к Контроллеру.
*/

#ifndef THERMOPLOT_H
#define THERMOPLOT_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "/home/walery/qtcustomplot/qcustomplot/qcustomplot.h"

#include "exchange/thermothread.h"

#include "myglobal.h"


extern MyGlobal mglobal;

enum eIndicate
{
    eiFail, eiGood
};

//#include "links/exchange.h"

class ThermoPlot: public QObject
{
    Q_OBJECT

public:
    //explicit Base(QObject *parent = 0);
    explicit ThermoPlot(QObject * parent = 0);

    ThermoPlot(QCustomPlot *plot);

    ~ThermoPlot()
    {
        logfile.close();
    }

signals:
    void sg_statusChanged(const Status_t* status);


private slots:
  void realtimeDataSlot();
  void updateStatus(const Status_t* status);
  void failedStatus();

private:
  QObject *parent;

    QCustomPlot* plot;

    QString plotName;

    float oldTemperature;

    QTimer dataTimer;

    ThermoThread thread;

    QString logfileName;

    QFile logfile;

    const Status_t* status;

    void setupPlot(QCustomPlot* customPlot);

    void printStatus(const Status_t *c_status);

    void  indicateTemperature(eIndicate ind, QString message);

    void createLog();

    void writeLog();

    QString datetime();

};

#endif // THERMOPLOT_H
