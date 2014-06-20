#ifndef Rcpp_wrap_MatrixWrapper_h
#define Rcpp_wrap_MatrixWrapper_h
 
namespace Rcpp{
    
    template <typename T> struct MatrixWrapper {
        static inline SEXP wrap(const T& object) ; 
    }; 
}

#endif
