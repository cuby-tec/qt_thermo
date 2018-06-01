#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QAction>

#include "qcustomplot.h"
#include "thermoplot.h"
//#include "profiles/profile.h"

#include "gparcer/gcodeworker.h"
#include "gconsole.h"
#include "coordinatuswindow.h"

class GConsole;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void editProfile();
    void openFileDo();
    void updateCoordinatus(const Status_t* status);

private:
    Ui::MainWindow *ui;

    void createActions(MainWindow *w);

//    Profile* profile;

    QAction* newAct;

    QMenu *fileMenu;

    QMenu *optionsMenu;

    QAction* optionEditAct; // Profile

    QMenu * menuTools;

    QAction* actThermo;

    QAction* pidParams;

    void pidParamsDo();

    void actTermoDo();

    QAction* actConfig;

    QAction* actFileOpen;

    GcodeWorker* gcodeworker;

    GConsole* gconsole;

    ThermoPlot* plotter;

    CoordinatusWindow* coordinatus;


    void setupPlot(QCustomPlot *customPlot);

    void setupGconsole(Ui::MainWindow *ui);

    void setupCoordinatus(Ui::MainWindow *ui);

};

#endif // MAINWINDOW_H
