#include "lexer.h"

FILE *fptr;
char *bg, *fp;
int line, ptrBuff1, ptrBuff2;
int lexSize;
int EOFReached = 0;

char *give_lexeme()
{

    retract(1);
    char *truelexeme = (char *)malloc(sizeof(char) * 32);
    char *cur = bg;
    int i = 0;
    while (cur != fp)
    {
        if (cur == (buf2 + BUFF_SIZE))
        {
            cur = buf1;
        }
        else if (cur == (buf1 + BUFF_SIZE))
        {
            cur = buf2;
        }
        if (cur == fp)
            break;
        truelexeme[i++] = *cur;
        cur++;
    }
    truelexeme[i] = '\0';
    bg = fp;
    return truelexeme;
}

Tk keywordEnum(char *str)
{
    return stringToEnum(str, hashMapKeys);
}

void removeComments(FILE *testcaseFile, char *cleanFile)
{
    char buffer1[BUFF_SIZE + 1];
    size_t k = 4096;
    FILE *out = fopen(cleanFile, "w");
    // printf("here");
    buffer1[BUFF_SIZE] = EOF;
    char *temp = buffer1;
    char **temp2 = &temp;
    int line_size = getline(temp2, &k, testcaseFile);

    char ch;
    while (line_size != -1)
    {
        // printf("%d", line_size);
        // printf("%s", buffer1);
        char ch = buffer1[0];
        int i = 0;
        while (ch != '%' && i != line_size)
        {
            i++;
            ch = buffer1[i];
        }
        if (i != line_size)
        {
            fprintf(out, "\n");
        }
        else
        {
            fprintf(out, "%s", buffer1);
        }
        line_size = getline(temp2, &k, testcaseFile);
    }
    fclose(out);
}

Token *fillToken(char *lex, Tk t, unsigned int lineno, value val, int tag)
{

    Token *res = (Token *)malloc(sizeof(Token));
    res->str = (char *)malloc(sizeof(char) * strlen(lex));
    strcpy(res->str, lex);
    res->tokenType = t; // fill enum here
    res->lineNo = lineno;
    // res->isKeyword = isKey;
    res->val = val;
    res->tag = tag;
    return res;
}

void throwErrorAndProceed(int toPrintErr, int *curState)
{
    *curState = 0;
    if (toPrintErr == TRUE)
        printf("Line:%d Lexical Error: ", line);
    retract(1);
    fp++;
    if (toPrintErr == TRUE)
        printf("%s\n", give_lexeme());
    bg = fp;
}

