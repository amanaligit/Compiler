#include "parser.h"

// some lines may be missing!
StackEle *initStack()
{
    StackEle *firstNode = (StackEle *)malloc(sizeof(StackEle));
    firstNode->next = NULL;
    firstNode->ele = (TreeNode *)malloc(sizeof(TreeNode));
    firstNode->ele->treeTag = TERM;
    firstNode->ele->node.leafNode.child = NULL;
    firstNode->ele->node.leafNode.sibling = NULL;
    firstNode->ele->node.leafNode.fromLexer.tokenType = DOLLAR;
}

StackEle *push(StackEle *node, StackEle *head)
{
    node->next = head;
    head = node;
    return head;
}

StackEle *pop(StackEle *head)
{
    if (!head)
    {
        return NULL;
    }
    else
    {
        StackEle *rem = head;
        head = head->next;
        free(rem);
        return head;
    }
}
