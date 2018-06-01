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
    setGeometry(100, 100, 840, 700);

    createActions(this);

    setupPlot(ui->plot);

    setupGconsole(ui);

    setupCoordinatus(ui);

}

//==============

void
MainWindow::setupCoordinatus(Ui::MainWindow *ui)
{
    coordinatus = new CoordinatusWindow(ui);

}


void
 MainWindow::setupGconsole(Ui::MainWindow* ui)
{
    gconsole = new GConsole(ui);
    connect(ui->pushButton_linestep,SIGNAL(clicked(bool)),gconsole,SLOT(on_pushButton_linestep_clicked()) );
    connect(ui->textEdit_command,SIGNAL(cursorPositionChanged()),gconsole,SLOT(on_textEdit_command_cursorPositionChanged()) );
}


void
MainWindow::updateCoordinatus(const Status_t* status)
{
//    ui->label_posX;
    ui->c_label_posX_value->setText(QString("%1").arg(status->coordinatus[X_AXIS]));
    ui->c_label_posY_value->setText(QString("%1").arg(status->coordinatus[Y_AXIS]));
    ui->c_label_posY_value->setText(QString("%1").arg(status->coordinatus[Z_AXIS]));
    ui->c_label_posE_value->setText(QString("%1").arg(status->coordinatus[E_AXIS]));
}

void
MainWindow::setupPlot(QCustomPlot *customPlot)
{

    plotter = new ThermoPlot(customPlot);
    connect(plotter,SIGNAL(sg_statusChanged(const Status_t*)),this,SLOT(updateCoordinatus(const Status_t* )));

}

//----------- Menu ACtions

const QString actionName1(QObject::tr("&Thermo"));
const QString actionName2(QObject::tr("&Config"));
const QString actionName3(QObject::tr("PID params"));
const QString actionName4(QObject::tr("&Open"));


const QString statusToolTip1(QObject::tr("Open file with G-Code content."));


void MainWindow::createActions(MainWindow* w)
{

//    newAct = new QAction(tr("&New"),w);

//    newAct->setStatusTip(tr("Edit profile"));

//    connect(newAct,&QAction::triggered,w,&MainWindow::editProfile);
//------------------- MENU File
    QMenu* menuFile = ui->menuFile;

    actFileOpen = new QAction(actionName4,w); // File Open.
    actFileOpen->setStatusTip(statusToolTip1);

    menuFile->addAction(actFileOpen);

    connect(actFileOpen,&QAction::triggered,w,&MainWindow::openFileDo);
//    connect(actFileOpen,&QAction::triggered,w,SLOT(openFileDo()));

//--------------------MWNU Options
    optionsMenu = ui->menuOptions;

    optionEditAct = new QAction(tr("&Edit"),w);

    optionEditAct->setStatusTip(tr("Edit profile"));

    optionsMenu->addAction(optionEditAct);

    connect(optionEditAct,&QAction::triggered,w,&MainWindow::editProfile);

//------------------ MENU Tools
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


void MainWindow::openFileDo()
{
QString folder("/home/walery/Документы/3d-printer/ragel"); //home/walery/Документы/3d-printer/ragel/exmple.gcode
    QString filename = QFileDialog::getOpenFileName(this, tr("Open G-Code file"),folder,tr("Gcode (*.gcode );; All (*.*)"));

    if(filename.isNull())
    {
        qDebug() << "File don't selected.";
    }else{

        qDebug()<< "Open faile with G-code file:"<<filename;

        gcodeworker = new GcodeWorker();
        gcodeworker->fileOpen(filename);

    }
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
