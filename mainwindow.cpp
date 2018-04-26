/**
  Project: thermo
  Company: CUBY,Ltd
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exchange/exchange.h"
#include "profile.h"

#include "profiles/profiledialog.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 742, 590);
//    setupPlot(ui->customPlot);
//    setupExchange((QTabWidget *)ui->tab_2);// profile page

//    editProfile();
    createActions(this);

//    fileMenu = menuBar()->addMenu(tr("&File"));
//    fileMenu->addAction(newAct);


    QMenu *mm = ui->menuOptions;

    QAction* op = mm->findChild<QAction *>("File",Qt::FindDirectChildrenOnly);

    QList<QAction*> lst = ui->menuBar->actions();// children();

//    lst[0]->connect(newAct,&QAction::triggered,&MainWindow::editProfile);
//    connect(lst[0],&QAction::triggered,this,&MainWindow::editProfile);
//    optionsMenu = ui->menuOptions;


    qDebug() << lst[0]->text() << "34 Line" << op;

//    ui->menuStart->addActions(editProfile);

}

void MainWindow::createActions(MainWindow* w)
{

//    newAct = new QAction(tr("&New"),w);

//    newAct->setStatusTip(tr("Edit profile"));

//    connect(newAct,&QAction::triggered,w,&MainWindow::editProfile);


    optionsMenu = ui->menuOptions;

    optionEditAct = new QAction(tr("&Edit"),w);

    optionsMenu->addAction(optionEditAct);

    optionEditAct->setStatusTip(tr("Edit profile"));

    connect(optionEditAct,&QAction::triggered,w,&MainWindow::editProfile);



}


void MainWindow::setupExchange(QTabWidget* tab)
{

    Exchange* exchange = new Exchange();

    profile = new Profile();

//    connect(tab,SIGNAL(currentIndexChanged(int)), SLOT(on_profileComboBox_currentIndexChanged(int)));

    profile->init_profile(tab);


    exchange->NoOperation();

    editProfile();

}


void MainWindow::editProfile()
{
    ProfileDialog* options = new ProfileDialog(this);


    qDebug() << "71 editProfile";
    if(options->exec())
    {
        options->baseSize();
    }
}

/*
void MainWindow::setupPlot(QCustomPlot *customPlot)
{
    plotName = "Hotend temperature";

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
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);

}
*/

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_profileComboBox_currentIndexChanged(int index)
{
    int i;
    i = index + 1;
    qDebug() << index << " MainWindow::on_profileComboBox_currentIndexChanged 81";
    profile->Profiles_increment(index);
}
*/
