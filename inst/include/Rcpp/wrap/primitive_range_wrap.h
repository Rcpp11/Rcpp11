#ifndef Rcpp_wrap_primitive_range_wrap_h
#define Rcpp_wrap_primitive_range_wrap_h
 
namespace Rcpp{
namespace internal{
	
// {{{ range wrap 
// {{{ unnamed range wrap

/**
 * Range based primitive wrap implementation. used when 
 * - T is a primitive type, indicated by the r_type_traits
 * - T needs a static_cast to be of the type suitable to fit in the R vector
 *
 * This produces an unnamed vector of the appropriate type using the 
 * std::transform algorithm
 */
template <typename InputIterator, typename T>
inline SEXP primitive_range_wrap__impl( InputIterator first, InputIterator last, std::true_type ){
	RCPP_DEBUG( "primitive_range_wrap__impl< InputIterator = %s , T = %s>(.,., true_type )\n", DEMANGLE(InputIterator), DEMANGLE(T) ) ;
	size_t size = std::distance( first, last ) ;
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
	Shield<SEXP> x = Rf_allocVector( RTYPE, size ) ;
	std::transform( first, last, r_vector_start<RTYPE>(x), 
		caster< T, typename ::Rcpp::traits::storage_type<RTYPE>::type >
		) ; 
	return x ;
}

template <typename InputIterator, typename T>
inline SEXP primitive_range_wrap__impl__nocast( InputIterator first, InputIterator last, std::random_access_iterator_tag ){
	size_t size = std::distance( first, last ) ;
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
	Shield<SEXP> x = Rf_allocVector( RTYPE, size ) ;
	                                          
	typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
	int __trip_count = size >> 2 ;
	STORAGE* start = r_vector_start<RTYPE>(x) ;
	size_t i = 0 ;
	for ( ; __trip_count > 0 ; --__trip_count) { 
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
    	start[i] = first[i] ; i++ ;            
	}                                            
	switch (size - i){                          
	  case 3:                                    
	      start[i] = first[i] ; i++ ;             
      case 2:                                    
	      start[i] = first[i] ; i++ ;             
	  case 1:                                    
	      start[i] = first[i] ; i++ ;             
	  case 0:                                    
	  default:                                   
	      {}                         
	}                                            
	
	return x ;
}

template <typename InputIterator, typename T>
inline SEXP primitive_range_wrap__impl__nocast( InputIterator first, InputIterator last, std::input_iterator_tag ){
	size_t size = std::distance( first, last ) ;
	const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
	Shield<SEXP> x = Rf_allocVector( RTYPE, size );
	std::copy( first, last, r_vector_start<RTYPE>(x) ) ; 
	return x ;
}

/**
 * Range based primitive wrap implementation. used when : 
 * - T is a primitive type
 * - T does not need a cast
 *
 * This produces an unnamed vector of the appropriate type using 
 * the std::copy algorithm
 */
template <typename InputIterator, typename T>
inline SEXP primitive_range_wrap__impl( InputIterator first, InputIterator last, std::false_type ){
	RCPP_DEBUG( "primitive_range_wrap__impl< InputIterator = %s , T = %s>(.,., false_type )\n", DEMANGLE(InputIterator), DEMANGLE(T) ) ;
	return primitive_range_wrap__impl__nocast<InputIterator,T>( first, last, typename std::iterator_traits<InputIterator>::iterator_category() ) ;
}

}
}    

#endif
