#include "hashTable.h"
#ifndef LEXER_DEF_H
#define LEXER_DEF_H

typedef enum
{
    isInt,
    isFloat
} Tag;

typedef union val
{
    int intVal;
    float floatVal;
} value;

typedef struct token
{
    char *str; // the string corresponding to the token
    Tk tokenType;
    int lineNo;
    // int isKeyword;
    value val;
    Tag tag; // the tag for the union
} Token;

#endif