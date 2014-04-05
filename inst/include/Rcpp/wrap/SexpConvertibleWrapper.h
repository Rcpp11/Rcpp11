#ifndef Rcpp_wrap_SexpConvertibleWrapper_h
#define Rcpp_wrap_SexpConvertibleWrapper_h
 
namespace Rcpp{

    template <typename T> struct SexpConvertibleWrapper{
        static inline SEXP wrap(const T& object) { 
            return (SEXP)object ;    
        }
    } ;
    
}

#endif
