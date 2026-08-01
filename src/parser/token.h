#ifndef TOKEN_H
#define TOKEN_H

/* Keywords */
#define T_INT          256
#define T_FLOAT        257
#define T_BOOL         258

#define T_IF           259
#define T_ELSE         260
#define T_WHILE        261
#define T_PRINT        262

#define T_TRUE         263
#define T_FALSE        264

/* Identifier & Literals */
#define T_IDENTIFIER   265
#define T_INT_LITERAL  266
#define T_FLOAT_LITERAL 267

/* Arithmetic Operators */
#define T_PLUS         268
#define T_MINUS        269
#define T_MUL          270
#define T_DIV          271
#define T_MOD          272

/* Assignment */
#define T_ASSIGN       273

/* Relational Operators */
#define T_LT           274
#define T_GT           275
#define T_LE           276
#define T_GE           277
#define T_EQ           278
#define T_NE           279

/* Logical Operators */
#define T_AND          280
#define T_OR           281
#define T_NOT          282

/* Delimiters */
#define T_LPAREN       283
#define T_RPAREN       284

#define T_LBRACE       285
#define T_RBRACE       286

#define T_SEMICOLON    287
#define T_COMMA        288

#endif