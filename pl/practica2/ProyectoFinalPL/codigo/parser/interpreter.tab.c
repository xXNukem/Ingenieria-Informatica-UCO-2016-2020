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
#line 7 "interpreter.y" /* yacc.c:339  */

#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"

#include "../table/stringVariable.hpp"

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST


#line 181 "interpreter.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "interpreter.tab.h".  */
#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    PRINT = 259,
    READ = 260,
    PRINT_STRING = 261,
    READ_STRING = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    END_IF = 266,
    WHILE = 267,
    DO = 268,
    END_WHILE = 269,
    REPEAT = 270,
    UNTIL = 271,
    FOR = 272,
    FROM = 273,
    STEP = 274,
    END_FOR = 275,
    ERASE = 276,
    PLACE = 277,
    ASSIGNMENT = 278,
    COMMA = 279,
    NUMBER = 280,
    BOOL = 281,
    STRING = 282,
    VARIABLE = 283,
    UNDEFINED = 284,
    CONSTANT = 285,
    BUILTIN = 286,
    OR = 287,
    AND = 288,
    GREATER_OR_EQUAL = 289,
    LESS_OR_EQUAL = 290,
    GREATER_THAN = 291,
    LESS_THAN = 292,
    EQUAL = 293,
    NOT_EQUAL = 294,
    NOT = 295,
    PLUS = 296,
    MINUS = 297,
    MULTIPLICATION = 298,
    DIVISION = 299,
    DIVISION_INT = 300,
    MODULO = 301,
    CONCATENATION = 302,
    LPAREN = 303,
    RPAREN = 304,
    UNARY = 305,
    UNARY_PLUS = 306,
    UNARY_MINUS = 307,
    POWER = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 133 "interpreter.y" /* yacc.c:355  */

  char * identifier; 				 /* NEW in example 7 */
  double number;  
  bool logic;						 /* NEW in example 15 */
  std::string * strings;
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 287 "interpreter.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 302 "interpreter.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   998

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   214,   214,   228,   233,   245,   256,   261,   266,   271,
     277,   282,   286,   289,   293,   296,   301,   305,   309,   313,
     317,   322,   327,   332,   340,   347,   355,   362,   369,   375,
     381,   387,   386,   396,   402,   409,   414,   421,   426,   432,
     440,   447,   451,   456,   461,   469,   476,   480,   486,   492,
     498,   504,   508,   514,   518,   522,   526,   529,   534,   540,
     547,   552,   557,   563,   570,   617,   623,   629,   635,   641,
     647,   653,   659,   665,   675,   680,   691,   696
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "PRINT", "READ",
  "PRINT_STRING", "READ_STRING", "IF", "THEN", "ELSE", "END_IF", "WHILE",
  "DO", "END_WHILE", "REPEAT", "UNTIL", "FOR", "FROM", "STEP", "END_FOR",
  "ERASE", "PLACE", "ASSIGNMENT", "COMMA", "NUMBER", "BOOL", "STRING",
  "VARIABLE", "UNDEFINED", "CONSTANT", "BUILTIN", "OR", "AND",
  "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "GREATER_THAN", "LESS_THAN",
  "EQUAL", "NOT_EQUAL", "NOT", "PLUS", "MINUS", "MULTIPLICATION",
  "DIVISION", "DIVISION_INT", "MODULO", "CONCATENATION", "LPAREN",
  "RPAREN", "UNARY", "UNARY_PLUS", "UNARY_MINUS", "POWER", "$accept",
  "program", "stmtlist", "stmt", "for", "if", "while", "repeat", "cond",
  "erase", "place", "$@1", "asgn", "print", "read", "exp", "listOfExp",
  "restOfListOfExp", YY_NULLPTR
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
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -52

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-3)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -52,     5,     3,   -52,   -52,   -52,   778,   -16,   778,   -31,
     -18,   -18,   -52,    -5,   -52,    -8,    11,    13,   -52,   -52,
     -52,   -52,   -52,   -52,   -52,    43,    46,    47,   -52,   -52,
     -30,   -52,     4,   778,   778,   778,   778,    25,    26,   884,
       6,   -14,   884,    28,   778,    48,    61,   472,   778,   348,
     759,   797,   797,   -52,   -52,   -52,   -52,   -52,   778,   339,
      29,    29,   818,   -52,   -52,   778,   778,   778,   778,   778,
     778,   778,   778,   778,   778,   778,   778,   778,   778,   778,
     778,   -52,    30,    32,   -52,    41,   840,   -52,   -52,   -18,
     270,   778,   294,    44,   369,    -4,    13,   -52,   884,   -52,
     884,   393,    45,   -52,   905,   925,   945,   945,   945,   945,
     945,   945,    42,    42,    29,    29,    29,    29,    29,    29,
     -52,   -52,   -52,   -52,   444,   500,   -52,   778,   318,   778,
     -52,   778,   778,   -52,   -52,   -52,   -52,   -52,    64,   778,
     130,    56,   862,   393,   528,   -52,   778,   165,   -52,   778,
      65,   -52,   -52,   -52,   556,   192,   -52,   778,   584,   612,
     219,    67,   -52,   -52,   640,   246,   -52,   -52,   -52,    55,
     668,   -52,   -52,   696,   724,   -52,   -52,   752,   -52,   -52,
     -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     5,     6,     0,     0,     0,     0,
       0,     0,     3,     0,    29,     0,     0,     0,     4,    13,
      10,    11,    12,    14,    15,     0,     0,     0,    45,    46,
      62,    63,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,    55,    56,    74,    73,
      57,    58,     0,    53,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,     0,    44,     0,     0,     3,     3,     0,
       0,     0,     0,     0,     0,    62,    63,    34,    33,    36,
      35,    76,     0,    52,    72,    71,    66,    68,    65,    67,
      69,    70,    47,    48,    49,    50,    51,    59,    61,    60,
      39,    41,    40,    28,     0,     0,    27,     0,     0,     0,
      31,     0,     0,    75,    64,     3,    24,    26,     0,     0,
       0,     0,     0,    76,     0,     3,     0,     3,     3,     0,
       0,    30,    77,    25,     0,     0,     3,     0,     0,     0,
       0,     0,    19,     3,     0,     3,    23,    21,     3,     0,
       0,    17,     3,     0,     0,    32,    18,     0,    22,    20,
      16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,   -12,   -52,   -52,   -52,   -52,   -52,    -9,   -52,
     -52,   -52,   -13,   -52,   -52,    -7,   -52,   -51
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    18,    19,    20,    21,    22,    45,    23,
      24,   141,    25,    26,    27,    39,   102,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    42,    46,    -2,     4,     3,     5,     6,     7,     8,
       9,    10,    40,    48,    82,    11,    83,    43,    12,    51,
      13,    56,    57,    49,    14,    15,    59,    60,    61,    62,
      44,    16,    41,    17,    51,    84,    52,    86,    97,    99,
      50,    90,    92,    94,    98,   100,    53,    56,    57,    54,
      55,   101,    58,    63,    64,    81,    85,    87,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    88,   124,   125,   145,   150,   120,
     126,   121,    80,   146,   128,    75,    76,    77,    78,    79,
     122,   169,   152,   130,   134,    80,    65,    66,    67,    68,
      69,    70,    71,    72,   175,    73,    74,    75,    76,    77,
      78,    79,     0,   161,     0,     0,     0,    80,     0,     0,
     138,     0,   140,   144,   142,   143,     0,     0,     0,     0,
       0,     0,   147,   154,     0,   158,   159,     0,     0,   155,
       0,     0,   160,   148,   164,     0,     0,     0,     0,   149,
     165,   170,     0,   173,     0,     0,   174,     0,     0,     0,
     177,     0,    65,    66,    67,    68,    69,    70,    71,    72,
       0,    73,    74,    75,    76,    77,    78,    79,   156,     0,
       0,     0,     0,    80,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,    70,    71,    72,   163,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      71,    72,   168,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,    80,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,   172,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,    65,    66,
      67,    68,    69,    70,    71,    72,   127,    73,    74,    75,
      76,    77,    78,    79,     0,     0,     0,     0,     0,    80,
       0,     0,    65,    66,    67,    68,    69,    70,    71,    72,
     129,    73,    74,    75,    76,    77,    78,    79,     0,     0,
       0,     0,     0,    80,     0,     0,    65,    66,    67,    68,
      69,    70,    71,    72,   139,    73,    74,    75,    76,    77,
      78,    79,     0,     0,     0,     0,     0,    80,     0,     0,
      65,    66,    67,    68,    69,    70,    71,    72,     0,    73,
      74,    75,    76,    77,    78,    79,    91,     0,     0,     0,
       0,    80,     0,    28,     0,    29,    30,     0,    31,    32,
      73,    74,    75,    76,    77,    78,    79,     0,    33,    34,
      35,     0,    80,   131,     0,     0,    36,     0,     0,    37,
      38,    65,    66,    67,    68,    69,    70,    71,    72,     0,
      73,    74,    75,    76,    77,    78,    79,   132,     0,     0,
       0,     0,    80,     0,     0,    65,    66,    67,    68,    69,
      70,    71,    72,     0,    73,    74,    75,    76,    77,    78,
      79,     0,     0,     0,     0,     4,    80,     5,     6,     7,
       8,     9,    10,     0,   135,   136,    11,     0,     0,    12,
       0,    13,     0,     0,     0,    14,    15,     0,     0,     0,
       0,     0,    16,     4,    17,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,     0,     0,    12,    89,    13,
       0,     0,     0,    14,    15,     0,     0,     0,     0,     0,
      16,     4,    17,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,     0,   137,    12,     0,    13,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,    16,     4,
      17,     5,     6,     7,     8,     9,    10,     0,     0,   153,
      11,     0,     0,    12,     0,    13,     0,     0,     0,    14,
      15,     0,     0,     0,     0,     0,    16,     4,    17,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,     0,
       0,    12,     0,    13,     0,     0,   162,    14,    15,     0,
       0,     0,     0,     0,    16,     4,    17,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,     0,     0,    12,
       0,    13,     0,     0,   166,    14,    15,     0,     0,     0,
       0,     0,    16,     4,    17,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,     0,     0,    12,     0,    13,
       0,     0,   167,    14,    15,     0,     0,     0,     0,     0,
      16,     4,    17,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,     0,     0,    12,     0,    13,     0,     0,
     171,    14,    15,     0,     0,     0,     0,     0,    16,     4,
      17,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,     0,     0,    12,     0,    13,     0,     0,   176,    14,
      15,     0,     0,     0,     0,     0,    16,     4,    17,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,     0,
       0,    12,     0,    13,     0,     0,   178,    14,    15,     0,
       0,     0,     0,     0,    16,     4,    17,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,     0,     0,    12,
       0,    13,     0,     0,   179,    14,    15,     0,     0,     0,
       0,     0,    16,     4,    17,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,     0,     0,    12,     0,    13,
       0,     0,   180,    14,    15,     0,     0,     0,     0,     0,
      16,     0,    17,    93,    28,     0,    29,    30,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,     0,    28,     0,    29,    30,    36,    31,    32,
      37,    38,     0,     0,     0,     0,     0,     0,    33,    34,
      35,     0,    28,     0,    29,    95,    36,    96,    32,    37,
      38,     0,     0,     0,     0,     0,     0,    33,    34,    35,
       0,     0,     0,     0,     0,    36,     0,     0,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    72,     0,    73,
      74,    75,    76,    77,    78,    79,     0,   103,     0,     0,
       0,    80,    65,    66,    67,    68,    69,    70,    71,    72,
       0,    73,    74,    75,    76,    77,    78,    79,     0,   123,
       0,     0,     0,    80,    65,    66,    67,    68,    69,    70,
      71,    72,     0,    73,    74,    75,    76,    77,    78,    79,
       0,   151,     0,     0,     0,    80,    65,    66,    67,    68,
      69,    70,    71,    72,     0,    73,    74,    75,    76,    77,
      78,    79,     0,     0,     0,     0,     0,    80,    66,    67,
      68,    69,    70,    71,    72,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,     0,     0,    80,    67,
      68,    69,    70,    71,    72,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,     0,     0,    80,    -3,
      -3,    -3,    -3,    -3,    -3,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,     0,     0,    80
};

