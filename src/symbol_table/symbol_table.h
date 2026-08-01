#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char name[100];
    char dataType[16];
    int scope;
    int line;
    struct Symbol *next;
} Symbol;

int insertSymbol(const char *name, const char *dataType, int scope, int line);
Symbol *lookupSymbol(const char *name);
int updateSymbol(const char *name, const char *dataType);
void printSymbolTable(void);
void enterScope(void);
void exitScope(void);
int getCurrentScope(void);
void setCurrentScope(int scope);
int getSymbolTableErrorCount(void);
void freeSymbolTable(void);

#endif
