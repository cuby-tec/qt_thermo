#ifndef GCONSOLE_H
#define GCONSOLE_H

#include <QObject>
#include <ui_mainwindow.h>


namespace Ui {
class MainWindow;
}

class GConsole : public QObject
{
    Q_OBJECT
public:
    explicit GConsole(QObject *parent = 0);

    GConsole(Ui::MainWindow *&ui);

signals:

public slots:
    void on_pushButton_linestep_clicked();
    void on_textEdit_command_cursorPositionChanged();


private:
    Ui::MainWindow* uia;

    int oldBlockNumber;

};

#endif // GCONSOLE_H
