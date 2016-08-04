/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.pascal" /* yacc.c:339  */


#include "global.h"
#include "SymbolTable.h"
#include "typeCheck.h"
#include "code.h"
#define WIDTH (4)
#define HEIGHT (0)

typedef struct stringConstNode {
	struct stringConstNode * next;
	char * name;
	char * value;
} stringConstNode;

void printAncestor(int *uncle, int level);
void printThisTree(TreeNode * t, int *uncle, int level);
extern void openFile(int argc, char** argv);
TreeNode * makeNewConstNode(int type, int value, int line_no);
TreeNode * makeNewFactorNode(int type, int value, int line_no);
TreeNode * makeNewTermNode(int type, int value, int line_no);
TreeNode * makeNewExprNode(int type, int value, int line_no);
TreeNode * makeNewExpressionNode(int type, int value, int line_no);
TreeNode * closeExpression(TreeNode * k);
void itoa(int value, char *buf, int radix);
int checkBool(TreeNode *);
TreeNode * eliminateUselessFromList(TreeNode * t);
TreeNode * getStmtNode(TreeNode * t);
int isUseless(TreeNode * t);
void setStmtNodeToNULL(TreeNode * t);
stringConstNode * insertIntoStringConstTable(TreeNode * t);
stringConstNode * makeNewStringConstNode();
void releaseStringConstNode(stringConstNode * t);
void updateConstPart();
void insertIntoConstPart(stringConstNode * sconst, TreeNode * const_part);
void printStringConstTable();

stringConstNode * stringConstTable = NULL;
int stringConstCount = 0;
int currentline = 0;
TreeNode * savedTree = NULL;
VarTable* MainVarTable = NULL;
ConstTable* MainConstTable = NULL;
TypeTable* MainTypeTable = NULL;
ProcedureTable* MainProcedureTable = NULL;


#line 114 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 283 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   442

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  283

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    58,    58,    72,    78,    87,    93,   109,   119,   125,
     141,   148,   161,   168,   181,   184,   188,   194,   206,   215,
     220,   225,   230,   254,   267,   274,   287,   290,   294,   300,
     312,   316,   320,   326,   340,   356,   369,   372,   376,   382,
     394,   405,   420,   423,   427,   433,   438,   443,   452,   461,
     471,   482,   493,   506,   513,   526,   529,   533,   539,   551,
     562,   575,   588,   591,   595,   601,   613,   626,   638,   649,
     658,   665,   680,   683,   687,   693,   703,   714,   720,   726,
     737,   752,   755,   759,   763,   769,   778,   786,   789,   792,
     795,   798,   801,   804,   807,   810,   815,   825,   839,   853,
     859,   869,   875,   885,   897,   908,   946,   954,   961,   974,
     997,  1015,  1020,  1027,  1041,  1049,  1062,  1065,  1069,  1075,
    1085,  1097,  1107,  1159,  1173,  1178,  1183,  1188,  1193,  1198,
    1205,  1251,  1265,  1270,  1275,  1282,  1332,  1346,  1351,  1356,
    1361,  1368,  1374,  1384,  1390,  1400,  1425,  1441,  1455,  1469,
    1480,  1491,  1502,  1518,  1522,  1526,  1532
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYS_CON", "SYS_TYPE", "DOT", "PROGRAM",
  "ID", "SEMI", "CONST", "EQUAL", "INTEGER", "REAL", "CHAR", "STRING",
  "TYPE", "ARRAY", "LB", "RB", "OF", "RECORD", "END", "COLON", "COMMA",
  "LP", "RP", "DOTDOT", "MINUS", "VAR", "FUNCTION", "PROCEDURE", "ASSIGN",
  "SYS_PROC", "READ", "BEGIN_PASCAL", "IF", "THEN", "ELSE", "REPEAT",
  "UNTIL", "WHILE", "DO", "FOR", "TO", "DOWNTO", "CASE", "GOTO", "GE",
  "GT", "LE", "LT", "UNEQUAL", "PLUS", "OR", "MUL", "DIV", "MOD", "AND",
  "SYS_FUNCT", "NOT", "$accept", "program", "program_head", "routine",
  "routine_head", "sub_routine", "label_part", "const_part",
  "const_expr_list", "const_expr", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "name_list",
  "name_list_1", "simple_type_decl", "var_part", "var_decl_list",
  "var_decl", "routine_part", "routine_part_1", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_decl", "routine_body", "stmt_list",
  "stmt_list_1", "stmt", "non_label_stmt", "assign_stmt", "proc_stmt",
  "compound_stmt", "if_stmt", "else_clause", "repeat_stmt", "while_stmt",
  "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr_list_1", "case_expr", "goto_stmt", "expression",
  "expression_op", "expr", "expr_op", "term", "term_op", "factor",
  "args_list", "args_list_1", "empty", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

#define YYPACT_NINF -194

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-194)))

