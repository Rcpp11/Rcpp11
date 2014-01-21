#ifndef Rcpp_wrap_primitive_wrap_h
#define Rcpp_wrap_primitive_wrap_h
 
namespace Rcpp{
namespace internal{
	
/**
 * wraps a single primitive value when there is no need for a cast
 */
template <typename T>
inline SEXP primitive_wrap__impl__cast( const T& object, std::false_type ){
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
	Shield<SEXP> x = Rf_allocVector( RTYPE, 1 );
	r_vector_start<RTYPE>(x)[0] = object ;
	return x;
}

/**
 * wraps a single primitive value when a cast is needed
 */ 
template <typename T>
inline SEXP primitive_wrap__impl__cast( const T& object, std::true_type ){
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
	typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE_TYPE ;
	Shield<SEXP> x = Rf_allocVector( RTYPE, 1 );
	r_vector_start<RTYPE>(x)[0] = caster<T,STORAGE_TYPE>(object) ;
	return x;
}

/**
 * primitive wrap for 'easy' primitive types: int, double, Rbyte, Rcomplex
 *
 * This produces a vector of length 1 of the appropriate type
 */
template <typename T>
inline SEXP primitive_wrap__impl( const T& object, ::Rcpp::traits::r_type_primitive_tag ){
	return primitive_wrap__impl__cast( object, typename ::Rcpp::traits::r_sexptype_needscast<T>() ); 
}

/**
 * primitive wrap for types that can be converted implicitely to std::string or std::wstring
 * 
 * This produces a character vector of length 1 containing the std::string or wstring
 */
template <typename T>
inline SEXP primitive_wrap__impl( const T& object, ::Rcpp::traits::r_type_string_tag){
	RCPP_DEBUG( "primitive_wrap__impl<%s>(., r_type_string_tag )", DEMANGLE(T) )
	return Rf_ScalarString( make_charsexp(object) ) ;
}


/**
 * called when T is a primitive type : int, bool, double, std::string, etc ...
 * This uses the Rcpp::traits::r_type_traits on the type T to perform
 * further dispatching and wrap the object into an vector of length 1
 * of the appropriate SEXP type 
 */
template <typename T>
inline SEXP primitive_wrap(const T& object){
	RCPP_DEBUG( "primitive_wrap<%s>()", DEMANGLE(T) )
	return primitive_wrap__impl( object, typename ::Rcpp::traits::r_type_traits<T>::r_category() ) ;
}

}
}

#endif
