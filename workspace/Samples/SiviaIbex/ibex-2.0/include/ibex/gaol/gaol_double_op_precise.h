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
 * CVS: $Id: gaol_double_op_precise.h,v 1.6 2007/09/12 12:41:57 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_double_op_precise.h
  \brief  Operations correctly rounded down and up.

  Accurate version using APmathlib

  \author Frédéric Goualard
  \date   2006-02-21
*/


#ifndef __gaol_double_op_precise_h__
#define __gaol_double_op_precise_h__

#include <cmath>
#include "gaol/gaol_mathlib.h"
#include "gaol/gaol_port.h"
#include "gaol/gaol_config.h"
#include "gaol/gaol_fpu.h"

namespace gaol {

  INLINE double previous_float(double d)
  {
    return nextafter(d,-GAOL_INFINITY);
  }

  INLINE double next_float(double d)
  {
    return nextafter(d,GAOL_INFINITY);
  }

  /*!
    \brief pow() correctly rounded down
    
    Assumes a correctly rounded pow(double) when rounding direction
    is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
  INLINE double pow_dn(double d, unsigned int e)
    {
      GAOL_RND_ENTER();
      round_nearest();
      double f=previous_float(d_pow(d,e));
      GAOL_RND_LEAVE();
      return f;
    }

  /*!
    \brief pow() correctly rounded up

    Assumes a correctly rounded pow(double) when rounding direction
    is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
   INLINE double pow_up(double d, unsigned int e)
    {
      GAOL_RND_ENTER();
      round_nearest();
      double f=next_float(d_pow(d,e));
      GAOL_RND_LEAVE();
      return f;
    }

  /*!
    \brief nthroot() correctly rounded down
    
    Assumes a correctly rounded pow(double) when rounding direction
    is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
  INLINE double nthroot_dn(double d, double e)
    {
      GAOL_RND_ENTER();
      round_nearest();
      double f=previous_float(d_pow(d,e));
      GAOL_RND_LEAVE();
      return f;
    }

  /*!
    \brief nthroot() correctly rounded up

    Assumes a correctly rounded pow(double) when rounding direction
    is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
   INLINE double nthroot_up(double d, double e)
    {
      GAOL_RND_ENTER();
      round_nearest();
      double f=next_float(d_pow(d,e));
      GAOL_RND_LEAVE();
      return f;
    }


  /*!
    \brief Exponential correctly rounded downward

    Assumes a correctly rounded function exp(double) when rounding
    direction is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
  INLINE double exp_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_exp(d));
    GAOL_RND_LEAVE();
    return f;
  }

  /*!
    \brief Exponential correctly rounded upward

    Assumes a correctly rounded function exp(double) when rounding
    direction is to nearest (such as ensured by the IBM math library).
    \caution The current rounding direction must be to nearest.
  */
  INLINE double exp_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_exp(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double cos_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_cos(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double cos_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_cos(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double tan_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_tan(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double tan_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_tan(d));
    GAOL_RND_LEAVE();
    return f;
  }

   INLINE double log_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_log(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double log_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_log(d));
    GAOL_RND_LEAVE();
    return f;
  }


  INLINE double acos_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_acos(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double acos_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_acos(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double asin_dn(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_asin(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double asin_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_asin(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double atan_dn(double d)
  {
    GAOL_RND_LEAVE();
    round_nearest();
    double f=previous_float(d_atan(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double atan_up(double d)
  {
    GAOL_RND_LEAVE();
    round_nearest();
    double f=next_float(d_atan(d));
    GAOL_RND_LEAVE();
    return f;
  }

} // namespace gaol

#endif /* __gaol_double_op_precise_h__ */
