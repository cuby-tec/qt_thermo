/**
  Project: thermo
  Company: CUBY,Ltd
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exchange/exchange.h"
//#include "profile.h"

#include "profiles/profiledialog.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 742, 590);

    createActions(this);

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


void MainWindow::editProfile()
{
    ProfileDialog* options = new ProfileDialog(this);


    qDebug() << "71 editProfile";
    if(options->exec())
    {
        options->baseSize();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
