/* ============================================================================
 * I B E X - Expressions
 * ============================================================================
 * Copyright   : Ecole des Mines de Nantes (FRANCE)
 * License     : This program can be distributed under the terms of the GNU LGPL.
 *               See the file COPYING.LESSER.
 *
 * Author(s)   : Gilles Chabert
 * Created     : Jan 05, 2012
 * ---------------------------------------------------------------------------- */

#ifndef _IBEX_EXPR_H
#define _IBEX_EXPR_H

#include <vector>
#include <iostream>

#include "ibex_SymbolMap.h"
#include "ibex_ExprVisitor.h"
#include "ibex_Interval.h"
#include "ibex_IntervalVector.h"
#include "ibex_IntervalMatrix.h"
#include "ibex_Dim.h"
#include "ibex_Domain.h"
#include "ibex_ExprLabel.h"

namespace ibex {

class ExprCtr;
class ExprIndex;
class Function;

/**
 * \ingroup symbolic
 * \brief Node in an expression.
 *
 * An object of this class is a node in a DAG, reprented by a #Function object.
 * Each node has a default decoration: the size of the subDAG (number of nodes) it represents
 * and the height of this node in the global expression.

 * All extra info can be stored in a generic decoration field, \a deco (See #ibex::Decorator).
 *
 * Example of <i>expression</i>: sin(x+y)^2*3.14.
 */
class ExprNode {

public:
	/** Builds a node of a given height, size and dimension.
	 * \see #height, #size, #dim. */
	ExprNode(int height, int size, const Dim& dim);

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const = 0;

	friend class Visitor;

	/**
	 * \brief Deletes this instance.
	 *
	 * Need to be virtual (see Function::~Function()) */
	virtual ~ExprNode();

	/** Streams out this expression. */
	friend std::ostream& operator<<(std::ostream&, const ExprNode&);

	/** height (following topological order) of this node in the DAG.
	 *  A leaf is at height 0. */
	const int height;

	/** Number of subnodes (including itself) in the DAG (not in the TREE:
	 * two subnodes referencing the same object count for 1).*/
	const int size;

	/** Unique number identifying this node in the global function.
	 *
	 * Undefined while this node is not part of a function expression. */
	const int id;

	/** Dimensions */
	const Dim dim;

	/** The label of this node.
	 *
	 * Uninitialized while this node is not part of a function expression. */
	mutable ExprLabel deco;

	/** The father node. NULL if none. */
	const ExprNode* father;

	/** Return true if this subexpression is the constant 0. */
	virtual bool is_zero() const;

	/** Return the type of this subexpression. */
	Dim::Type type() const;

	/** Indexing */
	const ExprIndex& operator[](int index) const;

	/** Create an equality constraint expr=expr. */
	const ExprCtr& operator=(const ExprNode& right) const;

	/** Create an equality constraint expr=value. */
	const ExprCtr& operator=(const Interval& value) const;

	/** Create an equality constraint expr=value. */
	const ExprCtr& operator=(const IntervalVector& value) const;

	/** Create an equality constraint expr=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const;

	/** Create an inequality constraint expr<=expr. */
	const ExprCtr& operator<=(const ExprNode& right) const;

	/** Create an inequality constraint expr<=value. */
	const ExprCtr& operator<=(const Interval& value) const;

	/** Create an inequality constraint expr>=expr. */
	const ExprCtr& operator>=(const ExprNode& right) const;

	/** Create an inequality constraint expr>=value. */
	const ExprCtr& operator>=(const Interval& value) const;

	/** Create an inequality constraint expr<value. */
	const ExprCtr& operator<(const ExprNode& right) const;

	/** Create an inequality constraint expr<value. */
	const ExprCtr& operator<(const Interval& value) const;

	/** Create an inequality constraint expr>expr. */
	const ExprCtr& operator>(const ExprNode& right) const;

	/** Create an inequality constraint expr>value. */
	const ExprCtr& operator>(const Interval& value) const;

	/**
	 * \brief Return all the subnodes.
	 *
	 * Subnodes appear only once in the array.
	 * The size of the array is this->size().
	 */
	const ExprNode** subnodes() const;

};

/**
 * \brief Streams out an expression.
 */
std::ostream& operator<<(std::ostream&, const ExprNode&);

/**
 * \brief Delete all the nodes of an expression, including itself.
 *
 * \param delete_symbols if false, symbols are not deleted.
 */
void cleanup(const ExprNode& expr, bool delete_symbols);

/**
 * \ingroup symbolic
 * \brief Indexed expression
 */
class ExprIndex : public ExprNode {

public:
	/** Accept an #ibex::ExprVisitor visitor. */
	void acceptVisitor(ExprVisitor& v) const { v.visit(*this); }

	/** Create an equality constraint expr[i]=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr[i]=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr[i]=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr[i]=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** The sub-expression */
	const ExprNode& expr;

	/** The index. */
	const int index;

	/**
	 * \brief Return true iff this node is an indexed symbol.
	 *
	 * E.g. x[0], x[0][1], x[0][1][0] are indexed symbols, (x+y)[0] is not.
	 */
	bool indexed_symbol() const;

