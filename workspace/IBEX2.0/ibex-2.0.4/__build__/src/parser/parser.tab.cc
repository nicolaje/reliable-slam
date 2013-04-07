/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         ibexparse
#define yylex           ibexlex
#define yyerror         ibexerror
#define yylval          ibexlval
#define yychar          ibexchar
#define yydebug         ibexdebug
#define yynerrs         ibexnerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"

//============================================================================
//                                  I B E X                                   
// File        : Yacc/Bison input for Ibex parser
// Author      : Gilles Chabert
// Copyright   : Ecole des Mines de Nantes (France)
// License     : See the LICENSE file
// Created     : Jun 12, 2012
// Last Update : Jun 12, 2012
//===========================================================================

#include "parser.cpp_"



/* Line 268 of yacc.c  */
#line 95 "parser.tab.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_CONSTANT = 258,
     TK_NEW_SYMBOL = 259,
     TK_FUNC_SYMBOL = 260,
     TK_FUNC_RET_SYMBOL = 261,
     TK_FUNC_INP_SYMBOL = 262,
     TK_FUNC_TMP_SYMBOL = 263,
     TK_ENTITY = 264,
     TK_ITERATOR = 265,
     TK_STRING = 266,
     TK_INTEGER = 267,
     TK_FLOAT = 268,
     TK_INFINITY = 269,
     TK_BOOL = 270,
     TK_PARAM = 271,
     TK_CONST = 272,
     TK_VARS = 273,
     TK_FUNCTION = 274,
     TK_MIN = 275,
     TK_MAX = 276,
     TK_INF = 277,
     TK_MID = 278,
     TK_SUP = 279,
     TK_SIGN = 280,
     TK_ABS = 281,
     TK_SQRT = 282,
     TK_EXPO = 283,
     TK_LOG = 284,
     TK_COS = 285,
     TK_SIN = 286,
     TK_TAN = 287,
     TK_ACOS = 288,
     TK_ASIN = 289,
     TK_ATAN = 290,
     TK_ATAN2 = 291,
     TK_COSH = 292,
     TK_SINH = 293,
     TK_TANH = 294,
     TK_ACOSH = 295,
     TK_ASINH = 296,
     TK_ATANH = 297,
     TK_LEQ = 298,
     TK_GEQ = 299,
     TK_EQU = 300,
     TK_ASSIGN = 301,
     TK_BEGIN = 302,
     TK_END = 303,
     TK_FOR = 304,
     TK_FROM = 305,
     TK_TO = 306,
     TK_RETURN = 307,
     TK_CTRS = 308,
     TK_MINIMIZE = 309,
     TK_IN = 310,
     TK_UNION = 311,
     TK_INTERSEC = 312
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 16 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"

  char*     str;
  int       itg;
  double    real;
  
  ibex::Interval* itv;
  
  ibex::Dim*      dim;
  
  const ibex::ExprSymbol*                 func_input_symbol;
  std::vector<const ibex::ExprSymbol*>*   func_input_symbols;

  ibex::parser::Entity*                   entity_symbol;

  ibex::parser::P_NumConstraint*               constraint;
  std::vector<ibex::parser::P_NumConstraint*>* constraints;

  const ibex::ExprNode*                expression;
  std::vector<const ibex::ExprNode*>*  expressions;




