#include <Rcpp.h>

using namespace Rcpp ;

static Rstreambuf<true>*  Rcout_buf = nullptr ;
static Rstreambuf<false>* Rcerr_buf = nullptr ;
static std::streambuf* cout_buf = nullptr ;
static std::streambuf* cerr_buf = nullptr ;

extern "C" void R_init_Rcpp11( DllInfo* info){
      
    // init routines
    Rostream<true>  Rcout;
    Rostream<false> Rcerr;
    Rcout_buf = new Rstreambuf<true> ;
    Rcerr_buf = new Rstreambuf<false> ;     
    cout_buf  = std::cout.rdbuf() ;           
    cerr_buf  = std::cerr.rdbuf() ;           
    
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );
    
    #define REGISTER(__FUN__) R_RegisterCCallable( "Rcpp11", #__FUN__ , (DL_FUNC)__FUN__ );
    
    REGISTER(forward_exception_to_r)
    REGISTER(exception_to_try_error)
    REGISTER(string_to_try_error)
    
}

extern "C" void R_unload_Rcpp11(DllInfo *info) {
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );
    delete Rcout_buf ; Rcout_buf = nullptr ;
    delete Rcerr_buf ; Rcerr_buf = nullptr ;
}

