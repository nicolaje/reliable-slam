/*-*-C++-*------------------------------------------------------------------
 * gaol -- a light and fast C++ interval library
 *--------------------------------------------------------------------------
 * This file is part of the gaol distribution. It has been developed at
 * the Institut de Recherche en Informatique de Nantes, France
 * 
 * Copyright (c) 2001-2003 Institut de Recherche en Informatique de Nantes
 *--------------------------------------------------------------------------
 * gaol is a software distributed WITHOUT ANY WARRANTY. Read the associated 
 * COPYING file for information.
 *--------------------------------------------------------------------------
 * CVS: $Id: gaol_fpu_c99.h,v 1.4 2006/09/12 07:54:40 goualard Exp $
 * Last modified: Wed May 24 09:53:42 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu_c99.h
  \brief  

  <long description>

  \author Frédéric Goualard
  \date   2004-01-13
*/


#ifndef __gaol_fpu_c99_h__
#define __gaol_fpu_c99_h__

#include <fenv.h>

namespace gaol {

INLINE  void
round_downward(void)
{  
  fesetround(FE_DOWNWARD);
}

INLINE  void 
round_upward(void)  
{
  fesetround(FE_UPWARD);
}

INLINE  void 
round_nearest(void)  
{
  fesetround(FE_TONEAREST);
}

INLINE unsigned short int save_fpu_cw()
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

#endif /* __gaol_fpu_c99_h__ */
