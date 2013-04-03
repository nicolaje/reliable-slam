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
 * CVS: $Id: gaol_interval_generic.h,v 1.7 2006/09/12 07:54:40 goualard Exp $
 * Last modified: Wed May 24 10:35:27 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_interval_generic.h
  \brief  Non-portable part of the interval methods. Generic version in C.

  <long description>

  \warning This version can only be used if the underlying architecture
  uses 64 bits-long floating-point registers.

  \author Frédéric Goualard
  \date   2001-11-12
*/


#ifndef __gaol_interval_generic_h__
#define __gaol_interval_generic_h__

INLINE interval& interval::operator+=(const interval& I)
  {
    GAOL_RND_ENTER();
    lb_  = -((-left())-I.left());
    rb_ += I.right();
    GAOL_RND_LEAVE();
    return *this;
  }
  
INLINE interval& interval::operator-=(const interval& I)
  {
    GAOL_RND_ENTER();
    lb_  = -(I.right()-left());
    rb_ -= I.left();
    GAOL_RND_LEAVE();
    return *this;
  }

INLINE interval& interval::operator+=(double d)
  {
    GAOL_RND_ENTER();
    lb_  = -((-left())-d);
    rb_ += d; 
    GAOL_RND_LEAVE();
    return *this;
  }

INLINE interval& interval::operator-=(double d)
  {
    GAOL_RND_ENTER();
    lb_  = -(d-left());
    rb_ -= d;
    GAOL_RND_LEAVE();
    return *this;
  }



#endif /* __gaol_interval_generic_h__ */
