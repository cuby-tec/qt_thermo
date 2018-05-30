#ifndef GCONSOLE_H
#define GCONSOLE_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class GConsole : public QObject
{
    Q_OBJECT
public:
    explicit GConsole(QObject *parent = 0);

signals:

public slots:
    void on_pushButton_linestep_clicked();

};

#endif // GCONSOLE_H
