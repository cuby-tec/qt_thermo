#include "gconsole.h"

#include <string.h>
#include <QDebug>

#include "gparcer/coordinatus.h"
#include "myglobal.h"

//#include "links/Status_t.h"
//#include "usbexchange.h"




GConsole::GConsole(QObject *parent) : QObject(parent), req_builder(new ComData())
{
//    QScopedPointer<ComData> this->req_builder(new ComData());
//    this->req_builder = req_builder;
//    this->req_builder = new ComData();
//    this->req_builder = &_comdata;
	oldBlockNumber = -1;
	uia = NULL;
}




GConsole::GConsole(Ui::MainWindow* &ui):req_builder(new ComData())
{
    this->uia = ui;
    oldBlockNumber = -1;
//    this->req_builder = &_comdata;
    setupGconsole();

    setupThread();
}


/*
 *     static QString msg_absolute;
    static QString msg_relative;

    static QString msg_abs_title;
    static QString msg_rel_title;
 * */
void
GConsole::setupGconsole()
{
    Profile* profile = Profile::instance();
    if(!profile->profileAtive)
    {
        profile->init_profile();
    }

    Coordinatus* cord = Coordinatus::instance();
    if(cord->isAbsolute())
    {
        uia->label_AbsRel->setText(MyGlobal::msg_absolute);
        uia->label_AbsRel->setToolTip(MyGlobal::msg_abs_title);
    }else{
        uia->label_AbsRel->setText(MyGlobal::msg_relative);
        uia->label_AbsRel->setToolTip(MyGlobal::msg_rel_title);
    }

    connect(uia->checkBox_immediately,SIGNAL(stateChanged(int)),this,SLOT(on_checkBox_immediately_stateChanged(int)) );
    checkBox_immediately = uia->checkBox_immediately->isChecked();
}


void
GConsole::setupThread()
{
    connect(&thread,SIGNAL(sg_status_updated(const Status_t*)),this,SLOT(updateStatus(const Status_t*)) );
    connect(&thread,SIGNAL(sg_failed_status()),this, SLOT(failedStatus()) );
}


/**
 * @brief GConsole::buildComData
 * @param cmdd
 * @return result
 */
bool
GConsole::buildComData(sGcode* sgcode)
{
    bool result;

// TODO build request


//    req->setRequestNumber(56);

//    ComDataReq_t* r = req_builder->getRequest();

    req_builder->setRequestNumber(++MyGlobal::commandIndex);

    req_builder->build(sgcode);


//    r->requestNumber= ++MyGlobal::commandIndex;



//======================

    ComDataReq_t* req = req_builder->getRequest();

    // immediately execute
    if(checkBox_immediately)
    	req->command.reserved |= EXECUTE_IMMEDIATELY;
    else
    	req->command.reserved &= ~EXECUTE_IMMEDIATELY;

// EXIT_CONTINUE
//    if(segment->head.reserved == EXIT_CONTINUE)
//    					ms_finBlock = continueBlock;
//					else
//    					ms_finBlock = exitBlock;
    req->payload.instrument1_parameter.head.reserved &= ~EXIT_CONTINUE;

    qDebug()<<"GConsole[121]: stepsX"<<req->payload.instrument1_parameter.axis[X_AXIS].steps;

    //===========
// TODO send requst and wait signal

   thread.setRequest(req);

    thread.process();

    return result;
}

//TODO
void
GConsole::failedStatus()
{

}

//TODO
void
GConsole::updateStatus(const Status_t* status)
{
	uint32_t rnumber = thread.getRequestNumber();

    qDebug()<<"GConsole[125]:"<<status->frameNumber<<"\tsended:"<<rnumber<<"\tquee:"<<status->freeSegments;
}

/**
 * Разбор одной строки.
 * @brief GcodeWorker::parceString
 * @param src
 * @return
 */
sGcode*
GConsole::parceString(char* src,int* error)
{
    sGcode* result = NULL;

    int state;
//    int error;
    initGparcer();
    clear_sgcode();
    //------------------------- begen parcing

    state = scanner();
    if(state == 4){
        strcpy(fsm.buf+fsm.have,src);

        fsm.lenfile = strlen(src);

        state = scanner();

        if(sgcode.line != 0){
//            clear_sgcode();

            result = &sgcode;
        }

        *error = fsm.cs;

    }
    return result;
}



/**
 * Формиирование команда для немедленного выполнения.
 * @brief GConsole::on_pushButton_linestep_clicked
 */
void
GConsole::on_pushButton_linestep_clicked()
{

    const QString error1("ERROR: Command dosn't accepted.");
    const QString error2("Command accepted.");
    const QString msg1("accepted:");

    int parce_error;
    sGcode* sgcode;

     QColor bkgColor(170, 255, 255);
    int bnumber = uia->textEdit_command->textCursor().block().blockNumber();


//    qDebug()<<"GConsole[60] Clicked line:"<<bnumber ;

    char cmdbuffer[80];
    char* pbuffer;
    size_t size = sizeof(cmdbuffer);
    size_t len;

    QString block =  uia->textEdit_command->textCursor().block().text();

    std::string cmdstd = block.toStdString();
    pbuffer = strncpy( cmdbuffer,cmdstd.data(),size );

    len = strlen(pbuffer);

    *(pbuffer+len) = 0x0A;

//    uia->label_commandLine->setText(uia->textEdit_command->document()->findBlockByLineNumber(bnumber).text());
    uia->label_commandLine->setText(pbuffer);
// -------- parcer

    sgcode = parceString(pbuffer, &parce_error);
    if( sgcode != 0 && sgcode->group != ' ')
    {
//        uia->label_commandLine->setText(QString(error2)+QString("%1").arg(parce_error) );
        uia->label_commandLine->setText(msg1+ QString(sgcode->group)+QString(sgcode->value) );
        buildComData(sgcode); // sGcode* sgcode

    }else{
        uia->label_commandLine->setText(QString(error1)+QString("%1").arg(parce_error) );
    }

//--------- parcer end

}


void
GConsole::on_checkBox_immediately_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Unchecked:
        checkBox_immediately = false;
        break;
    case Qt::Checked:
        checkBox_immediately = true;
        break;
    }
    qDebug()<<"GConsole[243]:"<<checkBox_immediately;
}

void
GConsole::on_textEdit_command_cursorPositionChanged()
{
    int bnumber = uia->textEdit_command->textCursor().block().blockNumber();

    QColor bkgColor(170, 255, 255);

//    QTextFormat format = ui->textEdit_command->textCursor().block().blockFormat();
    QString str = uia->textEdit_command->textCursor().block().text();
//    uia->label_commandLine->setText(str + QString("%1").arg(bnumber));
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

//    qDebug()<< "GConsole[107] old:"<< oldBlockNumber<<" now:"<< bnumber;
    oldBlockNumber = bnumber;

}
