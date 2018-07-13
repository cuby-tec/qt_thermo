
#include "coordinatuswindow.h"
#include "myglobal.h"
#include "gconsole.h"
#include "links/exchange/eModelstate.h"


CoordinatusWindow::CoordinatusWindow(QObject *parent) : QObject(parent)
{

}


CoordinatusWindow::CoordinatusWindow(Ui::MainWindow* ui)
{
    this->uic = ui;
    setupCoordinatus();
}



void
CoordinatusWindow::setupCoordinatus()
{
    coordinatus = Coordinatus::instance();
//    connect(coordinatus,SIGNAL(sg_coordUpdated()),this, SLOT(update()) );

}


#define ui_pos(arg1) uic->c_label_pos##arg1##_value->setText(QString("%1").arg(coordinatus->getWorkvalue( arg1##_AXIS )))

void CoordinatusWindow::update(const Status_t *status)
{
    uint8_t ms_state;
    if(coordinatus->isAbsolute())
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_absolute);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_abs_title);
    }else
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_relative);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_rel_title);
    }

    uic->c_label_queueState->setText(QString("%1").arg(status->modelState.queueState)) ;

    /*
     * enum eModelstate{
     *     ehIdle = 1, ehIwork, ehWait_instrument1, ehWait_instrument2,
     *     ehException, ehEnder1, ehEnder2, ehEnder3, ehEnder4, ehEnder5, ehEnder6
     * };
     */


    const QString state1("ehIdle");
    const QString state2("ehIwork");

    QString t_state;

    ms_state = status->modelState.modelState;

    switch (ms_state) {
    case ehIdle:
        t_state = state1;
        break;

    case ehIwork:
        t_state = state2;
        break;

    default:
        break;
    }
//     uic->c_label_modelState->setText(QString("%1").arg(status->modelState.modelState));
    uic->c_label_modelState->setText(QString(t_state));

    uic->c_label_temperature->setText(QString("%1 C").arg(status->temperature,0,'g',4) );//&deg;

    uic->label_contiCnt->setText(QString("%1").arg(status->instrument2_parameter) );

//    double_t d = comdata->getPath_mm();

    uic->c_label_posX_value->setText(QString("%1 (%2)").arg(comdata->getPath_mm(X_AXIS,status->coordinatus[X_AXIS])).arg(status->coordinatus[X_AXIS]));
    uic->c_label_posY_value->setText(QString("%1 (%2)").arg(comdata->getPath_mm(Y_AXIS,status->coordinatus[Y_AXIS])).arg(status->coordinatus[Y_AXIS]));
    uic->c_label_posZ_value->setText(QString("%1 (%2)").arg(comdata->getPath_mm(Z_AXIS,status->coordinatus[Z_AXIS])).arg(status->coordinatus[Z_AXIS]));
    uic->c_label_posE_value->setText(QString("%1").arg(status->coordinatus[E_AXIS]));


}

void
//CoordinatusWindow::update(const Status_t* status, QObject *pgconsole)
CoordinatusWindow::update(const Status_t* status, ComData *pgconsole)
{
//    GConsole* gconsole = (GConsole*) pgconsole;
    ComData* gconsole =  pgconsole;
//    gconsole;
    uint8_t ms_state;

    if(coordinatus->isAbsolute())
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_absolute);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_abs_title);
    }else
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_relative);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_rel_title);
    }
/*    ui_pos(X);
    ui_pos(Y);
    ui_pos(Z);
    ui_pos(E);
*/
    double_t d = gconsole->getPath_mm(X_AXIS,status->coordinatus[X_AXIS]);
    uint32_t c = status->coordinatus[X_AXIS];
QString str = QString("%1 (%2)").arg(gconsole->getPath_mm(X_AXIS,status->coordinatus[X_AXIS])).arg(status->coordinatus[X_AXIS]);
    uic->c_label_posX_value->setText(QString("%1 (%2)").arg(gconsole->getPath_mm(X_AXIS,status->coordinatus[X_AXIS])).arg(status->coordinatus[X_AXIS]));
    uic->c_label_posY_value->setText(QString("%1 (%2)").arg(gconsole->getPath_mm(Y_AXIS,status->coordinatus[Y_AXIS])).arg(status->coordinatus[Y_AXIS]));
    uic->c_label_posZ_value->setText(QString("%1 (%2)").arg(gconsole->getPath_mm(Z_AXIS,status->coordinatus[Z_AXIS])).arg(status->coordinatus[Z_AXIS]));
    uic->c_label_posE_value->setText(QString("%1").arg(status->coordinatus[E_AXIS]));

     uic->c_label_queueState->setText(QString("%1").arg(status->modelState.queueState)) ;

     /*
      * enum eModelstate{
      *     ehIdle = 1, ehIwork, ehWait_instrument1, ehWait_instrument2,
      *     ehException, ehEnder1, ehEnder2, ehEnder3, ehEnder4, ehEnder5, ehEnder6
      * };
      */


     const QString state1("ehIdle");
     const QString state2("ehIwork");

     QString t_state;

     ms_state = status->modelState.modelState;

     switch (ms_state) {
     case ehIdle:
         t_state = state1;
         break;

     case ehIwork:
         t_state = state2;
         break;

     default:
         break;
     }
//     uic->c_label_modelState->setText(QString("%1").arg(status->modelState.modelState));
     uic->c_label_modelState->setText(QString(t_state));

     uic->c_label_temperature->setText(QString("%1 C").arg(status->temperature,0,'g',4) );//&deg;

     uic->label_contiCnt->setText(QString("%1").arg(status->instrument2_parameter) );
}

