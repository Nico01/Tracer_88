/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING = 258,
    IDENT = 259,
    FBSYM = 260,
    CODE1 = 261,
    CODE2 = 262,
    CODE4 = 263,
    NUMBER0 = 264,
    NUMBER1 = 265,
    NUMBER2 = 266,
    NUMBER3 = 267,
    NUMBER = 268,
    DOT = 269,
    EXTERN = 270,
    DATA = 271,
    ASCII = 272,
    SECTION = 273,
    COMMON = 274,
    BASE = 275,
    SYMB = 276,
    SYMD = 277,
    ALIGN = 278,
    ASSERT = 279,
    SPACE = 280,
    LINE = 281,
    FILe = 282,
    LIST = 283,
    OP_EQ = 284,
    OP_NE = 285,
    OP_LE = 286,
    OP_GE = 287,
    OP_LL = 288,
    OP_RR = 289,
    OP_OO = 290,
    OP_AA = 291,
    R16 = 292,
    R8 = 293,
    RSEG = 294,
    PREFIX = 295,
    NOOP_1 = 296,
    NOOP_2 = 297,
    JOP = 298,
    PUSHOP = 299,
    IOOP = 300,
    ADDOP = 301,
    ROLOP = 302,
    INCOP = 303,
    NOTOP = 304,
    CALLOP = 305,
    CALFOP = 306,
    LEAOP = 307,
    ARPLOP = 308,
    ESC = 309,
    INT = 310,
    RET = 311,
    XCHG = 312,
    TEST = 313,
    MOV = 314,
    IMUL = 315,
    ENTER = 316,
    EXTOP = 317,
    EXTOP1 = 318,
    ST = 319
  };
#endif
/* Tokens.  */
#define STRING 258
#define IDENT 259
#define FBSYM 260
#define CODE1 261
#define CODE2 262
#define CODE4 263
#define NUMBER0 264
#define NUMBER1 265
#define NUMBER2 266
#define NUMBER3 267
#define NUMBER 268
#define DOT 269
#define EXTERN 270
#define DATA 271
#define ASCII 272
#define SECTION 273
#define COMMON 274
#define BASE 275
#define SYMB 276
#define SYMD 277
#define ALIGN 278
#define ASSERT 279
#define SPACE 280
#define LINE 281
#define FILe 282
#define LIST 283
#define OP_EQ 284
#define OP_NE 285
#define OP_LE 286
#define OP_GE 287
#define OP_LL 288
#define OP_RR 289
#define OP_OO 290
#define OP_AA 291
#define R16 292
#define R8 293
#define RSEG 294
#define PREFIX 295
#define NOOP_1 296
#define NOOP_2 297
#define JOP 298
#define PUSHOP 299
#define IOOP 300
#define ADDOP 301
#define ROLOP 302
#define INCOP 303
#define NOTOP 304
#define CALLOP 305
#define CALFOP 306
#define LEAOP 307
#define ARPLOP 308
#define ESC 309
#define INT 310
#define RET 311
#define XCHG 312
#define TEST 313
#define MOV 314
#define IMUL 315
#define ENTER 316
#define EXTOP 317
#define EXTOP1 318
#define ST 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 223 "as.y" /* yacc.c:1909  */

    short y_word;
    long y_valu;
    expr_t y_expr;
    item_t *y_item;

#line 189 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