static const yytype_int16 yycheck[] =
{
      12,     8,    11,     0,     1,     0,     3,     4,     5,     6,
       7,     8,    28,    18,    28,    12,    30,    48,    15,    23,
      17,    51,    52,    28,    21,    22,    33,    34,    35,    36,
      48,    28,    48,    30,    23,    49,    23,    44,    51,    52,
      48,    48,    49,    50,    51,    52,     3,    51,    52,     3,
       3,    58,    48,    28,    28,    49,    28,     9,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    13,    87,    88,    13,    22,    49,
      89,    49,    53,    19,    91,    43,    44,    45,    46,    47,
      49,    24,   143,    49,    49,    53,    32,    33,    34,    35,
      36,    37,    38,    39,    49,    41,    42,    43,    44,    45,
      46,    47,    -1,    48,    -1,    -1,    -1,    53,    -1,    -1,
     127,    -1,   129,   135,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   145,    -1,   147,   148,    -1,    -1,   146,
      -1,    -1,   149,    13,   156,    -1,    -1,    -1,    -1,    19,
     157,   163,    -1,   165,    -1,    -1,   168,    -1,    -1,    -1,
     172,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    13,    -1,
      -1,    -1,    -1,    53,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    13,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    13,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    13,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    16,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      16,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    16,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    18,    -1,    -1,    -1,
      -1,    53,    -1,    25,    -1,    27,    28,    -1,    30,    31,
      41,    42,    43,    44,    45,    46,    47,    -1,    40,    41,
      42,    -1,    53,    24,    -1,    -1,    48,    -1,    -1,    51,
      52,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    24,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,     1,    53,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    -1,    -1,    15,
      -1,    17,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,     1,    30,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,     1,    30,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    14,    15,    -1,    17,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,     1,
      30,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      12,    -1,    -1,    15,    -1,    17,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,     1,    30,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    15,    -1,    17,    -1,    -1,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,     1,    30,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,
      -1,    17,    -1,    -1,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,     1,    30,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,    17,
      -1,    -1,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,     1,    30,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    15,    -1,    17,    -1,    -1,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,     1,
      30,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    -1,    17,    -1,    -1,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,     1,    30,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    15,    -1,    17,    -1,    -1,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,     1,    30,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,
      -1,    17,    -1,    -1,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,     1,    30,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,    17,
      -1,    -1,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    24,    25,    -1,    27,    28,    -1,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    25,    -1,    27,    28,    48,    30,    31,
      51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    25,    -1,    27,    28,    48,    30,    31,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    53,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      -1,    -1,    -1,    53,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    53,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    53,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    56,     0,     1,     3,     4,     5,     6,     7,
       8,    12,    15,    17,    21,    22,    28,    30,    57,    58,
      59,    60,    61,    63,    64,    66,    67,    68,    25,    27,
      28,    30,    31,    40,    41,    42,    48,    51,    52,    69,
      28,    48,    69,    48,    48,    62,    62,    56,    18,    28,
      48,    23,    23,     3,     3,     3,    51,    52,    48,    69,
      69,    69,    69,    28,    28,    32,    33,    34,    35,    36,
      37,    38,    39,    41,    42,    43,    44,    45,    46,    47,
      53,    49,    28,    30,    49,    28,    69,     9,    13,    16,
      69,    18,    69,    24,    69,    28,    30,    66,    69,    66,
      69,    69,    70,    49,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      49,    49,    49,    49,    56,    56,    62,    16,    69,    16,
      49,    24,    24,    71,    49,    10,    11,    14,    69,    16,
      69,    65,    69,    69,    56,    13,    19,    69,    13,    19,
      22,    49,    71,    11,    56,    69,    13,    19,    56,    56,
      69,    48,    20,    13,    56,    69,    20,    20,    13,    24,
      56,    20,    13,    56,    56,    49,    20,    56,    20,    20,
      20
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    61,    62,    63,
      64,    65,    64,    66,    66,    66,    66,    67,    67,    68,
      68,    68,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     2,
       1,     1,     1,     1,     1,     1,    11,     9,    10,     8,
      10,     8,    10,     8,     5,     7,     5,     4,     3,     1,
       6,     0,     9,     3,     3,     3,     3,     2,     2,     4,
       4,     4,     3,     3,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     1,     1,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     0,     2,     0,     3
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
#line 215 "interpreter.y" /* yacc.c:1646  */
    { 
		    // Create a new AST
			(yyval.prog) = new lp::AST((yyvsp[0].stmts)); 

			// Assign the AST to the root
			root = (yyval.prog); 

			// End of parsing
			//	return 1;
		  }
#line 1671 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 228 "interpreter.y" /* yacc.c:1646  */
    { 
			// create a empty list of statements
			(yyval.stmts) = new std::list<lp::Statement *>(); 
		  }
#line 1680 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 234 "interpreter.y" /* yacc.c:1646  */
    { 
			// copy up the list and add the stmt to it
			(yyval.stmts) = (yyvsp[-1].stmts);
			(yyval.stmts)->push_back((yyvsp[0].st));

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true)
 			   (yyvsp[0].st)->evaluate();
           }
