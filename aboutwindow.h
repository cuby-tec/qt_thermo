#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class Aboutwindow;
}

class Aboutwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Aboutwindow(QWidget *parent = 0);
    ~Aboutwindow();

private:
    Ui::Aboutwindow *ui;
};

#endif // ABOUTWINDOW_H
