/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 41 "src/parser/parser.y"

#include "../ast/ast.h"

#line 53 "src/parser/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_INT = 258,                   /* T_INT  */
    T_FLOAT = 259,                 /* T_FLOAT  */
    T_BOOL = 260,                  /* T_BOOL  */
    T_IF = 261,                    /* T_IF  */
    T_ELSE = 262,                  /* T_ELSE  */
    T_WHILE = 263,                 /* T_WHILE  */
    T_PRINT = 264,                 /* T_PRINT  */
    T_TRUE = 265,                  /* T_TRUE  */
    T_FALSE = 266,                 /* T_FALSE  */
    T_IDENTIFIER = 267,            /* T_IDENTIFIER  */
    T_INT_LITERAL = 268,           /* T_INT_LITERAL  */
    T_FLOAT_LITERAL = 269,         /* T_FLOAT_LITERAL  */
    T_PLUS = 270,                  /* T_PLUS  */
    T_MINUS = 271,                 /* T_MINUS  */
    T_MUL = 272,                   /* T_MUL  */
    T_DIV = 273,                   /* T_DIV  */
    T_MOD = 274,                   /* T_MOD  */
    T_ASSIGN = 275,                /* T_ASSIGN  */
    T_LT = 276,                    /* T_LT  */
    T_GT = 277,                    /* T_GT  */
    T_LE = 278,                    /* T_LE  */
    T_GE = 279,                    /* T_GE  */
    T_EQ = 280,                    /* T_EQ  */
    T_NE = 281,                    /* T_NE  */
    T_AND = 282,                   /* T_AND  */
    T_OR = 283,                    /* T_OR  */
    T_NOT = 284,                   /* T_NOT  */
    T_LPAREN = 285,                /* T_LPAREN  */
    T_RPAREN = 286,                /* T_RPAREN  */
    T_LBRACE = 287,                /* T_LBRACE  */
    T_RBRACE = 288,                /* T_RBRACE  */
    T_SEMICOLON = 289,             /* T_SEMICOLON  */
    T_COMMA = 290,                 /* T_COMMA  */
    LOWER_THAN_ELSE = 291          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "src/parser/parser.y"

    ASTNode *node;
    char *text;

#line 111 "src/parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_PARSER_TAB_H_INCLUDED  */