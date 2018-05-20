#include "thermoplot.h"

#include <QMessageBox>
#include <QTextBlock>
#include <QDateTime>
#include <QFileInfo>

ThermoPlot::ThermoPlot(QObject* parent) : QObject(parent)
{

}


ThermoPlot::ThermoPlot(QCustomPlot* plot)
{
    this->plot = plot;
    setupPlot(plot);
    oldTemperature = 0;

    createLog();
}



void
ThermoPlot::setupPlot(QCustomPlot* customPlot)
{
    plotName = "Hotend temperature";

//    plotName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */
//    customPlot->addGraph(); // blue line
//    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(0)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 40);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));


//    connect(&thread, SIGNAL(renderedImage(QImage,double)), this, SLOT(updatePixmap(QImage,double)));
    connect(&thread, SIGNAL(sg_temperature_updated(const Status_t*)), this, SLOT(updateStatus(const Status_t*)));
    connect(&thread, SIGNAL(sg_failed_status()),this, SLOT(failedStatus()));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1001); // Interval 0 means to refresh as fast as possible
}

const QString message1("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected.");
const QString message2("Can't open device.");
const QString message3("Temperature in Hotend.(grad Celsium)");

void
ThermoPlot::indicateTemperature(eIndicate ind, QString message)
{
    QWidget* pa = plot->nativeParentWidget();
    QLabel* label =  pa->findChild<QLabel *>("temperatureIcon");//temperatureLabel
    QLabel * tempLabel = pa->findChild<QLabel*>("temperatureLabel");

    switch (ind)
    {
    case eiFail:
        if(label)
        {
            label->setPixmap(QPixmap(":/images/write.png"));
            label->setScaledContents(true);
            tempLabel->setText(message2);
            tempLabel->setToolTip(message1);

        }
        break;

    case eiGood:
        if(label)
        {
            label->setPixmap(QPixmap(":/images/copy.png"));
            label->setScaledContents(true);
             tempLabel->setText(message);
            tempLabel->setToolTip(message3);
        }

        break;
    }
}

void
ThermoPlot::failedStatus()
{
//    dataTimer.stop();
//    QMessageBox msgbox;
//    msgbox.setText("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected.");
//    msgbox.exec();

//    QWidget* pa = plot->nativeParentWidget();
//    QLabel* label =  pa->findChild<QLabel *>("temperatureIcon");//temperatureLabel
//    if(label)
//    {
//        label->setPixmap(QPixmap(":/images/write.png"));
//        label->setScaledContents(true);
//    }
//    QLabel * tempLabel = pa->findChild<QLabel*>("temperatureLabel");
//    if(tempLabel)
//    {
//        tempLabel->setText("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected.");

//    }


//    dataTimer.stop();


    indicateTemperature(eiFail,QString("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected."));
}


void
ThermoPlot::printStatus(const Status_t *c_status)
{
#ifdef PRINT_TO_CONSOLE
    QString line;
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin

//    printf("frameNumber: %u \n",c_status->frameNumber);
//	printf("freeSegments: %u \n",c_status->freeSegments);
//	printf("coordinatus X: %u \n",c_status->coordinatus[X_AXIS]);
//	printf("coordinatus Y: %u \n",c_status->coordinatus[Y_AXIS]);
//	printf("coordinatus Z: %u \n",c_status->coordinatus[Z_AXIS]);
//	printf("coordinatus E: %u \n",c_status->coordinatus[E_AXIS]);
//	printf("modelState: %u \n",c_status->modelState);
//	printf("currentSegmentNumber: %u \n",c_status->currentSegmentNumber);
//	printf("instrument2_parameter: %u \n",c_status->instrument2_parameter);
//	printf("instrument3_parameter: %u \n",c_status->instrument3_parameter);
//	printf("instrument4_parameter: %u \n",c_status->instrument4_parameter);
//	printf(" ======================= \n");

    line = QString("frameNumber: %1 \n").arg(c_status->frameNumber); print <<line; print.flush();
    line = QString("freeSegments: %1 \n").arg(c_status->freeSegments);print <<line; print.flush();
    line = QString("coordinatus X: %1 \n").arg(c_status->coordinatus[X_AXIS]);print <<line; print.flush();
    line = QString("coordinatus Y: %1 \n").arg(c_status->coordinatus[Y_AXIS]);print <<line; print.flush();
    line = QString("coordinatus Z: %1 \n").arg(c_status->coordinatus[Z_AXIS]);print <<line; print.flush();
    line = QString("coordinatus E: %1 \n").arg(c_status->coordinatus[E_AXIS]);print <<line; print.flush();
    line = QString("modelState: %1 \n").arg(c_status->modelState);print <<line; print.flush();
    line = QString("currentSegmentNumber: %1 \n").arg(c_status->currentSegmentNumber);print <<line; print.flush();
    line = QString("instrument2_parameter: %1 \n").arg(c_status->instrument2_parameter);print <<line; print.flush();
    line = QString("instrument3_parameter: %1 \n").arg(c_status->instrument3_parameter);print <<line; print.flush();
    line = QString("instrument4_parameter: %1 \n").arg(c_status->instrument4_parameter);print <<line; print.flush();
    line = QString("Temperaature: %1 \n").arg(c_status->temperature);print <<line; print.flush();
    line = QString(" ======================= \n");print <<line; print.flush();

#else
//    QWidget* pa = plot->nativeParentWidget();
//    QLabel* label =  pa->findChild<QLabel *>("temperatureIcon");//temperatureLabel
//    if(label)
//    {
//        label->setPixmap(QPixmap(":/images/copy.png"));
//        label->setScaledContents(true);
//    }
//    QLabel * tempLabel = pa->findChild<QLabel*>("temperatureLabel");
//    if(tempLabel)
//    {
//        QString lint = QString("now: %1").arg(c_status->temperature);
//        tempLabel->setText(lint);

//    }
    indicateTemperature(eiGood,QString("now: %1").arg(c_status->temperature));
#endif
}

