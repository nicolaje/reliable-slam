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
 * CVS: $Id: gaol_config.h,v 1.16 2007/09/12 12:41:57 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_config.h
  \brief  Configuration file

  This file contains the declarations of all the macros used to control the
  way gaol is compiled, depending on the host. It acts as a front-end for
  the configuration file created by configure and the one used when 
  compiling gaol with Borland C++ Builder.
  

  \author Frederic Goualard
  \date   2002-12-03
*/

#ifndef __gaol_config_h__
#define __gaol_config_h__

#if defined (_MSC_VER)

# define GAOL_ERRNO errno
# ifndef _GAOL_DLL_
#   ifdef _COMPILING_GAOL_DLL_
#     define _GAOL_DLL_ __declspec(dllexport)
#   else
#     define _GAOL_DLL_ __declspec(dllimport)
#   endif
# endif
# define INLINE inline
# include "gaol/gaol_config_msvc.h"

#elif defined (__MINGW32__)

# define GAOL_ERRNO errno
# undef PACKAGE
# undef VERSION
# include "gaol/gaol_config_mingw.h"
# ifndef _GAOL_DLL_
#  if defined (HAVE_VISIBILITY_OPTIONS)
#     define _GAOL_DLL_ __attribute__ ((visibility("default")))
#  else
#     define _GAOL_DLL_ 
#  endif
# endif
# define INLINE inline

#elif defined (__GNUC__)
# define GAOL_ERRNO errno
# undef PACKAGE
# undef VERSION
# include "gaol/gaol_configuration.h"
# ifndef _GAOL_DLL_
#  if defined (HAVE_VISIBILITY_OPTIONS)
#     define _GAOL_DLL_ __attribute__ ((visibility("default")))
#  else
#     define _GAOL_DLL_ 
#  endif
# endif
# define INLINE inline

#else

# define GAOL_ERRNO errno
# undef PACKAGE
# undef VERSION
# ifndef _GAOL_DLL_
#  define _GAOL_DLL_
# endif
# define INLINE inline
# include "gaol/gaol_configuration.h"
#endif

#endif /* __gaol_config_h__ */
