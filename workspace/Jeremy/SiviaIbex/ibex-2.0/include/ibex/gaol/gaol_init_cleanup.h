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
 * CVS: $Id: gaol_init_cleanup.h,v 1.2 2007/09/12 12:41:58 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_init_cleanup.h
  \brief  Initializes and cleans automatically the gaol environment.

  Used to avoid havoc if the user forgets to call explicitly gaol::init() 
  and gaol::cleanup.

  \author Fr�d�ric Goualard
  \date   2005-05-10
*/


#ifndef __gaol_init_cleanup_h__
#define __gaol_init_cleanup_h__

namespace gaol {

  void gaol_init_lib(void);

  void initialization_process(void);
  void cleanup_process(void);
  
} // namespace gaol

#endif /* __gaol_init_cleanup_h__ */
