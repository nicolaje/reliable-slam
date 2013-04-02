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
 * CVS: $Id: gaol_double_op_fast.h,v 1.7 2007/09/12 12:41:57 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_double_op_fast.h
  \brief  Operations correctly rounded down and up.

  Fast version using standard arithmetic operations

  \author Frédéric Goualard
  \date   2006-02-21
*/


#ifndef __gaol_double_op_fast_h__
#define __gaol_double_op_fast_h__

#include <cmath>
#include "gaol/gaol_config.h"
#include "gaol/gaol_mathlib.h"
#include "gaol/gaol_port.h"
#include "gaol/gaol_fpu.h"
#include "gaol/gaol_assert.h"
#include "gaol/gaol_common.h"

namespace gaol {

  INLINE double previous_float(double d)
  {
    return nextafter(d,-GAOL_INFINITY);
  }

  INLINE double next_float(double d)
  {
    return nextafter(d,GAOL_INFINITY);
  }

  // Returns -a while fooling the compiler to avoid bad optimization
  /*  INLINE double opposite_(double a)
  {
    GAOL_RND_ENTER();
    
    union { 
      unsigned int i[2];
      double d;
    } res;
    res.d = a;
    res.i[1] = ((~res.i[1]) & 0x80000000) | (res.i[1] & 0x7fffffff);
    
    GAOL_RND_LEAVE();
    return res.d;
  }
  */

  /*
    Computes d^n rounded upward with a binary exponentiation algorithm
    \warning "d" and "n" should be positive
   */

  INLINE double ipow_up(double d, unsigned int n) 
  {
    GAOL_RND_ENTER();
    GAOL_ASSERT(d >= 0.0);

    double y = 1;
    double z = d;

    for (;;) {
      if (odd(n)) {
	n >>= 1;
	y *= z;
	if (n == 0) {
	  GAOL_RND_LEAVE();
	  return double(y);
	}
      } else {
	n>>=1;
      }
      z *= z;
    }
  }

  /*
    Computes d^n rounded downward with a binary exponentiation algorithm
    \warning "d" and "n" should be positive
   */
  INLINE double ipow_dn(double d, unsigned int n) 
  {
    GAOL_RND_ENTER();

    GAOL_ASSERT(d >= 0.0);

    double y = 1;
    double z = d;

    for (;;) {
      if (odd(n)) {
	n >>= 1;
	y = opposite(opposite(y)*z);
	if (n == 0) {
	  GAOL_RND_LEAVE();
	  return y;
	}
      } else {
	n>>=1;
      }
      z = opposite(opposite(z)*z);
    }
  }

  /*!
    \brief pow() correctly rounded down
    
  */
  INLINE double pow_dn(double d, unsigned int e)
    {
      if (d >= 0) {
	return ipow_dn(d,e);
      } else { // d < 0
	if (even(e)) {
	  return ipow_dn(opposite(d),e);
	} else { // odd(e)
	  return opposite(ipow_up(opposite(d),e));
	}
      }
    }

  /*!
    \brief pow() correctly rounded up

  */
   INLINE double pow_up(double d, unsigned int e)
    {
      if (d >= 0) {
	return ipow_up(d,e);
      } else { // d < 0
	if (even(e)) {
	  return ipow_up(opposite(d),e);
	} else { // odd(e)
	  return opposite(ipow_dn(opposite(d),e));
	}
      }
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
    GAOL_RND_ENTER();
    round_nearest();
    double f=previous_float(d_atan(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double atan_up(double d)
  {
    GAOL_RND_ENTER();
    round_nearest();
    double f=next_float(d_atan(d));
    GAOL_RND_LEAVE();
    return f;
  }

  INLINE double cosh_dn(double x)
  {
    double a1 = exp_dn(x);
    double a2 = exp_up(-x);
    return opposite(opposite(a1)/2.0-a2/2.0);
  }
  
  INLINE double cosh_up(double x)
  {
    double a1 = exp_dn(x);
    double a2 = exp_up(-x);
    return a1/2.0+a2/2.0;
  }

  
} // namespace gaol

#endif /* __gaol_double_op_fast_h__ */
