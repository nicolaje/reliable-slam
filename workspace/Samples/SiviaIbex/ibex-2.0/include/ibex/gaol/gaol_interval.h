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
 * CVS: $Id: gaol_interval.h,v 1.40 2007/09/12 12:41:58 goualard Exp $
 * Last modified: 
 * By: 
 *--------------------------------------------------------------------------*/

/*!
  \file   gaol_interval.h
  \brief  The interval class and operators

  \author Goualard Frédéric
  \date   2001-09-28
*/


#ifndef __gaol_interval_h__
#define __gaol_interval_h__

#include <cmath>
#include <iosfwd>
#include <string>
#include <limits>
#include "gaol/gaol_config.h"
#include "gaol/gaol_double_op.h"
#include "gaol/gaol_port.h"
#include "gaol/gaol_common.h"
#include "gaol/gaol_fpu.h"
#include "gaol/gaol_limits.h"

#if defined (_MSC_VER)
#  include <float.h>  
#  undef min
#  undef max
#endif


using std::string;

namespace gaol {

  /*!
    \brief Format to use for the output of intervals.
    
    The supported formats so far are the following:
    - bounds: the interval is output in the form "[l, r]" where l and r
    are respectively its left and right bounds
    - width: the interval is output in the form "c (+/- w)" where
    c is its center and w its width
    - center: the interval is output as a single value, its center.
    - hexa: same as "bounds" except that bounds are printed as hexadecimal
    values to avoid problems due to round-off errors when translating
    the floats into decimal
    - agreeing: the interval is output in the form "r [l, r]" where
    r is the number containing all the digits that are the same in both
    left and right bounds, and where l and r are the disagreeing 
    remaining digits. See "Factored Notation for Interval I/O", Maarten
    Herman van Emden, CoRR index=cs.NA/0102023. 
  */
  struct _GAOL_DLL_ interval_format {
    enum format_t {
      bounds,
      width,
      center,
      hexa,
      agreeing
    };
  };


  class _GAOL_DLL_ interval {
  public:
    interval(void);
    interval(double a, double b);
    interval(double a);
    /*! 
      \brief Creation of an interval from a string. 
      
      Allows creating intervals with bounds not representable with 
      floats, e.g.: interval("0.1")=[0.09999,0.10001]. See the
      file jail_parser.h for a description of the supported format
      for representing intervals with strings.
     */
    interval(const char *const s);
    /*!
      \brief Creation of an interval from two strings

      Allows creating intervals by providing a string for each bound. Each string
      is evaluated using interval arithmetic; the left (resp. right) bound of the first 
      (resp. second) string is used to represent the left (resp. right) bound of the 
      interval constructed.
      */
    interval(const char *const sl, const char *const sr);
    interval& operator+=(double d);
    interval& operator-=(double d);
    interval& operator*=(double d);
    interval& operator/=(double d);
    //! Relational division
    interval& operator%=(double d);
    interval& operator+=(const interval& I);
    interval& operator-=(const interval& I);
    interval& operator*=(const interval& I);
    interval& operator/=(const interval& I);
    interval& operator%=(const interval& I);
    
    interval operator+(void) const;
    interval operator-(void) const;

    //! Intersection of *this and I
    interval& operator&=(const interval& I); 
    //! Union of *this and I
    interval& operator|=(const interval& I); 

    double left(void) const;
    double right(void) const;
    /*!
     \brief Returns the midpoint of an interval.

     Cases are:
     - \emptyset  -> Quiet NaN
     - [-oo, +oo] -> midP = 0.0
     - [-oo, b]   -> midP = -MAXREAL
     - [a, +oo]   -> midP = MAXREAL
     - [a, b]     -> midP = a + .5*(b-a) with + and * rounded toward 
                            nearest and - rounded downward.
    */
    double midpoint(void) const;
    /*!
      \brief Midpoint enclosing interval.
      
     Returns an interval enclosing the midpoint of '*this'. The returned
     interval is not guaranteed to be canonical.
     - mid([a,b])     = [(a+b)/2, (a+b)/2]
     - mid([-oo,b])   = mid([-MAXREAL,b])
     - mid([a,+oo])   = mid([a,+MAXREAL])
     - mid([-oo,+oo]) = [0,0]
    */
    interval mid(void) const;
    

