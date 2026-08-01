#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

/*========================================*/
/* Create AST Node                        */
/*========================================*/

ASTNode *createNode(NodeType type, const char *value)
{
    ASTNode *node = malloc(sizeof(*node));

    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->type = type;
    node->line = 0;
    node->scope = 0;

    if (value != NULL)
    {
        strncpy(node->value, value, sizeof(node->value) - 1);
        node->value[sizeof(node->value) - 1] = '\0';
    }
    else
    {
        node->value[0] = '\0';
    }

    node->left = NULL;
    node->right = NULL;
    node->next = NULL;

    return node;
}

/*========================================*/
/* Add Child                              */
/*========================================*/

void addChild(ASTNode *parent, ASTNode *child)
{
    if (parent == NULL || child == NULL)
        return;

    if (parent->left == NULL)
    {
        parent->left = child;
        return;
    }

    ASTNode *temp = parent->left;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = child;
}

/*========================================*/
/* Free AST                               */
/*========================================*/

void freeAST(ASTNode *root)
{
    if (root == NULL)
        return;

    freeAST(root->left);
    freeAST(root->right);
    freeAST(root->next);

    free(root);
}
