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
 * CVS: $Id: gaol_apmathlib.h,v 1.1 2007/09/12 12:48:45 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_apmathlib.h
  \brief  Interface of IBM APMathLib to gaol

  This file allows the C library APMathLib to be called from libraries written
  in C++

  \author Frederic Goualard
  \date   2002-08-21
*/


#ifndef __gaol_apmathlib_h__
#define __gaol_apmathlib_h__

#include "gaol/gaol_config.h"

#if defined (_MSC_VER)
# define _MATHLIB_DLL_ extern "C" __declspec(dllimport)
#elif defined (__GNUC__)
# define _MATHLIB_DLL_ extern "C" __attribute__ ((visibility("default")))
#else
# define _MATHLIB_DLL_ extern "C"
#endif

_MATHLIB_DLL_ unsigned short Init_Lib();
_MATHLIB_DLL_ void Exit_Lib(unsigned short);
_MATHLIB_DLL_ double uasin(double );
_MATHLIB_DLL_ double uacos(double );
_MATHLIB_DLL_ double uatan(double );
_MATHLIB_DLL_ double uatan2(double ,double );
_MATHLIB_DLL_ double ulog(double );
_MATHLIB_DLL_ double ulog2(double );
_MATHLIB_DLL_ double uexp(double );
_MATHLIB_DLL_ double uexp2(double );
_MATHLIB_DLL_ double usin(double );
_MATHLIB_DLL_ double ucos(double );
_MATHLIB_DLL_ double utan(double );
_MATHLIB_DLL_ double ucot(double );
_MATHLIB_DLL_ double usqrt(double );
_MATHLIB_DLL_ double upow(double , double );
_MATHLIB_DLL_ double uremainder(double , double );

#endif /* __gaol_apmathlib_h__ */
