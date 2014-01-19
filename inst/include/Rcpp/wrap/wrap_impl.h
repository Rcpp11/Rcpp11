#ifndef Rcpp_wrap_wrap_impl_h
#define Rcpp_wrap_wrap_impl_h
 
namespace Rcpp{

template <typename T>
inline SEXP wrap( std::initializer_list<T> init ){ return internal::range_wrap( init.begin(), init.end() ) ; } 

// this also handles char[] 
inline SEXP wrap(const char* const v ){ 
    return (v == nullptr) ? R_NilValue : Rf_mkString(v) ;
}

/**
 * Range based version of wrap
 */
template <typename InputIterator>
inline SEXP wrap(InputIterator first, InputIterator last){ 
	return internal::range_wrap( first, last ) ;
}


} // Rcpp

#endif
