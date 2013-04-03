/*-*-C++-*------------------------------------------------------------------
 * gaol -- Just Another Interval Library
 *--------------------------------------------------------------------------
 * This file is part of the gaol distribution. Gaol was primarily 
 * developed at the Swiss Federal Institute of Technology, Lausanne, 
 * Switzerland, and is now developed at the Institut de Recherche 
 * en Informatique de Nantes, France.
 *
 * Copyright (c) 2001 Swiss Federal Institute of Technology, Switzerland
 * Copyright (c) 2002 Institut de Recherche en Informatique de Nantes, France
 *--------------------------------------------------------------------------
 * gaol is a software distributed WITHOUT ANY WARRANTY. Read the associated 
 * COPYING file for information.
 *--------------------------------------------------------------------------
 * CVS: $Id: gaol_fpu_ix86.h,v 1.9 2007/09/12 12:41:58 goualard Exp $
 * Last modified: Fri Jun  2 11:03:09 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu_ix86.h
  \brief  

  <long description>

  \author Frédéric Goualard
  \date   2001-10-01
*/


#ifndef __gaol_fpu_ix86_h__
#define __gaol_fpu_ix86_h__

#include "gaol/gaol_config.h"

#if HAVE_FENV_H
#  include <fenv.h>
#else
#  error "No fenv.h header file found"
#endif

static unsigned short int gaol_round_up_      = 0x1A3F;
static unsigned short int gaol_round_down_    = 0x163F;
static unsigned short int gaol_round_near_    = 0x123F;

namespace gaol {

  /*!
    \brief Returns the opposite of the argument
    
    This macro is used to avoid the optimization if the negation is required
    for trust rounding.
   */
  INLINE double f_negate(double x)
  {
    asm volatile ("fldl %1; fchs; fstpl %0" : "=m" (x) : "m" (x));
    return x;
  }

  INLINE  void round_downward(void)
  {
    asm volatile ("fldcw %0" : : "m" (gaol_round_down_));
  }
  
  INLINE  void round_upward(void)
  {
    asm volatile ("fldcw %0" : : "m" (gaol_round_up_));
  }
  
  INLINE  void round_nearest(void)
  {
    asm volatile ("fldcw %0" : : "m" (gaol_round_near_));
  }



  // Return the status word of the FPU
  INLINE unsigned short get_fpu_sw(void)
  {
    static unsigned short int fpuSW = 0;
    asm("fstsw fpuSW");
    return fpuSW;
  }
  

INLINE unsigned short int get_fpu_cw()
{
  fenv_t tmp;
  fegetenv(&tmp);
  return tmp.__control_word;
}

INLINE void reset_fpu_cw(unsigned short int st)
{
  fenv_t tmp;
  fegetenv(&tmp);
  tmp.__control_word = st;
  fesetenv(&tmp);
}  
 
  
} // namespace gaol

#endif /* __gaol_fpu_ix86_h__ */
