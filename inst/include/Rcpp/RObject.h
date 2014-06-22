#ifndef Rcpp_RObject_h
#define Rcpp_RObject_h

namespace Rcpp{ 

    template <typename Storage>
    class RObject_Impl {
        RCPP_API_IMPL(RObject_Impl)
        
        inline void set(SEXP x){
            data = x ;    
        }
    };
    
} // namespace Rcpp

#endif
