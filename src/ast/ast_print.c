#include <stdio.h>
#include "ast.h"

/*========================================*/
/* Print Indentation                      */
/*========================================*/

static void printIndent(int level)
{
    for (int i = 0; i < level; ++i)
    {
        printf("    ");
    }
}

/*========================================*/
/* Node Type Name                         */
/*========================================*/

static const char *nodeTypeName(NodeType type)
{
    switch (type)
    {
        case NODE_PROGRAM:
            return "PROGRAM";

        case NODE_DECLARATION:
            return "DECLARATION";

        case NODE_ASSIGNMENT:
            return "ASSIGNMENT";

        case NODE_IF:
            return "IF";

        case NODE_WHILE:
            return "WHILE";

        case NODE_PRINT:
            return "PRINT";

        case NODE_BINARY_EXPR:
            return "BINARY_EXPR";

        case NODE_UNARY_EXPR:
            return "UNARY_EXPR";

        case NODE_IDENTIFIER:
            return "IDENTIFIER";

        case NODE_INT:
            return "INTEGER";

        case NODE_FLOAT:
            return "FLOAT";

        case NODE_BOOL:
            return "BOOLEAN";

        default:
            return "UNKNOWN";
    }
}

/*========================================*/
/* Print AST                              */
/*========================================*/

void printAST(ASTNode *root, int level)
{
    if (root == NULL)
        return;

    printIndent(level);

    printf("%s", nodeTypeName(root->type));

    if (root->value[0] != '\0')
    {
        printf(" (%s)", root->value);
    }

    printf("\n");

    /* First Child */
    printAST(root->left, level + 1);

    /* Next Sibling */
    printAST(root->next, level);
}
