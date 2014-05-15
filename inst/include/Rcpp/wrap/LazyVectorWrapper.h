#ifndef Rcpp_wrap_LazyVectorWrapper_h
#define Rcpp_wrap_LazyVectorWrapper_h
 
namespace Rcpp{

    template <typename T> struct LazyVectorWrapper {
        static inline SEXP wrap(const T& object) { 
            return Vector<T::r_type::value>(object) ;    
        }
    } ;
    
}

#endif