#define YYTABLE_NINF -157

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      54,    21,    37,    52,   333,    61,  -194,  -194,    83,     9,
      75,  -194,  -194,  -194,  -194,   152,  -194,  -194,    56,    74,
    -194,    84,    85,   122,  -194,  -194,   107,   326,  -194,   108,
      91,  -194,  -194,  -194,   123,   235,   118,   126,   141,    13,
     170,    13,   135,    13,   155,   171,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,   428,  -194,  -194,  -194,
     173,   345,  -194,   117,    96,  -194,  -194,   184,    13,    35,
      13,   305,    35,    13,  -194,   248,  -194,  -194,  -194,  -194,
      13,    13,   172,    13,  -194,   183,     1,   214,  -194,   156,
     197,   180,    97,  -194,  -194,   206,   373,  -194,  -194,   112,
    -194,   196,   285,    66,  -194,  -194,  -194,    98,  -194,   189,
     231,  -194,   245,   212,   216,   245,  -194,   217,   218,   249,
      13,    35,   226,  -194,    35,  -194,  -194,   290,  -194,  -194,
    -194,  -194,  -194,    13,  -194,  -194,  -194,    13,  -194,  -194,
    -194,  -194,    13,    13,   290,    13,   423,  -194,  -194,   241,
     266,   168,   169,   428,   258,   277,  -194,  -194,  -194,   373,
    -194,   250,   112,  -194,  -194,   291,   292,  -194,   294,  -194,
     295,    13,   269,  -194,    63,  -194,  -194,  -194,   240,   279,
    -194,   286,   280,     1,   214,  -194,   245,  -194,   178,  -194,
     296,   297,   299,   408,  -194,   314,   302,    79,   151,  -194,
     309,  -194,   319,   323,   428,  -194,   349,  -194,   329,   329,
     333,   333,   245,    13,  -194,   245,  -194,  -194,  -194,   290,
    -194,  -194,  -194,  -194,    13,   290,   290,  -194,  -194,  -194,
    -194,   340,    79,  -194,  -194,   373,  -194,   391,  -194,  -194,
      11,   337,  -194,  -194,     9,   356,   357,   245,  -194,   213,
     358,   360,   350,   362,   428,  -194,    26,   169,   359,    57,
    -194,   302,  -194,  -194,  -194,   290,  -194,  -194,   373,  -194,
    -194,   361,   302,  -194,    22,  -194,  -194,  -194,  -194,   302,
    -194,  -194,  -194
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     0,     0,     1,     8,     0,     0,
     156,    10,     4,     2,    78,     0,     6,    77,     0,   156,
      12,    84,     0,     0,    81,    16,     0,     0,    14,     0,
     156,    24,    83,   104,     0,    99,     0,   101,     0,     0,
       0,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,     0,    15,    13,    28,
       0,     0,    26,     0,     0,    53,    82,     0,     0,     0,
       0,     0,     0,     0,    22,   141,    18,    19,    20,    21,
       0,     0,   143,     0,   145,     0,   123,   131,   136,     0,
       0,     0,     0,   121,    80,     0,     0,    27,    25,    57,
      42,     0,     0,     0,    55,    64,     7,     0,    62,     0,
       0,   155,   153,     0,   151,    96,    85,     0,     0,     0,
       0,     0,     0,   148,     0,   147,   128,     0,   124,   125,
     126,   127,   129,     0,   133,   132,   134,     0,   137,   138,
     139,   140,     0,     0,     0,     0,     0,    17,    45,    46,
       0,     0,     0,     0,     0,     0,    31,    32,    30,     0,
      43,     0,    56,    54,    63,     0,     0,    60,     0,    61,
       0,     0,     0,   100,     0,   102,   103,   150,     0,     0,
     146,     0,   156,   122,   130,   135,   108,   109,     0,   118,
       0,     0,     0,     0,   116,     0,     0,    38,     0,    36,
       0,    44,     0,     0,     0,    29,     0,    41,   156,   156,
       0,     0,    98,     0,   154,   152,   149,   142,   144,     0,
     105,   107,   111,   112,     0,     0,     0,   113,   117,   115,
      51,     0,    37,    34,    35,     0,    47,     0,    48,    58,
       0,     0,    70,    68,     0,     0,     0,    97,   106,     0,
       0,     0,     0,     0,     0,    49,    44,     0,     0,     0,
      72,     0,     9,    65,    67,     0,   120,   119,     0,    39,
      50,     0,     0,    73,     0,    69,    66,   110,    33,     0,
      76,    71,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,  -194,   367,   161,  -194,  -194,  -194,   351,
     -55,  -194,  -194,   321,  -154,  -194,  -194,  -194,   190,  -137,
    -194,  -193,  -194,  -194,   287,  -194,  -194,  -194,  -194,  -194,
    -194,   182,  -194,   121,   148,   366,  -194,  -114,   325,  -194,
    -194,    -9,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,   205,  -194,   -35,  -194,   268,  -194,   262,  -194,   -64,
     -41,  -194,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     8,   244,   245,    10,    19,    27,    28,
      84,    30,    61,    62,   155,   156,   157,   198,   199,   101,
     102,   158,    64,   103,   104,   106,   107,   167,   168,   169,
     170,   241,   259,   260,    16,    22,    23,    45,    46,    47,
      48,    49,    50,   220,    51,    52,    53,   224,    54,   192,
     193,   194,    55,   112,   133,    86,   137,    87,   142,    88,
     113,   114,    11
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    95,    20,   231,    85,   206,    90,    24,    92,   118,
      14,    31,   256,   182,   200,   202,    74,   123,   100,   125,
      75,    -3,    65,   201,    76,    77,    78,    79,   134,   100,
     187,   117,    24,   110,   -74,   115,   111,    80,    74,   257,
      81,   154,    75,    15,     5,   122,    76,    77,    78,    79,
     257,   -74,     6,   135,   136,     1,   108,    25,   273,    80,
       2,   200,    81,    26,   214,   274,    74,   162,   276,    12,
      75,    82,    83,   100,    76,    77,    78,    79,   185,   280,
     179,   253,   275,   181,    18,   178,   282,    80,    13,    29,
      81,   191,    32,    82,    83,   -52,   -52,   105,   203,   164,
     -52,   -44,   -44,   258,   154,   248,    33,   126,   186,    59,
     188,   250,   251,   -44,   278,    60,   146,    56,    99,    63,
     271,    82,    83,    34,   100,  -156,  -156,   165,   166,    35,
    -156,    66,   -59,    36,   -44,   -44,   212,   258,   191,   215,
      71,   154,    91,   -79,   128,   129,   130,   131,   132,   238,
      72,   277,   232,    21,    37,    38,    15,    39,   100,  -156,
      40,   -79,    41,  -156,    42,    73,    93,    43,    44,   197,
     201,    21,   233,  -156,   221,   100,   100,  -156,   247,    94,
     154,  -156,   255,    96,  -156,  -156,  -156,  -156,   126,   249,
    -156,   109,  -156,   126,  -156,   143,   124,  -156,  -156,   270,
     242,   242,  -156,  -156,  -156,  -156,   154,   126,  -156,  -156,
    -156,   145,  -156,   154,   147,  -156,  -156,   154,   159,   127,
     171,   222,   223,   126,   154,   128,   129,   130,   131,   132,
     128,   129,   130,   131,   132,    17,   126,   173,   144,   174,
      67,   126,   175,   176,   128,   129,   130,   131,   132,   172,
     126,   180,    68,   119,   265,   126,   177,   207,   216,    69,
     128,   129,   130,   131,   132,   120,    70,   195,   138,   139,
     140,   141,   121,   128,   129,   130,   131,   132,   128,   129,
     130,   131,   132,   196,   204,   205,   160,   128,   129,   130,
     131,   132,   128,   129,   130,   131,   132,    35,   208,   209,
     213,    36,   210,   211,   217,    74,   148,   -40,   161,   149,
     -40,   218,    35,    76,    77,    78,    79,   219,   225,   226,
     227,   230,    37,    38,    15,    39,   152,    57,    40,   153,
      41,   235,    42,    26,     7,    43,    44,    37,    38,    15,
      39,   -11,  -156,    40,   236,    41,    97,    42,  -156,   237,
      43,    44,    60,   240,   -11,   -11,   -11,   239,   252,   261,
     -11,  -156,  -156,  -156,   263,   264,   266,  -156,   267,   268,
     269,     9,   246,   -23,   -23,   -23,    74,   148,    58,   -23,
     149,   272,    98,   279,    76,    77,    78,    79,   234,   150,
     163,   243,   262,   151,    74,   281,   116,   152,   229,   184,
     153,   183,    76,    77,    78,    79,    89,     0,     0,   228,
       0,    74,     0,     0,     0,   190,     0,     0,   254,    76,
      77,    78,    79,     0,   189,     0,    74,     0,     0,  -114,
     190,    74,     0,     0,    76,    77,    78,    79,     0,    76,
      77,    78,    79
};

