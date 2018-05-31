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

    void on_pushButton_3_clicked();

    void on_lineEdit_X_STEPS_textEdited(const QString &arg1);

    void on_lineEdit_Y_STEPS_textEdited(const QString &arg1);

    void on_lineEdit_Z_STEPS_textEdited(const QString &arg1);

    void on_lineEdit_X_RATE_textEdited(const QString &arg1);

    void on_lineEdit_Y_RATE_textEdited(const QString &arg1);

    void on_lineEdit_Z_RATE_textEdited(const QString &arg1);

    void on_lineEdit_X_ACCEL_textEdited(const QString &arg1);

    void on_lineEdit_Y_ACCEL_textEdited(const QString &arg1);

    void on_lineEdit_Z_ACCEL_textEdited(const QString &arg1);

    void on_LineEdit_X_TRAVEL_textEdited(const QString &arg1);

    void on_LineEdit_Y_TRAVEL_textEdited(const QString &arg1);

    void on_LineEdit_Z_TRAVEL_textEdited(const QString &arg1);

    void on_LineEdit_STEP_PULSE_MICROSECONDS_textEdited(const QString &arg1);

    void on_LineEdit_INVERT_MASK_textEdited(const QString &arg1);

    void on_LineEdit_D_INVERT_MASK_textEdited(const QString &arg1);

    void on_LineEdit_IDLE_LOCK_TIME_textEdited(const QString &arg1);

    void on_LineEdit_ARC_TOLERANCE_textEdited(const QString &arg1);

    void on_LineEdit_HOMING_DIR_MASK_textEdited(const QString &arg1);

    void on_LineEdit_HOMING_FEED_RATE_textEdited(const QString &arg1);

    void on_LineEdit_HOMING_SEEK_RATE_textEdited(const QString &arg1);

    void on_LineEdit_HOMING_D_DELAY_textEdited(const QString &arg1);

    void on_LineEdit_HOMING_PULLOFF_textEdited(const QString &arg1);


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


