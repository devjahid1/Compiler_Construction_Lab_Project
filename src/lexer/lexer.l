%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/parser.tab.h"

int line_no = 1;

static char *copy_lexeme(const char *text)
{
    size_t length = strlen(text) + 1;
    char *copy = malloc(length);

    if (copy == NULL) {
        fprintf(stderr, "Out of memory while reading token\n");
        exit(EXIT_FAILURE);
    }

    memcpy(copy, text, length);
    return copy;
}
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INTNUM      {DIGIT}+
FLOATNUM    {DIGIT}+\.{DIGIT}+

%%

"int"               { return T_INT; }
"float"             { return T_FLOAT; }
"bool"              { return T_BOOL; }
"if"                { return T_IF; }
"else"              { return T_ELSE; }
"while"             { return T_WHILE; }
"print"             { return T_PRINT; }
"true"              { return T_TRUE; }
"false"             { return T_FALSE; }

"=="                { return T_EQ; }
"!="                { return T_NE; }
"<="                { return T_LE; }
">="                { return T_GE; }
"&&"                { return T_AND; }
"||"                { return T_OR; }
"="                 { return T_ASSIGN; }
"<"                 { return T_LT; }
">"                 { return T_GT; }
"+"                 { return T_PLUS; }
"-"                 { return T_MINUS; }
"*"                 { return T_MUL; }
"/"                 { return T_DIV; }
"%"                 { return T_MOD; }
"!"                 { return T_NOT; }
"("                 { return T_LPAREN; }
")"                 { return T_RPAREN; }
"{"                 { return T_LBRACE; }
"}"                 { return T_RBRACE; }
";"                 { return T_SEMICOLON; }
","                 { return T_COMMA; }

{FLOATNUM}           { yylval.text = copy_lexeme(yytext); return T_FLOAT_LITERAL; }
{INTNUM}             { yylval.text = copy_lexeme(yytext); return T_INT_LITERAL; }
{ID}                 { yylval.text = copy_lexeme(yytext); return T_IDENTIFIER; }

"//".*              { /* Skip line comments. */ }
[ \t\r]+            { /* Skip whitespace. */ }
\n                  { ++line_no; }

.                    { fprintf(stderr, "Lexical error at line %d: %s\n", line_no, yytext); }

%%