#line 1694 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 246 "interpreter.y" /* yacc.c:1646  */
    { 
			// just copy up the stmtlist when an error occurs
			(yyval.stmts) = (yyvsp[-1].stmts);

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
           }
#line 1706 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 257 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new empty statement node
		(yyval.st) = new lp::EmptyStmt(); 
	  }
#line 1715 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 262 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1724 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 267 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1733 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 272 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1742 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 278 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	 }
#line 1751 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 283 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
	 }
#line 1759 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 286 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
	}
#line 1767 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 290 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
	}
#line 1775 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 293 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
	}
#line 1783 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 296 "interpreter.y" /* yacc.c:1646  */
    {

	}
#line 1791 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 302 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st) =new lp::ForStmt((yyvsp[-9].identifier), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
	}
#line 1799 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 306 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st) =new lp::ForStmt((yyvsp[-7].identifier), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
	}
#line 1807 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 310 "interpreter.y" /* yacc.c:1646  */
    {
			execerror("Error sintáctico","bucle para, recibe una variable");
	}
#line 1815 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 314 "interpreter.y" /* yacc.c:1646  */
    {
			execerror("Error sintáctico","bucle para, recibe una variable");
	}
#line 1823 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 318 "interpreter.y" /* yacc.c:1646  */
    {
			warning("Error sintáctico","bucle para, falta sentencia \"desde\"");
			(yyval.st) =new lp::ForStmt((yyvsp[-8].identifier), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
	}
#line 1832 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 323 "interpreter.y" /* yacc.c:1646  */
    {
			warning("Error sintáctico","bucle para, falta sentencia \"desde\"");
			(yyval.st) =new lp::ForStmt((yyvsp[-6].identifier), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
	}
#line 1841 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 328 "interpreter.y" /* yacc.c:1646  */
    {
			warning("Error sintáctico","bucle para, falta sentencia \"hacer\"");
			(yyval.st) =new lp::ForStmt((yyvsp[-8].identifier), (yyvsp[-6].expNode), (yyvsp[-4].expNode), (yyvsp[-2].expNode), (yyvsp[-1].stmts));
	}
#line 1850 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 333 "interpreter.y" /* yacc.c:1646  */
    {
			warning("Error sintáctico","bucle para, falta sentencia \"hacer\"");
			(yyval.st) =new lp::ForStmt((yyvsp[-6].identifier), (yyvsp[-4].expNode), (yyvsp[-2].expNode), (yyvsp[-1].stmts));
	}
#line 1859 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 341 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));
	}
#line 1868 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 348 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-5].expNode), (yyvsp[-3].stmts), (yyvsp[-1].stmts));
	 }
