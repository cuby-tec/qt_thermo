#ifndef COORDINATUSWINDOW_H
#define COORDINATUSWINDOW_H

#include <QMainWindow>
#include <QObject>

#include "gparcer/coordinatus.h"
#include "thermoplot.h"
//#include "gconsole.h"
#include "gparcer/comdata.h"
#include "step_motor/controller.h"


#include <ui_mainwindow.h>

namespace Ui {
class MainWindow;
}

class CoordinatusWindow : public QObject
{
    Q_OBJECT
public:
    explicit CoordinatusWindow(QObject *parent = 0);

    CoordinatusWindow(Ui::MainWindow* ui);

//    void setGconsole(GConsole& g){this->gconsole = &g; }

//    void update(const Status_t *status, QObject *pgconsole);
    void update(const Status_t *status, ComData *pgconsole);

//    void setController(Controller* contr) { this->controller = contr; }

    void setComdata(ComData *value) { this->comdata = value; }

signals:

public slots:
    //    void update();
    void update(const Status_t *status);


private:
    Ui::MainWindow* uic;

    Coordinatus* coordinatus;
    void setupCoordinatus();

//    Controller* controller;
    ComData* comdata;

//    GConsole* gconsole;

};

#endif // COORDINATUSWINDOW_H
