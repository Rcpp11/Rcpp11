#ifndef Rcpp__sugar__Comparator_With_One_Value_h
#define Rcpp__sugar__Comparator_With_One_Value_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, typename Operator, bool NA, typename T>
class Comparator_With_One_Value : public ::Rcpp::VectorBase< LGLSXP, true, Comparator_With_One_Value<RTYPE,Operator,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;
	typedef int (Comparator_With_One_Value::*METHOD)(int) const ;
	
	Comparator_With_One_Value( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
		lhs(lhs_), rhs(rhs_), m(), op() {
		
			m = Rcpp::traits::is_na<RTYPE>(rhs) ? 
				&Comparator_With_One_Value::rhs_is_na :
				&Comparator_With_One_Value::rhs_is_not_na ;
			
	}
	
	inline int operator[]( int i ) const {
		return (this->*m)(i) ;
	}
	
	inline int size() const { return lhs.size() ; }
	
private:
	const VEC_TYPE& lhs ;
	STORAGE rhs ;
	METHOD m ;
	Operator op ;

	inline int rhs_is_na(int i) const { return rhs ; }
	inline int rhs_is_not_na(int i) const { 
		STORAGE x = lhs[i] ;
		return Rcpp::traits::is_na<RTYPE>(x) ? x : op( x, rhs ) ;
	}
	
} ;


template <int RTYPE, typename Operator, typename T>
class Comparator_With_One_Value<RTYPE,Operator,false,T> : 
	public ::Rcpp::VectorBase< RTYPE, true, Comparator_With_One_Value<LGLSXP,Operator,false,T> > {

public:
	typedef typename Rcpp::VectorBase<RTYPE,false,T> VEC_TYPE ;
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;
	typedef int (Comparator_With_One_Value::*METHOD)(int) const ;
	
	Comparator_With_One_Value( const VEC_TYPE& lhs_, STORAGE rhs_ ) : 
		lhs(lhs_), rhs(rhs_), m(), op() {
		
			m = Rcpp::traits::is_na<RTYPE>(rhs) ? 
				&Comparator_With_One_Value::rhs_is_na :
				&Comparator_With_One_Value::rhs_is_not_na ;
			
	}
	
	inline int operator[]( int i ) const {
		return (this->*m)(i) ;
	}
	
	inline int size() const { return lhs.size() ; }
	
private:
	const VEC_TYPE& lhs ;
	STORAGE rhs ;
	METHOD m ;
	Operator op ;

	inline int rhs_is_na(int i) const { return rhs ; }
	inline int rhs_is_not_na(int i) const { 
		return op( lhs[i], rhs ) ;
	}
	
} ;


} // sugar
} // Rcpp





#endif