#line 1877 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 356 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new while statement node
			(yyval.st) = new lp::WhileStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));
        }
#line 1886 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 363 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st)=new lp::RepeatStmt((yyvsp[0].expNode),(yyvsp[-2].stmts));
		}
#line 1894 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 370 "interpreter.y" /* yacc.c:1646  */
    { 
			(yyval.expNode) = (yyvsp[-1].expNode);
		}
#line 1902 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 376 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st)=new lp::EraseStmt();
		}
#line 1910 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 382 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st)=new lp::PlaceStmt((yyvsp[-3].expNode), (yyvsp[-1].expNode));
		}
#line 1918 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 387 "interpreter.y" /* yacc.c:1646  */
    {
			execerror("Error semático:", "La función \"lugar\" recibe dos parámetros");
		}
#line 1926 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 391 "interpreter.y" /* yacc.c:1646  */
    {
			execerror("Error semático:", "La función \"lugar\" recibe dos parámetros");
		}
#line 1934 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 397 "interpreter.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (yyvsp[0].expNode));
		}
#line 1943 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 403 "interpreter.y" /* yacc.c:1646  */
    { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (lp::AssignmentStmt *) (yyvsp[0].st));
		}
#line 1952 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 410 "interpreter.y" /* yacc.c:1646  */
    {   
 			execerror("Error semático en la asignación: no está permitido modificar una constante ", (yyvsp[-2].identifier));
		}
