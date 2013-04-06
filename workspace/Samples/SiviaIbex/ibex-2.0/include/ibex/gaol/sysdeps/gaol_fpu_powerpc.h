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
 * CVS: $Id: gaol_fpu_powerpc.h,v 1.4 2006/03/22 08:35:14 goualard Exp $
 * Last modified: Wed Mar 15 14:41:13 2006 on pc-dubreil-123.irin.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu_powerpc.h
  \brief  

  \note This code is experimental. Not tested!


  \author Frédéric Goualard
  \date   2004-01-13
*/


#ifndef __gaol_fpu_powerpc_h__
#define __gaol_fpu_powerpc_h__

INLINE double f_negate(double x)
{
  return -x;
}

#include "gaol/sysdeps/gaol_fpu_c99.h"

#endif /* __gaol_fpu_powerpc_h__ */
