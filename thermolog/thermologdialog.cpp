#include "thermologdialog.h"
#include "ui_thermologdialog.h"
#include <QDebug>
#include <QFileDialog>
#include "myglobal.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

ThermoLogDialog::ThermoLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThermoLogDialog)
{
    ui->setupUi(this);

    //------- setup buttons

    buttonbox = ui->buttonBox;

    openButton = new QPushButton(tr("&Open"));
    openButton->setToolTip("Open termo sensor log file.");

    buttonbox->addButton(openButton,QDialogButtonBox::ActionRole);

    connect(openButton,SIGNAL(clicked(bool)),this, SLOT(openlog()) );

    logview = new ThermoLogView(ui->plot);

//    setupPlot(ui->plot);

}

void ThermoLogDialog::setupPlot(QCustomPlot *customPlot)
{
//    plotName = "Hotend temperature";

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


ThermoLogDialog::~ThermoLogDialog()
{
    delete ui;
}


void
ThermoLogDialog::openlog()
{
    qDebug() << "ThermoLogDialog::on_buttonBox_clicked[31]";

    QStringList list;

    setupPlot(ui->plot);


    QFileDialog::Options options;
    QString selectedFilter;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open log file"),
                                                    MyGlobal::logfileDir,
                                                    tr("Log file (*.log)"),
                                                    &selectedFilter,
                                                    options);

    qDebug() << "ThermoLogDialog::openlog[47]" <<fileName;
    if(fileName.isEmpty())
    {
        qDebug()<< MyGlobal::message4;
        return;
    }else{

        QFile logf(fileName);
        if(logf.open(QIODevice::ReadOnly|QIODevice::Text))
        {
          QTextStream in(&logf);
          while(!in.atEnd())
          {
              QString line = in.readLine();
              if(!line.contains(MyGlobal::comment))
              {
                  list.append(line);
              }
          }

          qDebug() << "ThermoLogDialog::openlog[71]"<<list.size();

          logf.close();

//          logview->setStrData(&list);

          logview->drawLogData(&list);


        }else {
            qDebug() << MyGlobal::message5;
        }
    }

}


//void ThermoLogDialog::on_buttonBox_clicked(QAbstractButton *button)
//{
//    qDebug() << "ThermoLogDialog::on_buttonBox_clicked[21]" << button->text();
//}
