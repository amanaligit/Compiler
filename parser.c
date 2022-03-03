#include "parser.h"

StackEle* initStack(){
    StackEle* firstNode = (StackEle*)malloc(sizeof(StackEle));
    firstNode->next = NULL;
    firstNode->ele = (TreeNode*)malloc(sizeof(TreeNode));
    firstNode->ele->treeTag = LEAF;
}