#ifndef Rcpp_wrap_ContainerWrapper_h
#define Rcpp_wrap_ContainerWrapper_h
 
namespace Rcpp{
  
    template <typename T> struct ContainerWrapper {
        static inline SEXP wrap(const T& object) ; 
    } ;
    
}

#endif