#line 1960 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 415 "interpreter.y" /* yacc.c:1646  */
    {   
 			execerror("Error semático en la asignación multiple: no está permitido modificar una constante ",(yyvsp[-2].identifier));
		}
#line 1968 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 422 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new print node
			 (yyval.st) = new lp::PrintStmt((yyvsp[0].expNode));
		}
#line 1977 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 427 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.st) = new lp::PrintStringStmt((yyvsp[0].expNode));
		}
#line 1985 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 433 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStmt((yyvsp[-1].identifier));
		}
#line 1994 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 441 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStringStmt((yyvsp[-1].identifier));
		}
#line 2003 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 448 "interpreter.y" /* yacc.c:1646  */
    {   
 			execerror("Error semático en \"escribir\": no está permitido modificar una constante ",(yyvsp[-1].identifier));
		}
#line 2011 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 452 "interpreter.y" /* yacc.c:1646  */
    {
 			warning("Error sintáctico", "sentencia \"escribir\": falta parentesis derecho");
 			(yyval.st) = new lp::ReadStmt((yyvsp[-1].identifier));
		}
#line 2020 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 457 "interpreter.y" /* yacc.c:1646  */
    {
 			warning("Error sintáctico", "sentencia \"escribir\": falta parentesis izquierdo");
			(yyval.st) = new lp::ReadStmt((yyvsp[0].identifier));
		}
