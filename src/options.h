#ifndef OPTIONS_H
#define OPTIONS_H

#include "utility.h"

typedef struct {
    bool only_lex;
    bool only_parse;
    bool only_asm;
    bool no_codegen;
} CompilerOptions;

#endif