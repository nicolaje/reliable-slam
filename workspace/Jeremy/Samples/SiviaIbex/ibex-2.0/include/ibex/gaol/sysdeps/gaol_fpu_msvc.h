/*-*-C++-*------------------------------------------------------------------
 * gaol -- Just Another Interval Library
 *--------------------------------------------------------------------------
 * This file is part of the gaol distribution. Gaol was primarily 
 * developed at the Swiss Federal Institute of Technology, Lausanne, 
 * Switzerland, and is now developed at the Institut de Recherche 
 * en Informatique de Nantes, France.
 *
 * Copyright (c) 2001 Swiss Federal Institute of Technology, Switzerland
 * Copyright (c) 2002-2006 Laboratoire d'Informatique de Nantes-Atlantique
 *--------------------------------------------------------------------------
 * gaol is a software distributed WITHOUT ANY WARRANTY. Read the associated 
 * COPYING file for information.
 *--------------------------------------------------------------------------
 * CVS: $Id: gaol_fpu_msvc.h,v 1.3 2006/09/12 07:54:40 goualard Exp $
 * Last modified: Wed May 24 09:57:28 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu_msvc.h
  \brief  Rounding control for Microsoft Visual C++


  \author Frédéric Goualard
  \date   2006-03-17
*/


#ifndef __gaol_fpu_msvc_h__
#define __gaol_fpu_msvc_h__

#include <float.h>

// s_nextafter provided by the SUN fdlibm library
extern "C" double s_nextafter(double,double);

namespace gaol {

  /*!
    \brief Returns the opposite of the argument

    This macro is used to avoid the optimization if the negation is required
    for trust rounding.
   */
  INLINE double f_negate(double x)
  {
    __asm { 
      fld x	   
      fchs	   
      fstp x	   
    }
    return x;
  }

  
  INLINE void round_downward(void)
  {
    _control87(MCW_EM|PC_53|RC_DOWN|IC_AFFINE,0xFFFF);
  }

  INLINE void round_upward(void)
  {
    _control87(MCW_EM|PC_53|RC_UP|IC_AFFINE,0xFFFF);
  }

  INLINE void round_nearest(void)
  {
    _control87(MCW_EM|PC_53|RC_NEAR|IC_AFFINE,0xFFFF);
  }

  INLINE double nextafter(double x, double y)
  {
    return s_nextafter(x,y);
  }

  INLINE bool isnan(double a)
  {
    return _isnan(a);
  }

  // Return the control word of the FPU
  INLINE unsigned short get_fpu_cw(void)
  {
    return (unsigned short int)_control87(0,0);
  }

  // Return the status word of the FPU
  INLINE unsigned short get_fpu_sw(void)
  {
    return (unsigned short int)_status87();
  }


  INLINE unsigned short int save_fpu_cw()
  {
    return get_fpu_cw();
  }
  
  INLINE void reset_fpu_cw(unsigned short int st)
  {
    _control87(st,0xFFFFFFFF);
  }


} // namespace gaol

#endif /* __gaol_fpu_msvc_h__ */