QString
ThermoPlot::datetime()
{
    QDateTime* dt = new QDateTime(QDate::currentDate(),QTime::currentTime(),Qt::LocalTime);

    QString str = dt->toString("ddMMyy-hhmmss");

    return str;
}

/**
 * init
 * Prepare log file and open it.
 * @brief ThermoPlot::createLog
 */
void
ThermoPlot::createLog()
{
    //QDate QDate::currentDate

    const static QString path = "profile/";

    QDateTime* dt = new QDateTime(QDate::currentDate(),QTime::currentTime(),Qt::LocalTime);

    QString str = dt->toString("ddMMyy-hhmmss");

    QString head = QString("#Logfile termo sensor. CUBY.Ltd\n");

    logfileName = QString("thermo-%1").arg(str);

    logfileName += ".log";

    QString st;

//    QDir::setCurrent(QDir::homePath()+"/tmp");
//    QString st(MyGlobal::logfileDir);

//    st = MyGlobal::logfileDir;

    st = MyGlobal::logfileDir;


    QDir::setCurrent(st);

    logfile.setFileName(logfileName);

    QFileInfo info = QFileInfo(logfile);

    if(!logfile.exists())
    {
      if(logfile.open(QFile::WriteOnly | QFile::Text))  ; // create file
      {
          QTextStream out(&logfile);

          out << head;

          logfile.close();

          logfile.open(QIODevice::Append);
      }
    }

    qDebug() << "ThermoPlot[207]"<<info.absoluteFilePath();

}


/**
 * Запись лога температур в файл.
 * @brief ThermoPlot::updateStatus
 * @param status
 */
void
ThermoPlot::writeLog()
{
    QString line = QString("");
    line += datetime();
    line += MyGlobal::logfileDelimiter;
    line.append(QString("  %1").arg(status->temperature));
//    line.arg(status->temperature);
    line += "\n";
    uint len;

    if(logfile.isOpen())
    {
        QTextStream out(&logfile);
//        len = logfile.write(line);
        out << line;


//        qDebug() << "ThermoPlot[219]:" << len;
    }

}


void
ThermoPlot::updateStatus(const Status_t *status)
{

    this->status = status;
    writeLog();


    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    printStatus(status);

    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
//      plot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));

//      plot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      if(isnan(status->temperature))
      {
          plot->graph(0)->addData(key, oldTemperature);
      }else{
          plot->graph(0)->addData(key, status->temperature);
          oldTemperature = status->temperature;
      }

      // rescale value (vertical) axis to fit the current data:
      //plot->graph(0)->rescaleValueAxis();
      //plot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    plot->xAxis->setRange(key, 8, Qt::AlignRight);
    plot->replot();
/*
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
//      ui->statusBar->showMessage(
//            QString("%1 FPS, Total Data points: %2")
//            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//            .arg(plot->graph(0)->data()->size()+plot->graph(1)->data()->size())
//            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
    */
}


void
ThermoPlot::realtimeDataSlot()
{
    thread.process();

}

