#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QWidget>
#include "qcustomplot.h"

#include "exchange/exchange.h"
#include "profile.h"

#include "profiles/profiledialog.h"

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = 0);
    ~ProfileDialog();

private slots:
    void on_profileComboBox_currentIndexChanged(int index);

private:
    Ui::ProfileDialog *uia;

    QString plotName;

    Profile* profile;

    void setupExchange(QWidget *tab);

    void setupPlot(QCustomPlot *customPlot);

};

#endif // PROFILEDIALOG_H
