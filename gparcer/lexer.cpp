#include "lexer.h"
#include <string.h>
#include <QtDebug>


Lexer::Lexer(sGcode *dst)
{
    this->dst = dst;
}

int
Lexer::parcer(char *buf, int len)
{
//    struct sGcode mdst;
    int res_parcer;
//    struct sGcode* dst = &mdst;
    setGcode(dst);

//    size_t len = strlen(str);


    memset(dst,0,sizeof(struct sGcode));

    res_parcer = setBuffer((char*)buf, len);

    //===============
/*
    qDebug()<<__FILE__<<"::"<<buf;
    qDebug()<<"=======  %s  ==========\n"<<__FILE__<<"\tresult:"<<res_parcer;
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

    //================
    return res_parcer;
}

sGcode *Lexer::getDst() const
{
    return dst;
}
