%{
#include <stdio.h>

int line = 1;
%}

%option noyywrap

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INT        {DIGIT}+
FLOAT      {DIGIT}+"."{DIGIT}+

%%

[\t\r ]+                    ;

\n                          { line++; }

"//".*                      ;

"int"                       { printf("KEYWORD : int\n"); }
"float"                     { printf("KEYWORD : float\n"); }
"bool"                      { printf("KEYWORD : bool\n"); }
"char"                      { printf("KEYWORD : char\n"); }
"string"                    { printf("KEYWORD : string\n"); }
"void"                      { printf("KEYWORD : void\n"); }

"if"                        { printf("KEYWORD : if\n"); }
"else"                      { printf("KEYWORD : else\n"); }
"while"                     { printf("KEYWORD : while\n"); }
"for"                       { printf("KEYWORD : for\n"); }
"return"                    { printf("KEYWORD : return\n"); }
"break"                     { printf("KEYWORD : break\n"); }
"continue"                  { printf("KEYWORD : continue\n"); }
"print"                     { printf("KEYWORD : print\n"); }

"true"                      { printf("BOOLEAN : true\n"); }
"false"                     { printf("BOOLEAN : false\n"); }

{FLOAT}                     { printf("FLOAT : %s\n", yytext); }
{INT}                       { printf("INTEGER : %s\n", yytext); }

{ID}                        { printf("IDENTIFIER : %s\n", yytext); }

"++"                        { printf("INCREMENT\n"); }
"--"                        { printf("DECREMENT\n"); }

"<="                        { printf("LE\n"); }
">="                        { printf("GE\n"); }
"=="                        { printf("EQ\n"); }
"!="                        { printf("NE\n"); }

"&&"                        { printf("AND\n"); }
"||"                        { printf("OR\n"); }

"+"                         { printf("PLUS\n"); }
"-"                         { printf("MINUS\n"); }
"*"                         { printf("MULTIPLY\n"); }
"/"                         { printf("DIVIDE\n"); }
"%"                         { printf("MOD\n"); }

"<"                         { printf("LT\n"); }
">"                         { printf("GT\n"); }

"="                         { printf("ASSIGN\n"); }

"!"                         { printf("NOT\n"); }

";"                         { printf("SEMICOLON\n"); }
","                         { printf("COMMA\n"); }

"("                         { printf("LPAREN\n"); }
")"                         { printf("RPAREN\n"); }

"{"                         { printf("LBRACE\n"); }
"}"                         { printf("RBRACE\n"); }

"["                         { printf("LBRACKET\n"); }
"]"                         { printf("RBRACKET\n"); }

\"[^\"]*\"                  { printf("STRING : %s\n", yytext); }

\'[^\']\'                   { printf("CHAR : %s\n", yytext); }

.                           {
                                printf("LEXICAL ERROR : %s at line %d\n", yytext, line);
                            }

%%

int main(void)
{
    printf("====================================\n");
    printf("      LEXICAL ANALYZER\n");
    printf("====================================\n");
    printf("Enter source code (Ctrl+D to finish)\n\n");

    yylex();

    printf("\n====================================\n");
    printf("Lexical Analysis Completed.\n");
    printf("====================================\n");

    return 0;
}