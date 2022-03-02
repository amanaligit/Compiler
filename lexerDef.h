#include "hashTable.h"
#ifndef LEXER_DEF_H
#define LEXER_DEF_H

typedef enum{
    isInt, isFloat
}Tag;

typedef struct token{
    char* str; //the string corresponding to the token
    Tk tokenType;
    int lineNo;
    typedef union val{
        int intVal;
        float floatVal;
    }value;
    Tag tag; //the tag for the union
}Token;

#endif