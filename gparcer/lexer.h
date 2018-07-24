#ifndef LEXER_H
#define LEXER_H

#include <gcode-lexer.h>

class Lexer
{
public:
    Lexer(sGcode* dst);

    int parcer(char* buf, int len );

    sGcode *getDst() const;

private:

//    struct sGcode mdst;

    struct sGcode* dst;

};

#endif // LEXER_H
