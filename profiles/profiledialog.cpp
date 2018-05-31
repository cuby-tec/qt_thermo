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
    profileSaved = true;
}

ProfileDialog::~ProfileDialog()
{
    delete uia;
}

#define RealtimeData

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

    Exchange* exchange = Exchange::instance() ;

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
    //DEFAULT_X_STEPS_PER_MM
    uia->lineEdit_X_STEPS->setText(profile->getX_STEPS());
    //DEFAULT_Y_STEPS_PER_MM
    uia->lineEdit_Y_STEPS->setText(profile->getY_STEPS());
    //DEFAULT_Z_STEPS_PER_MM
    uia->lineEdit_Z_STEPS->setText(profile->getZ_STEPS());
    //DEFAULT_X_MAX_RATE
    uia->lineEdit_X_RATE->setText(profile->getX_MAX_RATE());
    //DEFAULT_Y_MAX_RATE
    uia->lineEdit_Y_RATE->setText(profile->getY_MAX_RATE());
    //DEFAULT_Z_MAX_RATE
    uia->lineEdit_Z_RATE->setText(profile->getZ_MAX_RATE());
    //DEFAULT_X_ACCELERATION
    uia->lineEdit_X_ACCEL->setText(profile->getX_ACCELERATION());
    //DEFAULT_Y_ACCELERATION
    uia->lineEdit_Y_ACCEL->setText(profile->getY_ACCELERATION());
    //DEFAULT_Z_ACCELERATION
    uia->lineEdit_Z_ACCEL->setText(profile->getZ_ACCELERATION());
    //DEFAULT_X_MAX_TRAVEL
    uia->LineEdit_X_TRAVEL->setText(profile->getX_MAX_TRAVEL());
    //DEFAULT_Y_MAX_TRAVEL
    uia->LineEdit_Y_TRAVEL->setText(profile->getY_MAX_TRAVEL());
    //DEFAULT_Z_MAX_TRAVEL
    uia->LineEdit_Z_TRAVEL->setText(profile->getZ_MAX_TRAVEL());
    //DEFAULT_STEP_PULSE_MICROSECONDS
    uia->LineEdit_STEP_PULSE_MICROSECONDS->setText(profile->getSTEP_PULSE_MICROSECONDS());
    //DEFAULT_STEPPING_INVERT_MASK
    uia->LineEdit_INVERT_MASK->setText(profile->getSTEPPING_INVERT_MASK());
    //DEFAULT_DIRECTION_INVERT_MASK
    uia->LineEdit_D_INVERT_MASK->setText(profile->getDIRECTION_INVERT_MASK());
    //DEFAULT_STEPPER_IDLE_LOCK_TIME
    uia->LineEdit_IDLE_LOCK_TIME->setText(profile->getSTEPPER_IDLE_LOCK_TIME());
    //DEFAULT_ARC_TOLERANCE
    uia->LineEdit_ARC_TOLERANCE->setText(profile->getARC_TOLERANCE());
    //DEFAULT_HOMING_DIR_MASK
    uia->LineEdit_HOMING_DIR_MASK->setText(profile->getHOMING_DIR_MASK());
    //DEFAULT_HOMING_FEED_RATE
    uia->LineEdit_HOMING_FEED_RATE->setText(profile->getHOMING_FEED_RATE());
    //DEFAULT_HOMING_SEEK_RATE
    uia->LineEdit_HOMING_SEEK_RATE->setText(profile->getHOMING_SEEK_RATE());
    //DEFAULT_HOMING_DEBOUNCE_DELAY
    uia->LineEdit_HOMING_D_DELAY->setText(profile->getHOMING_DEBOUNCE_DELAY());
    //DEFAULT_HOMING_PULLOFF
    uia->LineEdit_HOMING_PULLOFF->setText(profile->getHOMING_PULLOFF());
}

