#ifndef Rcpp__sugar__pow_h
#define Rcpp__sugar__pow_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T, typename EXPONENT_TYPE>
class Pow : public SugarVectorExpression< REALSXP ,NA, Pow<RTYPE,NA,T,EXPONENT_TYPE> > {
public:
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

	Pow( const T& object_, EXPONENT_TYPE exponent ) : object(object_), op(exponent) {}

	inline double operator[]( int i ) const {
	    return ::pow( object[i], op );
	}
	inline int size() const { return object.size() ; }

private:
	const T& object ;
	EXPONENT_TYPE op ;
} ;

template <bool NA, typename T, typename EXPONENT_TYPE>
class Pow<INTSXP,NA,T,EXPONENT_TYPE> : public SugarVectorExpression< REALSXP ,NA, Pow<INTSXP,NA,T,EXPONENT_TYPE> > {
public:
	Pow( const T& object_, EXPONENT_TYPE exponent ) : object(object_), op(exponent) {}

	inline double operator[]( int i ) const {
		int x = object[i] ;
	    return x == NA_INTEGER ? NA_INTEGER : ::pow( x, op );
	}
	inline int size() const { return object.size() ; }

private:
	const T& object ;
	EXPONENT_TYPE op ;
} ;
template <typename T, typename EXPONENT_TYPE>
class Pow<INTSXP,false,T,EXPONENT_TYPE> : public SugarVectorExpression< REALSXP ,false, Pow<INTSXP,false,T,EXPONENT_TYPE> > {
public:
	Pow( const T& object_, EXPONENT_TYPE exponent ) : object(object_), op(exponent) {}

	inline double operator[]( int i ) const {
	    return ::pow( object[i], op );
	}
	inline int size() const { return object.size() ; }

private:
	const T& object ;
	EXPONENT_TYPE op ;
} ;


} // sugar

template <int RTYPE, bool NA, typename T, typename EXPONENT_TYPE>
inline sugar::Pow<RTYPE,NA,T,EXPONENT_TYPE> pow( 
	const VectorBase<RTYPE,NA,T>& t, 
	EXPONENT_TYPE exponent
){
	return sugar::Pow<RTYPE,NA,T,EXPONENT_TYPE>( t.get_ref() , exponent ) ;
}


} // Rcpp
#endif

