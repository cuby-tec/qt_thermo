#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QAction>

#include "qcustomplot.h"
#include "thermoplot.h"
//#include "profiles/profile.h"

#include "gparcer/gcodeworker.h"


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


    void setupPlot(QCustomPlot *customPlot);



};

#endif // MAINWINDOW_H
