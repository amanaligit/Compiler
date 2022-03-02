#include "lexer.h"

FILE *fptr;
char *bg, *fp;
int line, ptrBuff1, ptrBuff2;
int lexSize;

void removeComments(FILE* testcaseFile, char* cleanFile){
    FILE* out = fopen(cleanFile, "w");
    char ch = get_char(testcaseFile);
}

void retract(int count){
    lexSize -= count;
    if(fp >= buf1 &&fp < buf1 + count)
    {
        int tmp = count - (fp - buf1);
        fp = buf2 + BUFF_SIZE - tmp;
        ptrBuff1 = 0;
    }
    else if(fp >= buf2 && fp < buf2 + count)
    {
        int tmp = count - (fp - buf2);
        fp = buf1 + BUFF_SIZE - tmp;
        ptrBuff2 = 0;
    }
    else
        fp -= count;

}