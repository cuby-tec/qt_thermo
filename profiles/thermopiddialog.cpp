#include "thermopiddialog.h"
#include "ui_thermopiddialog.h"
#include <QDebug>

ThermoPIDDialog::ThermoPIDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThermoPIDDialog)
{
    ui->setupUi(this);

    setupFieldes();

    setuButtomBox();

    exch = new UsbExchange();
}

ThermoPIDDialog::~ThermoPIDDialog()
{
    delete ui;
}


void ThermoPIDDialog::setuButtomBox()
{
    buttonBox = ui->buttonBox;

    uploadButton = new QPushButton(tr("Upload"));
    uploadButton->setToolTip("Load data to controllerr.");
    buttonBox->addButton(uploadButton,QDialogButtonBox::ActionRole);
    connect(uploadButton,SIGNAL(clicked(bool)),this,SLOT(upload()));
}


void
ThermoPIDDialog::setupFieldes()
{
    bool ok;

    profile = Profile::instance();

    if(!profile->profileAtive)
    {
        profile->init_profile();
    }

    ui->temprature_lineEdit->setText(profile->get_TEMPERATURE());
    ui->tpropotional_lineEdit->setText(profile->get_PROPTIONAL());
    ui->tintegral_lineEdit->setText(profile->get_INTEGRAL());
    ui->tderivative_lineEdit->setText(profile->get_DERIVATIVE());

    p_temperaature = QString(profile->get_TEMPERATURE()).toFloat(&ok);
    p_propotional = QString(profile->get_PROPTIONAL()).toFloat(&ok);
    p_integral = QString(profile->get_INTEGRAL()).toFloat(&ok);
    p_derived = QString(profile->get_DERIVATIVE()).toFloat(&ok);

    if(!ok)
         qDebug()<<"Error convertion to a float" << "ThermoPIDDialog[43]";


}

/*
 * #ifdef EXAMPLE2
#define KD  12.5//0.1//0.013
#define KP  0.6//0.75
//#define KI  1.0 - KP - KD//0.15
#define KI  0.1
*/
void
ThermoPIDDialog::upload()
{
    int result_exch;

    qDebug()<< "Upload" << "ThermoPIDDialog::upload[65]";

    exch->buildComData(&request,eoProfile);

    request.payload.instrument_hotend.temperature = (int32_t)(p_temperaature*1000);
    request.payload.instrument_hotend.kp = (int32_t)(p_propotional*1000);
    request.payload.instrument_hotend.ki = (int32_t)(p_integral*1000);
    request.payload.instrument_hotend.kd = (int32_t)(p_derived*1000);

    request.requestNumber = ++MyGlobal::commandIndex;

    thermo_gmutex.lock();

    result_exch = exch->sendRequest(&request);

    if(result_exch == EXIT_SUCCESS)
    {
        status = exch->getStatus();
        qDebug()<<status->frameNumber<< "ThermoPIDDialog::upload[87]";
    }else{
        qDebug()<<" Error in exchange over USB. "<<"ThermoPIDDialog::upload[89]";
    }

     thermo_gmutex.unlock();

}

void ThermoPIDDialog::on_temprature_lineEdit_textEdited(const QString &arg1)
{
    bool ok;
    p_temperaature = arg1.toFloat(&ok);
    if(!ok)
        qDebug()<<"Error convertion to a float" << "ThermoPIDDialog[55]";
}

void ThermoPIDDialog::on_tpropotional_lineEdit_textEdited(const QString &arg1)
{
    bool ok;
    p_propotional = arg1.toFloat(&ok);
    if(!ok)
        qDebug()<<"Error convertion to a float" << "ThermoPIDDialog[63]";
}


void ThermoPIDDialog::on_tintegral_lineEdit_textEdited(const QString &arg1)
{
    bool ok;
    p_integral = arg1.toFloat(&ok);
    if(!ok)
        qDebug()<<"Error convertion to a float" << "ThermoPIDDialog[72]";
}

void ThermoPIDDialog::on_tderivative_lineEdit_textEdited(const QString &arg1)
{
    bool ok;
    p_derived = arg1.toFloat(&ok);
    if(!ok)
        qDebug()<<"Error convertion to a float" << "ThermoPIDDialog[80]";
}
