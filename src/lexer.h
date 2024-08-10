#ifndef LEXER_H
#define LEXER_H

#include "utility.h"

typedef struct {
    i32 test;
} Token;

void tokeniseSource(FILE *src);

#endif