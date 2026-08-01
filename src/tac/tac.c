#include <stdio.h>
#include <string.h>

#include "tac.h"

static int temporaryNumber;
static int labelNumber;

static void newTemporary(char *result, size_t size) { snprintf(result, size, "t%d", ++temporaryNumber); }
static void newLabel(char *result, size_t size) { snprintf(result, size, "L%d", ++labelNumber); }

static void generateExpression(ASTNode *node, char *result, size_t size)
{
    ASTNode *right;
    char leftValue[32], rightValue[32];

    if (node == NULL) { snprintf(result, size, "<error>"); return; }
    if (node->type == NODE_IDENTIFIER || node->type == NODE_INT || node->type == NODE_FLOAT || node->type == NODE_BOOL) {
        snprintf(result, size, "%s", node->value);
        return;
    }
    if (node->type == NODE_UNARY_EXPR) {
        generateExpression(node->left, leftValue, sizeof(leftValue));
        newTemporary(result, size);
        printf("%s = %s%s\n", result, node->value, leftValue);
        return;
    }
    generateExpression(node->left, leftValue, sizeof(leftValue));
    right = node->left == NULL ? NULL : node->left->next;
    generateExpression(right, rightValue, sizeof(rightValue));
    newTemporary(result, size);
    printf("%s = %s %s %s\n", result, leftValue, node->value, rightValue);
}

static void generateNode(ASTNode *node)
{
    ASTNode *condition;
    ASTNode *thenBranch;
    ASTNode *elseBranch;
    ASTNode *savedNext;
    char value[32], falseLabel[32], endLabel[32], startLabel[32];

    if (node == NULL) return;
    if (node->type == NODE_PROGRAM) {
        generateNode(node->left);
    } else if (node->type == NODE_ASSIGNMENT) {
        generateExpression(node->left->next, value, sizeof(value));
        printf("%s = %s\n", node->left->value, value);
    } else if (node->type == NODE_PRINT) {
        generateExpression(node->left, value, sizeof(value));
        printf("print %s\n", value);
    } else if (node->type == NODE_IF) {
        condition = node->left;
        thenBranch = condition->next;
        elseBranch = thenBranch->next;
        generateExpression(condition, value, sizeof(value));
        newLabel(falseLabel, sizeof(falseLabel));
        printf("ifFalse %s goto %s\n", value, falseLabel);
        savedNext = thenBranch->next;
        thenBranch->next = NULL;
        generateNode(thenBranch);
        thenBranch->next = savedNext;
        if (elseBranch != NULL) {
            newLabel(endLabel, sizeof(endLabel));
            printf("goto %s\n%s:\n", endLabel, falseLabel);
            generateNode(elseBranch);
            printf("%s:\n", endLabel);
        } else printf("%s:\n", falseLabel);
    } else if (node->type == NODE_WHILE) {
        condition = node->left;
        thenBranch = condition->next;
        newLabel(startLabel, sizeof(startLabel));
        newLabel(falseLabel, sizeof(falseLabel));
        printf("%s:\n", startLabel);
        generateExpression(condition, value, sizeof(value));
        printf("ifFalse %s goto %s\n", value, falseLabel);
        generateNode(thenBranch);
        printf("goto %s\n%s:\n", startLabel, falseLabel);
    }
    generateNode(node->next);
}

void generateTAC(ASTNode *root)
{
    temporaryNumber = 0;
    labelNumber = 0;
    printf("\nThree Address Code\n");
    generateNode(root);
}
