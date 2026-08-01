%{
#include <stdio.h>
#include <stdlib.h>

#include "../ast/ast.h"
#include "../symbol_table/symbol_table.h"
#include "../semantic/semantic.h"
#include "../tac/tac.h"

extern int yylex(void);
extern int line_no;

ASTNode *root = NULL;

void yyerror(const char *message);

static ASTNode *markNode(ASTNode *node)
{
    if (node != NULL) {
        node->line = line_no;
        node->scope = getCurrentScope();
    }
    return node;
}

static void insertDeclarationSymbols(ASTNode *type, ASTNode *identifiers)
{
    ASTNode *identifier;

    if (identifiers == NULL) {
        return;
    }

    insertSymbol(identifiers->value, type->value, getCurrentScope(), identifiers->line);
    for (identifier = identifiers->left; identifier != NULL; identifier = identifier->next) {
        insertSymbol(identifier->value, type->value, getCurrentScope(), identifier->line);
    }
}
%}

%code requires {
#include "../ast/ast.h"
}

%union {
    ASTNode *node;
    char *text;
}

%token T_INT T_FLOAT T_BOOL
%token T_IF T_ELSE T_WHILE T_PRINT
%token T_TRUE T_FALSE
%token <text> T_IDENTIFIER T_INT_LITERAL T_FLOAT_LITERAL
%token T_PLUS T_MINUS T_MUL T_DIV T_MOD T_ASSIGN
%token T_LT T_GT T_LE T_GE T_EQ T_NE
%token T_AND T_OR T_NOT
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_SEMICOLON T_COMMA

%type <node> program statement_list statement declaration assignment type
%type <node> identifier_list expression block if_statement while_statement print_statement

%nonassoc LOWER_THAN_ELSE
%nonassoc T_ELSE
%left T_OR
%left T_AND
%left T_EQ T_NE
%left T_LT T_GT T_LE T_GE
%left T_PLUS T_MINUS
%left T_MUL T_DIV T_MOD
%right T_NOT

%start program

%%

program
    : statement_list                 { root = $1; $$ = root; }
    | /* empty */                    { root = NULL; $$ = NULL; }
    ;

statement_list
    : statement_list statement        { addChild($1, $2); $$ = $1; }
    | statement                       { $$ = createNode(NODE_PROGRAM, "PROGRAM"); addChild($$, $1); }
    ;

statement
    : declaration                     { $$ = markNode($1); }
    | assignment                      { $$ = markNode($1); }
    | if_statement                    { $$ = markNode($1); }
    | while_statement                 { $$ = markNode($1); }
    | print_statement                 { $$ = markNode($1); }
    | block                           { $$ = $1; }
    | error T_SEMICOLON               { yyerrok; $$ = NULL; }
    ;

block
    : T_LBRACE { enterScope(); } statement_list T_RBRACE
                                    { $$ = markNode(createNode(NODE_PROGRAM, "BLOCK")); addChild($$, $3); exitScope(); }
    | T_LBRACE { enterScope(); } T_RBRACE
                                    { $$ = markNode(createNode(NODE_PROGRAM, "BLOCK")); exitScope(); }
    ;

type
    : T_INT                           { $$ = markNode(createNode(NODE_IDENTIFIER, "int")); }
    | T_FLOAT                         { $$ = markNode(createNode(NODE_IDENTIFIER, "float")); }
    | T_BOOL                          { $$ = markNode(createNode(NODE_IDENTIFIER, "bool")); }
    ;

identifier_list
    : T_IDENTIFIER                    { $$ = markNode(createNode(NODE_IDENTIFIER, $1)); free($1); }
    | identifier_list T_COMMA T_IDENTIFIER
                                    { addChild($1, markNode(createNode(NODE_IDENTIFIER, $3))); free($3); $$ = $1; }
    ;

declaration
    : type identifier_list T_SEMICOLON
                                    { $$ = markNode(createNode(NODE_DECLARATION, "DECLARATION")); addChild($$, $1); addChild($$, $2); insertDeclarationSymbols($1, $2); }
    ;

