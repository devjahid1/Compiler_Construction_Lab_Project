#include <stdio.h>
#include <string.h>

#include "semantic.h"
#include "../symbol_table/symbol_table.h"

static int errorCount;

static int isNumeric(const char *type)
{
    return strcmp(type, "int") == 0 || strcmp(type, "float") == 0;
}

static const char *expressionType(ASTNode *node)
{
    ASTNode *left;
    ASTNode *right;
    const char *leftType;
    const char *rightType;
    Symbol *symbol;

    if (node == NULL) return "error";
    if (node->type == NODE_INT) return "int";
    if (node->type == NODE_FLOAT) return "float";
    if (node->type == NODE_BOOL) return "bool";
    if (node->type == NODE_IDENTIFIER) {
        symbol = lookupSymbol(node->value);
        if (symbol == NULL) {
            fprintf(stderr, "Semantic Error at line %d: undeclared variable %s\n", node->line, node->value);
            ++errorCount;
            return "error";
        }
        return symbol->dataType;
    }
    if (node->type == NODE_UNARY_EXPR) {
        leftType = expressionType(node->left);
        if (strcmp(node->value, "!") == 0 && strcmp(leftType, "bool") != 0) {
            fprintf(stderr, "Semantic Error at line %d: ! requires a bool expression\n", node->line);
            ++errorCount;
            return "error";
        }
        return "bool";
    }
    if (node->type != NODE_BINARY_EXPR) return "error";

    left = node->left;
    right = left == NULL ? NULL : left->next;
    leftType = expressionType(left);
    rightType = expressionType(right);
    if (strcmp(leftType, "error") == 0 || strcmp(rightType, "error") == 0) return "error";

    if (strchr("+-*/%", node->value[0]) != NULL) {
        if (!isNumeric(leftType) || !isNumeric(rightType)) {
            fprintf(stderr, "Semantic Error at line %d: arithmetic operands must be numeric\n", node->line);
            ++errorCount;
            return "error";
        }
        return (strcmp(leftType, "float") == 0 || strcmp(rightType, "float") == 0) ? "float" : "int";
    }
    if (strcmp(node->value, "&&") == 0 || strcmp(node->value, "||") == 0) {
        if (strcmp(leftType, "bool") != 0 || strcmp(rightType, "bool") != 0) {
            fprintf(stderr, "Semantic Error at line %d: logical operands must be bool\n", node->line);
            ++errorCount;
        }
        return "bool";
    }
    if (strcmp(leftType, rightType) != 0 && !(isNumeric(leftType) && isNumeric(rightType))) {
        fprintf(stderr, "Semantic Error at line %d: incompatible comparison\n", node->line);
        ++errorCount;
    }
    return "bool";
}

static void analyzeNode(ASTNode *node)
{
    ASTNode *target;
    ASTNode *value;
    Symbol *symbol;
    const char *valueType;

    if (node == NULL) return;
    setCurrentScope(node->scope);

    if (node->type == NODE_ASSIGNMENT) {
        target = node->left;
        value = target == NULL ? NULL : target->next;
        symbol = target == NULL ? NULL : lookupSymbol(target->value);
        if (symbol == NULL) {
            fprintf(stderr, "Semantic Error at line %d: undeclared variable %s\n", node->line, target == NULL ? "<unknown>" : target->value);
            ++errorCount;
        } else {
            valueType = expressionType(value);
            if (strcmp(valueType, "error") != 0 && strcmp(symbol->dataType, valueType) != 0 &&
                !(strcmp(symbol->dataType, "float") == 0 && strcmp(valueType, "int") == 0)) {
                fprintf(stderr, "Semantic Error at line %d: type mismatch assigning %s to %s\n", node->line, valueType, symbol->dataType);
                ++errorCount;
            }
        }
    } else if (node->type == NODE_IF || node->type == NODE_WHILE || node->type == NODE_PRINT) {
        (void)expressionType(node->left);
    }

    analyzeNode(node->left);
    analyzeNode(node->next);
}

int semanticAnalyze(ASTNode *root)
{
    errorCount = getSymbolTableErrorCount();
    analyzeNode(root);
    if (errorCount == 0) printf("\nSemantic Analysis Result: successful\n");
    else printf("\nSemantic Analysis Result: %d error(s)\n", errorCount);
    return errorCount == 0;
}
