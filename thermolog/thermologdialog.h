#ifndef THERMOLOGDIALOG_H
#define THERMOLOGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QPushButton>

#include "thermologview.h"

namespace Ui {
class ThermoLogDialog;
}

class ThermoLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThermoLogDialog(QWidget *parent = 0);
    ~ThermoLogDialog();

private slots:
    void openlog();

private:
    Ui::ThermoLogDialog *ui;

    QDialogButtonBox* buttonbox;

    QPushButton* openButton;

    ThermoLogView* logview;

    void setupPlot(QCustomPlot *customPlot);


};

#endif // THERMOLOGDIALOG_H