Token *getNextToken(int toPrintErr)
{
    if (EOFReached)
    {
        return NULL;
    }

    char ch;
    int finished = 0;
    int curState = 0;
    int lengthOfIdentifier = 0;

    while (finished != 0)
    {
        ch = getNextChar();

        switch (curState)
        {
        // recheck
        case 0:
        {
            if (ch == '[')
            {
                curState = 1;
            }
            else if (ch == ']')
            {
                curState = 2;
            }
            else if (ch == ',')
            {
                curState = 3;
            }
            else if (ch == ';')
            {
                curState = 4;
            }
            else if (ch == ':')
            {
                curState = 5;
            }
            else if (ch == '.')
            {
                curState = 6;
            }
            else if (ch == '(')
            {
                curState = 7;
            }
            else if (ch == ')')
            {
                curState = 8;
            }
            else if (ch == '+')
            {
                curState = 9;
            }
            else if (ch == '-')
            {
                curState = 10;
            }
            else if (ch == '*')
            {
                curState = 11;
            }
            else if (ch == '/')
            {
                curState = 12;
            }
            else if (ch == '~')
            {
                curState = 13;
            }
            else if (ch == '<')
            {
                curState = 14;
            }
            else if (ch == '!')
            {
                curState = 20;
            }
            else if (ch == '>')
            {
                curState = 22;
            }
            else if (ch == '=')
            {
                curState = 25;
            }
            else if (ch == '_')
            {
                curState = 27;
            }
            else if (ch == '%')
            {
                curState = 32;
            }
            else if (ch == '&')
            {
                curState = 34;
            }
            else if (ch == '@')
            {
                curState = 37;
            }
            else if (ch >= 'b' && ch <= 'd')
            {
                curState = 40;
            }
            else if (ch == 'a' || (ch >= 'e' && ch <= 'z'))
            {
                curState = 45;
            }
            else if (ch >= '0' && ch <= '9')
            {
                curState = 47;
            }
            else if (ch == '#')
            {
                curState = 57;
            }
            else if (ch == ' ' || ch == '\t' || ch == '\r')
            {

                while (ch != ' ' && ch != '\t' && ch != '\r')
                    ch = getNextChar();
                bg = fp;
            }

            else if (ch == '\n')
            {
                bg = fp;
                line++;
            }

            else if (EOFReached == 1)
            {
                break;
            }

            else
            {
                curState = 0;
                if (toPrintErr == 1)
                    printf("Line:%d Lexical Error: ", line);
                fp++;
                if (toPrintErr == 1)
                    printf("%s\n", give_lexeme());
                bg = fp;
            }
        }
        break;

        case 1:
        {
            finished = 1;
            Tk c = TK_SQL;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 2:
        {
            finished = 1;
            Tk c = TK_SQR;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 3:
        {
            finished = 1;
            Tk c = TK_COMMA;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 4:
        {
            finished = 1;
            Tk c = TK_SEM;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 5:
        {
            finished = 1;
            Tk c = TK_COLON;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 6:
        {
            finished = 1;
            Tk c = TK_COMMA;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 7:
        {
            finished = 1;
            Tk c = TK_OP;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 8:
        {
            finished = 1;
            Tk c = TK_CL;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 9:
        {
            finished = 1;
            Tk c = TK_PLUS;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 10:
        {
            finished = 1;
            Tk c = TK_MINUS;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 11:
        {
            finished = 1;
            Tk c = TK_MUL;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 12:
        {
            finished = 1;
            Tk c = TK_DIV;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 13:
        {
            finished = 1;
            Tk c = TK_NOT;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 14:
        {
            if (ch == '-')
                curState = 15;
            else if (ch == '=')
                curState = 18;
            else
                curState = 19;
        }
        break;

        case 15:
        {
            if (ch == '-')
                curState = 16;
            else
            {
                throwErrorAndProceed(toPrintErr, &curState);
            }
        }
        break;

        case 16:
        {
            if (ch == '-')
            {
                curState = 17;
            }
            else
                throwErrorAndProceed(toPrintErr, &curState);
        }
        break;

        case 17:
        {
            finished = 1;
            Tk c = TK_ASSIGNOP;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;

        case 18:
        {
            finished = 1;
            Tk c = TK_LE;
            value num_val;
            num_val.intVal = 0;
            return fillToken(give_lexeme(), c, line, num_val, 0);
        }
        break;
        }
    }
}

char getNextChar()
{
    if (*fp == EOF)
    {
        if (fp == buf1 + BUFF_SIZE)
        {
            if (ptrBuff2 == 1)
            {
                int siz = fread(buf2, sizeof(char), BUFF_SIZE, fptr);
                buf2[siz] = EOF;
                ptrBuff2 = 0;
            }
            fp = buf2;
            ptrBuff1 = 1;
        }
        else if (fp == buf2 + BUFF_SIZE)
        {
            if (ptrBuff1 == 1)
            {
                int siz = fread(buf1, sizeof(char), BUFF_SIZE, fptr);
                buf1[siz] = EOF;
                ptrBuff1 = 0;
            }
            fp = buf1;
            ptrBuff2 = 1;
        }
        else
        {
            EOFReached = 1;
        }
    }

    char c = *fp;
    fp++;
    return c;
}

// remember to take a look
void retract(int count)
{
    lexSize -= count;
    if (fp >= buf1 && fp < buf1 + count)
    {
        int tmp = count - (fp - buf1);
        fp = buf2 + BUFF_SIZE - tmp;
        ptrBuff1 = 0;
    }
    else if (fp >= buf2 && fp < buf2 + count)
    {
        int tmp = count - (fp - buf2);
        fp = buf1 + BUFF_SIZE - tmp;
        ptrBuff2 = 0;
    }
    else
        fp -= count;
}

int main()
{
    // FILE *in = fopen("test", "r");
    // removeComments(in, "output");

    char c;
    fptr = fopen("test", "r");
    int siz = fread(buf1, sizeof(char), BUFF_SIZE, fptr);
    buf1[siz] = EOF;
    fp = buf1;
    while (!EOFReached)
    {
        printf("%c", c);
        c = getNextChar();
    }

    fclose(fptr);

    return 0;
}