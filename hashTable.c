#include "hashTable.h"

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

hashEntry* initHashEntry(hashEntry hashMap[], int hash){
    hashEntry* obj = &hashMap[hash];
    return obj;
}

void pushHashTable(char *str, Tk tokenType, hashEntry hashTable[])
{
    int hash = hashCode(str);
    // printf("%d\n", hash);
    if (!hashTable[hash].str)
    { // the cell at this hash is empty
        hashTable[hash].str = (char *)malloc(sizeof(char) * strlen(str) + 1);
        strcpy(hashTable[hash].str, str);
        // hashTable[hash].str = str;
        hashTable[hash].token = tokenType;
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

hashRet* initHashRet(){
    hashRet* obj = (hashRet*)malloc(sizeof(hashRet));
    obj->found = FALSE;
    obj->ent = NULL;
    return obj;
}

hashRet* search(char* str, hashEntry hashMap[]){
    int hash = hashCode(str);
    hashRet* obj = initHashRet();
    if(!hashMap[hash].str){
        hashEntry* trav = initHashEntry(hashMap, hash);
        while(trav){
            if(!strcmp(str, trav->str)){
                obj->found = TRUE;
                obj->ent = trav;
            }
            trav = trav->next;
        }
    }
    return obj;
}

void pushKeyword(hashEntry hashTable[])
{
    constructHashTable(hashTable);
    pushHashTable("with", TK_WITH, hashTable);
    pushHashTable("parameters", TK_PARAMETERS, hashTable);
    pushHashTable("end", TK_END, hashTable);
    pushHashTable("While", TK_WHILE, hashTable);
    pushHashTable("Union", TK_UNION, hashTable);
    pushHashTable("endunion", TK_ENDUNION, hashTable);
    pushHashTable("definetype", TK_DEFINETYPE, hashTable);
    pushHashTable("as", TK_AS, hashTable);
    pushHashTable("Type", TK_TYPE, hashTable);
    pushHashTable("_main", TK_MAIN, hashTable);
    pushHashTable("Global", TK_GLOBAL, hashTable);
    pushHashTable("parameter", TK_PARAMETER, hashTable);
    pushHashTable("List", TK_LIST, hashTable);
    pushHashTable("Input", TK_INPUT, hashTable);
    pushHashTable("Output", TK_OUTPUT, hashTable);
    pushHashTable("Int", TK_INT, hashTable);
    pushHashTable("Real", TK_REAL, hashTable);
    pushHashTable("endwhile", TK_ENDWHILE, hashTable);
    pushHashTable("If", TK_IF, hashTable);
    pushHashTable("Then", TK_WITH, hashTable);
    pushHashTable("Endif", TK_ENDIF, hashTable);
    pushHashTable("Read", TK_READ, hashTable);
    pushHashTable("Write", TK_WRITE, hashTable);
    pushHashTable("Return", TK_RETURN, hashTable);
    pushHashTable("Call", TK_CALL, hashTable);
    pushHashTable("Record", TK_RECORD, hashTable);
    pushHashTable("endrecord", TK_ENDRECORD, hashTable);
    pushHashTable("Else", TK_ELSE, hashTable);
}

int main()
{
    pushKeyword(hashMap);
    int coll = 0;
    int total = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashEntry *curr = &hashMap[i];
        if (curr->str != NULL)
        {
            while (curr && curr->str != NULL)
            {
                total++;
                coll++;
                printf("%s\n", curr->str);
                curr = curr->next;
            }
            coll--;
        }
    }
    printf("%d, %d", coll, total);
}