#line 2029 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 462 "interpreter.y" /* yacc.c:1646  */
    {
			execerror("Error semático:", "La función \"escribir\" recibe un parámetro");
		}
#line 2037 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 470 "interpreter.y" /* yacc.c:1646  */
    { 
			// Create a new number node
			(yyval.expNode) = new lp::NumberNode((yyvsp[0].number));
		}
#line 2046 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 476 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = new lp::StringNode((yyvsp[0].strings));
		}
#line 2054 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 481 "interpreter.y" /* yacc.c:1646  */
    { 
			// Create a new plus node
			 (yyval.expNode) = new lp::PlusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2063 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 487 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new minus node
			(yyval.expNode) = new lp::MinusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2072 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 493 "interpreter.y" /* yacc.c:1646  */
    { 
			// Create a new multiplication node
			(yyval.expNode) = new lp::MultiplicationNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2081 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 499 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new division node	
		  (yyval.expNode) = new lp::DivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	    }
#line 2090 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 504 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new division int node	
			(yyval.expNode) = new lp::DivisionIntNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2099 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 509 "interpreter.y" /* yacc.c:1646  */
    { 
		    // just copy up the expression node 
			(yyval.expNode) = (yyvsp[-1].expNode);
		 }
#line 2108 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 514 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = new lp::UnaryAddNode((yyvsp[0].identifier));
		}
