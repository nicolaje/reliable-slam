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
 * CVS: $Id: gaol_interval_ix86_cpp.h,v 1.24 2007/12/10 20:18:26 goualard Exp $
 * Last modified: Fri Jun  2 10:55:41 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_interval_ix86_cpp.h
  \brief  

  <long description>

  \author Frédéric Goualard
  \date   2001-11-07
*/


#ifndef __gaol_interval_ix86_cpp_h__
#define __gaol_interval_ix86_cpp_h__

#include <math.h>

  interval& interval::operator+=(const interval& I)
  {
    GAOL_RND_ENTER();
    asm volatile ("fldl %2 \n\t"
		  "fchs \n\t"
		  "fsubl %4 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  "fldl %3 \n\t"
		  "faddl %5 \n\t"
		  "fstpl %1 \n\t"
		  : "=m" (lb_), "=m" (rb_)
		  : "m" (lb_), "m" (rb_), 
		  "m" (I.lb_), "m" (I.rb_));
    GAOL_RND_LEAVE();
    return *this;
  }
  
  
  interval& interval::operator-=(const interval& I)
  {
    GAOL_RND_ENTER();
    asm volatile ("fldl %5 \n\t"
		  "fsubl %2 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  "fldl %3 \n\t"
		  "fsubl %4 \n\t"
		  "fstpl %1 \n\t"
		  : "=m" (lb_), "=m" (rb_)
		  : "m" (lb_), "m" (rb_), 
		  "m" (I.lb_), "m" (I.rb_));
    GAOL_RND_LEAVE();
    return *this;
  }

  
  interval& interval::operator+=(double d)
  {
    GAOL_RND_ENTER();
    asm volatile ("fldl %2 \n\t"
		  "fchs \n\t"
		  "fsubl %4 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  "fldl %3 \n\t"
		  "faddl %4 \n\t"
		  "fstpl %1 \n\t"
		  : "=m" (lb_), "=m" (rb_)
		  : "m" (lb_), "m" (rb_), "m" (d));
    GAOL_RND_LEAVE();
    return *this;
  }

  
  interval& interval::operator-=(double d)
  {
    GAOL_RND_ENTER();
    asm volatile ("fldl %2 \n\t"
		  "fchs \n\t"
		  "faddl %4 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  "fldl %3 \n\t"
		  "fsubl %4 \n\t"
		  "fstpl %1 \n\t"
		  : "=m" (lb_), "=m" (rb_)
		  : "m" (lb_), "m" (rb_), 
		  "m" (d));
    GAOL_RND_LEAVE();
    return *this;
  }

  
  interval& interval::operator*=(double d)
  {
    if (is_empty()) {
      *this=interval::emptyset;
      return *this;
    }
    if (d==0.0) {
      *this=interval::zero;
      return *this;
    }

    GAOL_RND_ENTER();
    if (d>0.0) {
      asm volatile ("fldl %2 \n\t"
		    "fchs \n\t"
		    "fmull %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %3 \n\t"
		    "fmull %4 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_), "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
      GAOL_RND_LEAVE();
      return *this;
    } else {
      asm volatile ("fldl %2 \n\t"
		    "fmull %4 \n\t"
		    "fldl %3 \n\t"
		    "fchs \n\t"
		    "fmull %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_), "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
      GAOL_RND_LEAVE();
      return *this;
    }
  }

   
  interval& interval::operator/=(double d)
  {
    if (is_empty()) {
      *this = interval::emptyset;
      return *this;
    }
    if (d == 0.0) {
      *this = interval::emptyset;
      return *this;
    }

    GAOL_RND_ENTER();
    if (d > 0.0) {
      asm volatile ("fldl %2 \n\t"
		    "fchs \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %3 \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_),  "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
      GAOL_RND_LEAVE();
      return *this;
    } else { // d < 0.0
      asm volatile ("fldl %2 \n\t"
		    "fdivl %4 \n\t"
		    "fldl %3 \n\t"
		    "fchs \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_),  "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
      GAOL_RND_LEAVE();
      return *this;
    }
  }

   
  interval& interval::operator%=(double d)
  {
    if (is_empty()) {
      *this = interval::emptyset;
      return *this;
    }

    if (d == 0.0) {
      if (straddles_zero()) {
	*this = interval::universe;
	return *this;
      } else { // this does not contain 0
	*this = interval::emptyset;
	return *this;
      }
    }

    GAOL_RND_ENTER();
    if (d > 0.0) {
      asm volatile ("fldl %2 \n\t"
		    "fchs \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %3 \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_),  "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
      GAOL_RND_LEAVE();
      return *this;
    } else { // d < 0.0
      asm volatile ("fldl %2 \n\t"
		    "fdivl %4 \n\t"
		    "fldl %3 \n\t"
		    "fchs \n\t"
		    "fdivl %4 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (lb_),  "=m" (rb_)
		    : "m" (lb_), "m" (rb_), "m" (d));
     GAOL_RND_LEAVE();
     return *this;
    }
  }


/*!
  \brief Computes a/b rounded downward
*/
inline double div_dn(double a, double b)
{
  GAOL_RND_ENTER();
  static double res;
  asm volatile ("fldl %1 \n\t"
		"fchs \n\t"
		"fdivl %2 \n\t"
		"fstpl %0 \n\t"
		"fldl %0 \n\t"
		"fchs \n\t"
		"fstpl %0 \n\t"
		: "=m" (res)
		: "m" (a), "m" (b));
  GAOL_RND_LEAVE();
  return res;
}

/*!
  \brief Computes 1/a rounded downward
*/
inline double inv_dn(double a)
{
  GAOL_RND_ENTER();
  static double res;
  asm volatile ("fld1 \n\t"
		"fchs \n\t"
		"fdivl %1 \n\t"
		"fstpl %0 \n\t"
		"fldl %0 \n\t"
		"fchs \n\t"
		"fstpl %0 \n\t"
		: "=m" (res)
		: "m" (a));
  GAOL_RND_LEAVE();
  return res;
}


double interval::midpoint() const
{
  if (is_empty()) {
    return NAN;
  }
  if (is_symmetric()) { // Symmetric case handles [-oo, +oo]
    return 0.0;
  }
  if (left() == -GAOL_INFINITY) {
    return -std::numeric_limits<double>::max();
  }
  if (right() == GAOL_INFINITY) {
    return std::numeric_limits<double>::max();
  }
  /*
    Rounding to the nearest is mandatory to avoid problems when the
    intervals is composed of 3 floats and the float in the middle is 
    closer to the left bound than to the right bound (e.g [1-,1+]).
   */
  GAOL_RND_ENTER();
  gaol::round_nearest();
  static double middle;
  asm volatile ("fld1 \n\t"
		"fchs \n\t"
		"fldl %1 \n\t"
		"faddl %2 \n\t"
		"fscale \n\t"
		"fstpl %0 \n\t"
		"ffree %%st; fincstp \n\t" /* popping unused value 1 */
		: "=m" (middle)
		: "m" (lb_), "m" (rb_));
  GAOL_RND_LEAVE();
  return middle;
}

interval interval::mid() const
{
  if (is_empty()) {
    return interval::emptyset;
  }
  if (is_symmetric()) { // symmetric case handles [-oo, +oo]
    return 0.0;
  }
  if (left() == -GAOL_INFINITY) {
    return interval(-std::numeric_limits<double>::max());
  }
  if (right() == GAOL_INFINITY) {
    return interval(std::numeric_limits<double>::max());
  }
  GAOL_RND_ENTER();
  static double mid_left, mid_right;
  asm volatile ("fld1 \n\t"
		"fchs \n\t"
		"fldl %2 \n\t"
		"fchs \n\t"
		"fsubl %3 \n\t"
		"fchs \n\t"
		"fscale \n\t"
		"fstpl %0 \n\t"
		"fldl %2 \n\t"
		"faddl %3 \n\t"
		"fscale \n\t"
		"fstpl %1 \n\t"
		"ffree %%st; fincstp \n\t" /* popping unused value */
		: "=m" (mid_left), "=m" (mid_right)
		: "m" (lb_), "m" (rb_));
  GAOL_RND_LEAVE();
  return interval(mid_left,mid_right);
}
  

  interval& interval::operator*=(const interval& I)
  {
    if (is_empty() || I.is_empty()) {
      *this=interval::emptyset;
      return *this;
    }

    if (is_zero()) {
      return *this;
    }
    if (I.is_zero()) {
      *this=I;
      return *this;
    }

    GAOL_RND_ENTER();
    /* Multiplication -- 
       Algorithm from:
       Interval Arithmetic: from Principles to Implementation
       Timothy J. Hickey, Qun Ju, and Maarten H. van Emden
       J. ACM 48:5, p. 1038--1068, sep. 2001
    */
    if (certainly_positive()) { // P ?
      if (I.certainly_positive()) { // P P
	lb_ *= -I.lb_; lb_=opposite(lb_);
	rb_ *= I.rb_;
      } else {
	if (I.strictly_straddles_zero()) { // P M
	  lb_ = (-rb_) * I.lb_; lb_=opposite(lb_);
	  rb_ *= I.rb_;
	} else { // P N
	  asm volatile ("fldl %5 \n\t"
			"fmull %2 \n\t"
			"fldl %3 \n\t"
			"fchs \n\t"
			"fmull %4 \n\t"
			"fstpl %0 \n\t"
			"fldl %0 \n\t"
			"fchs \n\t"
			"fstpl %0 \n\t"
			"fstpl %1 \n\t"
			: "=m" (lb_), "=m" (rb_)
			: "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	}
      }
    } else {
      if (strictly_straddles_zero()) { // M ?
	if (I.certainly_positive()) { // M P
	  lb_ *= -I.rb_; lb_=opposite(lb_);
	  rb_ *= I.rb_;
	} else {
	  if (I.strictly_straddles_zero()) { // M M
	    double tmp1 = (-lb_)*I.rb_; // beware: we consider -tmp1 now
	    double tmp2 = (-rb_)*I.lb_; // beware: we consider -tmp2 now
	    double tmp3 = lb_*I.lb_;
	    double tmp4 = rb_*I.rb_;
	    if (tmp1 < tmp2) { // i.e. lb_*I.rb_ > rb_*I.lb_
	      lb_ = -tmp2;
	    } else {
	      lb_ = -tmp1;
	    }
	    if (tmp3 > tmp4) {
	      rb_ = tmp3;
	    } else {
	      rb_ = tmp4;
	    }
	  } else { // M N
	    asm volatile ("fldl %3 \n\t"
			  "fchs \n\t"
			  "fldl %2 \n\t"
			  "fmull %4 \n\t"
			  "fstpl %1 \n\t"
			  "fmull %4 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (lb_), "=m" (rb_)
			  : "m" (lb_), "m" (rb_), "m" (I.lb_));
	  }
	}
      } else { // N  (case Z already tested)
	if (I.certainly_positive()) { // N P
	  lb_ *= -I.rb_; lb_=opposite(lb_);
	  rb_ *= I.lb_;
	} else {
	  if (I.strictly_straddles_zero()) { // N M
	    asm volatile ("fldl %4 \n\t"
			  "fmull %2 \n\t"
			  "fstpl %1 \n\t"
			  "fldl %5 \n\t"
			  "fchs \n\t"
			  "fmull %2 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (lb_), "=m" (rb_)
			  : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	  } else { // N N
	    asm volatile ("fldl %2 \n\t"
			  "fmull %4 \n\t"
			  "fldl %3 \n\t"
			  "fchs \n\t"
			  "fmull %5 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  "fstpl %1 \n\t"
			  : "=m" (lb_), "=m" (rb_)
			  : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	  }
	}
      }
    }
    GAOL_RND_LEAVE();
    return *this;
  }

  interval& interval::operator/=(const interval& I)
  {
    if (is_empty() || I.is_empty()) {
      *this = interval::emptyset;
      return *this;
    }

    GAOL_RND_ENTER();
    if (right() < 0.0) { // [this] N1
      if (I.right() < 0.0) { // [I] N1
	asm volatile ("fldl %3 \n\t"
		      "fchs \n\t"
		      "fdivl %4 \n\t"
		      "fldl %2 \n\t"
		      "fdivl %5 \n\t"
		      "fstpl %1 \n\t"
		      "fstpl %0 \n\t" /* Beware: rb_ uses lb_ */
		      "fldl %0 \n\t"
		      "fchs \n\t"
		      "fstpl %0 \n\t"
		      : "=m" (lb_), "=m" (rb_)
		      : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	GAOL_RND_LEAVE();
	return *this; // N1 N1
      } else { // [I] P or Z
	if (I.right() == 0.0) { // [I] N0 or Z
	  if ( I.left() == 0.0) { // [I] Z
	    *this = interval::emptyset; // N1 Z
	    GAOL_RND_LEAVE();
	    return *this;
	  }
	  asm volatile ("fldl %1 \n\t"
			"fchs \n\t"
			"fdivl %2 \n\t"
			"fstpl %0 \n\t"
			"fldl %0 \n\t"
			"fchs \n\t"
			"fstpl %0 \n\t"
			: "=m" (lb_)
			: "m" (rb_), "m" (I.lb_));
	  rb_ = GAOL_INFINITY;
	  GAOL_RND_LEAVE();
	  return *this; // N1 N0
	} else { // [I] P or M
	  if (I.left() < 0.0) { // [I] M
	    *this = interval::universe; // N1 M
	    GAOL_RND_LEAVE();
	    return *this;
	  } else { // [I] P0 or P1
	    if (I.left() == 0.0) { // [I] P0
	      *this = interval(-GAOL_INFINITY,right()/I.right()); // N1 P0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_)
			    : "m" (lb_), "m" (I.lb_));
	      rb_ /= I.right();
	      GAOL_RND_LEAVE();
	      return *this;
	    }
	  }
	}
      }
    } else { // [this] N0, Z, M, or P
      if (right() == 0.0) { // [this] N0 or Z
	if (left() == 0.0) { // [this] Z
	  if (I.left() == 0.0 && I.right() == 0.0) {
	    *this = interval::emptyset; // Z Z
	    GAOL_RND_LEAVE();
	    return *this;
	  } else {
	    *this = interval::zero; // Z (N,M,P)
	    GAOL_RND_LEAVE();
	    return *this;
	  }
	} else { // [this] N0
	  if (I.right() < 0.0) { // [I] N1
	    *this = interval(0.0,left()/I.right()); // N0 N1
	    GAOL_RND_LEAVE();
	    return *this;
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      if (I.left() == 0.0) { // [I] Z
		*this = interval::emptyset; // N0 Z
		GAOL_RND_LEAVE();
		return *this;
	      }
	      *this = interval(0.0,GAOL_INFINITY); // N0 N0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // N0 M
		GAOL_RND_LEAVE();
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval(-GAOL_INFINITY,0.0); // N0 P0
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P1
		  asm volatile ("fldl %1 \n\t"
				"fchs \n\t"
				"fdivl %2 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				: "=m" (lb_)
				: "m" (lb_), "m" (I.lb_));
		  rb_ = 0.0;
		  GAOL_RND_LEAVE();
		  return *this; // N0 P1
		}
	      }
	    }
	  }
	}
      } else { // [this] M, P0, or P1
	if (left() < 0.0) { // [this] M
	  if (I.right() < 0.0) { // [I] N1
	    asm volatile ("fldl %3 \n\t"
			  "fchs \n\t"
			  "fdivl %4 \n\t"
			  "fldl %2 \n\t"
			  "fdivl %4 \n\t"
			  "fstpl %1 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (lb_), "=m" (rb_)
			  : "m" (lb_), "m" (rb_), "m" (I.rb_));

	    GAOL_RND_LEAVE();
	    return *this; // M N1
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      if (I.left() == 0.0) { // [I] Z
		*this = interval::emptyset; // M Z
		GAOL_RND_LEAVE();
		return *this;
	      }
	      *this = interval::universe; // M N0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // M M
		GAOL_RND_LEAVE();
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // M P0
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P1
		  asm volatile ("fldl %2 \n\t"
				"fchs \n\t"
				"fdivl %4 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				"fldl %3 \n\t"
				"fdivl %4 \n\t"
				"fstpl %1 \n\t"
				: "=m" (lb_), "=m" (rb_)
				: "m" (lb_), "m" (rb_), "m" (I.lb_));
		  GAOL_RND_LEAVE();
	
		  return *this; // M P1
		}
	      }
	    }
	  }
	} else { // [this] P0 or P1
	  if (left() == 0.0) { // [this] P0
	    if (I.right() < 0.0) { // [I] N1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_)
			    : "m" (rb_), "m" (I.rb_));
	      rb_ = 0.0;
	      GAOL_RND_LEAVE();
	      return *this; // P0 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P0 Z
		  GAOL_RND_LEAVE();
		  return *this;
		}
		lb_ = -GAOL_INFINITY;
		rb_ = 0.0;
		GAOL_RND_LEAVE();
		return *this; // P0 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P0 M
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    lb_ = 0.0;
		    rb_ = GAOL_INFINITY;
		    GAOL_RND_LEAVE();
		    return *this;
		  } else { // [I] P1
		    *this = interval(0.0,right()/I.left()); // P0 P1
		    GAOL_RND_LEAVE();
		    return *this;
		  }
		}
	      }
	    }
	  } else { // [this] P1
	    if (I.right() < 0.0) { // [I] N1
	      asm volatile ("fldl %3 \n\t"
			    "fchs \n\t"
			    "fdivl %5 \n\t"
			    "fldl %2 \n\t"
			    "fdivl %4 \n\t"
			    "fstpl %1 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_), "=m" (rb_)
			    : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	      
	      GAOL_RND_LEAVE();
	      return *this; // P1 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P1 Z
		  GAOL_RND_LEAVE();
		  return *this;
		}
		rb_ = left()/I.left(); // beware: rb_ uses left()
		lb_ = -GAOL_INFINITY;
		GAOL_RND_LEAVE();
		return *this; // P1 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P1 M
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    asm volatile ("fldl %1 \n\t"
				  "fchs \n\t"
				  "fdivl %2 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  : "=m" (lb_)
				  : "m" (lb_), "m" (I.rb_));
		    rb_ = GAOL_INFINITY;
 		    GAOL_RND_LEAVE();
		    
		    return *this; // P1 P0
		  } else { // [I] P1
		    asm volatile ("fldl %2 \n\t"
				  "fchs \n\t"
				  "fdivl %5 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  "fldl %3 \n\t"
				  "fdivl %4 \n\t"
				  "fstpl %1 \n\t"
				  : "=m" (lb_), "=m" (rb_)
				  : "m" (lb_), "m" (rb_), 
				    "m" (I.lb_), "m" (I.rb_));
		    GAOL_RND_LEAVE();
		    
		    return *this; // P1 P1
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  interval& interval::operator%=(const interval& I)
  {
    if (is_empty() || I.is_empty()) {
      *this = interval::emptyset;
      return *this;
    }

    GAOL_RND_ENTER();
    if (right() < 0.0) { // [this] N1
      if (I.right() < 0.0) { // [I] N1
	asm volatile ("fldl %3 \n\t"
		      "fchs \n\t"
		      "fdivl %4 \n\t"
		      "fldl %2 \n\t"
		      "fdivl %5 \n\t"
		      "fstpl %1 \n\t"
		      "fstpl %0 \n\t"
		      "fldl %0 \n\t"
		      "fchs \n\t"
		      "fstpl %0 \n\t"
		      : "=m" (lb_), "=m" (rb_)
		      : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	GAOL_RND_LEAVE();
	return *this; // N1 N1
      } else { // [I] P or Z
	if (I.right() == 0.0) { // [I] N0 or Z
	  if ( I.left() == 0.0) { // [I] Z
	    *this = interval::emptyset; // N1 Z
	    GAOL_RND_LEAVE();
	    return *this;
	  }
	  asm volatile ("fldl %1 \n\t"
			"fchs \n\t"
			"fdivl %2 \n\t"
			"fstpl %0 \n\t"
			"fldl %0 \n\t"
			"fchs \n\t"
			"fstpl %0 \n\t"
			: "=m" (lb_)
			: "m" (rb_), "m" (I.lb_));
	  rb_ = GAOL_INFINITY;
	  GAOL_RND_LEAVE();
	  return *this; // N1 N0
	} else { // [I] P or M
	  if (I.left() < 0.0) { // [I] M
	    *this = interval::universe; // N1 M
	    GAOL_RND_LEAVE();
	    return *this;
	  } else { // [I] P0 or P1
	    if (I.left() == 0.0) { // [I] P0
	      *this = interval(-GAOL_INFINITY,right()/I.right()); // N1 P0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_)
			    : "m" (lb_), "m" (I.lb_));
	      rb_ /= I.right();
	      GAOL_RND_LEAVE();
	      return *this;
	    }
	  }
	}
      }
    } else { // [this] N0, Z, M, or P
      if (right() == 0.0) { // [this] N0 or Z
	if (left() == 0.0) { // [this] Z
	  if (I.straddles_zero()) {
	    *this = interval::universe; // Z (N0, M, P0)
	    GAOL_RND_LEAVE();
	    return *this;
	  } else {
	    *this = interval::zero; // Z (N1, P1)
	    GAOL_RND_LEAVE();
	    return *this;
	  }
	} else { // [this] N0
	  if (I.right() < 0.0) { // [I] N1
	    *this = interval(0.0,left()/I.right()); // N0 N1
	    GAOL_RND_LEAVE();
	    return *this;
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      if (I.left() == 0.0) { // [I] Z
		*this = interval::universe; // N0 Z
		GAOL_RND_LEAVE();
		return *this;
	      }
	      *this = interval::universe; // N0 N0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // N0 M
		GAOL_RND_LEAVE();
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // N0 P0
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P1
		  asm volatile ("fldl %1 \n\t"
				"fchs \n\t"
				"fdivl %2 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				: "=m" (lb_)
				: "m" (lb_), "m" (I.lb_));
		  rb_ = 0.0;
		  GAOL_RND_LEAVE();
		  return *this; // N0 P1
		}
	      }
	    }
	  }
	}
      } else { // [this] M, P0, or P1
	if (left() < 0.0) { // [this] M
	  if (I.right() < 0.0) { // [I] N1
	    asm volatile ("fldl %3 \n\t"
			  "fchs \n\t"
			  "fdivl %4 \n\t"
			  "fldl %2 \n\t"
			  "fdivl %4 \n\t"
			  "fstpl %1 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (lb_), "=m" (rb_)
			  : "m" (lb_), "m" (rb_), "m" (I.rb_));

	    GAOL_RND_LEAVE();
	    return *this; // M N1
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      *this = interval::universe; // M N0
	      GAOL_RND_LEAVE();
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // M M
		GAOL_RND_LEAVE();
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // M P0
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P1
		  asm volatile ("fldl %2 \n\t"
				"fchs \n\t"
				"fdivl %4 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				"fldl %3 \n\t"
				"fdivl %4 \n\t"
				"fstpl %1 \n\t"
				: "=m" (lb_), "=m" (rb_)
				: "m" (lb_), "m" (rb_), "m" (I.lb_));
		  
		  GAOL_RND_LEAVE();
		  return *this; // M P1
		}
	      }
	    }
	  }
	} else { // [this] P0 or P1
	  if (left() == 0.0) { // [this] P0
	    if (I.right() < 0.0) { // [I] N1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_)
			    : "m" (rb_), "m" (I.rb_));
	      rb_ = 0.0;
	      GAOL_RND_LEAVE();
	      return *this; // P0 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		*this = interval::universe; // P0 Z
		GAOL_RND_LEAVE();
		return *this; // P0 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P0 M
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    *this = interval::universe;
		    GAOL_RND_LEAVE();
		    return *this;
		  } else { // [I] P1
		    *this = interval(0.0,right()/I.left()); // P0 P1
		    GAOL_RND_LEAVE();
		    return *this;
		  }
		}
	      }
	    }
	  } else { // [this] P1
	    if (I.right() < 0.0) { // [I] N1
	      asm volatile ("fldl %3 \n\t"
			    "fchs \n\t"
			    "fdivl %5 \n\t"
			    "fldl %2 \n\t"
			    "fdivl %4 \n\t"
			    "fstpl %1 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (lb_), "=m" (rb_)
			    : "m" (lb_), "m" (rb_), "m" (I.lb_), "m" (I.rb_));
	      
	      GAOL_RND_LEAVE();
	      return *this; // P1 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P1 Z
		  GAOL_RND_LEAVE();
		  return *this;
		}
		rb_ = left()/I.left(); // beware: rb_ uses lb_
		lb_ = -GAOL_INFINITY;
		GAOL_RND_LEAVE();
		return *this; // P1 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P1 M
		  GAOL_RND_LEAVE();
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    asm volatile ("fldl %1 \n\t"
				  "fchs \n\t"
				  "fdivl %2 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  : "=m" (lb_)
				  : "m" (lb_), "m" (I.rb_));
		    rb_ = GAOL_INFINITY;
   
		    GAOL_RND_LEAVE();
		    return *this; // P1 P0
		  } else { // [I] P1
		    asm volatile ("fldl %2 \n\t"
				  "fchs \n\t"
				  "fdivl %5 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  "fldl %3 \n\t"
				  "fdivl %4 \n\t"
				  "fstpl %1 \n\t"
				  : "=m" (lb_), "=m" (rb_)
				  : "m" (lb_), "m" (rb_), 
				    "m" (I.lb_), "m" (I.rb_));
		    
		    GAOL_RND_LEAVE();
		    return *this; // P1 P1
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  interval div_rel(const interval &K, const interval &J, const interval &I)
  {
    static interval tmp;
    if (K.is_empty() || J.is_empty() || I.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    if (K.right() < 0.0) { // [this] N1
      if (J.right() < 0.0) { // [J] N1
	// I & [K.r/J.l, K.l/J.r]
	asm volatile ("fldl %3 \n\t"
		      "fchs \n\t"
		      "fdivl %4 \n\t"
		      "fldl %2 \n\t"
		      "fdivl %5 \n\t"
		      "fstpl %1 \n\t"
		      "fstpl %0 \n\t"
		      "fldl %0 \n\t"
		      "fchs \n\t"
		      "fstpl %0 \n\t"
		      : "=m" (tmp.lb_), "=m" (tmp.rb_)
		      : "m" (K.lb_), "m" (K.rb_), "m" (J.lb_), "m" (J.rb_));
	GAOL_RND_LEAVE();
	return I & tmp; // N1 N1
      } else { // [J] P or Z
	if (J.right() == 0.0) { // [J] N0 or Z
	  if (J.left() == 0.0) { // [J] Z
	    GAOL_RND_LEAVE();
	    return interval::emptyset; // N1 Z
	  }
	  // I & [K.r/J.l,+oo]
	  asm volatile ("fldl %1 \n\t"
			"fchs \n\t"
			"fdivl %2 \n\t"
			"fstpl %0 \n\t"
			"fldl %0 \n\t"
			"fchs \n\t"
			"fstpl %0 \n\t"
			: "=m" (tmp.lb_)
			: "m" (K.rb_), "m" (J.lb_));
	  tmp.rb_ = GAOL_INFINITY;
	  GAOL_RND_LEAVE();
	  return I & tmp; // N1 N0
	} else { // [I] P or M
	  if (J.left() < 0.0) { // [J] M
	    asm volatile ("fldl %1 \n\t"
			  "fchs \n\t"
			  "fdivl %2 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (tmp.lb_)
			  : "m" (K.rb_), "m" (J.lb_));
	    interval tmp2 = (I & interval(-GAOL_INFINITY,K.right()/J.right())) |
	      (I & interval(tmp.lb_,GAOL_INFINITY));
	    GAOL_RND_LEAVE();
	    return tmp2;
	  } else { // [J] P0 or P1
	    if (J.left() == 0.0) { // [J] P0
	      interval tmp2 = I & interval(-GAOL_INFINITY,K.right()/J.right()); // N1 P0
	      GAOL_RND_LEAVE();
			return tmp2;
	    } else { // [J] P1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (tmp.lb_)
			    : "m" (K.lb_), "m" (J.lb_));
	      tmp.rb_ = K.right() / J.right();
	      GAOL_RND_LEAVE();
	      return I & tmp;
	    }
	  }
	}
      }
    } else { // [this] N0, Z, M, or P
      if (K.right() == 0.0) { // [this] N0 or Z
	if (K.left() == 0.0) { // [this] Z
	  if (J.straddles_zero()) {
	    GAOL_RND_LEAVE();
	    return I; // Z (N0, M, P0)
	  } else {
	    GAOL_RND_LEAVE();
	    return I & interval::zero; // Z (N1, P1)
	  }
	} else { // [this] N0
	  if (J.right() < 0.0) { // [J] N1
	    interval tmp2 = I & interval(0.0,K.left()/J.right()); // N0 N1
	    GAOL_RND_LEAVE();
	    return tmp2;
	  } else { // [J] P or Z
	    if (J.right() == 0.0) { // [J] N0 or Z
	      if (J.left() == 0.0) { // [J] Z
		GAOL_RND_LEAVE();
		return I; // N0 Z
	      }
	      GAOL_RND_LEAVE();
	      return I; // N0 N0
	    } else { // [J] P or M
	      if (J.left() < 0.0) { // [J] M
		GAOL_RND_LEAVE();
		return I; // N0 M
	      } else { // [J] P0 or P1
		if (J.left() == 0.0) { // [J] P0
		  GAOL_RND_LEAVE();
		  return I; // N0 P0
		} else { // [J] P1
		  asm volatile ("fldl %1 \n\t"
				"fchs \n\t"
				"fdivl %2 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				: "=m" (tmp.lb_)
				: "m" (K.lb_), "m" (J.lb_));
		  tmp.rb_ = 0.0;
		  GAOL_RND_LEAVE();
		  return I & tmp; // N0 P1
		}
	      }
	    }
	  }
	}
      } else { // [this] M, P0, or P1
	if (K.left() < 0.0) { // [this] M
	  if (J.right() < 0.0) { // [J] N1
	    asm volatile ("fldl %3 \n\t"
			  "fchs \n\t"
			  "fdivl %4 \n\t"
			  "fldl %2 \n\t"
			  "fdivl %4 \n\t"
			  "fstpl %1 \n\t"
			  "fstpl %0 \n\t"
			  "fldl %0 \n\t"
			  "fchs \n\t"
			  "fstpl %0 \n\t"
			  : "=m" (tmp.lb_), "=m" (tmp.rb_)
			  : "m" (K.lb_), "m" (K.rb_), "m" (J.rb_));

	    GAOL_RND_LEAVE();
	    return I & tmp; // M N1
	  } else { // [J] P or Z
	    if (J.right() == 0.0) { // [J] N0 or Z
	      GAOL_RND_LEAVE();
	      return I; // M N0
	    } else { // [J] P or M
	      if (J.left() < 0.0) { // [J] M
		GAOL_RND_LEAVE();
		return I; // M M
	      } else { // [J] P0 or P1
		if (J.left() == 0.0) { // [J] P0
		  GAOL_RND_LEAVE();
		  return I; // M P0
		} else { // [J] P1
		  asm volatile ("fldl %2 \n\t"
				"fchs \n\t"
				"fdivl %4 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				"fldl %3 \n\t"
				"fdivl %4 \n\t"
				"fstpl %1 \n\t"
				: "=m" (tmp.lb_), "=m" (tmp.rb_)
				: "m" (K.lb_), "m" (K.rb_), "m" (J.lb_));
		  
		  GAOL_RND_LEAVE();
		  return I & tmp; // M P1
		}
	      }
	    }
	  }
	} else { // [this] P0 or P1
	  if (K.left() == 0.0) { // [this] P0
	    if (J.right() < 0.0) { // [J] N1
	      asm volatile ("fldl %1 \n\t"
			    "fchs \n\t"
			    "fdivl %2 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (tmp.lb_)
			    : "m" (K.rb_), "m" (J.rb_));
	      tmp.rb_ = 0.0;
	      GAOL_RND_LEAVE();
	      return I & tmp; // P0 N1
	    } else { // [J] P or Z
	      if (J.right() == 0.0) { // [J] N0 or Z
		GAOL_RND_LEAVE();
		return I; // P0 (Z or N0)
	      } else { // [J] P or M
		if (J.left() < 0.0) { // [J] M
		  GAOL_RND_LEAVE();
		  return I; // P0 M
		} else { // [J] P0 or P1
		  if (J.left() == 0.0) { // [J] P0
		    GAOL_RND_LEAVE();
		    return I;
		  } else { // [J] P1
		    interval tmp2 = I & interval(0.0,K.right()/J.left()); // P0 P1
		    GAOL_RND_LEAVE();
		    return tmp2;
		  }
		}
	      }
	    }
	  } else { // [this] P1
	    if (J.right() < 0.0) { // [J] N1
	      asm volatile ("fldl %3 \n\t"
			    "fchs \n\t"
			    "fdivl %5 \n\t"
			    "fldl %2 \n\t"
			    "fdivl %4 \n\t"
			    "fstpl %1 \n\t"
			    "fstpl %0 \n\t"
			    "fldl %0 \n\t"
			    "fchs \n\t"
			    "fstpl %0 \n\t"
			    : "=m" (tmp.lb_), "=m" (tmp.rb_)
			    : "m" (K.lb_), "m" (K.rb_), "m" (J.lb_), "m" (J.rb_));
	      
	      GAOL_RND_LEAVE();
	      return I & tmp; // P1 N1
	    } else { // [J] P or Z
	      if (J.right() == 0.0) { // [J] N0 or Z
		if (J.left() == 0.0) { // [J] Z
		  GAOL_RND_LEAVE();
		  return interval::emptyset; // P1 Z
		}
		interval tmp2 = I & interval(-GAOL_INFINITY,K.left()/J.left()); // P1 N0
		GAOL_RND_LEAVE();
		return tmp2;
	      } else { // [J] P or M
		if (J.left() < 0.0) { // [J] M
		  asm volatile ("fldl %1 \n\t"
				"fchs \n\t"
				"fdivl %2 \n\t"
				"fstpl %0 \n\t"
				"fldl %0 \n\t"
				"fchs \n\t"
				"fstpl %0 \n\t"
				: "=m" (tmp.lb_)
				: "m" (K.lb_), "m" (J.rb_));
		  interval tmp2 = (I & interval(-GAOL_INFINITY,K.left()/J.left()))
		    | (I & interval(tmp.left(),GAOL_INFINITY)); // P1 M
		  GAOL_RND_LEAVE();
		  return tmp2;
		} else { // [J] P0 or P1
		  if (J.left() == 0.0) { // [J] P0
		    asm volatile ("fldl %1 \n\t"
				  "fchs \n\t"
				  "fdivl %2 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  : "=m" (tmp.lb_)
				  : "m" (K.lb_), "m" (J.rb_));
		    tmp.rb_ = GAOL_INFINITY;
   
		    GAOL_RND_LEAVE();
		    return I & tmp; // P1 P0
		  } else { // [J] P1
		    asm volatile ("fldl %2 \n\t"
				  "fchs \n\t"
				  "fdivl %5 \n\t"
				  "fstpl %0 \n\t"
				  "fldl %0 \n\t"
				  "fchs \n\t"
				  "fstpl %0 \n\t"
				  "fldl %3 \n\t"
				  "fdivl %4 \n\t"
				  "fstpl %1 \n\t"
				  : "=m" (tmp.lb_), "=m" (tmp.rb_)
				  : "m" (K.lb_), "m" (K.rb_), 
				    "m" (J.lb_), "m" (J.rb_));
		    
		    GAOL_RND_LEAVE();
		    return I & tmp; // P1 P1
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }


  interval sqr(const interval& I) 
  {  
    static double l, r;
    if (I.is_empty()) {
      return interval::emptyset;
    }

    double Il = I.left(), Ir = I.right();
    GAOL_RND_ENTER();
    if (I.certainly_positive()) {
      asm volatile ("fldl %2 \n\t"
		    "fchs \n\t"
		    "fmull %2 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %3 \n\t"
		    "fmull %3 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (l), "=m" (r)
		    : "m" (Il), "m" (Ir));
      GAOL_RND_LEAVE();
      return interval(l,r);
    }
    
    if (I.certainly_negative()) {
      asm volatile ("fldl %3 \n\t"
		    "fchs \n\t"
		    "fmull %3 \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %2 \n\t"
		    "fmull %2 \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (l), "=m" (r)
		    : "m" (Il), "m" (Ir));
      GAOL_RND_LEAVE();
      return interval(l,r);
    }

    if (fabs(I.left()) >= fabs(I.right())) {
     interval tmp = interval(0.0,I.left()*I.left());
     GAOL_RND_LEAVE();
     return tmp;
    } else {
      interval tmp = interval(0.0,I.right()*I.right());
      GAOL_RND_LEAVE();
      return tmp;
    }

    /* Part removed because some of the opcodes where not supported by old ix86 computers
    asm volatile ("fldl %2 \n\t"
		  "fldl %1 \n\t"
		  "fchs \n\t"
		  "fcomi %%st(1), %%st(0) \n\t"
		  "fcmovb %%st(1), %%st(0) \n\t"
		  "fmul %%st(0), %%st(0)\n\t"
		  "fstpl %0 \n\t"
		  "ffree %%st; fincstp \n\t" 
		  : "=m" (r)
		  : "m" (I.left()), "m" (I.right()));
    return interval(0.0,r);
    */
  }

  interval sqrt(const interval& I)
  {
    interval Ipos = interval(maximum(0.0,I.left()),I.right());
    
    if (Ipos.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    if (Ipos.left() == 0.0) {
      interval tmp = interval(0.0,::sqrt(Ipos.right()));
      GAOL_RND_LEAVE();
      return tmp;
    } else {
      asm volatile ("fldl %2 \n\t"
		    "fsqrt \n\t"
		    "fldl %2 \n\t"
		    "fchs \n\t"
		    "fdivp \n\t"
		    "fstpl %0 \n\t"
		    "fldl %0 \n\t"
		    "fchs \n\t"
		    "fstpl %0 \n\t"
		    "fldl %3 \n\t"
		    "fsqrt \n\t"
		    "fstpl %1 \n\t"
		    : "=m" (Ipos.lb_), "=m" (Ipos.rb_)
		    : "m" (Ipos.lb_), "m" (Ipos.rb_));
      GAOL_RND_LEAVE();
     return (Ipos);
    }
  }


  interval sqrt_rel(const interval& J, const interval& I)
  {
    interval Jpos = interval(maximum(0.0,J.left()),J.right());
    
    if (Jpos.is_empty() || I.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    if (Jpos.left() == 0.0) {
      Jpos.lb_ = 0.0;
      Jpos.rb_ = ::sqrt(Jpos.right());
    } else {
      round_downward();
      asm volatile ("fldl %1 \n\t"
		    "fsqrt \n\t"
		    "fstpl %0 \n\t"
		    : "=m" (Jpos.lb_)
		    : "m" (Jpos.lb_));
      round_upward();
      asm volatile ("fldl %1 \n\t"
		    "fsqrt \n\t"
		    "fstpl %0 \n\t"
		    : "=m" (Jpos.rb_)
		    : "m" (Jpos.rb_));
    }
    GAOL_RND_LEAVE();

    if (I.certainly_positive()) {
      return Jpos & I;
    }
    if (I.certainly_negative()) {
      return (-Jpos) & I;
    }
    return (I & Jpos) | (I & (-Jpos));
  }


interval cos(const interval& I)
{
  if (I.is_empty()) {
    return interval::emptyset;
  }
  
  GAOL_RND_ENTER();
  static double a,b, Il, Ir;
  Il = I.left();
  Ir = I.right();
  if (I.left() >= 0) {
    asm volatile ("fldl %2 \n\t"
		  "fchs \n\t"
		  "fdivl %4 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  "fldl %3 \n\t"
		  "fdivl %5 \n\t"
		  "fstpl %1 \n\t"
		  : "=m" (a), "=m" (b)
		  : "m" (Il), "m" (Ir), "m" (pi_up), 
		  "m" (pi_dn));
  } else {
    asm volatile ("fldl %1 \n\t"
		  "fchs \n\t"
		  "fdivl %2 \n\t"
		  "fstpl %0 \n\t"
		  "fldl %0 \n\t"
		  "fchs \n\t"
		  "fstpl %0 \n\t"
		  : "=m" (a)
		  : "m" (Il), "m" (pi_dn));
    if (I.right() > 0) {
      asm volatile ("fldl %1 \n\t"
		    "fdivl %2 \n\t"
		    "fstpl %0 \n\t"
		    : "=m" (b)
		    : "m" (Ir), "m" (pi_dn));
    } else {
      asm volatile ("fldl %1 \n\t"
		    "fdivl %2 \n\t"
		    "fstpl %0 \n\t"
		    : "=m" (b)
		    : "m" (Ir), "m" (pi_up));
    }
  }
  
  double 
    m=std::floor(a), 
    n=std::ceil(b),
    u, v;
  
  double nm = (n-m); // Must be rounded towards +oo
  
  
  if (nm < 2.0) {
    if (feven(m)) { // even(m)? No conversion to int in order 
      // to avoid overflow
      u=cos_dn(I.right());// use of cos(x)=cos(-x)
      v=cos_up(I.left());
    } else { // odd(m)?
      u=cos_dn(I.left()); 
      v=cos_up(I.right());
    }
  } else {
    if (nm == 2.0) {
      if (feven(m)) {
	double 
	  u1=cos_up(I.left()),
	  u2=cos_up(I.right());
	u= -1.0;
	v= ((u1 > u2) ? u1 : u2);
	} else {
	  double 
	    u1=cos_dn(I.left()),
	    u2=cos_dn(I.right());
	  
	  u= ((u1 < u2) ? u1 : u2);
	  v= 1.0;
	}
    } else {
      GAOL_RND_LEAVE();
     return interval::minus_one_plus_one;
    }
  }
  GAOL_RND_LEAVE();
  return interval(u,v);
}



#endif /* __gaol_interval_ix86_cpp_h__ */