/* Line 293 of yacc.c  */
#line 212 "parser.tab.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 224 "parser.tab.cc"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   828

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNRULES -- Number of states.  */
#define YYNSTATES  291

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,     2,     2,     2,     2,     2,    65,
      67,    72,    61,    58,    69,    59,     2,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    73,    68,
      56,     2,    57,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    71,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,    75,     2,     2,     2,     2,
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
      55,    60,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    11,    12,    15,    24,
      26,    27,    31,    33,    37,    42,    47,    48,    52,    54,
      58,    62,    65,    67,    69,    73,    77,    79,    82,    87,
      88,    92,    99,   109,   115,   118,   119,   120,   132,   134,
     135,   139,   141,   144,   148,   149,   153,   157,   158,   162,
     163,   167,   170,   174,   176,   178,   180,   181,   193,   197,
     201,   205,   209,   213,   217,   221,   225,   229,   233,   240,
     247,   254,   257,   262,   267,   270,   275,   280,   285,   290,
     295,   300,   305,   310,   315,   320,   325,   330,   335,   340,
     345,   348,   352,   358,   362,   367,   372,   379,   388,   392,
     396,   398,   402,   404,   406,   408,   410,   415,   420,   422,
     424,   426,   428,   430,   435,   440,   445,   449,   453,   457
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    -1,    78,    81,    -1,    -1,    79,    82,
      -1,    -1,    80,    95,    -1,    83,    18,    89,    68,    86,
      94,   102,   103,    -1,   104,    -1,    -1,    17,    84,    68,
      -1,    85,    -1,    84,    68,    85,    -1,     4,    92,    45,
     110,    -1,     4,    92,    55,   110,    -1,    -1,    16,    87,
      68,    -1,    88,    -1,    87,    68,    88,    -1,    87,    69,
      88,    -1,    70,    91,    -1,    91,    -1,    90,    -1,    89,
      68,    90,    -1,    89,    69,    90,    -1,    91,    -1,     4,
      92,    -1,     4,    92,    55,   110,    -1,    -1,    66,   110,
      71,    -1,    66,   110,    71,    66,   110,    71,    -1,    66,
     110,    71,    66,   110,    71,    66,   110,    71,    -1,    66,
     110,    69,   110,    71,    -1,    94,    95,    -1,    -1,    -1,
      19,    96,     4,    67,    98,    72,   100,    52,   110,    97,
      48,    -1,    68,    -1,    -1,    98,    69,    99,    -1,    99,
      -1,     4,    92,    -1,   100,   101,    68,    -1,    -1,     4,
      45,   110,    -1,     3,    45,   110,    -1,    -1,    54,   110,
      97,    -1,    -1,    53,   104,    48,    -1,   105,    97,    -1,
     105,    68,   106,    -1,   106,    -1,   107,    -1,   109,    -1,
      -1,    49,     4,    45,   110,    73,   110,    68,   108,   105,
      97,    48,    -1,   110,    45,   110,    -1,   110,    43,   110,
      -1,   110,    44,   110,    -1,   110,    56,   110,    -1,   110,
      57,   110,    -1,    67,   109,    72,    -1,   110,    58,   110,
      -1,   110,    61,   110,    -1,   110,    59,   110,    -1,   110,
      62,   110,    -1,    21,    67,   110,    69,   110,    72,    -1,
      20,    67,   110,    69,   110,    72,    -1,    36,    67,   110,
      69,   110,    72,    -1,    59,   110,    -1,    26,    67,   110,
      72,    -1,    25,    67,   110,    72,    -1,   110,    65,    -1,
      27,    67,   110,    72,    -1,    28,    67,   110,    72,    -1,
      29,    67,   110,    72,    -1,    30,    67,   110,    72,    -1,
      31,    67,   110,    72,    -1,    32,    67,   110,    72,    -1,
      33,    67,   110,    72,    -1,    34,    67,   110,    72,    -1,
      35,    67,   110,    72,    -1,    37,    67,   110,    72,    -1,
      38,    67,   110,    72,    -1,    39,    67,   110,    72,    -1,
      40,    67,   110,    72,    -1,    41,    67,   110,    72,    -1,
      42,    67,   110,    72,    -1,    58,   110,    -1,    67,   110,
      72,    -1,    56,   110,    69,   110,    57,    -1,   110,    64,
     110,    -1,   110,    66,   110,    71,    -1,   110,    67,   110,
      72,    -1,   110,    67,   110,    69,   110,    72,    -1,   110,
      67,   110,    69,   110,    69,   110,    72,    -1,    67,   111,
      72,    -1,    67,   112,    72,    -1,     9,    -1,    74,    12,
      75,    -1,    10,    -1,     7,    -1,     8,    -1,     3,    -1,
       5,    67,   110,    72,    -1,     5,    67,   111,    72,    -1,
       4,    -1,    13,    -1,    14,    -1,    12,    -1,    93,    -1,
      22,    67,   110,    72,    -1,    23,    67,   110,    72,    -1,
      24,    67,   110,    72,    -1,   111,    69,   110,    -1,   110,
      69,   110,    -1,   112,    68,   110,    -1,   110,    68,   110,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,    99,   101,   101,   103,   103,   109,   117,
     124,   125,   128,   129,   132,   133,   136,   137,   140,   141,
     142,   145,   146,   149,   150,   151,   154,   158,   161,   167,
     168,   169,   170,   174,   181,   182,   185,   185,   204,   204,
     206,   207,   210,   215,   216,   219,   221,   229,   230,   237,
     238,   241,   244,   245,   249,   250,   255,   254,   263,   264,
     265,   266,   267,   268,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   310,   311,
     312,   313,   314,   315,   316,   317,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   332,   333,   337,   338
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_CONSTANT", "TK_NEW_SYMBOL",
  "TK_FUNC_SYMBOL", "TK_FUNC_RET_SYMBOL", "TK_FUNC_INP_SYMBOL",
  "TK_FUNC_TMP_SYMBOL", "TK_ENTITY", "TK_ITERATOR", "TK_STRING",
  "TK_INTEGER", "TK_FLOAT", "TK_INFINITY", "TK_BOOL", "TK_PARAM",
  "TK_CONST", "TK_VARS", "TK_FUNCTION", "TK_MIN", "TK_MAX", "TK_INF",
  "TK_MID", "TK_SUP", "TK_SIGN", "TK_ABS", "TK_SQRT", "TK_EXPO", "TK_LOG",
  "TK_COS", "TK_SIN", "TK_TAN", "TK_ACOS", "TK_ASIN", "TK_ATAN",
  "TK_ATAN2", "TK_COSH", "TK_SINH", "TK_TANH", "TK_ACOSH", "TK_ASINH",
  "TK_ATANH", "TK_LEQ", "TK_GEQ", "TK_EQU", "TK_ASSIGN", "TK_BEGIN",
  "TK_END", "TK_FOR", "TK_FROM", "TK_TO", "TK_RETURN", "TK_CTRS",
  "TK_MINIMIZE", "TK_IN", "'<'", "'>'", "'+'", "'-'", "TK_UNION", "'*'",
  "'/'", "TK_INTERSEC", "'^'", "'\\''", "'['", "'('", "';'", "','", "'!'",
  "']'", "')'", "':'", "'{'", "'}'", "$accept", "program", "$@1", "$@2",
  "$@3", "system", "choco_ctr", "decl_opt_cst", "decl_cst_list",
  "decl_cst", "decl_opt_par", "decl_par_list", "decl_par", "decl_var_list",
  "decl_var", "decl_entity", "dimension", "interval", "decl_fnc_list",
  "decl_fnc", "$@4", "semicolon_opt", "fnc_inpt_list", "fnc_input",
  "fnc_code", "fnc_assign", "decl_opt_goal", "decl_opt_ctrs",
  "ctr_blk_list", "ctr_blk_list_", "ctr_blk", "ctr_loop", "$@5", "ctr",
  "expr", "expr_row", "expr_col", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,    60,    62,    43,    45,
     311,    42,    47,   312,    94,    39,    91,    40,    59,    44,
      33,    93,    41,    58,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    78,    77,    79,    77,    80,    77,    81,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    89,    90,    91,    91,    92,
      92,    92,    92,    93,    94,    94,    96,    95,    97,    97,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   105,   105,   106,   106,   108,   107,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   111,   111,   112,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,     2,     8,     1,
       0,     3,     1,     3,     4,     4,     0,     3,     1,     3,
       3,     2,     1,     1,     3,     3,     1,     2,     4,     0,
       3,     6,     9,     5,     2,     0,     0,    11,     1,     0,
       3,     1,     2,     3,     0,     3,     3,     0,     3,     0,
       3,     2,     3,     1,     1,     1,     0,    11,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     6,
       6,     2,     4,     4,     2,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       2,     3,     5,     3,     4,     4,     6,     8,     3,     3,
       1,     3,     1,     1,     1,     1,     4,     4,     1,     1,
       1,     1,     1,     4,     4,     4,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    10,     0,     0,     1,     0,     3,     0,   105,
     108,     0,   103,   104,   100,   102,   111,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
     112,     9,    39,    53,    54,    55,     0,    36,     7,    29,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      90,    71,     0,     0,     0,     0,     0,     0,    38,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      74,     0,     0,     0,     0,     0,    11,    29,     0,    23,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,     0,    91,     0,    98,     0,    99,   101,    52,
      59,    60,    58,    61,    62,    64,    66,    65,    67,    93,
       0,     0,     0,     0,     0,     0,    13,    27,    16,     0,
     106,   107,     0,     0,   113,   114,   115,    73,    72,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,     0,     0,     0,   119,   117,
     116,   118,    94,     0,    95,     0,    30,    14,    15,     0,
       0,    35,    24,    25,     0,     0,     0,     0,    92,    33,
       0,    29,     0,    41,     0,    28,     0,     0,    18,    22,
      47,    69,    68,    70,     0,     0,    96,    42,     0,    44,
       0,    21,    17,     0,     0,    34,    49,    56,     0,    40,
       0,    31,    19,    20,    39,     0,     8,     0,    97,     0,
       0,     0,     0,     0,    38,    48,     0,    39,     0,     0,
      39,    43,     0,    50,     0,    46,    45,     0,    32,    57,
      37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     4,     7,    49,     8,    60,    61,
     221,   237,   238,   118,   119,   120,   115,    50,   240,    58,
     113,    99,   232,   233,   260,   272,   256,   266,    51,    52,
      53,    54,   267,    55,    56,    95,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -188
