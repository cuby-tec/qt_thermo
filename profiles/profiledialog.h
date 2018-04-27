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

    void on_profile_pushButton_Save_clicked();

    void on_temprature_lineEdit_editingFinished();

private:
    Ui::ProfileDialog *uia;

    QString plotName;

    Profile* profile;

    void setupExchange();

    void setupPlot(QCustomPlot *customPlot);

    void setupProfile(QWidget * tab);

    void fillProfilePage();
};

#endif // PROFILEDIALOG_H