    bool certainly_positive(void) const;
    bool certainly_negative(void) const;
    bool certainly_strictly_positive(void) const;
    bool certainly_strictly_negative(void) const;
    bool certainly_geq(const interval &I) const;
    bool certainly_leq(const interval &I) const;
    bool certainly_ge(const interval &I) const;
    bool certainly_le(const interval &I) const;
    bool certainly_eq(const interval &I) const;
    bool certainly_neq(const interval &I) const;
                        
    bool possibly_geq(const interval &I) const;
    bool possibly_leq(const interval &I) const;
    bool possibly_ge(const interval &I) const;
    bool possibly_le(const interval &I) const;
    bool possibly_eq(const interval &I) const;
    bool possibly_neq(const interval &I) const;

    bool set_contains(const interval& I) const;
    //! d shall not be a NaN
    bool set_contains(double d) const;
    bool set_strictly_contains(const interval& I) const;
    bool set_strictly_contains(double d) const;
    bool set_disjoint(const interval &I) const;
    bool set_eq(const interval& I) const;
    bool set_neq(const interval& I) const;
    bool set_leq(const interval& I) const;
    bool set_geq(const interval& I) const;
    bool set_le(const interval& I) const;
    bool set_ge(const interval& I) const;

    bool is_empty(void) const;
    bool is_symmetric(void) const;
    bool is_finite(void) const;
    /*!
      An interval is canonical if it is of the form [a, a] or 
      of the form [a,a+] with a+ the smallest floating-point number larger
      than a
    */
    bool is_canonical(void) const;
    bool is_zero(void) const;
    bool straddles_zero(void) const;
    bool strictly_straddles_zero(void) const;
    bool is_a_double(void) const;
    bool is_an_int(void) const;

    ///! Size of the interval
    double width(void) const;

    /*!
     \brief Mignitude.
     
     Returns the mignitude of '*this', that is, mig(*this)=
     - min_  if *this > 0
     - -max_ if *this < 0
     - 0 otherwise
     See "Global Optimization using interval Analysis", chap. 3, Eldon Hansen
     */
    double mig(void) const;
       /*!
      \brief Magnitude
      
      Returns the magnitude of '*this', that is, 
      mag(*this)=max(|min_|, |max_|)
    */
    double mag(void) const;

    /*!
      \brief Signed mignitude.

     Returns:
     - min_ if *this > 0
     - max_ if *this < 0
     - 0 otherwise

     See "interval Methods for Bounding the Range of Polynomials and Solving 
     Systems of Nonlinear Equations", Volker Stahl PhD. thesis, def. 1.3.28.
    */
    double smig(void) const; 
 

    static void format(interval_format::format_t f);
    static interval_format::format_t format(void);

    static const interval minus_one_plus_one;
    static const interval pi;
    static const interval two_pi;
    static const interval half_pi;
    static const interval emptyset;
    static const interval universe;
    static const interval zero;
    static const interval one;
    static const interval positive;
    static const interval negative;
    static const interval one_plus_infinity;

    friend _GAOL_DLL_ interval sqrt(const interval& I);
    friend _GAOL_DLL_ interval sqrt_rel(const interval& J, const interval& I);
    friend _GAOL_DLL_ interval div_rel(const interval &K, const interval &J, 
			    const interval &I);
    /*!
      @name Splitting methods 
    */
    //@{
    /*!
      \brief Splits *this in two using midpoint(). 
      
      Returns the left part in I1 and the right one in I2
    */
    void split(interval &I1, interval &I2) const;

    //! Returns the left part (i.e. [left,midpoint()] of the domain.
    interval split_left(void) const;
    //! Returns the right part (i.e. [midpoint(),right] of the domain.
    interval split_right(void) const;
    //@} // End of splitting methods

    //! Conversion to string
    operator string() const;