#line 2116 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 518 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = new lp::UnarySubstractNode((yyvsp[0].identifier));
		}
#line 2124 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 522 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = new lp::UnaryAddNode((yyvsp[-1].identifier));
		}
#line 2132 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 526 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = new lp::UnarySubstractNode((yyvsp[-1].identifier));
		}
#line 2140 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 530 "interpreter.y" /* yacc.c:1646  */
    { 
		  // Create a new unary plus node	
  		  (yyval.expNode) = new lp::UnaryPlusNode((yyvsp[0].expNode));
		}
#line 2149 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 535 "interpreter.y" /* yacc.c:1646  */
    { 
		  // Create a new unary minus node	
  		  (yyval.expNode) = new lp::UnaryMinusNode((yyvsp[0].expNode));
		}
#line 2158 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 541 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new modulo node	

		  (yyval.expNode) = new lp::ModuloNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
        }
#line 2168 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 548 "interpreter.y" /* yacc.c:1646  */
    { 
		  // Create a new power node	
  		  (yyval.expNode) = new lp::PowerNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2177 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 553 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new concatenate node	
  		  (yyval.expNode) = new lp::ConcatenateNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2186 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 558 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new variable node	
		  (yyval.expNode) = new lp::VariableNode((yyvsp[0].identifier));
		}
#line 2195 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 564 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new constant node	
		  (yyval.expNode) = new lp::ConstantNode((yyvsp[0].identifier));

		}
#line 2205 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 571 "interpreter.y" /* yacc.c:1646  */
    {
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol((yyvsp[-3].identifier));

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) (yyvsp[-1].parameters)->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_0((yyvsp[-3].identifier));
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 1 parameter node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_1((yyvsp[-3].identifier),e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = (yyvsp[-1].parameters)->front();
							(yyvsp[-1].parameters)->pop_front();
							lp::ExpNode *e2 = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 2 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_2((yyvsp[-3].identifier),e1,e2);
						}
						break;

					default:
				  			 execerror("Error sintáctico: demasiados parámetros para la función", (yyvsp[-3].identifier));
				} 
			}
			else
	  			 execerror("Error sintáctico: número de parámetros incompatibles con la función", (yyvsp[-3].identifier));
		}
#line 2255 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 618 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "greater than" node	
 			(yyval.expNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2264 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 624 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "greater or equal" node	
 			(yyval.expNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2273 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 630 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "less than" node	
 			(yyval.expNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2282 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 636 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "less or equal" node	
 			(yyval.expNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2291 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 642 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "equal" node	
 			(yyval.expNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2300 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 648 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "not equal" node	
 			(yyval.expNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2309 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 654 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic and" node	
 			(yyval.expNode) = new lp::AndNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2318 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 660 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic or" node	
 			(yyval.expNode) = new lp::OrNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2327 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 666 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic negation" node	
 			(yyval.expNode) = new lp::NotNode((yyvsp[0].expNode));
		}
#line 2336 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 675 "interpreter.y" /* yacc.c:1646  */
    {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>(); 
			}
#line 2345 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 681 "interpreter.y" /* yacc.c:1646  */
    {
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2356 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 691 "interpreter.y" /* yacc.c:1646  */
    {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>(); 
			}
#line 2365 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 697 "interpreter.y" /* yacc.c:1646  */
    {
				// Get the list of expressions
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2377 "interpreter.tab.c" /* yacc.c:1646  */
    break;


#line 2381 "interpreter.tab.c" /* yacc.c:1646  */
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
#line 708 "interpreter.y" /* yacc.c:1906  */