static const yytype_int16 yycheck[] =
{
       9,    56,    10,   196,    39,   159,    41,    15,    43,    73,
       1,    19,     1,   127,   151,   152,     3,    81,     7,    83,
       7,     0,    30,     1,    11,    12,    13,    14,    27,     7,
     144,    72,    40,    68,     8,    70,     1,    24,     3,    28,
      27,    96,     7,    34,     7,    80,    11,    12,    13,    14,
      28,    25,     0,    52,    53,     1,    64,     1,     1,    24,
       6,   198,    27,     7,     1,     8,     3,     1,   261,     8,
       7,    58,    59,     7,    11,    12,    13,    14,   142,   272,
     121,   235,    25,   124,     9,   120,   279,    24,     5,    15,
      27,   146,     8,    58,    59,    29,    30,     1,   153,     1,
      34,    22,    23,   240,   159,   219,    21,    10,   143,     1,
     145,   225,   226,     1,   268,     7,    19,    10,     1,    28,
     257,    58,    59,     1,     7,    29,    30,    29,    30,     7,
      34,     8,    34,    11,    22,    23,   171,   274,   193,   174,
      22,   196,     7,    21,    47,    48,    49,    50,    51,   204,
      24,   265,     1,     1,    32,    33,    34,    35,     7,     7,
      38,    39,    40,    11,    42,    24,    11,    45,    46,     1,
       1,     1,    21,    21,   182,     7,     7,     7,   213,     8,
     235,    11,   237,    10,    32,    33,    34,    35,    10,   224,
      38,     7,    40,    10,    42,    39,    24,    45,    46,   254,
     208,   209,    32,    33,    34,    35,   261,    10,    38,    39,
      40,    31,    42,   268,     8,    45,    46,   272,    22,    36,
      31,    43,    44,    10,   279,    47,    48,    49,    50,    51,
      47,    48,    49,    50,    51,   244,    10,    25,    41,    23,
       5,    10,    25,    25,    47,    48,    49,    50,    51,    18,
      10,    25,    17,     5,    41,    10,     7,     7,    18,    24,
      47,    48,    49,    50,    51,    17,    31,    26,    54,    55,
      56,    57,    24,    47,    48,    49,    50,    51,    47,    48,
      49,    50,    51,    17,    26,     8,     1,    47,    48,    49,
      50,    51,    47,    48,    49,    50,    51,     7,     7,     7,
      31,    11,     8,     8,    25,     3,     4,    22,    23,     7,
      25,    25,     7,    11,    12,    13,    14,    37,    22,    22,
      21,     7,    32,    33,    34,    35,    24,     1,    38,    27,
      40,    22,    42,     7,     1,    45,    46,    32,    33,    34,
      35,    15,     9,    38,    25,    40,     1,    42,    15,    26,
      45,    46,     7,    24,    28,    29,    30,     8,    18,    22,
      34,    28,    29,    30,     8,     8,     8,    34,     8,    19,
       8,     4,   211,    28,    29,    30,     3,     4,    27,    34,
       7,    22,    61,    22,    11,    12,    13,    14,   198,    16,
     103,   209,   244,    20,     3,   274,    71,    24,   193,   137,
      27,   133,    11,    12,    13,    14,    40,    -1,    -1,     1,
      -1,     3,    -1,    -1,    -1,     7,    -1,    -1,    27,    11,
      12,    13,    14,    -1,     1,    -1,     3,    -1,    -1,    21,
       7,     3,    -1,    -1,    11,    12,    13,    14,    -1,    11,
      12,    13,    14
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    61,    62,     7,     0,     1,    63,    64,
      66,   122,     8,     5,     1,    34,    94,   101,     9,    67,
     122,     1,    95,    96,   122,     1,     7,    68,    69,    15,
      71,   122,     8,    21,     1,     7,    11,    32,    33,    35,
      38,    40,    42,    45,    46,    97,    98,    99,   100,   101,
     102,   104,   105,   106,   108,   112,    10,     1,    69,     1,
       7,    72,    73,    28,    82,   122,     8,     5,    17,    24,
      31,    22,    24,    24,     3,     7,    11,    12,    13,    14,
      24,    27,    58,    59,    70,   113,   115,   117,   119,    95,
     113,     7,   113,    11,     8,    70,    10,     1,    73,     1,
       7,    79,    80,    83,    84,     1,    85,    86,   122,     7,
     113,     1,   113,   120,   121,   113,    98,   120,   119,     5,
      17,    24,   113,   119,    24,   119,    10,    36,    47,    48,
      49,    50,    51,   114,    27,    52,    53,   116,    54,    55,
      56,    57,   118,    39,    41,    31,    19,     8,     4,     7,
      16,    20,    24,    27,    70,    74,    75,    76,    81,    22,
       1,    23,     1,    84,     1,    29,    30,    87,    88,    89,
      90,    31,    18,    25,    23,    25,    25,     7,   113,   120,
      25,   120,    97,   115,   117,   119,   113,    97,   113,     1,
       7,    70,   109,   110,   111,    26,    17,     1,    77,    78,
      79,     1,    79,    70,    26,     8,    74,     7,     7,     7,
       8,     8,   113,    31,     1,   113,    18,    25,    25,    37,
     103,   122,    43,    44,   107,    22,    22,    21,     1,   111,
       7,    81,     1,    21,    78,    22,    25,    26,    70,     8,
      24,    91,   122,    91,    64,    65,    65,   113,    97,   113,
      97,    97,    18,    74,    27,    70,     1,    28,    79,    92,
      93,    22,    94,     8,     8,    41,     8,     8,    19,     8,
      70,    79,    22,     1,     8,    25,    81,    97,    74,    22,
      81,    93,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    62,    62,    63,    64,    64,    65,
      66,    67,    67,    68,    68,    68,    68,    69,    70,    70,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    73,
      74,    74,    74,    75,    76,    77,    77,    77,    77,    78,
      79,    80,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    83,    83,    83,    83,    84,    85,
      86,    86,    86,    86,    86,    87,    88,    89,    90,    91,
      91,    92,    92,    92,    92,    93,    93,    94,    94,    95,
      96,    96,    96,    96,    96,    97,    97,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    99,    99,    99,   100,
     100,   100,   100,   100,   101,   102,   103,   103,   104,   105,
     106,   107,   107,   108,   109,   110,   110,   110,   110,   111,
     111,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   116,   117,   117,   118,   118,   118,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   121,   121,   121,   121,   122
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     3,     1,     2,     5,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     1,     4,
       1,     1,     1,     6,     3,     2,     1,     2,     1,     4,
       1,     3,     1,     2,     1,     1,     1,     3,     3,     4,
       5,     3,     2,     1,     2,     1,     2,     1,     4,     1,
       2,     2,     1,     2,     1,     4,     5,     4,     3,     3,
       1,     3,     1,     2,     1,     4,     3,     1,     1,     1,
       3,     1,     3,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     1,
       4,     1,     4,     4,     3,     5,     2,     1,     4,     4,
       8,     1,     1,     5,     1,     2,     1,     2,     1,     4,
       4,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     4,     1,     4,     1,     3,     2,     2,     4,
       3,     1,     3,     1,     3,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 58 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = program_NodeKind;
    if ((yyvsp[-2]) != NULL) {
        (yyval)->child = (yyvsp[-2]);
        currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
        (yyvsp[-2])->sibling = (yyvsp[-1]);

        releaseNode((yyvsp[0]));

        savedTree = (yyval);
        updateConstPart();
    }
}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 72 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----missing dot at the end of the file\n");
    (yyval) = NULL;
}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 78 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = program_head_NodeKind;
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 87 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----program head error\n");
    (yyval) = NULL;
}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = routine_NodeKind;
    if ((yyvsp[-1]) != NULL) {
        (yyval)->child = (yyvsp[-1]);
        currentline = (yyval)->line_no = (yyvsp[-1])->line_no;
        (yyvsp[-1])->sibling = (yyvsp[0]);
    } else if ((yyvsp[0]) != NULL) {
        (yyval)->child = (yyvsp[0]);
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
    } else {
        (yyval)->child = NULL;
    }
}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 109 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = routine_head_NodeKind;
    (yyval)->child = (yyvsp[-4]);
    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    (yyvsp[-4])->sibling = (yyvsp[-3]);
    (yyvsp[-3])->sibling = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[-1]);
    (yyvsp[-1])->sibling = (yyvsp[0]);
}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 119 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----routine header error detected\n");
    (yyval) = NULL;
}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 125 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = sub_routine_NodeKind;
    if ((yyvsp[-1]) != NULL) {
        (yyval)->child = (yyvsp[-1]);
        currentline = (yyval)->line_no = (yyvsp[-1])->line_no;
        (yyvsp[-1])->sibling = (yyvsp[0]);
    } else if ((yyvsp[0]) != NULL) {
        (yyval)->child = (yyvsp[0]);
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
    } else {
        (yyval)->child = NULL;
    }
}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 141 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = empty_label_part_NodeKind;
    (yyval)->line_no = currentline;
}
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 148 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = const_part_NodeKind;

    if ((yyvsp[0]) == NULL) {
    	(yyval)->nodeKind = empty_const_part_NodeKind;
    }

    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    releaseNode((yyvsp[-1]));
}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 161 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = empty_const_part_NodeKind;
    (yyval)->line_no = currentline;
}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 168 "yacc.pascal" /* yacc.c:1646  */
    {
	if ((yyvsp[-1]) != NULL) {
		TreeNode * temp = (yyvsp[-1]);
		while (temp->sibling != NULL) {
		    temp = temp->sibling;
		}
		temp->sibling = (yyvsp[0]);
    	(yyval) = (yyvsp[-1]);
    }
    else {
    	(yyval) = (yyvsp[0]);
    }
}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 181 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 184 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----const declaration error detected\n");
	(yyval) = (yyvsp[-1]);
}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 188 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----const declaration error detected\n");
	(yyval) = NULL;
}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 194 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = const_expr_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 206 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = integer_const_value_NodeKind;
    currentline = (yyval)->line_no;

    (yyval)->computable = 1;
    (yyval)->result = atoi((yyval)->literal);
    (yyval)->type = 1;
}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 215 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = real_const_value_NodeKind;
    currentline = (yyval)->line_no;
}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 220 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = char_const_value_NodeKind;
    currentline = (yyval)->line_no;
}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 225 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = string_const_value_NodeKind;
    currentline = (yyval)->line_no;
}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 230 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    if ((yyval)->literal[0] == 'm') {
        free((yyval)->literal);

        char buffer[15];
        itoa(2147483647, buffer, 10);
        (yyval)->literal = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
        strcpy((yyval)->literal, buffer);
        (yyval)->nodeKind = integer_const_value_NodeKind;

        (yyval)->result = 2147483647;
            (yyval)->type = 1;
    } else {
        (yyval)->nodeKind = sys_con_const_value_NodeKind;
        (yyval)->result = (((yyval)->literal)[0] == 't') ? 1 : 0;
        (yyval)->type = 0;
    }

    (yyval)->computable = 1;
    currentline = (yyval)->line_no;
}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 254 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = type_part_NodeKind;

    if ((yyvsp[0]) == NULL) {
        (yyval)->nodeKind = empty_type_part_NodeKind;
    }

    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    releaseNode((yyvsp[-1]));
}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 267 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = empty_type_part_NodeKind;
    (yyval)->line_no = currentline;
}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 274 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) != NULL) {
        TreeNode * temp = (yyvsp[-1]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 287 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 290 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----type declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 294 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----type declaration error detected\n");
    (yyval) = NULL;
}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 300 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = type_definition_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 312 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    currentline = (yyval)->line_no;
}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 316 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    currentline = (yyval)->line_no;
}
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 320 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    currentline = (yyval)->line_no;
}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 326 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = array_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-5])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-5]));
    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[-1]));
}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 340 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = record_type_decl_NodeKind;

    if ((yyvsp[-1]) == NULL) {
        // error detected, no need to process further, exit
    }

    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 356 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) != NULL) {
        TreeNode * temp = (yyvsp[-1]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 369 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 372 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----record declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 376 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----record declaration error detected\n");
    (yyval) = NULL;
}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 382 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = field_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 394 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = name_list_NodeKind;
    (yyval)->line_no = currentline;
    if ((yyvsp[0]) != NULL) {
        (yyval)->child = (yyvsp[0]);
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
    }
}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 405 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-2]) != NULL) {
        TreeNode * temp = (yyvsp[-2]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-2]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }

    releaseNode((yyvsp[-1]));
}
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 420 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 423 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----name_list error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 427 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----name_list error detected\n");
    (yyval) = NULL;
}
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 433 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = sys_type_simple_type_decl_NodeKind;
    currentline = (yyval)->line_no;
}
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 438 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = id_simple_type_decl_NodeKind;
    currentline = (yyval)->line_no;
}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 443 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = lp_name_list_rp_simple_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 452 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = const_dotdot_const_simple_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 461 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = m_const_dotdot_const_simple_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-3]));
    releaseNode((yyvsp[-1]));
}
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 471 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = m_const_dotdot_m_const_simple_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[-1]));
}
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 482 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_dotdot_id_simple_type_decl_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 493 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = var_part_NodeKind;

    if ((yyvsp[0]) == NULL) {
        (yyval)->nodeKind = empty_var_part_NodeKind;
    }

    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    releaseNode((yyvsp[-1]));
}
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 506 "yacc.pascal" /* yacc.c:1646  */
    {
	(yyval) = makeNewNode();
    (yyval)->nodeKind = empty_var_part_NodeKind;
    (yyval)->line_no = currentline;
}
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 513 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) != NULL) {
        TreeNode * temp = (yyvsp[-1]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 526 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 529 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----var declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 533 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----var declaration error detected\n");
    (yyval) = NULL;
}
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 539 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = var_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 551 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = routine_part_NodeKind;
    (yyval)->line_no = currentline;
    if ((yyvsp[0]) != NULL) {
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
        (yyval)->child = (yyvsp[0]);
    }
}
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 562 "yacc.pascal" /* yacc.c:1646  */
    {
    TreeNode * temp = (yyvsp[-1]);
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 575 "yacc.pascal" /* yacc.c:1646  */
    {
    TreeNode * temp = (yyvsp[-1]);
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 588 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 591 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----routine declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 2399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 595 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----routine declaration error detected\n");
    (yyval) = NULL;
}
#line 2408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 601 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = function_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 613 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = function_head_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-1]));
}
#line 2439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 626 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = procedure_decl_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 638 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = procedure_head_NodeKind;
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-1])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-2]));
}
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 649 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = parameters_NodeKind;
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 658 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = empty_parameters_NodeKind;
    (yyval)->line_no = currentline;
}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 665 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-2]) != NULL) {
        TreeNode * temp = (yyvsp[-2]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-2]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }

    releaseNode((yyvsp[-1]));
}
#line 2512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 680 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 683 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----parameter list declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 2529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 687 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----parameter list declaration error detected\n");
    (yyval) = NULL;
}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 693 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = var_para_decl_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-3]));
    releaseNode((yyvsp[-1]));
}
#line 2553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 703 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = non_var_para_decl_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 2567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 714 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = routine_body_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 720 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----routine body declaration error detected\n");
    (yyval) = NULL;
}
#line 2587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 726 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = stmt_list_NodeKind;
    (yyval)->line_no = currentline;
    if ((yyvsp[0]) != NULL) {
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
        (yyval)->child = eliminateUselessFromList((yyvsp[0]));
    }
}
#line 2601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 737 "yacc.pascal" /* yacc.c:1646  */
    {
    TreeNode * temp = (yyvsp[-2]);
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[-1]);
        (yyval) = (yyvsp[-2]);
    }
    else {
        (yyval) = (yyvsp[-1]);
    }

    releaseNode((yyvsp[0]));
}
#line 2621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 752 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 755 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----statement error detected\n");
    (yyval) = (yyvsp[-2]);
}
#line 2638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 759 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----statement error detected\n");
    (yyval) = NULL;
}
#line 2647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 763 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----statement error detected\n");
    (yyval) = NULL;
}
#line 2656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 769 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = labeled_stmt_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 2670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 778 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = non_labeled_stmt_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 2681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 786 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 789 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 792 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 795 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 798 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 801 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 804 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 807 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 810 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 815 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_assign_stmt_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 2768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 825 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_lb_exp_rb_assign_stmt_NodeKind;
    (yyval)->child = (yyvsp[-5]);
    currentline = (yyval)->line_no = (yyvsp[-5])->line_no;
    (yyvsp[-3]) = closeExpression((yyvsp[-3]));
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    (yyvsp[-5])->sibling = (yyvsp[-3]);
    (yyvsp[-3])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[-1]));
}
#line 2787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 839 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_dot_id_assign_stmt_NodeKind;
    (yyval)->child = (yyvsp[-4]);
    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    (yyvsp[-4])->sibling = (yyvsp[-2]);
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-3]));
    releaseNode((yyvsp[-1]));
}
#line 2804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 853 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_proc_stmt_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 2815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 859 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_lp_args_rp_proc_stmt_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 869 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = sys_proc_proc_stmt_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 2841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 875 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = sys_proc_lp_args_rp_proc_stmt_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 885 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = read_lp_factor_rp_proc_stmt_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 897 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = compound_stmt_NodeKind;
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 2885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 908 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyvsp[-3]) = closeExpression((yyvsp[-3]));

    int boolRes = checkBool((yyvsp[-3]));
    if (boolRes == 0) {        // always false, take else
        if ((yyvsp[0])->nodeKind == empty_else_clause_NodeKind) {
    		(yyval) = makeNewNode();
            (yyval)->nodeKind = useless_stmt_NodeKind;
    		(yyval)->line_no = currentline;
        } else {
            (yyval) = getStmtNode((yyvsp[0])->child);
            setStmtNodeToNULL((yyvsp[0])->child);
        }
        releaseNode((yyvsp[-3]));
        releaseNode((yyvsp[-1]));
        releaseNode((yyvsp[0]));
    }
    else if (boolRes == 1) {    // always true, take if
        (yyval) = getStmtNode((yyvsp[-1]));
        setStmtNodeToNULL((yyvsp[-1]));
        releaseNode((yyvsp[-1]));
        releaseNode((yyvsp[-3]));
        releaseNode((yyvsp[0]));
    }
    else {
    	(yyval) = makeNewNode();
    	(yyval)->nodeKind = if_stmt_NodeKind;
	    (yyval)->child = (yyvsp[-3]);
	    (yyvsp[-3])->sibling = (yyvsp[-1]);
	    (yyvsp[-1])->sibling = (yyvsp[0]);
    }

    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-2]));
}
#line 2926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 946 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = else_clause_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    releaseNode((yyvsp[-1]));
}
#line 2939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 954 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = empty_else_clause_NodeKind;
    (yyval)->line_no = currentline;
}
#line 2949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 961 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = repeat_stmt_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-3]));
    releaseNode((yyvsp[-1]));
}
#line 2965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 974 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyvsp[-2]) = closeExpression((yyvsp[-2]));

    int boolRes = checkBool((yyvsp[-2]));
    if (boolRes == 0) {		// always false
	    (yyval) = makeNewNode();
	    (yyval)->nodeKind = useless_stmt_NodeKind;
	    releaseNode((yyvsp[-2]));
	    releaseNode((yyvsp[0]));
    }
    else {
	    (yyval) = makeNewNode();
	    (yyval)->nodeKind = while_stmt_NodeKind;
	    (yyval)->child = (yyvsp[-2]);
	    (yyvsp[-2])->sibling = (yyvsp[0]);
    }

	currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    releaseNode((yyvsp[-3]));
    releaseNode((yyvsp[-1]));
}
#line 2991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 997 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = for_stmt_NodeKind;
    (yyval)->child = (yyvsp[-6]);
    currentline = (yyval)->line_no = (yyvsp[-7])->line_no;
    (yyvsp[-4]) = closeExpression((yyvsp[-4]));
    (yyvsp[-2]) = closeExpression((yyvsp[-2]));
    (yyvsp[-6])->sibling = (yyvsp[-4]);
    (yyvsp[-4])->sibling = (yyvsp[-3]);
    (yyvsp[-3])->sibling = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-7]));
    releaseNode((yyvsp[-5]));
    releaseNode((yyvsp[-1]));
}
#line 3012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1015 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = to_direction_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1020 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = down_direction_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1027 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = case_stmt_NodeKind;
    (yyvsp[-3]) = closeExpression((yyvsp[-3]));
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-4])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-4]));
    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1041 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = case_expr_list_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 3060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1049 "yacc.pascal" /* yacc.c:1646  */
    {
    if ((yyvsp[-1]) != NULL) {
        TreeNode * temp = (yyvsp[-1]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-1]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }
}
#line 3078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1062 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 3086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1065 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----case declaration error detected\n");
    (yyval) = (yyvsp[-1]);
}
#line 3095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1069 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----case declaration error detected\n");
    (yyval) = NULL;
}
#line 3104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1075 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = const_case_expr_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1085 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_case_expr_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1097 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = goto_stmt_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    releaseNode((yyvsp[-1]));
}
#line 3147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1107 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = expression_NodeKind;
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    if ((yyvsp[-2])->computable == 1 && (yyvsp[0])->computable == 1) {

        (yyval)->computable = 1;
        (yyval)->type = 0;

        switch ((yyvsp[-1])->nodeKind) {
            case ge_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result >= (yyvsp[0])->result) ? 1 : 0;
            }
                break;
            case gt_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result > (yyvsp[0])->result) ? 1 : 0;
            }
                break;
            case le_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result <= (yyvsp[0])->result) ? 1 : 0;
            }
                break;
            case lt_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result < (yyvsp[0])->result) ? 1 : 0;
            }
                break;
            case equal_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result == (yyvsp[0])->result) ? 1 : 0;
            }
                break;
            case unequal_expression_op_NodeKind: {
                (yyval)->result = ((yyvsp[-2])->result != (yyvsp[0])->result) ? 1 : 0;
            }
                break;
        }
    } else {
        if ((yyvsp[-2])->computable == 1) {
            TreeNode * temp = makeNewExpressionNode((yyvsp[-2])->type, (yyvsp[-2])->result, currentline);
            releaseNode((yyvsp[-2]));
            (yyvsp[-2]) = temp;
        } else if ((yyvsp[0])->computable == 1) {
            TreeNode * temp = makeNewExprNode((yyvsp[0])->type, (yyvsp[0])->result, currentline);
            releaseNode((yyvsp[0]));
            (yyvsp[0]) = temp;
        }
    }

    (yyval)->child = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[-1]);
    (yyvsp[-1])->sibling = (yyvsp[0]);
}
#line 3204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1159 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = end_expression_NodeKind;
    (yyval)->child = (yyvsp[0]);
    (yyval)->line_no = currentline = (yyvsp[0])->line_no;

    if ((yyvsp[0])->computable == 1) {
        (yyval)->computable = 1;
        (yyval)->result = (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }
}
#line 3221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1173 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = ge_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1178 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = gt_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3241 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1183 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = le_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1188 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = lt_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1193 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = equal_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1198 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = unequal_expression_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3281 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1205 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = expr_NodeKind;
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    if  (
        ((yyvsp[-2])->computable == 1 && (yyvsp[0])->computable == 1 && (yyvsp[-2])->type == (yyvsp[0])->type)
        &&
        (((yyvsp[-1])->nodeKind == or_expr_op_NodeKind && (yyvsp[-2])->type == 0) ||
         ((yyvsp[-1])->nodeKind != or_expr_op_NodeKind && (yyvsp[-2])->type == 1))
        ) {

        (yyval)->computable = 1;
        (yyval)->type = (yyvsp[-2])->type;

        switch ((yyvsp[-1])->nodeKind) {
            case plus_expr_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result + (yyvsp[0])->result;
            }
                break;
            case minus_expr_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result - (yyvsp[0])->result;
            }
                break;
            case or_expr_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result | (yyvsp[0])->result;
            }
                break;
        }
    }
    else {
        if ((yyvsp[-2])->computable == 1) {
            TreeNode * temp = makeNewExprNode((yyvsp[-2])->type, (yyvsp[-2])->result, currentline);
            releaseNode((yyvsp[-2]));
            (yyvsp[-2]) = temp;
        } else if ((yyvsp[0])->computable == 1) {
            TreeNode * temp = makeNewTermNode((yyvsp[0])->type, (yyvsp[0])->result, currentline);
            releaseNode((yyvsp[0]));
            (yyvsp[0]) = temp;
        }
    }

    (yyval)->child = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[-1]);
    (yyvsp[-1])->sibling = (yyvsp[0]);
}
#line 3332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1251 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = end_expr_NodeKind;
    (yyval)->line_no = currentline = (yyvsp[0])->line_no;
    (yyval)->child = (yyvsp[0]);

    if ((yyvsp[0])->computable == 1) {
        (yyval)->computable = 1;
        (yyval)->result = (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }
}
#line 3349 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1265 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = plus_expr_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1270 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = minus_expr_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1275 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = or_expr_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1282 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = term_NodeKind;
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    if  (
        ((yyvsp[-2])->computable == 1 && (yyvsp[0])->computable == 1 && (yyvsp[-2])->type == (yyvsp[0])->type)
        &&
        (((yyvsp[-1])->nodeKind == and_term_op_NodeKind && (yyvsp[-2])->type == 0) ||
         ((yyvsp[-1])->nodeKind != and_term_op_NodeKind && (yyvsp[-2])->type == 1))
        ) {

        (yyval)->computable = 1;
        (yyval)->type = (yyvsp[-2])->type;

        switch ((yyvsp[-1])->nodeKind) {
            case mul_term_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result * (yyvsp[0])->result;
            }
                break;
            case div_term_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result / (yyvsp[0])->result;
            }
                break;
            case mod_term_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result % (yyvsp[0])->result;
            }
                break;
            case and_term_op_NodeKind: {
                (yyval)->result = (yyvsp[-2])->result & (yyvsp[0])->result;
            }
                break;
        }
    }
    else {
        if ((yyvsp[-2])->computable == 1) {
            TreeNode * temp = makeNewTermNode((yyvsp[-2])->type, (yyvsp[-2])->result, currentline);
            releaseNode((yyvsp[-2]));
            (yyvsp[-2]) = temp;
        } else if ((yyvsp[0])->computable == 1) {
            TreeNode * temp = makeNewFactorNode((yyvsp[0])->type, (yyvsp[0])->result, currentline);
            releaseNode((yyvsp[0]));
            (yyvsp[0]) = temp;
        }
    }

    (yyval)->child = (yyvsp[-2]);
    (yyvsp[-2])->sibling = (yyvsp[-1]);
    (yyvsp[-1])->sibling = (yyvsp[0]);
}
#line 3434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1332 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = end_term_NodeKind;
    (yyval)->line_no = currentline = (yyvsp[0])->line_no;
    (yyval)->child = (yyvsp[0]);

    if ((yyvsp[0])->computable == 1) {
        (yyval)->computable = 1;
        (yyval)->result = (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }
}
#line 3451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1346 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = mul_term_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1351 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = div_term_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1356 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = mod_term_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1361 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
    (yyval)->nodeKind = and_term_op_NodeKind;
    currentline = (yyval)->line_no;
}
#line 3491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1368 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_factor_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 3502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1374 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_lp_args_rp_factor_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1384 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = sys_func_factor_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;
}
#line 3528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1390 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = sys_func_lp_args_rp_factor_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1400 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = const_factor_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[0])->line_no;

    if ((yyvsp[0])->computable == 1) {
        (yyval)->computable = 1;
        (yyval)->result = (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }

    if ((yyvsp[0])->nodeKind == string_const_value_NodeKind) {
            stringConstNode * temp = insertIntoStringConstTable((yyvsp[0]));        
            TreeNode * t = makeNewNode();       
            t->literal = (char *)malloc(strlen(temp->name) * sizeof(char) + 1);         
            strcpy(t->literal, temp->name);
            
            t->line_no = (yyvsp[0])->line_no;       
            releaseNode((yyvsp[0]));
            (yyval)->nodeKind = id_factor_NodeKind;      
            (yyval)->child = t;
  
    }
}
#line 3573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1425 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = lp_exp_rp_factor_NodeKind;
    //$2 = closeExpression($2);
    (yyval)->child = (yyvsp[-1]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;

    if ((yyvsp[-1])->computable == 1) {
        (yyval)->computable = 1;
        (yyval)->type = (yyvsp[-1])->type;
        (yyval)->result = (yyvsp[-1])->result;
    }

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1441 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = not_factor_factor_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    if ((yyvsp[0])->computable == 1 && (yyvsp[0])->type == 0) {
        (yyval)->computable = 1;
        (yyval)->result = 1 - (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }

    releaseNode((yyvsp[-1]));
}
#line 3613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1455 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = minus_factor_factor_NodeKind;
    (yyval)->child = (yyvsp[0]);
    currentline = (yyval)->line_no = (yyvsp[-1])->line_no;

    if ((yyvsp[0])->computable == 1 && (yyvsp[0])->type == 1) {
        (yyval)->computable = 1;
        (yyval)->result = 0 - (yyvsp[0])->result;
        (yyval)->type = (yyvsp[0])->type;
    }

    releaseNode((yyvsp[-1]));
}
#line 3632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1469 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_lb_exp_rb_factor_NodeKind;
    (yyval)->child = (yyvsp[-3]);
    currentline = (yyval)->line_no = (yyvsp[-3])->line_no;
    (yyvsp[-1]) = closeExpression((yyvsp[-1]));
    (yyvsp[-3])->sibling = (yyvsp[-1]);

    releaseNode((yyvsp[-2]));
    releaseNode((yyvsp[0]));
}
#line 3648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1480 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = id_dot_id_factor_NodeKind;
    (yyval)->child = (yyvsp[-2]);
    currentline = (yyval)->line_no = (yyvsp[-2])->line_no;
    (yyvsp[-2])->sibling = (yyvsp[0]);

    releaseNode((yyvsp[-1]));
}
#line 3662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1491 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = makeNewNode();
    (yyval)->nodeKind = args_list_NodeKind;
    (yyval)->line_no = currentline;
    if ((yyvsp[0]) != NULL) {
        (yyval)->child = (yyvsp[0]);
        currentline = (yyval)->line_no = (yyvsp[0])->line_no;
    }
}
#line 3676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1502 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    if ((yyvsp[-2]) != NULL) {
        TreeNode * temp = (yyvsp[-2]);
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = (yyvsp[0]);
        (yyval) = (yyvsp[-2]);
    }
    else {
        (yyval) = (yyvsp[0]);
    }

    releaseNode((yyvsp[-1]));
}
#line 3697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1518 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyvsp[0]) = closeExpression((yyvsp[0]));
    (yyval) = (yyvsp[0]);
}
#line 3706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1522 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----argument list declaration error detected\n");
    (yyval) = (yyvsp[-2]);
}
#line 3715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1526 "yacc.pascal" /* yacc.c:1646  */
    {
    printf("----argument list declaration error detected\n");
    (yyval) = NULL;
}
#line 3724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1532 "yacc.pascal" /* yacc.c:1646  */
    {
    (yyval) = NULL;
}
#line 3732 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3736 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1537 "yacc.pascal" /* yacc.c:1906  */


