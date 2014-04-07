#ifndef Rcpp_wrap_SugarExpressionWrapper_h
#define Rcpp_wrap_SugarExpressionWrapper_h
 
namespace Rcpp{

    template <typename T> struct SugarExpressionWrapper {
        static inline SEXP wrap(const T& object) { 
            return Vector<T::r_type::value>(object) ;    
        }
    } ;
    
}

#endif
