#include <Rcpp.h>

using namespace Rcpp ;

extern "C" void R_init_Rcpp11( DllInfo* info){
    #define REGISTER(__FUN__) R_RegisterCCallable( "Rcpp11", #__FUN__ , (DL_FUNC)__FUN__ );
    
    REGISTER(forward_exception_to_r)
    REGISTER(exception_to_try_error)
    REGISTER(string_to_try_error)
    
}

