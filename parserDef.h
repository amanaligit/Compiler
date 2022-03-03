#include "lexer.h"

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

typedef enum treeNodeTag{
    NT, LEAF
} TreeNodeTag;

typedef struct ntNode{
    Tk tokenType;
    TreeNode *child, *sibling, *parent;
} NTNode;

typedef struct leafNode{
    Token fromLexer;
    TreeNode* child, *sibling, *parent;
} LeafNode;

typedef union combine{
        NTNode ntNode;
        LeafNode leafNode;
    } Combine;

typedef struct treeNode{
    Combine node;
    TreeNodeTag treeTag;
}TreeNode;

typedef struct stackEle{
    TreeNode* ele;
    struct stackEle* next;
} StackEle;

#endif