#include "profiledialog.h"

#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    uia(new Ui::ProfileDialog)
{
    uia->setupUi(this);
    setupPlot(uia->customPlot);
    setupExchange(uia->tab_2);
}

ProfileDialog::~ProfileDialog()
{
    delete uia;
}

void ProfileDialog::setupPlot(QCustomPlot *customPlot)
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


void ProfileDialog::setupExchange(QWidget* tab)
{

    Exchange* exchange = new Exchange();

    profile = new Profile();

//    connect(tab,SIGNAL(currentIndexChanged(int)), SLOT(on_profileComboBox_currentIndexChanged(int)));

    profile->init_profile(tab);


    exchange->NoOperation();


}



void ProfileDialog::on_profileComboBox_currentIndexChanged(int index)
{
    int i;
    i = index + 1;
    qDebug() << index << " ProfileDialog::on_profileComboBox_currentIndexChanged 81";
//    profile->Profiles_increment(index);
}