	static const ExprIndex& new_(const ExprNode& subexpr, int index);

private:
	/** Create an indexed expression. */
	ExprIndex(const ExprNode& subexpr, int index);

};

/**
 * \ingroup symbolic
 * \brief N-ary expressions
 */
class ExprNAryOp : public ExprNode {
public:

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	/** Return a reference to the ith argument expression. */
	const ExprNode& arg(int i) const { return *args[i]; }

	/** The arguments. */
	const ExprNode** args;

	/** The number of arguments */
	const int nb_args;

	/** Delete the array (but not the subexpressions). */
	~ExprNAryOp();

protected:
	// TO DO: replace args by Array<...>
	ExprNAryOp(const ExprNode** args, int n, const Dim& dim);
};

/**
 * \ingroup symbolic
 * \brief Vector of expressions
 *
 * If e_1 and e_n are n column vectors of m elements,and v=[e_1 ... e_n] then
 * the type of v is a mxn matrix. In particular, by indexing v we get a row
 * of the matrix and not one of the e_i's. E.g., v[1] is the first row, not e_1 (the first column).
 * This ensures the consistency of indexing system: if one expression e is a matrix,
 * e[i] gives a row and e[i][j] the element (i,j) of the matrix. See also the comment of
 * #row_vector() const.
 * <p>
 * So v[i] can either be a scalar if v is a (row or column) vector, a row vector (if v is a matrix) or
 * a matrix (if v is an array of matrices). A column vector is not possible here.
 */
class ExprVector : public ExprNAryOp {
public:
	/**
	 * \brief Accept an #ibex::ExprVisitor visitor.
	 */
	void acceptVisitor(ExprVisitor& v) const { v.visit(*this); }

	/**
	 * \brief Create a vector of expressions.
	 */
	static const ExprVector& new_(const ExprNode** components, int n, bool in_rows);

	/**
	 * \brief Create a vector of expressions.
	 */
	static const ExprVector& new_(const Array<const ExprNode>& components, bool in_rows);

	/**
	 * \brief Create a vector of two expressions.
	 */
	static const ExprVector& new_(const ExprNode& e1, const ExprNode& e2, bool in_rows);

	/** \brief It the vector structured as a row or a column?
	 *
	 * \note A matrix is a "row vector" if it is a vector of column vectors.
	 * It is a "column vector" if it is a vector of row vectors.
	 * Important: this concerns the structure only, that is, the object viewed
	 * as an array of nodes. E.g., if *this is a row vector, then get(i) returns a column.
	 * But, as said above, in any case (*this)[i], as an expression, denotes the ith row.
	 */
	bool row_vector() const;

	/**
	 * \brief Get the ith component of the vector.
	 *
	 * \warning Not to be confused with operator[] (that build a new expression
	 * corresponding to the ith row of this expression). This function does not
	 * create any expression.
	 */
	const ExprNode& get(int i) const { return arg(i); }

	/**
	 * \brief Length of the vector.
	 *
	 * The length is the number of elements (not to be
	 * confused with the dimension #dim of the vector
	 * nor the #size() (that is, of the DAG)).
	 */
	int length() const { return nb_args; }

private:
	ExprVector(const ExprNode**, int n, bool in_row);

};

/**
 * (syntax sugar for users)
 */
class Return {
public:
	Return(const ExprNode& f1, const ExprNode& f2, bool in_rows=false) :
		vec(ExprVector::new_(f1,f2,in_rows)) { }
	Return(const ExprNode& f1, const ExprNode& f2, const ExprNode& f3, bool in_rows=false) :
		vec(ExprVector::new_(Array<const ExprNode>(f1,f2,f3),in_rows)) { }
	Return(const ExprNode& f1, const ExprNode& f2, const ExprNode& f3, const ExprNode& f4, bool in_rows=false) :
		vec(ExprVector::new_(Array<const ExprNode>(f1,f2,f3,f4),in_rows)) { }
	Return(const ExprNode& f1, const ExprNode& f2, const ExprNode& f3, const ExprNode& f4, const ExprNode& f5, bool in_rows=false) :
		vec(ExprVector::new_(Array<const ExprNode>(f1,f2,f3,f4,f5),in_rows)) { }
	Return(const ExprNode& f1, const ExprNode& f2, const ExprNode& f3, const ExprNode& f4, const ExprNode& f5, const ExprNode& f6, bool in_rows=false) :
		vec(ExprVector::new_(Array<const ExprNode>(f1,f2,f3,f4,f5,f6),in_rows)) { }

	operator const ExprVector&() const { return vec; }

	operator const ExprNode&() const { return vec; }

	const ExprIndex& operator[](int index) { return vec[index]; }

	const ExprVector& vec;
};

/**
 * \ingroup symbolic
 * \brief Function application expression
 *
 * In the following Quimper example:
 * \code
 * Variables
 *   a in [0,10];
 *
 * function z=foo(x,y)
 *   z=sqrt(x^2+y^2);
 * end;
 *
 * Constraints
 *   foo(a,1-a)=1
 * ...
 * \endcode
 * \a f(a,1-a) is an instance of ExprApply, where \link ExprApply::func func \endlink is "foo" and the
 * actual arguments arg(0) and arg(1) are the subexpressions \a a and \a 1-a.
 *
 * \see #ibex::Function::operator()(const ExprNode&).
 *
 */
class ExprApply : public ExprNAryOp {

public:

