#include "profiledialog.h"

#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    uia(new Ui::ProfileDialog)
{
    uia->setupUi(this);
    setupPlot(uia->customPlot);
    setupExchange();
    setupProfile(uia->tab_3);
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


void ProfileDialog::setupExchange()
{

    Exchange* exchange = new Exchange();

    exchange->NoOperation();
}

void ProfileDialog::fillProfilePage()
{
    int index;
    QString str;
//---------------------- Page 1
    index = uia->profileComboBox->currentIndex();

    uia->pfofileNameEdit->setText(profile->getProfileName(index));

    uia->profileDescription_textEdit->setText(profile->getProfileDescription(index));

    uia->profileFile_Edit->setText(profile->getProfileFileName(index));

    if(profile->isDefaultProfile(index))
        uia->profileDefault_checkBox->setCheckState(Qt::Checked);
    else
        uia->profileDefault_checkBox->setCheckState(Qt::Unchecked);

//----------------- Page 2 Temperature

    uia->temprature_lineEdit->setText(profile->get_TEMPERATURE());
    uia->tpropotional_lineEdit->setText(profile->get_PROPTIONAL());
    uia->tintegral_lineEdit->setText(profile->get_INTEGRAL());
    uia->tderivative_lineEdit->setText(profile->get_DERIVATIVE());

}

void  ProfileDialog::setupProfile(QWidget * tab)
{
    profile = new Profile();
    if( profile->init_profile())
    {
        for(int i=0;i<profile->getProfileNameCount();i++)
        {
            uia->profileComboBox->addItem(profile->getProfileName(i));
        }

        fillProfilePage();

    }
    //    connect(tab,SIGNAL(currentIndexChanged(int)), SLOT(on_profileComboBox_currentIndexChanged(int)));

}

//-------- slot
void ProfileDialog::on_profileComboBox_currentIndexChanged(int index)
{
    int i;
    i = index + 1;
    qDebug() << index << " ProfileDialog::on_profileComboBox_currentIndexChanged 71";
//    profile->Profiles_increment(index);
}


void ProfileDialog::on_profile_pushButton_Save_clicked()
{
    profile->saveProfileDocument(); // Save current Document
}

void ProfileDialog::on_temprature_lineEdit_editingFinished()
{
    profile->set_TEMPERATURE(uia->temprature_lineEdit->text());
}
