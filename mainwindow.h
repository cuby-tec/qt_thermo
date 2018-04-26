#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QAction>

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



private slots:
    void editProfile();

private:
    Ui::MainWindow *ui;

    void createActions(MainWindow *w);

    Profile* profile;

    QAction* newAct;

    QMenu *fileMenu;

    QMenu *optionsMenu;

    QAction* optionEditAct;

};

#endif // MAINWINDOW_H
