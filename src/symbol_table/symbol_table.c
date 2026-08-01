#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

static Symbol *symbols;
static int currentScope;
static int nextScope = 1;
static int errorCount;
static int scopeParents[256];

static Symbol *lookupInScope(const char *name, int scope)
{
    Symbol *symbol;

    for (symbol = symbols; symbol != NULL; symbol = symbol->next) {
        if (symbol->scope == scope && strcmp(symbol->name, name) == 0) {
            return symbol;
        }
    }
    return NULL;
}

int insertSymbol(const char *name, const char *dataType, int scope, int line)
{
    Symbol *symbol;

    if (lookupInScope(name, scope) != NULL) {
        fprintf(stderr, "Semantic Error at line %d: duplicate declaration of %s\n", line, name);
        ++errorCount;
        return 0;
    }

    symbol = malloc(sizeof(*symbol));
    if (symbol == NULL) {
        fprintf(stderr, "Unable to allocate symbol table entry.\n");
        exit(EXIT_FAILURE);
    }

    snprintf(symbol->name, sizeof(symbol->name), "%s", name);
    snprintf(symbol->dataType, sizeof(symbol->dataType), "%s", dataType);
    symbol->scope = scope;
    symbol->line = line;
    symbol->next = symbols;
    symbols = symbol;
    return 1;
}

Symbol *lookupSymbol(const char *name)
{
    int scope = currentScope;
    Symbol *symbol;

    for (;;) {
        symbol = lookupInScope(name, scope);
        if (symbol != NULL) {
            return symbol;
        }
        if (scope == 0) {
            break;
        }
        scope = scopeParents[scope];
    }
    return NULL;
}

int updateSymbol(const char *name, const char *dataType)
{
    Symbol *symbol = lookupSymbol(name);

    if (symbol == NULL) {
        return 0;
    }
    snprintf(symbol->dataType, sizeof(symbol->dataType), "%s", dataType);
    return 1;
}

void enterScope(void)
{
    if (nextScope >= (int)(sizeof(scopeParents) / sizeof(scopeParents[0]))) {
        fprintf(stderr, "Symbol table scope limit exceeded.\n");
        exit(EXIT_FAILURE);
    }
    scopeParents[nextScope] = currentScope;
    currentScope = nextScope++;
}

void exitScope(void)
{
    if (currentScope != 0) {
        currentScope = scopeParents[currentScope];
    }
}

int getCurrentScope(void)
{
    return currentScope;
}

void setCurrentScope(int scope)
{
    currentScope = scope;
}

int getSymbolTableErrorCount(void)
{
    return errorCount;
}

void printSymbolTable(void)
{
    Symbol *symbol;

    printf("\nSymbol Table\n");
    printf("%-16s %-10s %-7s %s\n", "Identifier", "Type", "Scope", "Line");
    printf("------------------------------------------------\n");
    for (symbol = symbols; symbol != NULL; symbol = symbol->next) {
        printf("%-16s %-10s %-7d %d\n", symbol->name, symbol->dataType,
               symbol->scope, symbol->line);
    }
}

void freeSymbolTable(void)
{
    Symbol *symbol = symbols;

    while (symbol != NULL) {
        Symbol *next = symbol->next;
        free(symbol);
        symbol = next;
    }
    symbols = NULL;
    currentScope = 0;
    nextScope = 1;
    errorCount = 0;
    memset(scopeParents, 0, sizeof(scopeParents));
}