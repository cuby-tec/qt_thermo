#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "qcustomplot.h"

#include "profile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupPlot(QCustomPlot *customPlot);

    void setupExchange(QTabWidget *tab);

private slots:
    void on_profileComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QString plotName;

     Profile* profile;

};

#endif // MAINWINDOW_H
