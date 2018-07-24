#include "gconsole.h"

#include <string.h>
#include <QDebug>

#include "gparcer/coordinatus.h"
#include "myglobal.h"

//#include "links/Status_t.h"
//#include "usbexchange.h"

#include "links/exchange/eModelstate.h"
#include <gcode-lexer.h>

#include "gparcer/lexer.h"

GConsole::GConsole(QObject *parent) : QObject(parent)
{
//    QScopedPointer<ComData> this->req_builder(new ComData());
//    this->req_builder = req_builder;
//    this->req_builder = new ComData();
//    this->req_builder = &_comdata;
	oldBlockNumber = -1;
	uia = NULL;
     coord = Coordinatus::instance();
     req_builder = new ComData();
}




GConsole::GConsole(Ui::MainWindow* &ui)
{
    this->uia = ui;
    oldBlockNumber = -1;
//    this->req_builder = &_comdata;
    setupGconsole();

    coord = Coordinatus::instance();
    coord->setupProfileData();
    req_builder = new ComData();

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
//    connect(&thread,SIGNAL(sg_status_updated(const Status_t*)),this,SLOT(updateStatus(const Status_t*)) );
//    connect(&thread,SIGNAL(sg_failed_status()),this, SLOT(failedStatus()) );

    connect(req_builder,SIGNAL(sg_updateStatus(const Status_t*)),this,SLOT(updateStatus(const Status_t*)) );

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

//    req_builder->setRequestNumber(++MyGlobal::commandIndex);

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

//   thread.setRequest(req);

//    thread.process();

//    return result;
}


void GConsole::setDisabledCursor() {
    uia->pushButton_linestep->setDisabled(true);
    uia->dockWidget_Console->setCursor(Qt::BusyCursor);

}

void GConsole::setEnabledCursor() {
    uia->pushButton_linestep->setDisabled(false);
    uia->dockWidget_Console->setCursor(Qt::ArrowCursor);
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
//	uint32_t rnumber = thread.getRequestNumber();

//    qDebug()<<"GConsole[125]:"<<status->frameNumber<<"\tsended:"<<rnumber<<"\tquee:"<<status->freeSegments;

//    coordinatuswindow->update(status,req_builder);
    if(status->modelState.modelState == ehIdle)
        setEnabledCursor();
}

/**
 * Разбор одной строки.
 * @brief GcodeWorker::parceString
 * @param src
 * @return
 */
int
GConsole::parceString(char* src,sGcode* dst )
{
    int result = 0;

//    struct sGcode mdst;
//    struct sGcode* pmdst = &mdst;

    size_t len = strlen(src);

    Lexer* le = new Lexer(dst);

    result = le->parcer(src,len);

//    pmdst = le->getDst();

//===============
/*    qDebug()<<__FILE__<<src;
    qDebug()<<"=======  %s  ==========\n"<<__FILE__<<"\tresult:"<<result;
//    printf("_h_report: line number:%i  \tgroup:%c \tindex:%s \tcomment:%s \n",dst->line,dst->group,dst->value , dst->comment);
    qDebug()<<"_h_report: line number:"<<dst->line<<"\tgroup:"<<dst->group<<"\tindex:"<<dst->value<<"\tcomment:"<<dst->comment;
    for(int i=0;i<dst->param_number;i++)
    {
        struct sGparam *param = &dst->param[i];
//        printf("\t_h_param: group:%c \tvalue:%s\n",param->group,param->value);
        qDebug()<<"\t_h_param: group:"<<param->group<<"\tvalue:"<<param->value;
    }

    qDebug()<<"=================";
*/
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
    sGcode sgcode;

     QColor bkgColor(170, 255, 255);
//    int bnumber = uia->textEdit_command->textCursor().block().blockNumber();

    setDisabledCursor();

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

//    Coordinatus* coord = Coordinatus::instance();

    coord->setupProfileData();

    memset(&sgcode,0,sizeof(struct sGcode));
//    sgcode = parceString(pbuffer, &parce_error);
    parce_error = parceString(pbuffer,&sgcode);

    if( parce_error > 0 )
    {
//        uia->label_commandLine->setText(QString(error2)+QString("%1").arg(parce_error) );
        uia->label_commandLine->setText(msg1+ QString(sgcode.group)+QString(sgcode.value) );
//        buildComData(sgcode); // sGcode* sgcode
        if( sgcode.group & 0x50)
            req_builder->buildComData(&sgcode,checkBox_immediately);

    }else{
        uia->label_commandLine->setText(QString(error1)+QString("%1").arg(parce_error) );
        setEnabledCursor();
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