assignment
    : T_IDENTIFIER T_ASSIGN expression T_SEMICOLON
                                    { $$ = markNode(createNode(NODE_ASSIGNMENT, "=")); addChild($$, markNode(createNode(NODE_IDENTIFIER, $1))); free($1); addChild($$, $3); }
    ;

if_statement
    : T_IF T_LPAREN expression T_RPAREN statement %prec LOWER_THAN_ELSE
                                    { $$ = markNode(createNode(NODE_IF, "if")); addChild($$, $3); addChild($$, $5); }
    | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement
                                    { $$ = markNode(createNode(NODE_IF, "if")); addChild($$, $3); addChild($$, $5); addChild($$, $7); }
    ;

while_statement
    : T_WHILE T_LPAREN expression T_RPAREN statement
                                    { $$ = markNode(createNode(NODE_WHILE, "while")); addChild($$, $3); addChild($$, $5); }
    ;

print_statement
    : T_PRINT T_LPAREN expression T_RPAREN T_SEMICOLON
                                    { $$ = markNode(createNode(NODE_PRINT, "print")); addChild($$, $3); }
    ;

expression
    : T_IDENTIFIER                    { $$ = markNode(createNode(NODE_IDENTIFIER, $1)); free($1); }
    | T_INT_LITERAL                   { $$ = markNode(createNode(NODE_INT, $1)); free($1); }
    | T_FLOAT_LITERAL                 { $$ = markNode(createNode(NODE_FLOAT, $1)); free($1); }
    | T_TRUE                          { $$ = markNode(createNode(NODE_BOOL, "true")); }
    | T_FALSE                         { $$ = markNode(createNode(NODE_BOOL, "false")); }
    | T_LPAREN expression T_RPAREN    { $$ = $2; }
    | T_NOT expression                { $$ = markNode(createNode(NODE_UNARY_EXPR, "!")); addChild($$, $2); }
    | expression T_PLUS expression    { $$ = markNode(createNode(NODE_BINARY_EXPR, "+")); addChild($$, $1); addChild($$, $3); }
    | expression T_MINUS expression   { $$ = markNode(createNode(NODE_BINARY_EXPR, "-")); addChild($$, $1); addChild($$, $3); }
    | expression T_MUL expression     { $$ = markNode(createNode(NODE_BINARY_EXPR, "*")); addChild($$, $1); addChild($$, $3); }
    | expression T_DIV expression     { $$ = markNode(createNode(NODE_BINARY_EXPR, "/")); addChild($$, $1); addChild($$, $3); }
    | expression T_MOD expression     { $$ = markNode(createNode(NODE_BINARY_EXPR, "%")); addChild($$, $1); addChild($$, $3); }
    | expression T_LT expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, "<")); addChild($$, $1); addChild($$, $3); }
    | expression T_GT expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, ">")); addChild($$, $1); addChild($$, $3); }
    | expression T_LE expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, "<=")); addChild($$, $1); addChild($$, $3); }
    | expression T_GE expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, ">=")); addChild($$, $1); addChild($$, $3); }
    | expression T_EQ expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, "==")); addChild($$, $1); addChild($$, $3); }
    | expression T_NE expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, "!=")); addChild($$, $1); addChild($$, $3); }
    | expression T_AND expression     { $$ = markNode(createNode(NODE_BINARY_EXPR, "&&")); addChild($$, $1); addChild($$, $3); }
    | expression T_OR expression      { $$ = markNode(createNode(NODE_BINARY_EXPR, "||")); addChild($$, $1); addChild($$, $3); }
    ;

%%

void yyerror(const char *message)
{
    fprintf(stderr, "Syntax error at line %d: %s\n", line_no, message);
}

int main(void)
{
    int result = yyparse();

    if (result == 0 && root != NULL) {
        printAST(root, 0);
        printSymbolTable();
        semanticAnalyze(root);
        generateTAC(root);
        freeAST(root);
    }

    freeSymbolTable();

    return result;
}