int main(int argc, char** argv) {
    openFile(argc, argv);

    errorOccur = 0;
    yyparse();

    int uncle[200] = {0};
    printThisTree(savedTree, uncle, 0);

    if (errorOccur != 0) {
        printf("%d syntax error found, parsing failed.\n", errorOccur);
        exit(0);
    }

    MainVarTable = (VarTable*)malloc(sizeof(VarTable));
    MainConstTable = (ConstTable*)malloc(sizeof(VarTable));
    MainTypeTable = (TypeTable*)malloc(sizeof(TypeTable));
    MainProcedureTable = (ProcedureTable*)malloc(sizeof(ProcedureTable));
    int i = 0;
    for(i = 0; i < 50; i++)
    {
        MainVarTable->bucket[i] = NULL;
        MainConstTable->bucket[i] = NULL;
        MainTypeTable->bucket[i] = NULL;
        MainProcedureTable->bucket[i] = NULL;
    }

    errorOccur = 0;

    searchTree(savedTree, MainConstTable,MainTypeTable,MainVarTable, MainProcedureTable);

    if (errorOccur != 0) {
        printf("%d syntax error found, parsing failed.\n", errorOccur);
        exit(0);
    }

    printConstTable(MainConstTable);
    printTypeTable(MainTypeTable);
    printVarTable(MainVarTable);
    printProcedureTable(MainProcedureTable);

    typeCheck(savedTree,"main");
    int uncle1[200]={0};
    printThisTree(savedTree, uncle1, 0);
    FILE *fp =fopen("test.code","w");
    ConvertConstToCode(MainConstTable, fp);
    make_code("test.code", fp);
   // releaseNode(savedTree);

    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "%s around line %d\n", s, currentline);
    errorOccur++;
    return (0);
}

