#ifndef Rcpp_wrap_PrimitiveWrapper_h
#define Rcpp_wrap_PrimitiveWrapper_h
 
namespace Rcpp{

    template <typename T> struct PrimitiveWrapper {
        static inline SEXP wrap(const T& object) ;
    } ;
}

#endif
