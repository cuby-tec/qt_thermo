/**
  Project: thermo
  Company: CUBY,Ltd
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exchange/exchange.h"
//#include "profile.h"

#include "profiles/profiledialog.h"
#include "thermolog/thermologdialog.h"
#include "profiles/thermopiddialog.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 742, 590);

    createActions(this);

    setupPlot(ui->plot);

}


void
MainWindow::setupPlot(QCustomPlot *customPlot)
{

    ThermoPlot* plotter = new ThermoPlot(customPlot);

}

//----------- Menu ACtions

const QString actionName1(QObject::tr("&Thermo"));
const QString actionName2(QObject::tr("&Config"));
const QString actionName3(QObject::tr("PID params"));

void MainWindow::createActions(MainWindow* w)
{

//    newAct = new QAction(tr("&New"),w);

//    newAct->setStatusTip(tr("Edit profile"));

//    connect(newAct,&QAction::triggered,w,&MainWindow::editProfile);


    optionsMenu = ui->menuOptions;

    optionEditAct = new QAction(tr("&Edit"),w);

    optionEditAct->setStatusTip(tr("Edit profile"));

    optionsMenu->addAction(optionEditAct);

    connect(optionEditAct,&QAction::triggered,w,&MainWindow::editProfile);




    menuTools = ui->menuTools;

    actThermo = new QAction(actionName1,w); // Thermo
    actThermo->setStatusTip("View thermo log.");
    menuTools->addAction(actThermo);
    connect(actThermo,&QAction::triggered,w,&MainWindow::actTermoDo);


    actConfig = new QAction(actionName2,w); // Config

//    QList<QAction *> act = menuTools->findChildren<QAction *>();// Config

//    qDebug() << "MainWindow[61]" << act[0]->text();

    pidParams = new QAction(actionName3,w);//
    pidParams->setStatusTip("setting up PID parameters in current session.");
    menuTools->addAction(pidParams);
    connect(pidParams,&QAction::triggered,w,&MainWindow::pidParamsDo);

}


void
MainWindow::pidParamsDo()
{
    ThermoPIDDialog* tpidDialg = new ThermoPIDDialog(this);
    tpidDialg->show();
}


void
MainWindow::actTermoDo()
{

    qDebug() << "MainWindow::actTermoDo()[103]";

    ThermoLogDialog* thermolog = new ThermoLogDialog(this);

    thermolog->show();

}


void
MainWindow::editProfile()
{
    ProfileDialog* options = new ProfileDialog(this);


    qDebug() << "editProfile 58";
    if(options->exec())
    {
        options->baseSize();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
