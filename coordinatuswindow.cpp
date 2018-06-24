

#include "coordinatuswindow.h"
#include "myglobal.h"

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
/*
void
CoordinatusWindow::update()
{
    if(coordinatus->isAbsolute())
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_absolute);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_abs_title);
    }else
    {
        uic->c_label_positioning_value->setText(MyGlobal::msg_relative);
        uic->c_label_positioning_value->setToolTip(MyGlobal::msg_rel_title);
    }
    ui_pos(X);
    ui_pos(Y);
    ui_pos(Z);
    ui_pos(E);

}
*/