void  ProfileDialog::setupProfile(QWidget * tab)
{
    //    profile = new Profile();
    profile = Profile::instance();

    if(!profile->profileAtive)
    {
        if( profile->init_profile())
        {
            for(int i=0;i<profile->getProfileNameCount();i++)
            {
                uia->profileComboBox->addItem(profile->getProfileName(i));
            }

            fillProfilePage();
        }
    }else{
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

// profileSaved, tabWidget_2
void ProfileDialog::indicate_ProfileSaved()
{
    QString tab = uia->tabWidget_2->tabText(0);

//    if(!profileSaved){
    if(!profile->profileSaved){
        //TODO Проверить наличие символа * и удалить его
        if(!tab.contains('*',Qt::CaseInsensitive))
        {
            tab.append(QChar('*'));
        }
    }else{
        //TODO Поверить наличие символа * и если его нет, то добавить
        if(tab.contains('*'))
        {
            tab.remove(QChar('*'),Qt::CaseInsensitive);
        }
    }
    uia->tabWidget_2->setTabText(0,tab);

}

// -------------- Temperature


void ProfileDialog::on_profile_pushButton_Save_clicked()
{
    profile->saveProfileDocument(); // Save current Document
    profile->profileSaved = true;
    indicate_ProfileSaved();
}

void ProfileDialog::on_temprature_lineEdit_textEdited(const QString &arg1)
{
    //    profile->set_TEMPERATURE(uia->temprature_lineEdit->text());
    profile->set_TEMPERATURE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}

void ProfileDialog::on_tpropotional_lineEdit_textEdited(const QString &arg1)
{
//    profile->set_PROPTIONAL(uia->tpropotional_lineEdit->text()); // tpropotional_lineEdit
    profile->set_PROPTIONAL(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}

void ProfileDialog::on_tintegral_lineEdit_textEdited(const QString &arg1)
{
//    profile->set_INTEGRAL(uia->tintegral_lineEdit->text()); // tintegral_lineEdit
    profile->set_INTEGRAL(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}



void ProfileDialog::on_tderivative_lineEdit_textEdited(const QString &arg1)
{
//    profile->set_DERIVATIVE(uia->tderivative_lineEdit->text());
    profile->set_DERIVATIVE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}

//DEFAULT_X_STEPS_PER_MM
void ProfileDialog::on_lineEdit_X_STEPS_textEdited(const QString &arg1)
{
    profile->set_X_STEPS_PER_MM(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_Y_STEPS_PER_MM
void ProfileDialog::on_lineEdit_Y_STEPS_textEdited(const QString &arg1)
{
    profile->setY_STEPS_PER_MM(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_Z_STEPS_PER_MM
void ProfileDialog::on_lineEdit_Z_STEPS_textEdited(const QString &arg1)
{
    profile->setZ_STEPS_PER_MM(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_X_MAX_RATE
void ProfileDialog::on_lineEdit_X_RATE_textEdited(const QString &arg1)
{
    profile->setX_MAX_RATE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}

//DEFAULT_Y_MAX_RATE
void ProfileDialog::on_lineEdit_Y_RATE_textEdited(const QString &arg1)
{
    profile->setY_MAX_RATE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();

}

//DEFAULT_Z_MAX_RATE
void ProfileDialog::on_lineEdit_Z_RATE_textEdited(const QString &arg1)
{
    profile->setZ_MAX_RATE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_X_ACCELERATION
void ProfileDialog::on_lineEdit_X_ACCEL_textEdited(const QString &arg1)
{
    profile->setX_ACCELERATION(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_Y_ACCELERATION
void ProfileDialog::on_lineEdit_Y_ACCEL_textEdited(const QString &arg1)
{
    profile->setY_ACCELERATION(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_Z_ACCELERATION
void ProfileDialog::on_lineEdit_Z_ACCEL_textEdited(const QString &arg1)
{
    profile->setZ_ACCELERATION(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_X_MAX_TRAVEL
void ProfileDialog::on_LineEdit_X_TRAVEL_textEdited(const QString &arg1)
{
    profile->setX_MAX_TRAVEL(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_Y_MAX_TRAVEL
void ProfileDialog::on_LineEdit_Y_TRAVEL_textEdited(const QString &arg1)
{
    profile->setY_MAX_TRAVEL(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_Z_MAX_TRAVEL
void ProfileDialog::on_LineEdit_Z_TRAVEL_textEdited(const QString &arg1)
{
    profile->setZ_MAX_TRAVEL(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_STEP_PULSE_MICROSECONDS
void ProfileDialog::on_LineEdit_STEP_PULSE_MICROSECONDS_textEdited(const QString &arg1)
{
    profile->setSTEP_PULSE_MICROSECONDS(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_STEPPING_INVERT_MASK
void ProfileDialog::on_LineEdit_INVERT_MASK_textEdited(const QString &arg1)
{
    profile->setSTEPPING_INVERT_MASK(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_DIRECTION_INVERT_MASK
void ProfileDialog::on_LineEdit_D_INVERT_MASK_textEdited(const QString &arg1)
{
    profile->setDIRECTION_INVERT_MASK(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_STEPPER_IDLE_LOCK_TIME
void ProfileDialog::on_LineEdit_IDLE_LOCK_TIME_textEdited(const QString &arg1)
{
    profile->setSTEPPER_IDLE_LOCK_TIME(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_ARC_TOLERANCE
void ProfileDialog::on_LineEdit_ARC_TOLERANCE_textEdited(const QString &arg1)
{
    profile->setARC_TOLERANCE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_HOMING_DIR_MASK
void ProfileDialog::on_LineEdit_HOMING_DIR_MASK_textEdited(const QString &arg1)
{
    profile->setHOMING_DIR_MASK(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_HOMING_FEED_RATE
void ProfileDialog::on_LineEdit_HOMING_FEED_RATE_textEdited(const QString &arg1)
{
    profile->setHOMING_FEED_RATE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_HOMING_SEEK_RATE
void ProfileDialog::on_LineEdit_HOMING_SEEK_RATE_textEdited(const QString &arg1)
{
    profile->setHOMING_SEEK_RATE(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}

//DEFAULT_HOMING_DEBOUNCE_DELAY
void ProfileDialog::on_LineEdit_HOMING_D_DELAY_textEdited(const QString &arg1)
{
    profile->setHOMING_DEBOUNCE_DELAY(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}


//DEFAULT_HOMING_PULLOFF
void ProfileDialog::on_LineEdit_HOMING_PULLOFF_textEdited(const QString &arg1)
{
    profile->setHOMING_PULLOFF(arg1);
    profile->profileSaved = false;
    indicate_ProfileSaved();
}




void ProfileDialog::on_pfofileNameEdit_textEdited(const QString &arg1)
{
    profile->profileSaved = false;
    indicate_ProfileSaved();

}



void ProfileDialog::on_profileDescription_textEdit_textChanged()
{
//    profileSaved = false;
    // TODO Программная загрузка вызывает это событие и взводдит
    // флаг Запись.
    indicate_ProfileSaved();

}

void ProfileDialog::on_profileFile_Edit_textEdited(const QString &arg1)
{
    profile->profileSaved = false;
    indicate_ProfileSaved();
}



/**
 * @brief ProfileDialog::on_pushButton_3_clicked
 * Загрузка лога темпреатур.
 */
void ProfileDialog::on_pushButton_3_clicked()
{
//  Exchange* exch = Exchange::instance();
//  ComDataReq_t comdata;
//  exch->mutex.lock();
//  exch->buildComData(&comdata,eoProfile);
//  exch->mutex.unlock();
}


//-------------- temperature
