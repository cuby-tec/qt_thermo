/**
 *  File: gParcer.h
 * Company: CUBY,Ltd
*/

#ifndef GPARCER
#define GPARCER

//#include <stdio.h>

#include "ghelper.h"

//#include "sourcefiles.h"

#ifdef __cplusplus
// using std;
   extern "C" {
#endif
//---- vars
//extern FILE *fp;
//extern FILE *flog;

#define INPUT_BUFSIZE 1024


enum prsCmd{
    eCommand, eComment, eGcommand, eXparam, eYparam, eZparam, eAparam
    , eBparam, eCparam, eDparam, eEparam, eFparam, eIparam, eJparam
    , eKparam, eLparam, eMparam, eNparam, ePparam, eRparam, eSparam
    , eTpaam, eUparam, eVparam, eWparam, eStarparam,ePunct

};


typedef void (*WriteFunc)( char *data, int len );

struct format
{
    char* buf;	//char buf[BUFLEN+1];
    int buflen;
    WriteFunc write;

    int flags;
    int width;
    int prec;
    int cs;
    //--------
    int act;
    char* te;
    char* ts;
    char* p;
    char* pe;
    char* eof;
    int done;	// Исполнение текущего тега.
    int have;
    int curline;
    int space;
    int eofile;
    int lenfile;
    uint32_t state;
};


   //------- vars
extern struct format fsm;


//Разбор очередной строки.
extern int scanner();

extern void initGparcer();

#ifdef __cplusplus
   }
#endif

#endif

