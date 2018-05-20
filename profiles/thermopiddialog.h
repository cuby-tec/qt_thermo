#ifndef THERMOPIDDIALOG_H
#define THERMOPIDDIALOG_H

#include <QDialog>
#include <QWidget>
#include "profile.h"
#include <QPushButton>
#include "exchange/usbexchange.h"
#include <QDialogButtonBox>

namespace Ui {
class ThermoPIDDialog;
}

extern QMutex thermo_gmutex;

class ThermoPIDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThermoPIDDialog(QWidget *parent = 0);
    ~ThermoPIDDialog();

private slots:
    void on_temprature_lineEdit_textEdited(const QString &arg1);

    void on_tpropotional_lineEdit_textEdited(const QString &arg1);

    void on_tintegral_lineEdit_textEdited(const QString &arg1);

    void on_tderivative_lineEdit_textEdited(const QString &arg1);

    void upload();

private:
    Ui::ThermoPIDDialog *ui;


    Profile* profile;

    UsbExchange* exch;

    Status_t* status;

    ComDataReq_t request;

    // session values

    float_t p_temperaature;
    float_t p_propotional;
    float_t p_integral;
    float_t p_derived;


    QDialogButtonBox* buttonBox;

    // buttons
    QPushButton* uploadButton;

    void setupFieldes();

    void setuButtomBox();



};

#endif // THERMOPIDDIALOG_H
