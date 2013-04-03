/*-*-C++-*------------------------------------------------------------------
 * gaol -- Just Another Interval Library
 *--------------------------------------------------------------------------
 * This file is part of the gaol distribution. It has been developed at
 * the Institut de Recherche en Informatique de Nantes, France
 * 
 * Copyright (c) 2002 Institut de Recherche en Informatique de Nantes
 *--------------------------------------------------------------------------
 * gaol is a software distributed WITHOUT ANY WARRANTY. Read the associated 
 * COPYING file for information.
 *--------------------------------------------------------------------------
 * CVS: $Id: gaol_exact_sparc.h,v 1.2 2002/12/16 16:52:18 exupery Exp $
 * Last modified: Thu Dec  5 13:05:14 2002 on victory.irin.sciences.univ-nantes.fr
 * By: Frederic Goualard <Frederic.Goualard@irin.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_exact_sparc.h
  \brief  functions get_inexact() and clear_inexact() for 
  SUN UltraSparc/Solaris

  <long description>

  \author Frederic Goualard
  \date   2002-12-05
*/


#ifndef __gaol_exact_sparc_h__
#define __gaol_exact_sparc_h__

#if GAOL_USING_ASM
inline int get_inexact(void)
{
  int flags;
  asm  ("st %%fsr,%0" : "=m" (*&flags));
  return (flags >> 5) & 0x1f;
}


inline void clear_inexact(void)
{
  int flags;
  asm  ("st %%fsr,%0" : "=m" (*&flags));
  flags &= 0xfffffc1f;
  asm  ("ld %0,%%fsr" : : "m" (*&flags));
}
#else // !GAOL_USING_ASM
# if HAVE_FENV_H
#  include "sysdeps/gaol_exact_c99.h"
# else // !HAVE_FENV_H
#  error "no C code for inexact for Sparc/Solaris"
# endif // HAVE_FENV_H
#endif // GAOL_USING_ASM

#endif /* __gaol_exact_sparc_h__ */
