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


    void on_temprature_lineEdit_textEdited(const QString &arg1);

    void on_tpropotional_lineEdit_textEdited(const QString &arg1);

    void on_tintegral_lineEdit_textEdited(const QString &arg1);

    void on_tderivative_lineEdit_textEdited(const QString &arg1);

    void on_pfofileNameEdit_textEdited(const QString &arg1);

    void on_profileDescription_textEdit_textChanged();

    void on_profileFile_Edit_textEdited(const QString &arg1);

private:
    Ui::ProfileDialog *uia;

    QString plotName;

    Profile* profile;

    void setupExchange();

    void setupPlot(QCustomPlot *customPlot);

    void setupProfile(QWidget * tab);

    void fillProfilePage();

    void indicate_ProfileSaved();

    bool profileSaved;
};

#endif // PROFILEDIALOG_H

