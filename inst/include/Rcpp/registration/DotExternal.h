#ifndef Rcpp_registration_DotExternal_h
#define Rcpp_registration_DotExternal_h

namespace Rcpp{

struct DotExternal : R_CallMethodDef {
    template <typename OUT, typename... Args>
    DotExternal( const char* name_, OUT (*fun_)(Args...) ) {
        name = name_ ;
        fun = (DL_FUNC)fun_ ; 
        numArgs = -1 ;
    }
} ;
    
}

#endif
