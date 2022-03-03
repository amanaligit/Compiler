#include "lexer.h"

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

typedef enum treeNodeTag
{
    NT,
    TERM
} TreeNodeTag;

#define MAX_TERMS 64

typedef struct grammar
{
    int productions[MAX_TERMS][MAX_TERMS][MAX_TERMS];
    int first[MAX_TERMS][MAX_TERMS];
    int follow[MAX_TERMS][MAX_TERMS];

    // 0: [[1, 2, 3], [2, 4, 5], ]

} Grammar;

typedef struct ntNode
{
    Tk tokenType;
    TreeNode *child, *sibling, *parent;
} NTNode;

typedef struct leafNode
{
    Token fromLexer;
    TreeNode *child, *sibling, *parent;
} LeafNode;

typedef union combine
{
    NTNode ntNode;
    LeafNode leafNode;
} Combine;

typedef struct treeNode
{
    Combine node;
    TreeNodeTag treeTag;
} TreeNode;

typedef struct stackEle
{
    TreeNode *ele;
    struct stackEle *next;
} StackEle;

#endif