#include "gconsole.h"

#include <QDebug>

GConsole::GConsole(QObject *parent) : QObject(parent)
{

}


GConsole::GConsole(Ui::MainWindow* &ui)
{
    this->uia = ui;
    oldBlockNumber = -1;
}

void
GConsole::on_pushButton_linestep_clicked()
{
     QColor bkgColor(170, 255, 255);
    int bnumber = uia->textEdit_command->textCursor().block().blockNumber();
//    Ui::MainWindow * ui = (Ui::MainWindow*)parent();
//    uia->textEdit_command->setText("Settext");
/*

    QTextBlock block =  uia->textEdit_command->textCursor().block();
    bnumber = block.blockNumber();
    uia->textEdit_command->append(QString("appen-d%1").arg(bnumber));

    QTextBlock prevBlock = block.previous();
    if(prevBlock.length()>0){
        QTextCursor cu1(prevBlock);
        QTextBlockFormat blockFprev = cu1.blockFormat();
        blockFprev.setBackground(bkgColor);
        cu1.setBlockFormat(blockFprev);
    }

    QTextBlock nextBlock = block.next();
    if(nextBlock.length() > 0)
    {
        QTextCursor cuNext(nextBlock);
        QTextBlockFormat blockNextFormat = cuNext.blockFormat();
        blockNextFormat.setBackground(bkgColor );
        cuNext.setBlockFormat(blockNextFormat);
    }

    if(oldBlockNumber>=0 && oldBlockNumber!= bnumber){
        QTextBlock oldBlock = uia->textEdit_command->document()->findBlockByLineNumber(oldBlockNumber);
        QTextCursor cuOld(oldBlock);
        QTextBlockFormat blockOldNextFormat = cuOld.blockFormat();
        blockOldNextFormat.setBackground(bkgColor );
        cuOld.setBlockFormat(blockOldNextFormat);

    }
 qDebug()<< "GConsole[54] old:"<< oldBlockNumber<<" now:"<< bnumber;
    oldBlockNumber = bnumber;
*/
//    ui->textEdit_command->append("append2");
    uia->label_commandLine->setText(uia->textEdit_command->document()->findBlockByLineNumber(bnumber).text());
    qDebug()<<"GConsole[60] Clicked line:"<<bnumber ;
}

void
GConsole::on_textEdit_command_cursorPositionChanged()
{
    int bnumber = uia->textEdit_command->textCursor().block().blockNumber();

    QColor bkgColor(170, 255, 255);

//    QTextFormat format = ui->textEdit_command->textCursor().block().blockFormat();
    QString str = uia->textEdit_command->textCursor().block().text();
    uia->label_commandLine->setText(str + QString("%1").arg(bnumber));
//    ui->textEdit_command->textCursor().block().blockFormat().setBackground(QBrush(QColor(120,120,120)));

    QTextBlock block =  uia->textEdit_command->textCursor().block();
    QTextCursor cursor(block);

    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setBackground(QColor(Qt::yellow));
    cursor.setBlockFormat(blockFormat);

    QTextBlock prevBlock = block.previous();
    if(prevBlock.length()>0){
        QTextCursor cu1(prevBlock);
        QTextBlockFormat blockFprev = cu1.blockFormat();
        blockFprev.setBackground(bkgColor);
        cu1.setBlockFormat(blockFprev);
    }

    QTextBlock nextBlock = block.next();
    if(nextBlock.length() > 0)
    {
        QTextCursor cuNext(nextBlock);
        QTextBlockFormat blockNextFormat = cuNext.blockFormat();
        blockNextFormat.setBackground(bkgColor );
        cuNext.setBlockFormat(blockNextFormat);
    }

    if(oldBlockNumber>=0 && oldBlockNumber!= bnumber){
        QTextBlock oldBlock = uia->textEdit_command->document()->findBlockByLineNumber(oldBlockNumber);
        QTextCursor cuOld(oldBlock);
        QTextBlockFormat blockOldNextFormat = cuOld.blockFormat();
        blockOldNextFormat.setBackground(bkgColor );
        cuOld.setBlockFormat(blockOldNextFormat);

    }

    qDebug()<< "GConsole[107] old:"<< oldBlockNumber<<" now:"<< bnumber;
    oldBlockNumber = bnumber;

}