	/** Create an equality constraint apply=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint apply=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint apply=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint apply=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	/** The applied function. */
	const Function& func;

	static const ExprApply& new_(const Function& func, const ExprNode** args) {
		return *new ExprApply(func,args);
	}

private:

	ExprApply(const Function& expr, const ExprNode** args);
};

namespace parser {
class ExprEntity;
}


/**
 * \ingroup symbolic
 * \brief Leaf in the DAG
 */
class ExprLeaf : public ExprNode {
protected:
	ExprLeaf(const Dim& dim);
};

/**
 * \ingroup symbolic
 * \brief Symbol
 *
 * An instance of this class represents a leaf in the syntax tree. This leaf
 * merely contains the name of the symbol, a string (char*).
 */
class ExprSymbol : public ExprLeaf {

public:
	/** Create an equality constraint symbol=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint symbol=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint symbol=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint symbol=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	/** Deletes this instance. */
	~ExprSymbol();

	/** The symbol identifier. */
	const char* name;

	/** Key of this symbol. Every symbol in an expression is also
	 * an argument of the corresponding function; this key simply corresponds to the
	 * order of this symbol in the list of arguments. Initialized to -1. */
	int key;

	/* Create a new anonymous symbol. The string \a name is generated. */
	static const ExprSymbol& new_(const Dim& dim=Dim::scalar());

	/* Create a new symbol. The string \a name is duplicated. */
	static const ExprSymbol& new_(const char* name, const Dim& dim=Dim::scalar());

private:
	friend class Variable;
	friend class parser::ExprEntity;

	/** Create a symbol. */
	ExprSymbol(const Dim& dim);

	/** Create a symbol. */
	ExprSymbol(const char* name, const Dim& dim);

	/** Duplicate this symbol: forbidden. */
	ExprSymbol(const ExprSymbol&);
};

/**
 * \brief Variable.
 *
 * \note This is syntax sugar for users. The "real" class is ExprSymbol.
 */
class Variable {
public:
	/** Create a variable of dimension \a dim (by default: scalar). */
	explicit Variable(const Dim& dim=Dim::scalar()) : symbol(new ExprSymbol(dim)) { }

	/** Create a scalar variable named \a name. */
	explicit Variable(const char* name) : symbol(new ExprSymbol(name,Dim::scalar())) { }

	/** Create a variable of dimension \a dim named \a name. */
	Variable(const Dim& dim, const char* name) : symbol(new ExprSymbol(name, dim)) { }

	/** Create a vector variable of \a n components. */
	explicit Variable(int n) : symbol(new ExprSymbol(Dim::col_vec(n))) { }

	/** Create a vector variable of \a n components named \a name. */
	Variable(int n, const char* name) : symbol(new ExprSymbol(name, Dim::col_vec(n))) { }

	/** Create a \a m x \a n matrix variable. */
	Variable(int m, int n) : symbol(new ExprSymbol(Dim::matrix(m,n))) { }

	/** Create a \a m x \a n matrix variable named \a name. */
	Variable(int m, int n, const char* name) : symbol(new ExprSymbol(name, Dim::matrix(m,n))) { }

	/** Create a (\a k-sized array of \a m x \a n matrices) variable. */
	Variable(int k, int m, int n) : symbol(new ExprSymbol(Dim::matrix_array(k,m,n))) { }

	/** Create a (\a k-sized array of \a m x \a n matrices) variable named \a name. */
	Variable(int k, int m, int n, const char* name) : symbol(new ExprSymbol(name, Dim::matrix_array(k,m,n))) { }

	operator const ExprSymbol&() const {
		if (symbol->deco.f) // already used build new one.
			symbol=new ExprSymbol(symbol->name, symbol->dim);
		return *symbol;
	}

	operator const ExprNode&() const {
		if (symbol->deco.f) // already used build new one.
			symbol=new ExprSymbol(symbol->name, symbol->dim);
		return *symbol;
	}

	/** Create the expression x[index]. */
	const ExprIndex& operator[](int index) { return ((const ExprNode&) *this)[index]; }

	/** Create an equality constraint x=value. */
	const ExprCtr& operator=(const Interval& value) const { return ((const ExprNode&) *this)=value; }

	/** Create an equality constraint x=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((const ExprNode&) *this)=value; }

	/** Create an equality constraint x=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((const ExprNode&) *this)=value; }

	/** Create an inequality constraint x<=value. */
	const ExprCtr& operator<=(const Interval& value) const { return ((const ExprNode&) *this)<=value; }

	/** Create an inequality constraint x>=value. */
	const ExprCtr& operator>=(const Interval& value) const { return ((const ExprNode&) *this)>=value; }

	/** Create an inequality constraint x<value. */
	const ExprCtr& operator<(const Interval& value) const { return ((const ExprNode&) *this)<value; }

	/** Create an inequality constraint x>value. */
	const ExprCtr& operator>(const Interval& value) const { return ((const ExprNode&) *this)>value; }

