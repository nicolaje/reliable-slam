/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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




/* Line 2068 of yacc.c  */
#line 131 "parser.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE ibexlval;


