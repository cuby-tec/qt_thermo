#include "gconsole.h"

#include <QDebug>

GConsole::GConsole(QObject *parent) : QObject(parent)
{

}

void
GConsole::on_pushButton_linestep_clicked()
{
//    Ui::MainWindow * ui = (Ui::MainWindow*)parent();
//    ui->textEdit_command->setText("Settext");
//    ui->textEdit_command->append("append1");
//    ui->textEdit_command->append("append2");
//    ui->label_commandLine->setText(ui->textEdit_command->document()->findBlockByLineNumber(1).text());
    qDebug()<<"Clicked " ;
}
