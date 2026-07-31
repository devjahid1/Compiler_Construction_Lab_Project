%{
#include <stdio.h>

int line = 1;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT         {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+

%%

"int"           { printf("KEYWORD : int\n"); }
"float"         { printf("KEYWORD : float\n"); }
"bool"          { printf("KEYWORD : bool\n"); }

"if"            { printf("KEYWORD : if\n"); }
"else"          { printf("KEYWORD : else\n"); }
"while"         { printf("KEYWORD : while\n"); }

"print"         { printf("KEYWORD : print\n"); }

"true"          { printf("BOOLEAN : true\n"); }
"false"         { printf("BOOLEAN : false\n"); }

{FLOAT}         { printf("FLOAT : %s\n",yytext); }

{INT}           { printf("INTEGER : %s\n",yytext); }

{ID}            { printf("IDENTIFIER : %s\n",yytext); }

"+"             { printf("PLUS\n"); }
"-"             { printf("MINUS\n"); }
"*"             { printf("MULTIPLY\n"); }
"/"             { printf("DIVIDE\n"); }

"="             { printf("ASSIGN\n"); }

";"             { printf("SEMICOLON\n"); }

"("             { printf("LPAREN\n"); }
")"             { printf("RPAREN\n"); }

"{"             { printf("LBRACE\n"); }
"}"             { printf("RBRACE\n"); }

[ \t\r]+        ;

\n              { line++; }

.               {
                    printf("LEXICAL ERROR : %s at line %d\n",yytext,line);
                }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}