    //! Returns the current number of digits used for display
    static std::streamsize precision(void);
    /*! 
      Sets the number of digits for display to 'n'. 
      \return The number of digits previously used
    */
    static std::streamsize precision(std::streamsize n);

  private:
    double lb_, rb_;
    static interval_format::format_t output;
    //! Number of digits to display
    static std::streamsize output_precision;
  };

  INLINE
  interval::interval(void)
  {
    lb_ = -GAOL_INFINITY;
    rb_ = GAOL_INFINITY;
  }
  
  INLINE
  interval::interval(double a)
  {
    lb_ = rb_ = a;
  }

  INLINE
  interval::interval(double a, double b)
  {
    lb_ = a;
    rb_ = b;
  }

  INLINE
  bool interval::is_empty(void) const
  {
    return !(left() <= right()); // Negation to handle NaNs
  }
  
  INLINE
  bool interval::is_symmetric(void) const
  {
    return (-left()) == right();
  }

  INLINE
  bool interval::certainly_positive(void) const
  {
    return is_empty() || (left() >= 0.0);
  }
  
  INLINE
  bool interval::certainly_negative(void) const
  {
    return is_empty() || (right() <= 0.0);
  }

  INLINE
  bool interval::certainly_strictly_positive(void) const
  {
    return is_empty() || (left() > 0.0);
    
  }
  
  INLINE
  bool interval::certainly_strictly_negative(void) const
  {
    return is_empty() || (right() < 0.0);
  }

  INLINE bool interval::certainly_ge(const interval &I) const
  {
    return I.is_empty() || (left() > I.right());
  }
  
  INLINE bool interval::certainly_geq(const interval &I) const
  {
    return I.is_empty() || (left() >= I.right());
  }
  
  INLINE bool interval::certainly_le(const interval &I) const
  {
    return is_empty() || (right() < I.left());
  }
  
  INLINE bool interval::certainly_leq(const interval &I) const
  {
      return is_empty() || (right() <= I.left());
  }
  

  INLINE bool interval::certainly_eq(const interval &I) const
  {
    return (is_empty() && I.is_empty()) || (right()<=I.right() && left() >= I.right());
  }

  INLINE bool interval::certainly_neq(const interval &I) const
  {
    return !certainly_eq(I);
  }


  INLINE bool interval::possibly_geq(const interval &I) const
  {
    return right()>= I.left();
  }
  
 
  INLINE bool interval::possibly_leq(const interval &I) const
  {
    return left() <= I.right();
  }
  
  INLINE bool interval::possibly_ge(const interval &I) const
  {
    return right() > I.left();
  }
  INLINE bool interval::possibly_le(const interval &I) const
  {
    return left() < I.right();
  }
  
  
  INLINE bool interval::possibly_eq(const interval &I) const
  {
    return (left() <= I.right()) && (right() >= I.left());
  }

  INLINE bool interval::possibly_neq(const interval &I) const
  {
    return (!is_empty() && !I.is_empty()) && !((right()<= I.left()) && (left()>=I.right()));
  }

  INLINE
  bool interval::is_zero(void) const
  {
    return (left() == 0.0 && right() == 0.0);
  }

  INLINE
  bool interval::straddles_zero(void) const
  {
    return (left() <= 0.0 && right() >= 0.0);
  }

  INLINE
  bool interval::strictly_straddles_zero(void) const
  {
    return (left() < 0.0 && right() > 0.0);
  }

  INLINE 
  bool interval::is_a_double(void) const
  {
    return left() == right();
  }

  INLINE 
  bool interval::is_an_int(void) const
  {
    return (left() == right()) && (std::floor(left()) == left()) && 
      (left() <= (std::numeric_limits<int>::max)() && // Strange call way needed by msvc++
       left() >= (std::numeric_limits<int>::min)());
  }
  
  INLINE 
  interval interval::operator+(void) const
  {
    return *this;
  }

  INLINE 
  interval interval::operator-(void) const
  {
    return interval(-right(),-left());
  }

  INLINE double
  interval::left(void) const
  {
    return lb_;
  }

