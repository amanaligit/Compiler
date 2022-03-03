#include "hashTable.h"

char *enumToString(Tk token)
{
    if (token == TK_ASSIGNOP)
        return "TK_ASSIGNOP";
    if (token == TK_COMMENT)
        return "TK_COMMENT";
    if (token == TK_FIELDID)
        return "TK_FIELDID";
    if (token == TK_ID)
        return "TK_ID";
    if (token == TK_NUM)
        return "TK_NUM";
    if (token == TK_RNUM)
        return "TK_RNUM";
    if (token == TK_FUNID)
        return "TK_FUNID";
    if (token == TK_RUID)
        return "TK_RUID";
    if (token == TK_WITH)
        return "TK_WITH";
    if (token == TK_PARAMETERS)
        return "TK_PARAMETERS";
    if (token == TK_END)
        return "TK_END";
    if (token == TK_WHILE)
        return "TK_WHILE";
    if (token == TK_UNION)
        return "TK_UNION";
    if (token == TK_ENDUNION)
        return "TK_ENDUNION";
    if (token == TK_DEFINETYPE)
        return "TK_DEFINETYPE";
    if (token == TK_AS)
        return "TK_AS";
    if (token == TK_TYPE)
        return "TK_TYPE";
    if (token == TK_MAIN)
        return "TK_MAIN";
    if (token == TK_GLOBAL)
        return "TK_GLOBAL";
    if (token == TK_PARAMETER)
        return "TK_PARAMETER";
    if (token == TK_LIST)
        return "TK_LIST";
    if (token == TK_SQL)
        return "TK_SQL";
    if (token == TK_SQR)
        return "TK_SQR";
    if (token == TK_INPUT)
        return "TK_INPUT";
    if (token == TK_OUTPUT)
        return "TK_OUTPUT";
    if (token == TK_INT)
        return "TK_INT";
    if (token == TK_REAL)
        return "TK_REAL";
    if (token == TK_COMMA)
        return "TK_COMMA";
    if (token == TK_SEM)
        return "TK_SEM";
    if (token == TK_COLON)
        return "TK_COLON";
    if (token == TK_DOT)
        return "TK_DOT";
    if (token == TK_ENDWHILE)
        return "TK_ENDWHILE";
    if (token == TK_OP)
        return "TK_OP";
    if (token == TK_CL)
        return "TK_CL";
    if (token == TK_IF)
        return "TK_IF";
    if (token == TK_THEN)
        return "TK_THEN";
    if (token == TK_ENDIF)
        return "TK_ENDIF";
    if (token == TK_READ)
        return "TK_READ";
    if (token == TK_WRITE)
        return "TK_WRITE";
    if (token == TK_RETURN)
        return "TK_RETURN";
    if (token == TK_PLUS)
        return "TK_PLUS";
    if (token == TK_MINUS)
        return "TK_MINUS";
    if (token == TK_MUL)
        return "TK_MUL";
    if (token == TK_DIV)
        return "TK_DIV";
    if (token == TK_CALL)
        return "TK_CALL";
    if (token == TK_RECORD)
        return "TK_RECORD";
    if (token == TK_ENDRECORD)
        return "TK_ENDRECORD";
    if (token == TK_ELSE)
        return "TK_ELSE";
    if (token == TK_AND)
        return "TK_AND";
    if (token == TK_OR)
        return "TK_OR";
    if (token == TK_NOT)
        return "TK_NOT";
    if (token == TK_LT)
        return "TK_LT";
    if (token == TK_LE)
        return "TK_LE";
    if (token == TK_EQ)
        return "TK_EQ";
    if (token == TK_GT)
        return "TK_GT";
    if (token == TK_GE)
        return "TK_GE";
    if (token == TK_NE)
        return "TK_NE";
    return "token not recognised";
}

int hashCode(char *str)
{
    int length = strlen(str);
    ll mod = 1e9 + 9;
    ll p = 1e6 + 7;
    ll curMult = 0;
    int iterator = 0;
    for (iterator = 0; iterator < length; iterator++)
    {
        curMult = ((curMult * p) + str[iterator]) % mod;
    }
    curMult %= TABLE_SIZE;
    return curMult;
}

void constructHashTable(hashEntry hashTable[])
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        hashTable[i].str = NULL;
        hashTable[i].next = NULL;
    }
}

