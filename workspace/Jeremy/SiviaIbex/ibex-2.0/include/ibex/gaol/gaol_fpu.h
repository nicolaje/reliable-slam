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
 * CVS: $Id: gaol_fpu.h,v 1.12 2007/09/12 12:41:58 goualard Exp $
 * Last modified: Tue Sep 12 10:26:06 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_fpu.h
  \brief  

  <long description>

  \author Frédéric Goualard
  \date   2001-10-01
*/


#ifndef __gaol_fpu_h__
#define __gaol_fpu_h__

// To overcome problems with old versions of autoconf
#undef PACKAGE
#include "gaol/gaol_config.h"

#if (IX86_LINUX || IX86_CYGWIN)
#  include "gaol/sysdeps/gaol_fpu_ix86.h"
#elif SPARC_SOLARIS
#  include "gaol/sysdeps/gaol_fpu_sparc.h"
#elif defined (_MSC_VER)
#  include "gaol/sysdeps/gaol_fpu_msvc.h"
#elif POWERPC_UNIX
#  include "gaol/sysdeps/gaol_fpu_powerpc.h"
#else
# error "unsupported platform"
#endif

//  Mask 0x0a7f: 53 bits precision, all exceptions masked, rounding to +oo
#define GAOL_FPU_MASK 0x0a7f

#if GAOL_PRESERVE_ROUNDING
/*
  Beware: GAOL_RND_ENTER() should always be called at the very 
  beginning of a function to avoid
  problems with it being expanded to multiple statements.
*/
#  define GAOL_RND_ENTER() unsigned short int _save_state=get_fpu_cw(); reset_fpu_cw(GAOL_FPU_MASK)
#  define GAOL_RND_LEAVE() reset_fpu_cw(_save_state)
#else // !GAOL_PRESERVE_ROUNDING
#  define GAOL_RND_ENTER()
#  define GAOL_RND_LEAVE()
#endif


#endif /* __gaol_fpu_h__ */
