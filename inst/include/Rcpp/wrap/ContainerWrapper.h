#ifndef Rcpp_wrap_ContainerWrapper_h
#define Rcpp_wrap_ContainerWrapper_h
 
namespace Rcpp{
  
    template <typename T> struct ContainerWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "ContainerWrapper<%s>::wrap() ", DEMANGLE(T) ) 
            return internal::range_wrap( object.begin(), object.end() ) ;    
        }
    } ;
    
}

#endif