hashEntry *initHashEntry(hashEntry hashMap[], int hash)
{
    hashEntry *obj = &hashMap[hash];
    return obj;
}

void pushHashTable(char *str, Tk tokenType, hashEntry hashMap[])
{
    int hash = hashCode(str);
    // printf("%d\n", hash);
    if (!hashMap[hash].str)
    { // the cell at this hash is empty
        hashMap[hash].str = (char *)malloc(sizeof(char) * strlen(str) + 1);
        strcpy(hashMap[hash].str, str);
        // hashTable[hash].str = str;
        hashMap[hash].token = tokenType;
    }
    else
    {
        hashEntry *trav = initHashEntry(hashMap, hash);
        while (trav->next)
        {
            trav = trav->next;
        }
        trav->next = (hashEntry *)malloc(sizeof(hashEntry));
        trav = trav->next;
        trav->str = (char *)malloc(sizeof(char) * strlen(str) + 1);
        strcpy(trav->str, str);
        // hashTable[hash].str = str;
        trav->token = tokenType;
        trav->next = NULL;
    }
}

hashRet initHashRet()
{
    hashRet obj;
    obj.found = FALSE;
    obj.ent = NULL;
    return obj;
}

hashRet search(char *str, hashEntry hashMap[])
{
    int hash = hashCode(str);
    hashRet obj = initHashRet();
    hashEntry temp = hashMap[hash];

    if (hashMap[hash].str)
    {
        hashEntry *trav = initHashEntry(hashMap, hash);
        while (trav && trav->str)
        {
            if (!strcmp(str, trav->str))
            {
                obj.found = TRUE;
                obj.ent = trav;
            }
            trav = trav->next;
        }
        free(trav);
    }
    return obj;
}

void pushKeyword(hashEntry hashTable[])
{
    constructHashTable(hashTable);
    pushHashTable("with", TK_WITH, hashTable);
    pushHashTable("parameters", TK_PARAMETERS, hashTable);
    pushHashTable("end", TK_END, hashTable);
    pushHashTable("while", TK_WHILE, hashTable);
    pushHashTable("union", TK_UNION, hashTable);
    pushHashTable("endunion", TK_ENDUNION, hashTable);
    pushHashTable("definetype", TK_DEFINETYPE, hashTable);
    pushHashTable("as", TK_AS, hashTable);
    pushHashTable("type", TK_TYPE, hashTable);
    pushHashTable("_main", TK_MAIN, hashTable);
    pushHashTable("global", TK_GLOBAL, hashTable);
    pushHashTable("parameter", TK_PARAMETER, hashTable);
    pushHashTable("list", TK_LIST, hashTable);
    pushHashTable("input", TK_INPUT, hashTable);
    pushHashTable("output", TK_OUTPUT, hashTable);
    pushHashTable("int", TK_INT, hashTable);
    pushHashTable("real", TK_REAL, hashTable);
    pushHashTable("endwhile", TK_ENDWHILE, hashTable);
    pushHashTable("if", TK_IF, hashTable);
    pushHashTable("then", TK_WITH, hashTable);
    pushHashTable("endif", TK_ENDIF, hashTable);
    pushHashTable("read", TK_READ, hashTable);
    pushHashTable("write", TK_WRITE, hashTable);
    pushHashTable("return", TK_RETURN, hashTable);
    pushHashTable("call", TK_CALL, hashTable);
    pushHashTable("record", TK_RECORD, hashTable);
    pushHashTable("endrecord", TK_ENDRECORD, hashTable);
    pushHashTable("else", TK_ELSE, hashTable);
}

// int isKeyWord(char *lexeme)
// {
//     return search(lexeme, hashMapKeys).found;
// }

// int main()
// {
//     pushKeyword(hashMapKeys);
//     int coll = 0;
//     int total = 0;
//     for (int i = 0; i < TABLE_SIZE; i++)
//     {
//         hashEntry *curr = &hashMapKeys[i];
//         if (curr->str != NULL)
//         {
//             while (curr && curr->str != NULL)
//             {
//                 total++;
//                 coll++;
//                 printf("%s\n", curr->str);
//                 curr = curr->next;
//             }
//             coll--;
//         }
//     }
//     printf("%d, %d", coll, total);
// }