void printAncestor(int *uncle, int level) {
    int i = 0;
    for (; i < level - 1; ++i) {
        if (uncle[i] == 1) {
            printf("|");
        }
        else {
            printf(" ");
        }
        int j = 0;
        for (; j < WIDTH - 1; ++j)    {
            printf(" ");
        }
    }
}

void printThisTree(TreeNode * t, int *uncle, int level) {
    if (t == NULL)
        return;

    printAncestor(uncle, level);
    if (level != 0) {
        printf("|");
        int i = 0;
        for (; i < WIDTH - 1; ++i) {
            printf("-");
        }
    }

    if (t->literal) {
        printf("%s-(%s-%d-%d-%d-%d)-%s-%d\n", t->literal, t->label,t->address,t->size,t->level,t->leveltofather, NodeKindStr[t->nodeKind], t->Type);
    }
    else {
        if (t->nodeKind >= 0 && t->nodeKind < 97) {
            printf("%s%d\n", NodeKindStr[t->nodeKind], t->line_no);
        }
        else {
            printf("%c%d\n", 0x01, t->nodeKind);
        }
    }

    TreeNode * k = t->child;
    while (k != NULL) {

        if (k->sibling) {
            uncle[level] = 1;
        }
        else {
            uncle[level] = 0;
        }

        int i = 0;
        for (; i < HEIGHT; i++) {
            printAncestor(uncle, level + 1);
            printf("|\n");
        }

        printThisTree(k, uncle, level + 1);

        k = k->sibling;
    }
}

