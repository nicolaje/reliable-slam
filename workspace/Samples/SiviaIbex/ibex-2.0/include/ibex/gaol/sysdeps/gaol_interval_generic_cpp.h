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
 * CVS: $Id: gaol_interval_generic_cpp.h,v 1.16 2007/12/10 20:18:26 goualard Exp $
 * Last modified: Wed May 24 11:09:03 2006 on pc-goualard.lina.sciences.univ-nantes.prive
 * By: Frederic Goualard <Frederic.Goualard@lina.univ-nantes.fr>
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_interval_generic_cpp.h
  \brief  Non-portable part of the interval methods. Generic version in C.

  <long description>

  \author Frédéric Goualard
  \date   2001-11-12
*/


#ifndef __gaol_interval_generic_cpp_h__
#define __gaol_interval_generic_cpp_h__

// fast_modulo_k_pi defined in gaol_interval.cpp
extern bool fast_modulo_k_pi(const interval &I, double &k_left, double &k_right);


  /*!
    \brief Computes a/b rounded downward
  */
  inline double div_dn(double a, double b)
  {
    /* Do not optimize the expression as -((-a)/b) since we need to force 
       (-a)/b to be stored in a 64 bits format before negating it
    */
    GAOL_RND_ENTER();
    double tmp = (-a)/b;
    GAOL_RND_LEAVE();
    return -tmp;
  }

  /*!
    \brief Computes 1/a rounded downward
  */
  inline double inv_dn(double a)
  {
    GAOL_RND_ENTER();
    double tmp = (-1.0)/a;
    GAOL_RND_LEAVE();
    return -tmp;
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
      lb_  = -((-left())*d);
      rb_ *= d; 
    } else {
      // Beware: cross-dependency between lb_ and rb_
      double old_lb = lb_;
      lb_ = -((-right())*d);
      rb_ = old_lb*d;
    }
    GAOL_RND_LEAVE();
    return *this;
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
      lb_ = -((-left())/d);
      rb_ /= d;
    } else { // d < 0.0
      // Warning: cross-dependency between lb_ and rb_
      double old_lb = left();
      lb_ = -((-right())/d);
      rb_ = old_lb/d;
    }
    GAOL_RND_LEAVE();
    return *this;
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
      lb_ = -((-left())/d);
      rb_ /= d;
    } else { // d < 0.0
      // Warning: cross-dependency between lb_ and rb_
      double old_lb = left();
      lb_ = -((-right())/d);
      rb_ = old_lb/d;
    }
    GAOL_RND_LEAVE();
    return *this;
  }


  double interval::midpoint() const
  {
    if (is_symmetric()) { // Symmetric case handles [-oo, +oo]
      return 0.0;
    }
    if (left() == -GAOL_INFINITY) {
      return -std::numeric_limits<double>::max();
    }
    if (right() == GAOL_INFINITY) {
      return std::numeric_limits<double>::max();
    }
    gaol::round_nearest();
    // middle <- right/2 + left/2 : two divisions to avoid spurrious overflow
    double m = ((left()/2.0)+(right()/2.0));
    gaol::round_upward();
    return m;
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
    double tmp = ((-left())/2.0)-(right()/2.0);
    interval tmp = interval(-tmp,left()+right());
    GAOL_RND_LEAVE();
    return tmp;
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
       To appear in Journal of the ACM.
    */
    if (certainly_positive()) { // P ?
      if (I.certainly_positive()) { // P P
	lb_  = lb_*(-I.lb_);
	lb_ = -lb_;
	rb_ *= I.rb_;
      } else {
	if (I.strictly_straddles_zero()) { // P M
	  lb_  = (-rb_) * I.lb_;
	  lb_ = -lb_;
	  rb_ *= I.rb_;
	} else { // P N
	  // Warning: cross-dependency between lb_ and rb_
	  double old_lb = left();
	  lb_ = (-right())*I.left();
	  lb_ = -lb_;
	  rb_ = I.right()*old_lb;
	}
      }
    } else {
      if (strictly_straddles_zero()) { // M ?
	if (I.certainly_positive()) { // M P
	  lb_ = lb_*(-I.rb_);
	  lb_ = -lb_;
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
	    // Warning: cross-dependency between lb_ and rb_
	    double old_lb = left();
	    lb_ = (-right())*I.left();
	    lb_ = -lb_;
	    rb_ = old_lb*I.left();
	  }
	}
      } else { // N  (case Z already tested)
	if (I.certainly_positive()) { // N P
	  lb_  = lb_*(-I.rb_);
	  lb_ = -lb_;
	  rb_ *= I.lb_;
	} else {
	  if (I.strictly_straddles_zero()) { // N M
	    // Warning: dependency lb_ -> rb_
	    rb_ = I.left()*left();
	    lb_ = (-I.right())*left();
	    lb_ = -lb_;
	  } else { // N N
	    // Warning: cross-dependency between lb_ and rb_
	    double old_lb = left();
	    lb_ = (-right())*I.right();
	    lb_ = -lb_;
	    rb_ = old_lb*I.left();
	  }
	}
      }
    }
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
	// Warning: cross-dependency between lb_ and rb_
	double old_lb = left();
	lb_ = (-right())/I.left();
	lb_ = -lb_;
	rb_ = old_lb/I.right();
	return *this; // N1 N1
      } else { // [I] P or Z
	if (I.right() == 0.0) { // [I] N0 or Z
	  if ( I.left() == 0.0) { // [I] Z
	    *this = interval::emptyset; // N1 Z
	    return *this;
	  }
	  lb_ = (-right())/I.left();
	  lb_ = -lb_;
	  rb_ = GAOL_INFINITY;
	  return *this; // N1 N0
	} else { // [I] P or M
	  if (I.left() < 0.0) { // [I] M
	    *this = interval::universe; // N1 M
	    return *this;
	  } else { // [I] P0 or P1
	    if (I.left() == 0.0) { // [I] P0
	      *this = interval(-GAOL_INFINITY,right()/I.right()); // N1 P0
	      return *this;
	    } else { // [I] P1
	      lb_  = (-left())/I.left();
	      lb_ = -lb_;
	      rb_ /= I.right();
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
	    return *this;
	  } else {
	    *this = interval::zero; // Z (N,M,P)
	    return *this;
	  }
	} else { // [this] N0
	  if (I.right() < 0.0) { // [I] N1
	    *this = interval(0.0,left()/I.right()); // N0 N1
	    return *this;
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      if (I.left() == 0.0) { // [I] Z
		*this = interval::emptyset; // N0 Z
		return *this;
	      }
	      *this = interval(0.0,GAOL_INFINITY); // N0 N0
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // N0 M
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval(-GAOL_INFINITY,0.0); // N0 P0
		  return *this;
		} else { // [I] P1
		  lb_ = (-left())/I.left();
		  lb_ = -lb_;
		  rb_ = 0.0;
		  return *this; // N0 P1
		}
	      }
	    }
	  }
	}
      } else { // [this] M, P0, or P1
	if (left() < 0.0) { // [this] M
	  if (I.right() < 0.0) { // [I] N1
	    // Warning: cross-dependency between lb_ and rb_
	    double old_lb = left();
	    lb_ = (-right())/I.right();
	    lb_ = -lb_;
	    rb_ = old_lb/I.right();
	    return *this; // M N1
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      if (I.left() == 0.0) { // [I] Z
		*this = interval::emptyset; // M Z
		return *this;
	      }
	      *this = interval::universe; // M N0
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // M M
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // M P0
		  return *this;
		} else { // [I] P1
		  lb_  = (-left())/I.left();
		  lb_ = -lb_;
		  rb_ /= I.left();
		  return *this; // M P1
		}
	      }
	    }
	  }
	} else { // [this] P0 or P1
	  if (left() == 0.0) { // [this] P0
	    if (I.right() < 0.0) { // [I] N1
	      lb_ = (-right())/I.right();
	      lb_ = -lb_;
	      rb_ = 0.0;
	      return *this; // P0 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P0 Z
		  return *this;
		}
		lb_ = -GAOL_INFINITY;
		rb_ = 0.0;
		return *this; // P0 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P0 M
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    lb_ = 0.0;
		    rb_ = GAOL_INFINITY;
		    return *this;
		  } else { // [I] P1
		    *this = interval(0.0,right()/I.left()); // P0 P1
		    return *this;
		  }
		}
	      }
	    }
	  } else { // [this] P1
	    if (I.right() < 0.0) { // [I] N1
	      // Warning: cross-dependency between lb_ and rb_
	      double old_lb = left();
	      lb_ = (-right())/I.right();
	      lb_ = -lb_;
	      rb_ = old_lb/I.left();
	      return *this; // P1 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P1 Z
		  return *this;
		}
		rb_ = left()/I.left(); // beware: rb_ uses left()
		lb_ = -GAOL_INFINITY;
		return *this; // P1 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P1 M
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    lb_ = (-left())/I.right();
		    lb_ = -lb_;
		    rb_ = GAOL_INFINITY;
   
		    return *this; // P1 P0
		  } else { // [I] P1
		    lb_ = (-left())/I.right();
		    lb_ = -lb_;
		    rb_ /= I.left();
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
	// Warning: cross-dependency between lb_ and rb_
	double old_lb = left();
	lb_ = (-right())/I.left();
	lb_ = -lb_;
	rb_ = old_lb/I.right();

	return *this; // N1 N1
      } else { // [I] P or Z
	if (I.right() == 0.0) { // [I] N0 or Z
	  if ( I.left() == 0.0) { // [I] Z
	    *this = interval::emptyset; // N1 Z
	    return *this;
	  }
	  lb_ = (-right())/I.left();
	  lb_ = -lb_;
	  rb_ = GAOL_INFINITY;
	  return *this; // N1 N0
	} else { // [I] P or M
	  if (I.left() < 0.0) { // [I] M
	    *this = interval::universe; // N1 M
	    return *this;
	  } else { // [I] P0 or P1
	    if (I.left() == 0.0) { // [I] P0
	      *this = interval(-GAOL_INFINITY,right()/I.right()); // N1 P0
	      return *this;
	    } else { // [I] P1
	      lb_  = (-left())/I.left();
	      lb_ = -lb_;
	      rb_ /= I.right();
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
	    return *this;
	  } else {
	    *this = interval::zero; // Z (N1, P1)
	    return *this;
	  }
	} else { // [this] N0
	  if (I.right() < 0.0) { // [I] N1
	    *this = interval(0.0,left()/I.right()); // N0 N1
	    return *this;
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      *this = interval::universe; // N0 N0
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // N0 M
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // N0 P0
		  return *this;
		} else { // [I] P1
		  lb_ = (-left())/I.left();
		  lb_ = -lb_;
		  rb_ = 0.0;
		  return *this; // N0 P1
		}
	      }
	    }
	  }
	}
      } else { // [this] M, P0, or P1
	if (left() < 0.0) { // [this] M
	  if (I.right() < 0.0) { // [I] N1
	    // Warning: cross-dependency between lb_ and rb_
	    double old_lb = left();
	    lb_ = (-right())/I.right();
	    lb_ = -lb_;
	    rb_ = old_lb/I.right();

	    return *this; // M N1
	  } else { // [I] P or Z
	    if (I.right() == 0.0) { // [I] N0 or Z
	      *this = interval::universe; // M N0
	      return *this;
	    } else { // [I] P or M
	      if (I.left() < 0.0) { // [I] M
		*this = interval::universe; // M M
		return *this;
	      } else { // [I] P0 or P1
		if (I.left() == 0.0) { // [I] P0
		  *this = interval::universe; // M P0
		  return *this;
		} else { // [I] P1
		  lb_  = (-left())/I.left();
		  lb_ = -lb_;
		  rb_ /= I.left();
		  return *this; // M P1
		}
	      }
	    }
	  }
	} else { // [this] P0 or P1
	  if (left() == 0.0) { // [this] P0
	    if (I.right() < 0.0) { // [I] N1
	      lb_ = (-right())/I.right();
	      lb_ = -lb_;
	      rb_ = 0.0;
	      return *this; // P0 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		*this = interval::universe; // P0 Z
		return *this; // P0 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P0 M
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    *this = interval::universe;
		    return *this;
		  } else { // [I] P1
		    *this = interval(0.0,right()/I.left()); // P0 P1
		    return *this;
		  }
		}
	      }
	    }
	  } else { // [this] P1
	    if (I.right() < 0.0) { // [I] N1
	      // Warning: cross-dependency between lb_ and rb_
	      double old_lb = left();
	      lb_ = (-right())/I.right();
	      lb_ = -lb_;
	      rb_ = old_lb/I.left();
	      
	      return *this; // P1 N1
	    } else { // [I] P or Z
	      if (I.right() == 0.0) { // [I] N0 or Z
		if (I.left() == 0.0) { // [I] Z
		  *this = interval::emptyset; // P1 Z
		  return *this;
		}
		rb_ = left()/I.left(); // beware: rb_ uses lb_
		lb_ = -GAOL_INFINITY;
		return *this; // P1 N0
	      } else { // [I] P or M
		if (I.left() < 0.0) { // [I] M
		  *this = interval::universe; // P1 M
		  return *this;
		} else { // [I] P0 or P1
		  if (I.left() == 0.0) { // [I] P0
		    lb_ = (-left())/I.right();
		    lb_ = -lb_;
		    rb_ = GAOL_INFINITY;
		    
		    return *this; // P1 P0
		  } else { // [I] P1
		    lb_ = (-left())/I.right();
		    lb_ = -lb_;
		    rb_ /= I.left();
		    
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
  if (K.is_empty() || J.is_empty() || I.is_empty()) {
    return interval::emptyset;
  }
  
  GAOL_RND_ENTER();
  if (K.right() < 0.0) { // [K] N1
    if (J.right() < 0.0) { // [J] N1
      double tmp = (-K.right())/J.left();
      return I & interval(-tmp, K.left()/J.right()); // N1 N1
    } else { // [I] P or Z
      if (J.right() == 0.0) { // [J] N0 or Z
	if (J.left() == 0.0) { // [J] Z
	  return interval::emptyset; // N1 Z
	}
	double tmp = (-K.right())/J.left();
	return I & interval(-tmp,GAOL_INFINITY); // N1 N0
      } else { // [I] P or M
	if (J.left() < 0.0) { // [I] M
	  double tmp = (-K.right())/J.left();
	  return (I & interval(-GAOL_INFINITY,K.right()/J.right())) 
	        | (I & interval(-tmp,GAOL_INFINITY)); // N1 M
	} else { // [I] P0 or P1
	  if (J.left() == 0.0) { // [I] P0
	    return I & interval(-GAOL_INFINITY,K.right()/J.right()); // N1 P0
	  } else { // [I] P1
	    double tmp = (-K.left())/J.left();
	    return I & interval(-tmp, K.right()/J.right()); // N1 P1
	  }
	}
      }
    }
  } else { // [this] N0, Z, M, or P
    if (K.right() == 0.0) { // [this] N0 or Z
      if (K.left() == 0.0) { // [this] Z
	if (J.straddles_zero()) {
	  return I; // Z (N0, M, P0)
	} else {
	  return I & interval::zero; // Z (N1, P1)
	}
      } else { // [this] N0
	if (J.right() < 0.0) { // [I] N1
	  return I & interval(0.0,K.left()/J.right()); // N0 N1
	} else { // [I] P or Z
	  if (J.right() == 0.0) { // [I] N0 or Z
	    if (J.left() == 0.0) { // [I] Z
	      return I; // N0 Z
	    }
	    return I; // N0 N0
	  } else { // [I] P or M
	    if (J.left() < 0.0) { // [I] M
	      return I; // N0 M
	    } else { // [I] P0 or P1
	      if (J.left() == 0.0) { // [I] P0
		return I; // N0 P0
	      } else { // [I] P1
		double tmp = (-K.left())/J.left();
		return I & interval(-tmp,0.0);
	      }
	    }
	  }
	}
      }
    } else { // [this] M, P0, or P1
      if (K.left() < 0.0) { // [this] M
	if (J.right() < 0.0) { // [I] N1
	  double tmp = (-K.right())/J.right();
	  return I & interval(-tmp,K.left()/J.right()); // M N1
	} else { // [I] P or Z
	  if (J.right() == 0.0) { // [I] N0 or Z
	    return I; // M N0
	  } else { // [I] P or M
	    if (J.left() < 0.0) { // [I] M
	      return I; // M M
	    } else { // [I] P0 or P1
	      if (J.left() == 0.0) { // [I] P0
		return I; // M P0
	      } else { // [I] P1
		double tmp = (-K.left())/J.left();
		return I & interval(-tmp,K.right()/J.left()); // M P1
	      }
	    }
	  }
	}
      } else { // [this] P0 or P1
	if (K.left() == 0.0) { // [this] P0
	  if (J.right() < 0.0) { // [I] N1
	    double tmp = (-K.right())/J.right();
	    return I & interval(-tmp,0.0); // P0 N1
	  } else { // [I] P or Z
	    if (J.right() == 0.0) { // [I] N0 or Z
	      return I; // P0 (N0 or Z)
	    } else { // [I] P or M
	      if (J.left() < 0.0) { // [I] M
		return I; // P0 M
	      } else { // [I] P0 or P1
		if (J.left() == 0.0) { // [I] P0
		  return I; // P0 P0
		} else { // [I] P1
		  return I & interval(0.0,K.right()/J.left()); // P0 P1
		}
	      }
	    }
	  }
	} else { // [this] P1
	  if (J.right() < 0.0) { // [I] N1
	    double tmp = (-K.right())/J.right();
	    return I & interval(-tmp,K.left()/J.left()); // P1 N1
	  } else { // [I] P or Z
	    if (J.right() == 0.0) { // [I] N0 or Z
	      if (J.left() == 0.0) { // [I] Z
		return interval::emptyset; // P1 Z
	      }
	      return I & interval(-GAOL_INFINITY,K.left()/J.left()); // P1 N0
	    } else { // [I] P or M
	      if (J.left() < 0.0) { // [I] M
		double tmp = (-K.left())/J.right();
		return (I & interval(-GAOL_INFINITY,K.left()/J.left()))
		      | (I & interval(-tmp,GAOL_INFINITY)); // P1 M
	      } else { // [I] P0 or P1
		if (J.left() == 0.0) { // [I] P0
		  double tmp = (-K.left())/J.right();
		  return I & interval(-tmp,GAOL_INFINITY); // P1 P0
		} else { // [I] P1
		  double tmp = (-K.left())/J.right();
		  return I & 
		    interval(-tmp,K.right()/J.left()); // P1 P1
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
    if (I.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    double l = I.left(), r = I.right(); 
    if (I.certainly_positive()) {
      double tmp = (-l)*l;
      return interval(-tmp,r*r);
    }
    
    if (I.certainly_negative()) {
      double tmp = (-r)*r;
      return interval(-tmp,l*l);
    }
    double ll = l*l, rr = r*r;
    return interval(0.0,((ll>rr) ? ll : rr));
  }

  interval sqrt(const interval& I)
  {
    interval Ipos = interval(maximum(0.0,I.left()),I.right());
    
    if (Ipos.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    if (Ipos.left() == 0.0) {
      return interval(0.0,std::sqrt(Ipos.right()));
    } else {
      double tmp = (-Ipos.left())/std::sqrt(Ipos.left());
      Ipos.lb_ = -tmp;
      Ipos.rb_ = std::sqrt(Ipos.right());
      return (Ipos);
    }
  }


  interval sqrt_rel(const interval& J, const interval& I)
  {
    interval Jpos = interval(maximum(0.0,J.left()),J.right());
    
    if (Jpos.is_empty()) {
      return interval::emptyset;
    }

    GAOL_RND_ENTER();
    if (I.certainly_positive()) {
      if (Jpos.left() == 0.0) {
	return interval(0.0,std::sqrt(Jpos.right())) & I;
      } else {
	double tmp = (-Jpos.left())/std::sqrt(Jpos.left());
	Jpos.lb_ = -tmp;
	Jpos.rb_ = std::sqrt(Jpos.right());
	return (Jpos & I);
      }
    }
    // I straddles 0 or is certainly negative

    // Computing projection on [-oo, 0]
    if (Jpos.left() == 0.0) {
      round_downward();
      Jpos = interval(-std::sqrt(Jpos.right()),0.0);
      round_upward();
    } else {
      double old_lb = Jpos.lb_;
      round_downward();
      Jpos.lb_ = -std::sqrt(Jpos.right());
      round_upward();
      Jpos.rb_ = -std::sqrt(old_lb);
    }
    if (I.certainly_negative()) {
      return (Jpos & I);
    } else {
      return ((I & Jpos) | (I & -Jpos));
    }
  }



  interval cos_i(double i, const interval& I)
  {
    if (feven(i)) {
      return interval(cos_dn(I.right()),cos_up(I.left()));
    } else {
      return interval(cos_dn(I.left()),cos_up(I.right()));
    }
  }



  interval cos(const interval& I)
  {
    // Empty set?
    if (I.is_empty()) {
      return interval::emptyset;
    }

    // I spans the whole period?
    if (I.width() >= 2*pi_up) { // We use pi_up since width() is rounded upward
      return interval::minus_one_plus_one;
    }

    /*
      If I is outside [-2^52,2^52], it is useless to compute
      the cosine because the rounding error in modulo_k_pi 
      would forbid computing k_left or k_right accurately.
    */
    if (I.right() < -two_power_52 || I.left() > two_power_52) {
      return interval::minus_one_plus_one;
    }
    double kl, kr;

    GAOL_RND_ENTER();
    /*
      For the moment, we return [-1,1] whenever one of the bounds could not
      be decomposed modulo \pi.
    */
    if (fast_modulo_k_pi(I,kl,kr)) { 
      interval 
	tmpll = kl*interval::pi,
	tmplr = tmpll+interval::pi,
	tmprl = kr*interval::pi,
	tmprr = tmprl+interval::pi;
      
      return cos_i(kl,I & interval(tmpll.left(),tmplr.right())) |
	      cos_i(kr,I & interval(tmprl.left(),tmprr.right()));
    } else {
      return interval::minus_one_plus_one;
    }
  }


#endif /* __gaol_interval_generic_cpp_h__ */
