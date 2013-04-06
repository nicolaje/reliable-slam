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
 * CVS: $Id: gaol_fpu_sparc.h,v 1.6 2006/03/22 08:35:14 goualard Exp $
 * Last modified: Wed Mar 15 14:42:12 2006 on pc-dubreil-123.irin.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu_sparc.h
  \brief  

  <long description>

  \author Frédéric Goualard
  \date   2001-10-04
*/


#ifndef __gaol_fpu_sparc_h__
#define __gaol_fpu_sparc_h__

namespace gaol {

  /*!
    \brief Returns the opposite of the argument
    
    This macro is used to avoid the optimization if the negation required
    for trust rounding.
   */
  INLINE double f_negate(double x)
  {
    asm volatile ("ldd %1, %%f0; fnegs %%f0, %%f0; std %%f0, %0"
		  : "=m" (x) : "m" (x));				
    return x;
  }

  inline  void
  round_downward(void)
  {
    int cw;
    asm  ("st %%fsr,%0" : "=m" (*&cw));
    cw = (cw & 0x3fffffff) | 0xC0000000;
    asm  ("ld %0,%%fsr" : : "m" (*&cw));
  }

inline  void 
round_upward(void)  
{
  int cw;
  asm  ("st %%fsr,%0" : "=m" (*&cw));
  cw = (cw & 0x3fffffff) | 0x80000000;
  asm  ("ld %0,%%fsr" : : "m" (*&cw));
}

inline  void 
round_nearest(void)  
{
  int cw;
  asm  ("st %%fsr,%0" : "=m" (*&cw));
  cw = (cw & 0x3fffffff);  
  asm  ("ld %0,%%fsr" : : "m" (*&cw));
}

} // namespace gaol

#endif /* __gaol_fpu_sparc_h__ */