  INLINE double
  interval::right(void) const
  {
    return rb_;
  }

  INLINE
  interval& interval::operator&=(const interval& I)
  {
    if (is_empty()) {
      return *this;
    }
    // From now on, "this" is known to be nonempty.
    if (!(I.left() <= left())) { // I.left() == NaN => lb_ <- NaN
      lb_ = I.left();
    }
    if (!(I.right() >= right())) {
      rb_ = I.right();
    }
    return *this;
  }

  INLINE
  interval& interval::operator|=(const interval& I)
  {
    if (is_empty()) {
      *this = I;
      return *this;
    }
    if (I.is_empty()) {
      return *this;
    }

    if (I.left() < left()) {
      lb_ = I.left();
    }
    if (I.right() > right()) {
      rb_ = I.right();
    }
    return *this;
  }

  INLINE bool interval::set_contains(const interval& I) const
  {
    return (I.is_empty() || ((left()<=I.left()) && (right()>=I.right())));
  }

  /**
    @note d should not be a NaN
    */
  INLINE bool interval::set_contains(double d) const
  {    
    return ((left()<=d)&&(right()>=d));
  }

  INLINE bool interval::set_strictly_contains(const interval& I) const
  {
    return (I.is_empty() || ((left()<I.left()) && (right()>I.right())));
  }

  /**
    @note d should not be a NaN
    */
  INLINE bool interval::set_strictly_contains(double d) const
  {    
    return ((left()<d) && (right()>d));
  }

  INLINE bool interval::set_disjoint(const interval &I) const
  {    
      return (right() < I.left()) || (left() > I.right()) 
	  || (is_empty() || I.is_empty());
  }

  INLINE bool interval::set_eq(const interval& I) const
  {
    return (is_empty() && I.is_empty()) || ((left()==I.left()) && (right()==I.right()));
  }

  INLINE bool interval::set_neq(const interval& I) const
  {
    return !set_eq(I);
  }
 
   INLINE bool interval::set_le(const interval& I) const
   {
       return (is_empty() && !I.is_empty()) || (left()>I.left() && right()<I.right());
   }
   
   INLINE bool interval::set_leq(const interval& I) const
   {
       return is_empty() || (left()>=I.left() && right()<=I.right());
   }

   INLINE bool interval::set_ge(const interval& I) const
  {
    return set_strictly_contains(I);
  }
   
   INLINE bool interval::set_geq(const interval& I) const
  {
    return set_contains(I);
  }

  INLINE void interval::split(interval &I1, interval &I2) const
  {
    double l = left(), m = midpoint(), r = right();
    I1 = interval(l,m);
    I2 = interval(m,r);
  }
 
  INLINE interval interval::split_left(void) const
  {
    return interval(left(),midpoint());
  }

  INLINE interval interval::split_right(void) const
  {
    return interval(midpoint(),right());
  }

  //! \brief Prototypes
  //@{
  /*!
    \brief Chi function
    
    Function given in:
    Interval Methods. Helmut Ratschek and Jon Rokne. Handbook of Global Optimization, 
    R. Horst and P.M. Pardalos (eds.), p. 751--828, 1995 Kluwer Academic Publishers.

    This function characterizes the degree of symmetry of intervals.
    
    Definition:
    chi([a,b]) = 0,    if a==b==0
               = a/b,  if |a| <= |b|
               = b/a,  otherwise

   */
  extern _GAOL_DLL_ double chi(const interval &I); 
  /*!
    \brief maximum of 2 intervals
   */
  extern _GAOL_DLL_ interval max(const interval &I, const interval &J);
  /*!
    \brief minimum of 2 intervals
   */
  extern _GAOL_DLL_ interval min(const interval &I, const interval &J);

  extern _GAOL_DLL_ std::ostream& operator<<(std::ostream& os, 
					     const interval& I);
  extern _GAOL_DLL_ std::istream& operator>>(std::istream& is, 
					     interval& I);
  //! I^2
  extern _GAOL_DLL_   interval sqr(const interval& I);  
  //! I^e for an integer e.
  extern _GAOL_DLL_   interval pow(const interval& I, int e);