	/** Create an equality constraint x=value. */
	const ExprCtr& operator=(const ExprNode& value) const { return ((const ExprNode&) *this)=value; }

	/** Create an inequality constraint x<=value. */
	const ExprCtr& operator<=(const ExprNode& value) const { return ((const ExprNode&) *this)<=value; }

	/** Create an inequality constraint x>=value. */
	const ExprCtr& operator>=(const ExprNode& value) const { return ((const ExprNode&) *this)>=value; }

	/** Create an inequality constraint x<value. */
	const ExprCtr& operator<(const ExprNode& value) const { return ((const ExprNode&) *this)<value; }

	/** Create an inequality constraint x>value. */
	const ExprCtr& operator>(const ExprNode& value) const { return ((const ExprNode&) *this)>value; }

	mutable ExprSymbol* symbol;
};

/**
 * \ingroup symbolic
 * \brief Constant expression
 */
class ExprConstant : public ExprLeaf {

public:
	/** Create a scalar constant. */
	static const ExprConstant& new_scalar(const Interval& value);

	/** Create a vector constant. */
	static const ExprConstant& new_vector(const IntervalVector& value, bool in_row);

	/** Create a matrix constant. */
	static const ExprConstant& new_matrix(const IntervalMatrix& value);

	/** Create a constant array of matrices. */
	static const ExprConstant& new_matrix_array(const IntervalMatrixArray& value);

	/** Create a constant from a domain. */
	static const ExprConstant& new_(const Domain& d, bool reference=false);

	/** Return true if this constant is either 0, the null vector or the null matrix. */
	virtual bool is_zero() const;

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	/** Return the value of the constant iff it is an Interval. */
	const Interval& get_value() const;

	/** Return the value of the constant iff it is an IntervalVector.*/
	const IntervalVector& get_vector_value() const;

	/** Return the value of the constant iff it is an IntervalMatrix. */
	const IntervalMatrix& get_matrix_value() const;

	/** Return the value of the constant iff it is an IntervalMatrixArray. */
	const IntervalMatrixArray& get_matrix_array_value() const;

	/** Return the value of the constant under the form of a domain. */
	const Domain& get() const;

	/** Return a copy of *this.
	 */
	const ExprConstant& copy() const;

private:
	friend class Visitor;

	ExprConstant(const Interval& value);

	ExprConstant(const IntervalVector& value, bool in_row);

	ExprConstant(const IntervalMatrix& value);

	ExprConstant(const IntervalMatrixArray& value);

	ExprConstant(const Domain& value, bool reference);

	/** Duplicate this constant: forbidden. */
	ExprConstant(const ExprConstant& c);

	Domain value;
};


/*==========================================================================================================*/
/*                                         Binary expressions                                               */
/*==========================================================================================================*/

/**
 * \ingroup symbolic
 * \brief Binary expression
 */
class ExprBinaryOp : public ExprNode {
public:
	/** Left subexpression. */
	const ExprNode& left;

	/** Right subexpression. */
	const ExprNode& right;

protected:
	friend class Visitor;

	ExprBinaryOp(const ExprNode& left, const ExprNode& right, const Dim& dim);

private:
	ExprBinaryOp(const ExprBinaryOp&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Addition of 2 expressions
 */
class ExprAdd : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const {
		v.visit(*this); };

	static const ExprAdd& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprAdd(left,right);
	}

private:
	ExprAdd(const ExprNode& left, const ExprNode& right);
	ExprAdd(const ExprAdd&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Multiplication of 2 expressions
 */
class ExprMul : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1*expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1*expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1*expr2=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1*expr2=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprMul& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprMul(left,right);
	}

private:
	ExprMul(const ExprNode& left, const ExprNode& right);
	ExprMul(const ExprMul&); // copy constructor forbidden
};


/**
 * \ingroup symbolic
 * \brief Subtraction of 2 expressions
 */
class ExprSub : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSub& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprSub(left,right);
	}

private:
	ExprSub(const ExprNode& left, const ExprNode& right);
	ExprSub(const ExprSub&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Division of 2 expressions
 */
class ExprDiv : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprDiv& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprDiv(left,right);
	}

private:
	ExprDiv(const ExprNode& left, const ExprNode& right);
	ExprDiv(const ExprDiv&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Maximum of 2 expressions
 */
class ExprMax : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprMax& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprMax(left,right);
	}

private:
	ExprMax(const ExprNode& left, const ExprNode& right);
	ExprMax(const ExprMax&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Minimum of 2 expressions
 */
class ExprMin : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprMin& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprMin(left,right);
	}

