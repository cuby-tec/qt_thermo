#include "coordinatuswindow.h"

CoordinatusWindow::CoordinatusWindow(QObject *parent) : QObject(parent)
{

}


CoordinatusWindow::CoordinatusWindow(Ui::MainWindow* ui)
{
    this->uic = ui;

    coordinatus = Coordinatus::instance();
}

/*
 *
 * //    ui->label_posX;
    ui->c_label_posX_value->setText(QString("%1").arg(status->coordinatus[X_AXIS]));
    ui->c_label_posY_value->setText(QString("%1").arg(status->coordinatus[Y_AXIS]));
    ui->c_label_posY_value->setText(QString("%1").arg(status->coordinatus[Z_AXIS]));
    ui->c_label_posE_value->setText(QString("%1").arg(status->coordinatus[E_AXIS]));
 * */
void
CoordinatusWindow::update()
{
    uic->c_label_positioning_value->setText("Tmp");
}
