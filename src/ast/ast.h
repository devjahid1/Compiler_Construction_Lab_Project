#ifndef AST_H
#define AST_H

/*========================================*/
/* AST NODE TYPES                         */
/*========================================*/

typedef enum
{
    NODE_PROGRAM,

    NODE_DECLARATION,
    NODE_ASSIGNMENT,

    NODE_IF,
    NODE_WHILE,
    NODE_PRINT,

    NODE_BINARY_EXPR,
    NODE_UNARY_EXPR,

    NODE_IDENTIFIER,
    NODE_INT,
    NODE_FLOAT,
    NODE_BOOL

} NodeType;

/*========================================*/
/* AST NODE                               */
/*========================================*/

typedef struct ASTNode
{
    NodeType type;

    char value[100];
    int line;
    int scope;

    struct ASTNode *left;  /* First child. */
    struct ASTNode *right; /* Reserved for binary-tree compatibility. */
    struct ASTNode *next;  /* Next sibling. */

} ASTNode;

/*========================================*/
/* FUNCTIONS                              */
/*========================================*/

/* Create a new AST node */
ASTNode *createNode(NodeType type, const char *value);

/* Add child to node */
void addChild(ASTNode *parent, ASTNode *child);

/* Print AST */
void printAST(ASTNode *root, int level);

/* Free memory */
void freeAST(ASTNode *root);

#endif /* AST_H */