private:
	ExprMin(const ExprNode& left, const ExprNode& right);
	ExprMin(const ExprMin&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Atan2 of 2 expressions
 */
class ExprAtan2 : public ExprBinaryOp {
public:
	/** Create an equality constraint expr1+expr2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr1+expr2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAtan2& new_(const ExprNode& left, const ExprNode& right) {
		return *new ExprAtan2(left,right);
	}

private:
	ExprAtan2(const ExprNode& left, const ExprNode& right);
	ExprAtan2(const ExprAtan2&); // copy constructor forbidden
};
/*==========================================================================================================*/
/*                                         unary expressions                                                */
/*==========================================================================================================*/

/**
 * \ingroup symbolic
 * \brief Unary expression
 */
class ExprUnaryOp : public ExprNode {
public:

	/** The subexpression */
	const ExprNode& expr;

protected:
	ExprUnaryOp(const ExprNode& subexpr, const Dim& dim);

};

/**
 * \ingroup symbolic
 * \brief Minus an expression
 */
class ExprMinus : public ExprUnaryOp {
public:
	/** Create an equality constraint (-expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint (-expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint (-expr)=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint (-expr)=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprMinus& new_(const ExprNode& expr) { return *new ExprMinus(expr); }

private:
	ExprMinus(const ExprNode& expr) : ExprUnaryOp(expr,expr.dim) { }
	ExprMinus(const ExprMinus&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Transpose
 */
class ExprTrans : public ExprUnaryOp {
public:
	/** Create an equality constraint expr'=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr'=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr'=value. */
	const ExprCtr& operator=(const IntervalVector& value) const  { return ((ExprNode&) *this)=value; }

	/** Create an equality constraint expr'=value. */
	const ExprCtr& operator=(const IntervalMatrix& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprTrans& new_(const ExprNode& expr) { return *new ExprTrans(expr); }

private:
	ExprTrans(const ExprNode& expr) : ExprUnaryOp(expr,expr.dim.transpose_dim()) { }
	ExprTrans(const ExprTrans&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Sign of an expression
 */
class ExprSign : public ExprUnaryOp {
public:
	/** Create an equality constraint (-expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint (-expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSign& new_(const ExprNode& expr) { return *new ExprSign(expr); }

private:
	ExprSign(const ExprNode& expr);
	ExprSign(const ExprSign&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Absolute value of an expression
 */
class ExprAbs : public ExprUnaryOp {
public:
	/** Create an equality constraint (-expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint (-expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAbs& new_(const ExprNode& expr) { return *new ExprAbs(expr); }

private:
	ExprAbs(const ExprNode& expr);
	ExprAbs(const ExprAbs&); // copy constructor forbidden
};


/**
 * \ingroup symbolic
 * \brief Power expression.
 */
class ExprPower : public ExprUnaryOp {

public:
	/** Create an equality constraint expr^n=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr^n=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprPower& new_(const ExprNode& expr, int expon) {
		return *new ExprPower(expr,expon);
	}

	const int expon;

private:
	ExprPower(const ExprNode& expr, int expon) : ExprUnaryOp(expr,expr.dim), expon(expon) { }
	ExprPower(const ExprPower&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Square of an expression.
 */
class ExprSqr : public ExprUnaryOp {

public:
	/** Create an equality constraint expr^2=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint expr^2=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSqr& new_(const ExprNode& expr) {
		return *new ExprSqr(expr);
	}

private:
	ExprSqr(const ExprNode& expr);
	ExprSqr(const ExprSqr&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Square root of an expression.
 */
class ExprSqrt : public ExprUnaryOp {

public:
	/** Create an equality constraint sqrt(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint sqrt(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSqrt& new_(const ExprNode& expr) { return *new ExprSqrt(expr); }

private:
	ExprSqrt(const ExprNode& expr);
	ExprSqrt(const ExprSqrt&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Exponential of an expression.
 */
class ExprExp : public ExprUnaryOp {

public:
	/** Create an equality constraint e^expr=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint e^expr=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprExp& new_(const ExprNode& expr) {
		return *new ExprExp(expr);
	}

private:
	ExprExp(const ExprNode& expr);
	ExprExp(const ExprExp&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Neperian logarithm of an expression.
 */
class ExprLog : public ExprUnaryOp {

public:
	/** Create an equality constraint log(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint log(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprLog& new_(const ExprNode& expr) {
		return *new ExprLog(expr);
	}

private:
	ExprLog(const ExprNode& expr);
	ExprLog(const ExprLog&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Cosine of an expression.
 */
class ExprCos : public ExprUnaryOp {

public:
	/** Create an equality constraint cos(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint cos(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprCos& new_(const ExprNode& expr) {
		return *new ExprCos(expr);
	}

private:
	ExprCos(const ExprNode& expr);
	ExprCos(const ExprCos&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Sine of an expression.
 */
class ExprSin : public ExprUnaryOp {

public:
	/** Create an equality constraint sin(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint sin(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSin& new_(const ExprNode& expr) {
		return *new ExprSin(expr);
	}

private:
	ExprSin(const ExprNode& expr);
	ExprSin(const ExprSin&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Tangent of an expression.
 */
class ExprTan : public ExprUnaryOp {

public:
	/** Create an equality constraint tan(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint tan(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprTan& new_(const ExprNode& expr) {
		return *new ExprTan(expr);
	}

private:
	ExprTan(const ExprNode& expr);
	ExprTan(const ExprTan&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Hyperbolic cosine of an expression.
 */
class ExprCosh : public ExprUnaryOp {

public:
	/** Create an equality constraint cosh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint cosh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprCosh& new_(const ExprNode& expr) {
		return *new ExprCosh(expr);
	}

private:
	ExprCosh(const ExprNode& expr);
	ExprCosh(const ExprCosh&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Hyperbolic sine of an expression.
 */
class ExprSinh : public ExprUnaryOp {

public:
	/** Create an equality constraint sinh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint sinh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprSinh& new_(const ExprNode& expr) {
		return *new ExprSinh(expr);
	}

private:
	ExprSinh(const ExprNode& expr);
	ExprSinh(const ExprSinh&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Hyperbolic tangent of an expression.
 */
class ExprTanh : public ExprUnaryOp {

public:
	/** Create an equality constraint tanh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint tanh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprTanh& new_(const ExprNode& expr) {
		return *new ExprTanh(expr);
	}

private:
	ExprTanh(const ExprNode& expr);
	ExprTanh(const ExprTanh&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse cosine of an expression.
 */
class ExprAcos : public ExprUnaryOp {

public:
	/** Create an equality constraint acos(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint acos(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAcos& new_(const ExprNode& expr) {
		return *new ExprAcos(expr);
	}

private:
	ExprAcos(const ExprNode& expr);
	ExprAcos(const ExprAcos&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse sine of an expression.
 */
class ExprAsin : public ExprUnaryOp {

public:
	/** Create an equality constraint asin(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint asin(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAsin& new_(const ExprNode& expr) {
		return *new ExprAsin(expr);
	}

private:
	ExprAsin(const ExprNode& expr);
	ExprAsin(const ExprAsin&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse tangent of an expression.
 */
class ExprAtan : public ExprUnaryOp {

public:
	/** Create an equality constraint atan(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint atan(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAtan& new_(const ExprNode& expr) {
		return *new ExprAtan(expr);
	}

private:
	ExprAtan(const ExprNode& expr);
	ExprAtan(const ExprAtan&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse hyperbolic cosine of an expression.
 */
class ExprAcosh : public ExprUnaryOp {

public:
	/** Create an equality constraint acosh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint acosh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAcosh& new_(const ExprNode& expr) {
		return *new ExprAcosh(expr);
	}

private:
	ExprAcosh(const ExprNode& expr);
	ExprAcosh(const ExprAcosh&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse hyperbolic sine of an expression.
 */
class ExprAsinh : public ExprUnaryOp {

public:
	/** Create an equality constraint asinh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint asinh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAsinh& new_(const ExprNode& expr) {
		return *new ExprAsinh(expr);
	}

private:
	ExprAsinh(const ExprNode& expr);
	ExprAsinh(const ExprAsinh&); // copy constructor forbidden
};

/**
 * \ingroup symbolic
 * \brief Inverse hyperbolic tangent of an expression.
 */
class ExprAtanh : public ExprUnaryOp {

public:
	/** Create an equality constraint atanh(expr)=expr. */
	const ExprCtr& operator=(const ExprNode& expr) const { return ((ExprNode&) *this)=expr; }

	/** Create an equality constraint atanh(expr)=value. */
	const ExprCtr& operator=(const Interval& value) const  { return ((ExprNode&) *this)=value; }

	/** Accept an #ibex::ExprVisitor visitor. */
	virtual void acceptVisitor(ExprVisitor& v) const { v.visit(*this); };

	static const ExprAtanh& new_(const ExprNode& expr) {
		return *new ExprAtanh(expr);
	}

private:
	ExprAtanh(const ExprNode& expr);
	ExprAtanh(const ExprAtanh&); // copy constructor forbidden
};


/* ============================================================================
 	 	 	 	 	 	 	 inline implementation
  ============================================================================*/

inline ExprNode::~ExprNode() {
}

inline bool ExprNode::is_zero() const {
	return false; }

inline Dim::Type ExprNode::type() const {
	return dim.type(); }

inline const ExprIndex& ExprNode::operator[](int index) const {
	return ExprIndex::new_(*this, index); }

inline const ExprIndex& ExprIndex::new_(const ExprNode& subexpr, int index) {
	return *new ExprIndex(subexpr,index); }

inline bool ExprVector::row_vector() const {
	return (dim.type()==Dim::ROW_VECTOR || get(0).type()==Dim::COL_VECTOR); /* last case occurs if *this is a matrix */ }

inline ExprLeaf::ExprLeaf(const Dim& dim) : ExprNode(0,1,dim) { }

inline ExprSymbol::~ExprSymbol() {
	free((char*) name); }

inline const ExprSymbol& ExprSymbol::new_(const char* name, const Dim& dim) {
	return *new ExprSymbol(name,dim); }

inline ExprSymbol::ExprSymbol(const char* name, const Dim& dim)
: ExprLeaf(dim), name(strdup(name)), key(-1) { }

inline const ExprConstant& ExprConstant::new_scalar(const Interval& value) {
	return *new ExprConstant(value); }

inline const ExprConstant& ExprConstant::new_vector(const IntervalVector& value, bool in_row) {
	return *new ExprConstant(value,in_row); }

inline const ExprConstant& ExprConstant::new_matrix(const IntervalMatrix& value) {
	return *new ExprConstant(value); }

inline const ExprConstant& ExprConstant::new_matrix_array(const IntervalMatrixArray& value) {
	return *new ExprConstant(value); }

inline const ExprConstant& ExprConstant::new_(const Domain& value, bool reference) {
	return *new ExprConstant(value,reference); }

inline const Interval& ExprConstant::get_value() const {
	return value.i(); }

inline const IntervalVector& ExprConstant::get_vector_value() const {
	return value.v(); }

inline const IntervalMatrix& ExprConstant::get_matrix_value() const {
	return value.m(); }

inline const IntervalMatrixArray& ExprConstant::get_matrix_array_value() const {
	return value.ma(); }

inline const Domain& ExprConstant::get() const {
	return value; }

/** Addition */
inline const ExprAdd& operator+(const ExprNode& left, const ExprNode& right) {
	return ExprAdd::new_(left, right); }

/** Subtraction */
inline const ExprSub& operator-(const ExprNode& left, const ExprNode& right) {
	return ExprSub::new_(left, right); }

/** Multiplication */
inline const ExprMul& operator*(const ExprNode& left, const ExprNode& right) {
	return ExprMul::new_(left, right); }

/** Division */
inline const ExprDiv& operator/(const ExprNode& left, const ExprNode& right) {
	return ExprDiv::new_(left, right); }

/** Maximum */
inline const ExprMax& max(const ExprNode& left, const ExprNode& right) {
	return ExprMax::new_(left, right); }

/** Minimum */
inline const ExprMin& min(const ExprNode& left, const ExprNode& right) {
	return ExprMin::new_(left, right); }

/** Arctangent2 of two expressions */
inline const ExprAtan2& atan2(const ExprNode& exp1, const ExprNode& exp2) {
	return ExprAtan2::new_(exp1, exp2); }

/** Addition of an expression to a constant */
inline const ExprAdd& operator+(const ExprNode& left, const Interval& value) {
	return left+ExprConstant::new_scalar(value); }

/** Addition of an expression to a constant vector */
inline const ExprAdd& operator+(const ExprNode& left, const IntervalVector& vec) {
	return left+ExprConstant::new_vector(vec, left.type()==Dim::ROW_VECTOR); }

/** Addition of an expression to a constant matrix */
inline const ExprAdd& operator+(const ExprNode& left, const IntervalMatrix& m) {
	return left+ExprConstant::new_matrix(m); }

/** Subtraction of an expression from a constant */
inline const ExprSub& operator-(const ExprNode& left, const Interval& value) {
	return left-ExprConstant::new_scalar(value); }

/** Subtraction of an expression to a constant vector */
inline const ExprSub& operator-(const ExprNode& left, const IntervalVector& vec) {
	return left-ExprConstant::new_vector(vec, left.type()==Dim::ROW_VECTOR); }

/** Subtraction of an expression to a constant matrix */
inline const ExprSub& operator-(const ExprNode& left, const IntervalMatrix& m) {
	return left-ExprConstant::new_matrix(m); }

/** Multiplication of an expression by a constant */
inline const ExprMul& operator*(const ExprNode& left, const Interval& value) {
	return left*ExprConstant::new_scalar(value); }

/** Multiplication of an expression by a constant vector */
inline const ExprMul& operator*(const ExprNode& left, const IntervalVector& vec) {
	return left*ExprConstant::new_vector(vec, false); }

/** Multiplication of an expression by a constant */
inline const ExprMul& operator*(const ExprNode& left, const IntervalMatrix& m) {
	return left*ExprConstant::new_matrix(m); }

/** Division of an expression by a constant */
inline const ExprDiv& operator/(const ExprNode& left, const Interval& value) {
	return left/ExprConstant::new_scalar(value); }

/** Maximum of an expression and a constant */
inline const ExprMax& max(const ExprNode& left, const Interval& value) {
	return max(left, ExprConstant::new_scalar(value)); }

/** Minimum of an expression and a constant */
inline const ExprMin& min(const ExprNode& left, const Interval& value) {
	return min(left, ExprConstant::new_scalar(value)); }

/** Arctangent2 of an expression and a constant */
inline const ExprAtan2& atan2(const ExprNode& exp1, const Interval& value) {
	return ExprAtan2::new_(exp1, ExprConstant::new_scalar(value)); }

/** Addition of a constant to an expression */
inline const ExprAdd& operator+(const Interval& value, const ExprNode& right) {
	return ExprConstant::new_scalar(value)+right; }

/** Addition of a vector constant to an expression */
inline const ExprAdd& operator+(const IntervalVector& vec, const ExprNode& right) {
	return ExprConstant::new_vector(vec, right.type()==Dim::ROW_VECTOR)+right; }

/** Addition of a matrix constant to an expression */
inline const ExprAdd& operator+(const IntervalMatrix& m, const ExprNode& right) {
	return ExprConstant::new_matrix(m)+right; }

/** Subtraction of a constant from an expression */
inline const ExprSub& operator-(const Interval& value, const ExprNode& right) {
	return ExprConstant::new_scalar(value)-right; }

/** Subtraction of a vector constant to an expression */
inline const ExprSub& operator-(const IntervalVector& vec, const ExprNode& right) {
	return ExprConstant::new_vector(vec, right.type()==Dim::ROW_VECTOR)-right; }

/** Subtraction of a matrix constant to an expression */
inline const ExprSub& operator-(const IntervalMatrix& m, const ExprNode& right) {
	return ExprConstant::new_matrix(m)-right; }

/** Multiplication of a constant by an expression*/
inline const ExprMul& operator*(const Interval& value, const ExprNode& right) {
	return ExprConstant::new_scalar(value)*right; }

/** Multiplication of a vector constant by an expression*/
inline const ExprMul& operator*(const IntervalVector& vec, const ExprNode& right) {
	return ExprConstant::new_vector(vec, true)*right; }

/** Multiplication of a matrix constant by an expression*/
inline const ExprMul& operator*(const IntervalMatrix& m, const ExprNode& right) {
	return ExprConstant::new_matrix(m)*right; }

/** Division of a constant by an expression */
inline const ExprDiv& operator/(const Interval& value, const ExprNode& right) {
	return ExprConstant::new_scalar(value)/right; }

/** Maximum of a constant and an expression */
inline const ExprMax& max (const Interval& value, const ExprNode& right) {
	return max(ExprConstant::new_scalar(value), right); }

/** Minimum of a constant and an expression */
inline const ExprMin& min (const Interval& value, const ExprNode& right) {
	return min(ExprConstant::new_scalar(value), right); }

/** Arctangent2 of a constant and an expression */
inline const ExprAtan2& atan2(const Interval& value, const ExprNode& exp2) {
	return ExprAtan2::new_(ExprConstant::new_scalar(value), exp2); }

/** Square of an expression */
inline const ExprSqr& sqr  (const ExprNode& exp) { return ExprSqr::new_(exp); }

/** Square root of an expression */
inline const ExprSqrt& sqrt (const ExprNode& exp) { return ExprSqrt::new_(exp); }

/** Exponential of an expression */
inline const ExprExp& exp  (const ExprNode& exp) { return ExprExp::new_(exp); }

/** Neperian logarithm of an expression */
inline const ExprLog& log  (const ExprNode& exp) { return ExprLog::new_(exp); }

/** Cosine of an expression */
inline const ExprCos& cos  (const ExprNode& exp) { return ExprCos::new_(exp); }

/** Sine of an expression */
inline const ExprSin& sin  (const ExprNode& exp) { return ExprSin::new_(exp); }

/** Tangent of an expression */
inline const ExprTan& tan  (const ExprNode& exp) { return ExprTan::new_(exp); }

/** Arccosine of an expression */
inline const ExprAcos& acos (const ExprNode& exp) { return ExprAcos::new_(exp); }

/** Arcsine of an expression */
inline const ExprAsin& asin (const ExprNode& exp) { return ExprAsin::new_(exp); }

/** Arctangent of an expression */
inline const ExprAtan& atan (const ExprNode& exp) { return ExprAtan::new_(exp); }

/** Hyperbolic cosine of an expression */
inline const ExprCosh& cosh (const ExprNode& exp) { return ExprCosh::new_(exp); }

/** Hyperbolic sine of an expression */
inline const ExprSinh& sinh (const ExprNode& exp) { return ExprSinh::new_(exp); }

/** Hyperbolic tangent of an expression */
inline const ExprTanh& tanh (const ExprNode& exp) { return ExprTanh::new_(exp); }

/** Inverse hyperbolic cosine of an expression */
inline const ExprAcosh& acosh(const ExprNode& exp) { return ExprAcosh::new_(exp); }

/** Inverse hyperbolic sine of an expression */
inline const ExprAsinh& asinh(const ExprNode& exp) { return ExprAsinh::new_(exp); }

/** Inverse hyperbolic tangent of an expression */
inline const ExprAtanh& atanh(const ExprNode& exp) { return ExprAtanh::new_(exp); }

/** Raises \a left to the power \a expnon.
    \note operator ^ is not used because its associativity and priority defined in C++ does
    not match mathematical usage. */
inline const ExprNode& pow(const ExprNode& left, int expon) {
	if (expon==1) return left;
	if (expon==2) return sqr(left);
	return ExprPower::new_(left, expon);
}

/** Minus sign */
inline const ExprMinus& operator-(const ExprNode& expr) {
	return ExprMinus::new_(expr);
}

/** Transpose */
inline const ExprTrans& transpose(const ExprNode& expr) {
	return ExprTrans::new_(expr);
}

/** Sign */
inline const ExprSign& sign(const ExprNode& expr) {
	return ExprSign::new_(expr);
}

/** Absolute value */
inline const ExprAbs& abs(const ExprNode& expr) {
	return ExprAbs::new_(expr);
}

/** Expression raised to the power of another expression */
inline const ExprExp& pow(const ExprNode& left, const ExprNode& right) {
	return exp(right*log(left));
}

/** Expression raised to the power of a constant */
inline const ExprExp& pow(const ExprNode& left, const Interval& value) {
	return exp(ExprConstant::new_scalar(value)*log(left));
}
/** Constant raised to the power of an expression */
inline const ExprExp& pow(const Interval& value, const ExprNode& right) {
	return exp(right*log(ExprConstant::new_scalar(value)));
}

} // end namespace ibex

#endif // end _IBEX_EXPR_H
