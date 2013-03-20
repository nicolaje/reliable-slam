/*-*-C++-*------------------------------------------------------------------
 * gaol -- NOT Just Another Interval Library
 *--------------------------------------------------------------------------
 * This file is part of the gaol distribution. Gaol was primarily 
 * developed at the Swiss Federal Institute of Technology, Lausanne, 
 * Switzerland, and is now developed at the Laboratoire d'Informatique de 
 * Nantes-Atlantique, France.
 *
 * Copyright (c) 2001 Swiss Federal Institute of Technology, Switzerland
 * Copyright (c) 2002-2006 Laboratoire d'Informatique de 
 *                         Nantes-Atlantique, France
 *--------------------------------------------------------------------------
 * gaol is a software distributed WITHOUT ANY WARRANTY. Read the associated 
 * COPYING file for information.
 *--------------------------------------------------------------------------
 * CVS: $Id: gaol_mathlib.h,v 1.7 2007/09/12 12:41:58 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_mathlib.h
  \brief  Interface of any mathematical library to gaol

  \author Frederic Goualard
  \date   2002-08-21
*/


#ifndef __gaol_mathlib_h__
#define __gaol_mathlib_h__

#include "gaol/gaol_config.h"

#if GAOL_USING_APMATHLIB
#  include "gaol/gaol_apmathlib.h"
#  define d_asin uasin
#  define d_acos uacos
#  define d_atan uatan
#  define d_log  ulog
#  define d_exp  uexp
#  define d_sin  usin
#  define d_cos  ucos
#  define d_tan  utan
#  define d_sqrt usqrt
#  define d_pow  upow

#else // !GAOL_USING_APMATHLIB
#  include <math.h>
#  define d_asin asin
#  define d_acos acos
#  define d_atan atan
#  define d_log  log
#  define d_exp  exp
#  define d_sin  sin
#  define d_cos  cos
#  define d_tan  tan
#  define d_sqrt sqrt
#  define d_pow  pow
#endif // GAOL_USING_APMATHLIB

#endif /* __gaol_mathlib_h__ */
