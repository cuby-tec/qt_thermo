#include "aboutwindow.h"
#include "ui_aboutwindow.h"

Aboutwindow::Aboutwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aboutwindow)
{
    ui->setupUi(this);
}

Aboutwindow::~Aboutwindow()
{
    delete ui;
}