static const yytype_int16 yypact[] =
{
      29,    79,    68,   234,    88,  -188,   108,  -188,    98,  -188,
    -188,    78,  -188,  -188,  -188,  -188,  -188,  -188,  -188,    81,
      91,   102,   106,   116,   121,   129,   134,   136,   137,   138,
     141,   149,   156,   164,   166,   167,   173,   178,   182,   183,
     184,   185,   120,   302,   302,   302,   302,   370,   151,  -188,
    -188,  -188,   209,  -188,  -188,  -188,    85,  -188,  -188,   187,
     212,  -188,   284,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   244,   302,   678,
     -12,   -12,   690,   222,    30,   -57,     8,   221,   234,  -188,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
    -188,   302,   302,   291,   302,    55,   108,   187,    57,  -188,
    -188,   128,     9,   702,   714,   287,   355,   381,   393,   405,
     417,   429,   441,   453,   465,   477,   489,   501,   513,   726,
     525,   537,   549,   561,   573,   585,   302,   113,   302,   302,
    -188,   302,   302,  -188,   302,  -188,   302,  -188,  -188,  -188,
     -48,   -48,   -48,   -48,   -48,   -12,   -12,    69,    69,    71,
      56,   148,   230,   220,   302,   302,  -188,   243,    66,   284,
    -188,  -188,   302,   302,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,   302,  -188,
    -188,  -188,  -188,  -188,  -188,    95,   739,   645,   -48,   -48,
     -48,   -48,  -188,   302,  -188,   295,   236,   -48,   -48,   302,
       2,  -188,  -188,  -188,   597,   609,   621,   302,  -188,  -188,
     160,   187,    32,  -188,   302,   -48,   284,    96,  -188,  -188,
     -10,  -188,  -188,  -188,   749,   302,  -188,  -188,   295,  -188,
     656,  -188,     2,     2,   302,  -188,   250,  -188,   633,  -188,
       4,   238,  -188,  -188,   760,   234,  -188,   234,  -188,   268,
     272,   302,   251,   302,  -188,  -188,   270,   209,   302,   302,
     760,  -188,   667,  -188,   273,   -48,   -48,   299,  -188,  -188,
    -188
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,   204,
    -188,  -188,   -86,  -188,    20,  -169,  -112,  -188,  -188,   110,
    -188,  -187,  -188,   107,  -188,  -188,  -188,  -188,    92,    89,
     264,  -188,  -188,   316,   -43,   301,  -188
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -7
static const yytype_int16 yytable[] =
{
      89,    90,    91,    92,    94,   177,   117,   269,   270,    57,
     105,   106,   154,   107,   108,   155,   109,   110,   111,   112,
     121,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   254,   147,    -2,    -2,    -6,   107,
     108,   239,   109,   110,   111,   112,   271,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   251,   170,   171,
     117,   173,   236,   100,   101,   102,   156,   275,   154,     5,
     157,   181,   220,   239,   239,     6,   103,   104,   105,   106,
     284,   107,   108,   287,   109,   110,   111,   112,   151,   152,
     174,   248,   153,   205,   249,   206,   207,    57,   208,   209,
     175,   210,    59,   211,   105,   106,    62,   107,   108,   247,
     109,   110,   111,   112,    87,   178,   179,   212,   100,   101,
     102,   217,   218,   109,   110,   111,   112,   111,   112,   224,
     225,   103,   104,   105,   106,    63,   107,   108,    64,   109,
     110,   111,   112,   105,   106,   226,   107,   108,    65,   109,
     110,   111,   112,    97,   252,   253,   262,   263,   227,    66,
     230,   105,   106,    67,   107,   108,   235,   109,   110,   111,
     112,   151,   152,    68,   244,   153,   105,   106,    69,   107,
     108,   250,   109,   110,   111,   112,    70,   152,   222,   223,
     180,    71,   258,    72,    73,    74,   105,   106,    75,   107,
     108,   264,   109,   110,   111,   112,    76,   213,   105,   106,
     214,   107,   108,    77,   109,   110,   111,   112,   280,   245,
     282,    78,   246,    79,    80,   285,   286,     9,    10,    11,
      81,    12,    13,    14,    15,    82,    16,    17,    18,    83,
      84,    85,    86,   114,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    98,   105,   106,
     116,   107,   108,    42,   109,   110,   111,   112,   117,   146,
      43,   216,    44,    45,   150,   172,   158,   215,   219,   231,
      46,    47,   234,   265,   273,     9,    10,    11,    48,    12,
      13,    14,    15,   278,    16,    17,    18,   279,   283,   281,
     176,   289,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,   105,   106,   290,   107,   108,
     255,   109,   110,   111,   112,   259,   277,   276,    43,   184,
      44,    45,   159,    93,   122,     0,     0,     0,    46,    88,
       0,     0,     0,     9,    10,    11,    48,    12,    13,    14,
      15,     0,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,   105,   106,     0,   107,   108,     0,   109,
     110,   111,   112,     0,     0,     0,    43,   185,    44,    45,
       0,     0,     0,     0,     0,     0,    46,    47,     0,   105,
     106,     0,   107,   108,    48,   109,   110,   111,   112,     0,
       0,   105,   106,   186,   107,   108,     0,   109,   110,   111,
     112,     0,     0,   105,   106,   187,   107,   108,     0,   109,
     110,   111,   112,     0,     0,   105,   106,   188,   107,   108,
       0,   109,   110,   111,   112,     0,     0,   105,   106,   189,
     107,   108,     0,   109,   110,   111,   112,     0,     0,   105,
     106,   190,   107,   108,     0,   109,   110,   111,   112,     0,
       0,   105,   106,   191,   107,   108,     0,   109,   110,   111,
     112,     0,     0,   105,   106,   192,   107,   108,     0,   109,
     110,   111,   112,     0,     0,   105,   106,   193,   107,   108,
       0,   109,   110,   111,   112,     0,     0,   105,   106,   194,
     107,   108,     0,   109,   110,   111,   112,     0,     0,   105,
     106,   195,   107,   108,     0,   109,   110,   111,   112,     0,
       0,   105,   106,   196,   107,   108,     0,   109,   110,   111,
     112,     0,     0,   105,   106,   197,   107,   108,     0,   109,
     110,   111,   112,     0,     0,   105,   106,   199,   107,   108,
       0,   109,   110,   111,   112,     0,     0,   105,   106,   200,
     107,   108,     0,   109,   110,   111,   112,     0,     0,   105,
     106,   201,   107,   108,     0,   109,   110,   111,   112,     0,
       0,   105,   106,   202,   107,   108,     0,   109,   110,   111,
     112,     0,     0,   105,   106,   203,   107,   108,     0,   109,
     110,   111,   112,     0,     0,   105,   106,   204,   107,   108,
       0,   109,   110,   111,   112,     0,     0,   105,   106,   241,
     107,   108,     0,   109,   110,   111,   112,     0,     0,   105,
     106,   242,   107,   108,     0,   109,   110,   111,   112,     0,
       0,   105,   106,   243,   107,   108,     0,   109,   110,   111,
     112,     0,     0,   105,   106,   268,   107,   108,     0,   109,
     110,   111,   112,     0,   105,   106,   229,   107,   108,     0,
     109,   110,   111,   112,     0,   105,   106,   261,   107,   108,
       0,   109,   110,   111,   112,     0,   105,   106,   288,   107,
     108,     0,   109,   110,   111,   112,     0,   148,   105,   106,
       0,   107,   108,     0,   109,   110,   111,   112,     0,   149,
     105,   106,     0,   107,   108,     0,   109,   110,   111,   112,
       0,   182,   105,   106,     0,   107,   108,     0,   109,   110,
     111,   112,     0,   183,   105,   106,     0,   107,   108,     0,
     109,   110,   111,   112,     0,   198,   228,   105,   106,     0,
     107,   108,     0,   109,   110,   111,   112,   105,   106,     0,
     107,   108,     0,   109,   110,   111,   112,   257,   105,   106,
       0,   107,   108,     0,   109,   110,   111,   112,   274
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-188))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      43,    44,    45,    46,    47,   117,     4,     3,     4,    19,
      58,    59,    69,    61,    62,    72,    64,    65,    66,    67,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    54,    88,    17,    18,    19,    61,
      62,   220,    64,    65,    66,    67,    52,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   236,   111,   112,
       4,   114,    70,    43,    44,    45,    68,   264,    69,     0,
      72,    72,    16,   252,   253,    17,    56,    57,    58,    59,
     277,    61,    62,   280,    64,    65,    66,    67,    68,    69,
      45,    69,    72,   146,    72,   148,   149,    19,   151,   152,
      55,   154,     4,   156,    58,    59,    18,    61,    62,   231,
      64,    65,    66,    67,     4,    68,    69,    71,    43,    44,
      45,   174,   175,    64,    65,    66,    67,    66,    67,   182,
     183,    56,    57,    58,    59,    67,    61,    62,    67,    64,
      65,    66,    67,    58,    59,   198,    61,    62,    67,    64,
      65,    66,    67,    12,    68,    69,   252,   253,    73,    67,
     213,    58,    59,    67,    61,    62,   219,    64,    65,    66,
      67,    68,    69,    67,   227,    72,    58,    59,    67,    61,
      62,   234,    64,    65,    66,    67,    67,    69,   178,   179,
      72,    67,   245,    67,    67,    67,    58,    59,    67,    61,
      62,   254,    64,    65,    66,    67,    67,    69,    58,    59,
      72,    61,    62,    67,    64,    65,    66,    67,   271,    69,
     273,    67,    72,    67,    67,   278,   279,     3,     4,     5,
      67,     7,     8,     9,    10,    67,    12,    13,    14,    67,
      67,    67,    67,    66,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    68,    58,    59,
      68,    61,    62,    49,    64,    65,    66,    67,     4,    45,
      56,    71,    58,    59,    72,     4,    75,    67,    55,     4,
      66,    67,    66,    53,    66,     3,     4,     5,    74,     7,
       8,     9,    10,    45,    12,    13,    14,    45,    48,    68,
     116,    48,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    58,    59,    48,    61,    62,
     240,    64,    65,    66,    67,   248,   267,   265,    56,    72,
      58,    59,    98,    47,    63,    -1,    -1,    -1,    66,    67,
      -1,    -1,    -1,     3,     4,     5,    74,     7,     8,     9,
      10,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    58,    59,    -1,    61,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    56,    72,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    58,
      59,    -1,    61,    62,    74,    64,    65,    66,    67,    -1,
      -1,    58,    59,    72,    61,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    58,    59,    72,    61,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    58,    59,    72,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    58,    59,    72,
      61,    62,    -1,    64,    65,    66,    67,    -1,    -1,    58,
      59,    72,    61,    62,    -1,    64,    65,    66,    67,    -1,
      -1,    58,    59,    72,    61,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    58,    59,    72,    61,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    58,    59,    72,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    58,    59,    72,
      61,    62,    -1,    64,    65,    66,    67,    -1,    -1,    58,
      59,    72,    61,    62,    -1,    64,    65,    66,    67,    -1,
      -1,    58,    59,    72,    61,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    58,    59,    72,    61,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    58,    59,    72,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    58,    59,    72,
      61,    62,    -1,    64,    65,    66,    67,    -1,    -1,    58,
      59,    72,    61,    62,    -1,    64,    65,    66,    67,    -1,
      -1,    58,    59,    72,    61,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    58,    59,    72,    61,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    58,    59,    72,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    58,    59,    72,
      61,    62,    -1,    64,    65,    66,    67,    -1,    -1,    58,
      59,    72,    61,    62,    -1,    64,    65,    66,    67,    -1,
      -1,    58,    59,    72,    61,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    58,    59,    72,    61,    62,    -1,    64,
      65,    66,    67,    -1,    58,    59,    71,    61,    62,    -1,
      64,    65,    66,    67,    -1,    58,    59,    71,    61,    62,
      -1,    64,    65,    66,    67,    -1,    58,    59,    71,    61,
      62,    -1,    64,    65,    66,    67,    -1,    69,    58,    59,
      -1,    61,    62,    -1,    64,    65,    66,    67,    -1,    69,
      58,    59,    -1,    61,    62,    -1,    64,    65,    66,    67,
      -1,    69,    58,    59,    -1,    61,    62,    -1,    64,    65,
      66,    67,    -1,    69,    58,    59,    -1,    61,    62,    -1,
      64,    65,    66,    67,    -1,    69,    57,    58,    59,    -1,
      61,    62,    -1,    64,    65,    66,    67,    58,    59,    -1,
      61,    62,    -1,    64,    65,    66,    67,    68,    58,    59,
      -1,    61,    62,    -1,    64,    65,    66,    67,    68
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,    78,    79,    80,     0,    17,    81,    83,     3,
       4,     5,     7,     8,     9,    10,    12,    13,    14,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    49,    56,    58,    59,    66,    67,    74,    82,
      93,   104,   105,   106,   107,   109,   110,    19,    95,     4,
      84,    85,    18,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,     4,    67,   110,
     110,   110,   110,   109,   110,   111,   112,    12,    68,    97,
      43,    44,    45,    56,    57,    58,    59,    61,    62,    64,
      65,    66,    67,    96,    66,    92,    68,     4,    89,    90,
      91,   110,   111,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,    45,   110,    69,    69,
      72,    68,    69,    72,    69,    72,    68,    72,    75,   106,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,     4,   110,    45,    55,    85,    92,    68,    69,
      72,    72,    69,    69,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    69,    72,
      72,    72,    72,    72,    72,   110,   110,   110,   110,   110,
     110,   110,    71,    69,    72,    67,    71,   110,   110,    55,
      16,    86,    90,    90,   110,   110,   110,    73,    57,    71,
     110,     4,    98,    99,    66,   110,    70,    87,    88,    91,
      94,    72,    72,    72,   110,    69,    72,    92,    69,    72,
     110,    91,    68,    69,    54,    95,   102,    68,   110,    99,
     100,    71,    88,    88,   110,    53,   103,   108,    72,     3,
       4,    52,   101,    66,    68,    97,   104,   105,    45,    45,
     110,    68,   110,    48,    97,   110,   110,    97,    71,    48,
      48
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 99 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { begin_system(); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 100 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { end_system(); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 101 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { begin_choco(); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 102 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { end_choco(); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 103 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { begin_function(); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 104 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { end_function(); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 117 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 132 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { scopes.top().add_cst((yyvsp[(1) - (4)].str), *(yyvsp[(2) - (4)].dim), _2domain(*(yyvsp[(4) - (4)].expression))); free((yyvsp[(1) - (4)].str)); delete (yyvsp[(2) - (4)].dim); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 133 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { scopes.top().add_cst((yyvsp[(1) - (4)].str), *(yyvsp[(2) - (4)].dim), _2domain(*(yyvsp[(4) - (4)].expression))); free((yyvsp[(1) - (4)].str)); delete (yyvsp[(2) - (4)].dim); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 145 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(2) - (2)].entity_symbol)->type=Entity::EPR; source.vars.push_back((yyvsp[(2) - (2)].entity_symbol)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 146 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (1)].entity_symbol)->type=Entity::SYB; source.vars.push_back((yyvsp[(1) - (1)].entity_symbol)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 154 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (1)].entity_symbol)->type=Entity::VAR; 
	                                              source.vars.push_back((yyvsp[(1) - (1)].entity_symbol)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 158 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.entity_symbol) = new Entity((yyvsp[(1) - (2)].str),*(yyvsp[(2) - (2)].dim),Interval::ALL_REALS);
		                                          scopes.top().add_entity((yyvsp[(1) - (2)].str),(yyval.entity_symbol));  
		                                          free((yyvsp[(1) - (2)].str)); delete (yyvsp[(2) - (2)].dim); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 162 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.entity_symbol) = new Entity((yyvsp[(1) - (4)].str),*(yyvsp[(2) - (4)].dim),_2domain(*(yyvsp[(4) - (4)].expression)));
		                                          scopes.top().add_entity((yyvsp[(1) - (4)].str),(yyval.entity_symbol)); 
						                          free((yyvsp[(1) - (4)].str)); delete (yyvsp[(2) - (4)].dim); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 167 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.dim)=new Dim(); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 168 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.dim)=new Dim(Dim::col_vec(_2int(*(yyvsp[(2) - (3)].expression))));  }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 169 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.dim)=new Dim(Dim::matrix(_2int(*(yyvsp[(2) - (6)].expression)),_2int(*(yyvsp[(5) - (6)].expression)))); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 171 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.dim)=new Dim(Dim::matrix_array(_2int(*(yyvsp[(2) - (9)].expression)),_2int(*(yyvsp[(5) - (9)].expression)),_2int(*(yyvsp[(8) - (9)].expression)))); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 174 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.itv)=new Interval(_2dbl(*(yyvsp[(2) - (5)].expression)), _2dbl(*(yyvsp[(4) - (5)].expression))); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 185 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { scopes.push(Scope(scopes.top(),true)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 190 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { Array<const ExprSymbol> x((yyvsp[(5) - (11)].func_input_symbols)->size());
                								  int i=0;
                								  for(vector<const ExprSymbol*>::const_iterator it=(yyvsp[(5) - (11)].func_input_symbols)->begin(); it!=(yyvsp[(5) - (11)].func_input_symbols)->end(); it++)
                								      x.set_ref(i++,ExprSymbol::new_((*it)->name,(*it)->dim));
                								  const ExprNode& y= ExprGenerator(scopes.top()).generate(Array<const ExprSymbol>(*(yyvsp[(5) - (11)].func_input_symbols)),x,*(yyvsp[(9) - (11)].expression));
                								  Function* f=new Function(x,y,(yyvsp[(3) - (11)].str));                                                  
                                                  scopes.pop();
                                                  scopes.top().add_func((yyvsp[(3) - (11)].str),f); 
                                                  source.func.push_back(f);
                                                  free((yyvsp[(3) - (11)].str)); 
                                                  cleanup(*(yyvsp[(9) - (11)].expression),true); // will also delete symbols in $5
                                                  delete (yyvsp[(5) - (11)].func_input_symbols); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 206 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (3)].func_input_symbols)->push_back((yyvsp[(3) - (3)].func_input_symbol)); (yyval.func_input_symbols)=(yyvsp[(1) - (3)].func_input_symbols); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 207 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.func_input_symbols)=new vector<const ExprSymbol*>(); (yyval.func_input_symbols)->push_back((yyvsp[(1) - (1)].func_input_symbol)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 210 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.func_input_symbol)=&ExprSymbol::new_((yyvsp[(1) - (2)].str),*(yyvsp[(2) - (2)].dim));
                                                  scopes.top().add_func_input((yyvsp[(1) - (2)].str),(yyval.func_input_symbol));  
                                                  free((yyvsp[(1) - (2)].str)); delete (yyvsp[(2) - (2)].dim); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 219 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { /* TODO: if this tmp symbol is not used, the expr $3 will never be deleted */
                                                  scopes.top().add_func_tmp_symbol((yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].expression)); free((yyvsp[(1) - (3)].str)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 221 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { cerr << "Warning: line " << ibex_lineno << ", local variable " << (yyvsp[(1) - (3)].str) << " shadows the constant of the same name\n"; 
                                                  scopes.top().rem_cst((yyvsp[(1) - (3)].str));
                                                  scopes.top().add_func_tmp_symbol((yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].expression)); free((yyvsp[(1) - (3)].str)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 229 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { source.goal = NULL; }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 230 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { source.goal = (yyvsp[(2) - (3)].expression); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 241 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { source.ctrs=new P_ConstraintList(*(yyvsp[(1) - (2)].constraints)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 244 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (3)].constraints)->push_back((yyvsp[(3) - (3)].constraint)); (yyval.constraints) = (yyvsp[(1) - (3)].constraints); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 245 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraints) = new vector<P_NumConstraint*>();
              								      (yyval.constraints)->push_back((yyvsp[(1) - (1)].constraint)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 249 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = (yyvsp[(1) - (1)].constraint); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 250 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = (yyvsp[(1) - (1)].constraint); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 255 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { scopes.push(scopes.top());
						       					 scopes.top().add_iterator((yyvsp[(2) - (7)].str)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 258 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_ConstraintLoop((yyvsp[(2) - (11)].str), *(yyvsp[(4) - (11)].expression), *(yyvsp[(6) - (11)].expression), *(yyvsp[(9) - (11)].constraints)); 
						                          scopes.pop();
		                                          free((yyvsp[(2) - (11)].str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 263 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_OneConstraint(*(yyvsp[(1) - (3)].expression),EQ,*(yyvsp[(3) - (3)].expression)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 264 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_OneConstraint(*(yyvsp[(1) - (3)].expression),LEQ,*(yyvsp[(3) - (3)].expression)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 265 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_OneConstraint(*(yyvsp[(1) - (3)].expression),GEQ,*(yyvsp[(3) - (3)].expression)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 266 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_OneConstraint(*(yyvsp[(1) - (3)].expression),LT,*(yyvsp[(3) - (3)].expression)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 267 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = new P_OneConstraint(*(yyvsp[(1) - (3)].expression),GT,*(yyvsp[(3) - (3)].expression)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 268 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.constraint) = (yyvsp[(2) - (3)].constraint); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 275 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &(*(yyvsp[(1) - (3)].expression) + *(yyvsp[(3) - (3)].expression));    } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 276 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &(*(yyvsp[(1) - (3)].expression) * *(yyvsp[(3) - (3)].expression));    } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 277 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &(*(yyvsp[(1) - (3)].expression) - *(yyvsp[(3) - (3)].expression));    } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 278 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &(*(yyvsp[(1) - (3)].expression) / *(yyvsp[(3) - (3)].expression));    } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 279 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &max(*(yyvsp[(3) - (6)].expression),*(yyvsp[(5) - (6)].expression));   } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 280 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &min(*(yyvsp[(3) - (6)].expression),*(yyvsp[(5) - (6)].expression));   } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 281 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &atan2(*(yyvsp[(3) - (6)].expression),*(yyvsp[(5) - (6)].expression)); } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 282 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &(-*(yyvsp[(2) - (2)].expression));         } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 283 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &abs  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 284 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &sign (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 285 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &transpose(*(yyvsp[(1) - (2)].expression)); } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 286 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &sqrt (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 287 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &exp  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 288 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &log  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 289 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &cos  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 290 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &sin  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 291 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &tan  (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 292 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &acos (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 293 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &asin (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 294 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &atan (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 295 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &cosh (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 296 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &sinh (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 297 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &tanh (*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 298 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &acosh(*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 299 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &asinh(*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 300 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { try { (yyval.expression) = &atanh(*(yyvsp[(3) - (4)].expression));     } catch(DimException& e) { ibexerror(e.message()); } }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 301 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = (yyvsp[(2) - (2)].expression); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 302 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 303 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_(ball(_2domain(*(yyvsp[(2) - (5)].expression)),_2dbl(*(yyvsp[(4) - (5)].expression)))); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 304 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new P_ExprPower(*(yyvsp[(1) - (3)].expression), *(yyvsp[(3) - (3)].expression)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 305 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new P_ExprIndex(*(yyvsp[(1) - (4)].expression),*(yyvsp[(3) - (4)].expression), false); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 306 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new P_ExprIndex(*(yyvsp[(1) - (4)].expression),*(yyvsp[(3) - (4)].expression), true); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 307 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new P_ExprIndex(*new P_ExprIndex(*(yyvsp[(1) - (6)].expression),*(yyvsp[(3) - (6)].expression), true),*(yyvsp[(5) - (6)].expression), true); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 309 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new P_ExprIndex(*new P_ExprIndex(*new P_ExprIndex(*(yyvsp[(1) - (8)].expression),*(yyvsp[(3) - (8)].expression), true),*(yyvsp[(5) - (8)].expression), true), *(yyvsp[(7) - (8)].expression), true); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 310 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprVector::new_(Array<const ExprNode>(*(yyvsp[(2) - (3)].expressions)),true); delete (yyvsp[(2) - (3)].expressions); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 311 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprVector::new_(Array<const ExprNode>(*(yyvsp[(2) - (3)].expressions)),false); delete (yyvsp[(2) - (3)].expressions); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 312 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &scopes.top().get_entity((yyvsp[(1) - (1)].str)).symbol; free((yyvsp[(1) - (1)].str)); /* cannot happen inside a function expr */}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 313 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &source.vars[(yyvsp[(2) - (3)].itg)]->symbol;                      /* CHOCO variable symbols */ }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 314 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new ExprIter((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 315 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &scopes.top().get_func_input_symbol((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 316 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &scopes.top().get_func_tmp_expr((yyvsp[(1) - (1)].str)); free((yyvsp[(1) - (1)].str)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 317 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { /*$$ = &ExprConstant::new_(scopes.top().get_cst($1));*/
              									  (yyval.expression) = new ExprConstantRef(scopes.top().get_cst((yyvsp[(1) - (1)].str)));
              									  free((yyvsp[(1) - (1)].str)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 320 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &apply(scopes.top().get_func((yyvsp[(1) - (4)].str)), *(yyvsp[(3) - (4)].expression)); free((yyvsp[(1) - (4)].str)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 321 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &apply(scopes.top().get_func((yyvsp[(1) - (4)].str)), *(yyvsp[(3) - (4)].expressions)); free((yyvsp[(1) - (4)].str)); delete (yyvsp[(3) - (4)].expressions); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 322 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { ibexerror("unknown symbol"); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 323 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar((yyvsp[(1) - (1)].real)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 324 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = new ExprInfinity(); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 325 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar((double) (yyvsp[(1) - (1)].itg)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 326 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar(*(yyvsp[(1) - (1)].itv)); delete (yyvsp[(1) - (1)].itv); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 327 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar(_2domain(*(yyvsp[(3) - (4)].expression)).i().lb()); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 328 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar(_2domain(*(yyvsp[(3) - (4)].expression)).i().ub()); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 329 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expression) = &ExprConstant::new_scalar(_2domain(*(yyvsp[(3) - (4)].expression)).i().mid()); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 332 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (3)].expressions)->push_back((yyvsp[(3) - (3)].expression)); (yyval.expressions)=(yyvsp[(1) - (3)].expressions); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 333 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expressions) = new vector<const ExprNode*>(); 
                                                  (yyval.expressions)->push_back((yyvsp[(1) - (3)].expression)); (yyval.expressions)->push_back((yyvsp[(3) - (3)].expression)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 337 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyvsp[(1) - (3)].expressions)->push_back((yyvsp[(3) - (3)].expression)); (yyval.expressions)=(yyvsp[(1) - (3)].expressions); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 338 "/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/IBEX2.0/ibex-2.0.4/src/parser/parser.yc"
    { (yyval.expressions) = new vector<const ExprNode*>(); 
                                                  (yyval.expressions)->push_back((yyvsp[(1) - (3)].expression)); (yyval.expressions)->push_back((yyvsp[(3) - (3)].expression)); }
    break;



/* Line 1806 of yacc.c  */
#line 2519 "parser.tab.cc"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



