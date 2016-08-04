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
    SYS_CON = 258,
    SYS_TYPE = 259,
    DOT = 260,
    PROGRAM = 261,
    ID = 262,
    SEMI = 263,
    CONST = 264,
    EQUAL = 265,
    INTEGER = 266,
    REAL = 267,
    CHAR = 268,
    STRING = 269,
    TYPE = 270,
    ARRAY = 271,
    LB = 272,
    RB = 273,
    OF = 274,
    RECORD = 275,
    END = 276,
    COLON = 277,
    COMMA = 278,
    LP = 279,
    RP = 280,
    DOTDOT = 281,
    MINUS = 282,
    VAR = 283,
    FUNCTION = 284,
    PROCEDURE = 285,
    ASSIGN = 286,
    SYS_PROC = 287,
    READ = 288,
    BEGIN_PASCAL = 289,
    IF = 290,
    THEN = 291,
    ELSE = 292,
    REPEAT = 293,
    UNTIL = 294,
    WHILE = 295,
    DO = 296,
    FOR = 297,
    TO = 298,
    DOWNTO = 299,
    CASE = 300,
    GOTO = 301,
    GE = 302,
    GT = 303,
    LE = 304,
    LT = 305,
    UNEQUAL = 306,
    PLUS = 307,
    OR = 308,
    MUL = 309,
    DIV = 310,
    MOD = 311,
    AND = 312,
    SYS_FUNCT = 313,
    NOT = 314
  };
#endif
/* Tokens.  */
#define SYS_CON 258
#define SYS_TYPE 259
#define DOT 260
#define PROGRAM 261
#define ID 262
#define SEMI 263
#define CONST 264
#define EQUAL 265
#define INTEGER 266
#define REAL 267
#define CHAR 268
#define STRING 269
#define TYPE 270
#define ARRAY 271
#define LB 272
#define RB 273
#define OF 274
#define RECORD 275
#define END 276
#define COLON 277
#define COMMA 278
#define LP 279
#define RP 280
#define DOTDOT 281
#define MINUS 282
#define VAR 283
#define FUNCTION 284
#define PROCEDURE 285
#define ASSIGN 286
#define SYS_PROC 287
#define READ 288
#define BEGIN_PASCAL 289
#define IF 290
#define THEN 291
#define ELSE 292
#define REPEAT 293
#define UNTIL 294
#define WHILE 295
#define DO 296
#define FOR 297
#define TO 298
#define DOWNTO 299
#define CASE 300
#define GOTO 301
#define GE 302
#define GT 303
#define LE 304
#define LT 305
#define UNEQUAL 306
#define PLUS 307
#define OR 308
#define MUL 309
#define DIV 310
#define MOD 311
#define AND 312
#define SYS_FUNCT 313
#define NOT 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
