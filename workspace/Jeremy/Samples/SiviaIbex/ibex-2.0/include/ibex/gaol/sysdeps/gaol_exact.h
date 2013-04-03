/*-*-C-*--------------------------------------------------------------------
 * gaol -- a light and fast C++ interval library
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
 * CVS: $Id: gaol_exact.h,v 1.2 2006/02/17 15:47:22 goualard Exp $
 * Last modified: Fri Feb 17 10:52:34 2006 on pc-dubreil-123.irin.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_exact.h
  \brief  Functions needed by dtoa.c to report inexact translation from
  ASCII to double by gay_strtod().

  \note This is C code, not C++. Moreover, it is not meant to be included in
  any namespace.

  \author Frederic Goualard
  \date   2002-04-15
*/


#ifndef __gaol_exact_h__
#define __gaol_exact_h__

// To overcome problems with old versions of autoconf
#undef PACKAGE
#include "gaol/gaol_config.h"


/*!
  \brief Returns a non-zero value if the inexact bit is already set
*/
int get_inexact()
{
  int res_exact;
#if (IX86_LINUX || IX86_CYGWIN)
  asm  ("fstsw %0" : "=m" (*&res_exact));
  return (res_exact & 0x0020);
#elif SPARC_SOLARIS
  int flags;
  asm  ("st %%fsr,%0" : "=m" (*&flags));
  return (flags >> 5) & 0x1f;
#else
#  error "Architecture not yet supported"
#endif
}

/*!
  \brief Set the inexact bit to 0
*/
void clear_inexact()
{
#if (IX86_LINUX || IX86_CYGWIN)
  asm ("fnclex");
#elif SPARC_SOLARIS
  int flags;
  asm  ("st %%fsr,%0" : "=m" (*&flags));
  flags &= 0xfffffc1f;
  asm  ("ld %0,%%fsr" : : "m" (*&flags));
#else
#  error "Architecture not yet supported"
#endif

}

#endif /* __gaol_exact_h__ */