TreeNode * makeNewConstNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->line_no = line_no;

    if (type == 0) {    // boolean
        char trueStr[] = "true";
        char falseStr[] = "false";
        temp->nodeKind = sys_con_const_value_NodeKind;
        if (value > 0) {
            temp->literal = (char *)malloc(strlen(trueStr) * sizeof(char) + 1);
            strcpy(temp->literal, trueStr);
        }
        else {
            temp->literal = (char *)malloc(strlen(falseStr) * sizeof(char) + 1);
            strcpy(temp->literal, falseStr);
        }
    } else {            // int
        temp->nodeKind = integer_const_value_NodeKind;
        char buffer[50];
        itoa(value, buffer, 10);
        temp->literal = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
        strcpy(temp->literal, buffer);
    }

    return temp;
}

TreeNode * makeNewFactorNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->line_no = line_no;

    if (type != 0 && value < 0) {
        temp->nodeKind = minus_factor_factor_NodeKind;
        temp->child = makeNewFactorNode(type, (-1 * value), line_no);
        return temp;
    }

    temp->nodeKind = const_factor_NodeKind;
    temp->child = makeNewConstNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewTermNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_term_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewFactorNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewExprNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_expr_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewTermNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewExpressionNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_expression_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewExprNode(type, value, line_no);
    return temp;
}