  /// I^J
  extern _GAOL_DLL_   interval pow(const interval &I, const interval &J);
  /*! 
    \brief relational square root of J w.r.t. I
    \f$sqrt_rel(J,I) = Hull{x\in I\mid \exists y\in J\colon y=x^2}\f$
  */
extern _GAOL_DLL_   interval sqrt_rel(const interval& J, const interval& I);

  /*!
    \brief relational division of K by J w.r.t. I

    div_rel(K,J,I) = hull(x\in I\mid\exists z\in K\exists y\in J:z=xy)
   */
extern _GAOL_DLL_   interval div_rel(const interval &K, 
				      const interval &J, const interval &I);

  /*! 
    \brief square root of I
  */
extern _GAOL_DLL_   interval sqrt(const interval& I);
  /*! 
    \brief relational nth root of J w.r.t. I, for a positive n 
    \f$nthroot_rel(J,I) = Hull{x\in I\mid \exists y\in J\colon y=x^n}\f$
  */
extern _GAOL_DLL_   interval nth_root_rel(const interval& J, 
					   unsigned int n, const interval& I);
  /*! 
    \brief nth root of I for a positive n 
  */
extern _GAOL_DLL_   interval nth_root(const interval& I, unsigned int n);

  /*!
    \brief Returns the number of floating-point numbers in [a,b]
    
    - nb_fp_numbers(a,a+) == 2
    - nb_fp_numbers(a,a) == 1

    \warning Returns numeric_limits<ULONGLONGINT>::max() if either 
    a or b is a NaN or +/-oo. In addition, raises an invalid_action_error
    exception or calls gaol_error depending on the way the library was
    configured.
    \precond a must be smaller or equal to b
  */
extern _GAOL_DLL_   ULONGLONGINT nb_fp_numbers(double a, double b);

extern _GAOL_DLL_	  unsigned short int modulo_k_pi(const interval &I, double &k_left, double &k_right);

extern _GAOL_DLL_   interval exp(const interval& I);
extern _GAOL_DLL_   interval log(const interval& I);

extern _GAOL_DLL_   interval cos(const interval& I);
extern _GAOL_DLL_   interval tan(const interval& I);

extern _GAOL_DLL_   interval acos(const interval& I);
extern _GAOL_DLL_   interval asin(const interval& I);
extern _GAOL_DLL_   interval atan(const interval& I);
  
extern _GAOL_DLL_   interval atan2(const interval& Y, const interval& X);

extern _GAOL_DLL_   interval cosh(const interval& I);
extern _GAOL_DLL_   interval sinh(const interval& I);
extern _GAOL_DLL_   interval tanh(const interval& I);

extern _GAOL_DLL_   interval acosh(const interval& I);
extern _GAOL_DLL_   interval asinh(const interval& I);
extern _GAOL_DLL_   interval atanh(const interval& I);
  
extern _GAOL_DLL_   interval acos_rel(const interval& J, const interval &I);
extern _GAOL_DLL_   interval asin_rel(const interval& J, const interval &I);
extern _GAOL_DLL_   interval atan_rel(const interval& J, const interval &I);

extern _GAOL_DLL_   interval acosh_rel(const interval& J, const interval &I);
extern _GAOL_DLL_   interval asinh_rel(const interval& J, const interval &I);
extern _GAOL_DLL_   interval atanh_rel(const interval& J, const interval &I);

extern _GAOL_DLL_   interval abs(const interval &I);
extern _GAOL_DLL_   interval invabs_rel(const interval &J, const interval &I);
   
  //@}


  

