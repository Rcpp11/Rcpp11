#ifndef Rcpp_wrap_forward_h
#define Rcpp_wrap_forward_h
 
namespace Rcpp{

    template <typename InputIterator>
    inline SEXP wrap_range(InputIterator first, InputIterator last) ;
        
    template <typename T> 
    inline SEXP wrap( const T& object ) ;

}
#endif
