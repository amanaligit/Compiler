#include<hashTable.h>

int hashCode(char* str){
    int p = 31;
    int m = 1e9+9;
    long long ans = 0;
    int len = strlen(str);
    int currMult = 1;
    for(int i = 0; i<len; ++i){
        ans = (ans+ str[i]*currMult)%m;
        currMult = (currMult*p)%m;
    }
    return ans%TABLE_SIZE;
}

void constructHashTable(hashEntry hashTable[]){
    for(int i = 0; i<TABLE_SIZE; ++i){
        hashTable[i].str = NULL;
        hashTable[i].token = -1;
        hashTable[i].next = NULL;
    }
}

void pushHashTable(char* str, Tk tokenType, hashEntry hashTable[]){
    int hash = hashCode(str);
    if(!hashTable[hash].str){ //the cell at this hash is empty
        hashTable[hash].str = (char*)malloc(sizeof(char)*strlen(str)+1);
        strcpy(hashTable[hash].str, str);
        hashTable[hash].token = tokenType;
    }
    else{
        
    }
}