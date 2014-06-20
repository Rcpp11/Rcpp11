#ifndef Rcpp_wrap_forward_h
#define Rcpp_wrap_forward_h
 
namespace Rcpp{

    template <typename T> SEXP wrap( const T& object ) ;
    
    namespace internal{
        template <typename InputIterator> SEXP range_wrap(InputIterator first, InputIterator last) ;
    }

}
#endif