TreeNode * closeExpression(TreeNode * k) {

    if (k->computable == 1) {
        TreeNode * temp = makeNewExpressionNode(k->type, k->result, currentline);
        releaseNode(k);
        k = temp;
    }

    return k;
}

void itoa(int value, char *buf, int radix) {
    sprintf(buf, "%d", value);
}

int checkBool(TreeNode * t) {
    if (t->nodeKind != end_expression_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != end_expr_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != end_term_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != const_factor_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind == integer_const_value_NodeKind) {
        return (atoi(t->literal) != 0) ? 1 : 0;
    }
    else if (t->nodeKind == sys_con_const_value_NodeKind) {
        return (t->literal[0] == 't') ? 1 : 0;
    }

    return -1;
}

TreeNode * eliminateUselessFromList(TreeNode * t) {
	TreeNode * head = makeNewNode();
	TreeNode * temp = head;
	while (t != NULL) {
		if (isUseless(t)) {
			TreeNode * tmp = t;
			t = t->sibling;
			tmp->sibling = NULL;
			releaseNode(tmp);
		} else {
			temp->sibling = t;
			temp = t;
			t = t->sibling;
		}
	}
	return head->sibling;
}

int isUseless(TreeNode * t) {
	return (getStmtNode(t)->nodeKind == useless_stmt_NodeKind) ? 1 : 0;
}

