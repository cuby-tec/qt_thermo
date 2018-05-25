/**
 *  File: gParcer.h
 * Company: CUBY,Ltd
*/

#ifndef GPARCER
#define GPARCER

#include "ghelper.h"


#ifdef __cplusplus
// using std;
   extern "C" {
#endif
//---- vars
extern FILE *fp;
extern FILE *flog;


//Разбор очередной строки.
extern void scanner();

extern int parcerFileOpen(char* filename);

extern void parcerFileClose();

#ifdef __cplusplus
   }
#endif

#endif

