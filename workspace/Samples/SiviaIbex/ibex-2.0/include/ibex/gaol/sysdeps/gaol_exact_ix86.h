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
 * CVS: $Id: gaol_exact_ix86.h,v 1.3 2007/09/12 12:41:58 goualard Exp $
 * Last modified: Thu Dec  5 13:04:32 2002 on victory.irin.sciences.univ-nantes.fr
 * By: Frederic Goualard <Frederic.Goualard@irin.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_exact_ix86.h
  \brief  functions get_inexact() and clear_inexact() for ix86/Linux

  <long description>

  \author Frederic Goualard
  \date   2002-12-05
*/


#ifndef __gaol_exact_ix86_h__
#define __gaol_exact_ix86_h__

#if GAOL_USING_ASM
int get_inexact(void)
{
  int res_exact;
  asm  ("fstsw %0" : "=m" (*&res_exact));
  return (res_exact & 0x20);
}


void clear_inexact(void)
{
  asm ("fnclex");
}
#else // !GAOL_USING_ASM
# if HAVE_FENV_H
#  include "sysdeps/gaol_exact_c99.h"
# else // !HAVE_FENV_H
#  error "no C code for inexact for ix86/Linux"
# endif // HAVE_FENV_H
#endif // GAOL_USING_ASM

#endif /* __gaol_exact_ix86_h__ */
