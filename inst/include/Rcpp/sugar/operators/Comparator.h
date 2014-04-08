#ifndef Rcpp__sugar__Comparator_h
#define Rcpp__sugar__Comparator_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, typename Operator, bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
class Comparator : 
	public SugarVectorExpression< LGLSXP, true, Comparator<RTYPE,Operator,LHS_NA,LHS_T,RHS_NA,RHS_T> > {

public:
	typedef typename Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T> LHS_TYPE ;
	typedef typename Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;

	Comparator( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_) : 
		lhs(lhs_), rhs(rhs_), op() {}

	inline int operator[]( int i ) const {
		STORAGE x = lhs[i] ;
		if( Rcpp::traits::is_na<RTYPE>( x ) ) return NA_LOGICAL ;
		STORAGE y = rhs[i] ;
		if( Rcpp::traits::is_na<RTYPE>( y ) ) return NA_LOGICAL ;
		return op( x, y ) ;
	}

	inline int size() const { return lhs.size() ; }

private:
	const LHS_TYPE& lhs ;
	const RHS_TYPE& rhs ;
	Operator op ;

} ;



template <int RTYPE, typename Operator, typename LHS_T, bool RHS_NA, typename RHS_T>
class Comparator<RTYPE,Operator,false,LHS_T,RHS_NA,RHS_T> : 
	public SugarVectorExpression< LGLSXP, true, Comparator<RTYPE,Operator,false,LHS_T,RHS_NA,RHS_T> > {

public:
	typedef typename Rcpp::VectorBase<RTYPE,false,LHS_T> LHS_TYPE ;
	typedef typename Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;

	Comparator( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_) : 
		lhs(lhs_), rhs(rhs_), op() {}

	inline int operator[]( int i ) const {
		STORAGE y = rhs[i] ;
		if( Rcpp::traits::is_na<RTYPE>( y ) ) return NA_LOGICAL ;
		return op( lhs[i], y ) ;
	}

	inline int size() const { return lhs.size() ; }

private:
	const LHS_TYPE& lhs ;
	const RHS_TYPE& rhs ;
	Operator op ;

} ;


template <int RTYPE, typename Operator, typename LHS_T, typename RHS_T>
class Comparator<RTYPE,Operator,false,LHS_T,false,RHS_T> : 
	public SugarVectorExpression< LGLSXP, true, Comparator<RTYPE,Operator,false,LHS_T,false,RHS_T> > {

public:
	typedef typename Rcpp::VectorBase<RTYPE,false,LHS_T> LHS_TYPE ;
	typedef typename Rcpp::VectorBase<RTYPE,false,RHS_T> RHS_TYPE ;
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;

	Comparator( const LHS_TYPE& lhs_, const RHS_TYPE& rhs_) : 
		lhs(lhs_), rhs(rhs_), op() {}

	inline int operator[]( int i ) const {
		return op( lhs[i], rhs[i] ) ;
	}

	inline int size() const { return lhs.size() ; }

private:
	const LHS_TYPE& lhs ;
	const RHS_TYPE& rhs ;
	Operator op ;

} ;


}
}


#endif
