#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef HASHTABLE_H
#define HASHTABLE_H
#define BUFF_SIZE 4096
#define TABLE_SIZE 1000
#define MAX_ID_SIZE 20

char buf1[BUFF_SIZE+1];
char buf2[BUFF_SIZE+1];

typedef enum {
    TK_ASSIGNOP, TK_COMMENT, TK_FIELDID, TK_ID, TK_NUM, TK_RNUM, TK_FUNID, TK_RUID, TK_WITH, TK_PARAMETERS, TK_END, TK_WHILE, TK_UNION, TK_ENDUNION, TK_DEFINETYPE, TK_AS, TK_TYPE, 
    TK_MAIN, TK_GLOBAL, TK_PARAMETER, TK_LIST, TK_SQL, TK_SQR, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_COMMA, TK_SEM, TK_COLON, TK_DOT, TK_ENDWHILE, TK_OP, TK_CL, TK_IF, TK_THEN,
    TK_ENDIF, TK_READ, TK_WRITE, TK_RETURN, TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_CALL, TK_RECORD, TK_ENDRECORD, TK_ELSE, TK_AND, TK_OR, TK_NOT, TK_LT, TK_LE, TK_EQ, TK_GT, TK_LE,
    TK_NE
} Tk;

typedef struct entry{
    char* str; //the string corresponding to the lexeme
    Tk token; //the value for the lexeme
    struct entry* next; //if separate chaining has to be employed for collision management

} hashEntry;

hashEntry hashMap[TABLE_SIZE];

int hashCode(char* str);
void constructHashTable(hashEntry hashTable[]);
void pushHashTable(char* str, Tk tokenType, hashEntry hashTable[]);
void pushKeyword(hashEntry hashTable[]);

#endif