  // Non-methods
  //@{
  /*!
    \brief 
   */

INLINE interval floor(const interval &I)
  {
    return interval(std::floor(I.left()),std::floor(I.right()));
  }
  
INLINE interval ceil(const interval &I)
  {
    return interval(std::ceil(I.left()),std::ceil(I.right()));
  }

INLINE interval integer(const interval &I)
  {
    return interval(std::ceil(I.left()),std::floor(I.right()));
  }

INLINE interval operator+(const interval& I, double d)
  {
    return interval(I)+=d;
  }

INLINE interval operator-(const interval& I, double d)
  {
    return interval(I)-=d;
  }


INLINE interval operator*(const interval& I, double d)
  {
    return interval(I)*=d;
  }

INLINE interval operator/(const interval& I, double d)
  {
    return interval(I)/=d;
  }

INLINE interval operator%(const interval& I, double d)
  {
    return interval(I)%=d;
  }

INLINE interval operator+(double d,const interval& I)
  {
    return interval(d)+=I;
  }

INLINE interval operator-(double d, const interval& I)
  {
    return interval(d)-=I;
  }

INLINE interval operator*(double d, const interval& I)
  {
    return interval(d)*=I;
  }

INLINE interval operator/(double d, const interval& I)
  {
    return interval(d)/=I;
  }

INLINE interval operator%(double d, const interval& I)
  {
    return interval(d)%=I;
  }

INLINE interval operator+(const interval& I1, const interval& I2)
  {
    return interval(I1) += I2;
  }

INLINE interval operator-(const interval& I1, const interval& I2)
  {
    return interval(I1) -= I2;
  }

INLINE interval operator*(const interval& I1, const interval& I2)
  {
    return interval(I1) *= I2;
  }

INLINE interval operator/(const interval& I1, const interval& I2)
  {
    return interval(I1) /= I2;
  }

INLINE interval operator%(const interval& I1, const interval& I2)
  {
    return interval(I1) %= I2;
  }

INLINE interval operator&(const interval& I1, const interval& I2)
  {
    return interval(I1) &= I2;
  }

INLINE interval operator|(const interval& I1, const interval& I2)
  {
    return interval(I1) |= I2;
  }

INLINE interval sin(const interval& I)
  {
    return cos(I-interval::half_pi);
  }

  //@}

  /*!
    \brief Diameter of an interval
    Returns the width of the interval (rounded upward).
    \note Returns -1 if the interval is empty
   */
INLINE double interval::width(void) const
{
    if (is_empty()) {
	return -1.0;
    } else {
	GAOL_RND_ENTER();
	return right() - left();
	GAOL_RND_LEAVE();
    }
}

  //! Relations
  //@{
INLINE bool operator==(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_eq(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_eq(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_eq(I2); 
#endif
  }

INLINE bool operator!=(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_neq(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_neq(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_neq(I2); 
#endif
  }

INLINE bool operator<=(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_leq(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_leq(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_leq(I2); 
#endif
  }

INLINE bool operator>=(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_geq(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_geq(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_geq(I2); 
#endif
  }

INLINE bool operator<(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_le(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_le(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_le(I2); 
#endif
  }

INLINE bool operator>(const interval &I1, const interval &I2)
  {
#if GAOL_SET_RELATION
    return I1.set_ge(I2);
#elif GAOL_CERTAINLY_RELATIONS
    return I1.certainly_ge(I2);
#else
    // No other case than GAOL_POSSIBLY_RELATIONS
    return I1.possibly_ge(I2); 
#endif
  }
 
  //@}
  

extern _GAOL_DLL_ bool feven(double d);

  
  /*!
    \brief Hausdorff distance between two intervals:

    hausdorff([a,b],[c,d]) = max(|a-c|,|b-d|)
   */
  extern _GAOL_DLL_ double hausdorff(const interval &I1, const interval &I2);

  /* 
     Including the right definition for the remaining methods depending on
     the architecture for which it is compiled
  */
#if (IX86_LINUX || IX86_CYGWIN)
  // Nothing done.
#elif SPARC_SOLARIS
#  include "gaol/sysdeps/gaol_interval_sparc.h"
#elif POWERPC_UNIX
#  include "gaol/sysdeps/gaol_interval_powerpc.h"
#elif defined (_MSC_VER)
#  include "gaol/sysdeps/gaol_interval_generic.h"
#else
#  error "unsupported platform"
#endif




} // namespace gaol

#endif /* __gaol_interval_h__ */
