#ifndef Rcpp_registration_DotCall_h
#define Rcpp_registration_DotCall_h

namespace Rcpp{

struct DotCall : R_CallMethodDef {
    template <typename OUT, typename... Args>
    DotCall( const char* name_, OUT (*fun_)(Args...) ) {
        name = name_ ;
        fun = (DL_FUNC)fun_, 
        numArgs = sizeof...(Args) ;
    }
} ;
    
}

#endif