TreeNode * getStmtNode(TreeNode * t) {
	if (t->nodeKind == labeled_stmt_NodeKind) {
		return t->child->sibling;
	}
	return t->child;
}

void setStmtNodeToNULL(TreeNode * t) {
	if (t->nodeKind == labeled_stmt_NodeKind) {
		t->child->sibling = NULL;
	} else {
		t->child = NULL;
	}
}

stringConstNode * makeNewStringConstNode() {
	stringConstNode * temp = (stringConstNode *)malloc(sizeof(stringConstNode));
	temp->next = NULL;
	temp->name = NULL;
	temp->value = NULL;

	return temp;
}

void releaseStringConstNode(stringConstNode * t) {
	if (t == NULL) {
		return;
	}

	if (t->name != NULL) {
		free(t->name);
	}

	if (t->value != NULL) {
		free(t->value);
	}

	releaseStringConstNode(t->next);
}

void printStringConstTable() {
	stringConstNode * temp = stringConstTable;
	while (temp != NULL) {
		printf("%s %s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

stringConstNode * insertIntoStringConstTable(TreeNode * t) {
	stringConstCount++;

	stringConstNode * temp = NULL;
	if (stringConstTable == NULL) {
		stringConstTable = makeNewStringConstNode();
		temp = stringConstTable;
	} else {
		temp = stringConstTable;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = makeNewStringConstNode();
		temp = temp->next;
	}
	char buffer[50];
	sprintf(buffer, "stringconst%d", stringConstCount);
	temp->name = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
	strcpy(temp->name, buffer);

	temp->value = (char *)malloc(strlen(t->literal) * sizeof(char) + 1);
	strcpy(temp->value, t->literal);

	return temp;
}

void updateConstPart() {
	//printStringConstTable();
	if (stringConstTable == NULL) {
		return;
	}

	TreeNode *routine = getChild(2, savedTree);
	TreeNode *routine_head = getChild(1, routine);
	TreeNode *const_part = getChild(2, routine_head); //const_part

	if (const_part->nodeKind == empty_const_part_NodeKind) {
		TreeNode * temp = makeNewNode();
		temp->nodeKind = const_part_NodeKind;
		routine_head->child->sibling = temp;
        temp->sibling = const_part->sibling;
        const_part->sibling = NULL;
		releaseNode(const_part);
		const_part = temp;
	}

	stringConstNode * sconst = stringConstTable;
	do {
		//printf("1\n");
		insertIntoConstPart(sconst, const_part);
		sconst = sconst->next;
	} while (sconst != NULL);

    releaseStringConstNode(stringConstTable);
}

void insertIntoConstPart(stringConstNode * sconst, TreeNode * const_part) {
	TreeNode * const_expr = makeNewNode();
	const_expr->nodeKind = const_expr_NodeKind;

	TreeNode * id = makeNewNode();
	id->nodeKind = 0;
	id->literal = (char *)malloc(strlen(sconst->name) * sizeof(char) + 1);
	strcpy(id->literal, sconst->name);

	TreeNode * const_value = makeNewNode();
	const_value->nodeKind = string_const_value_NodeKind;
	const_value->literal = (char *)malloc(strlen(sconst->value) * sizeof(char) + 1);
	strcpy(const_value->literal, sconst->value);

	const_expr->child = id;
	id->sibling = const_value;

	TreeNode * temp = const_part->child;
	const_part->child = const_expr;
	const_expr->sibling = temp;
}
