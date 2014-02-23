#include <Rcpp.h>
#include "internal.h"

using namespace Rcpp ;

#define DOT_EXT(name)  DotExternal(#name, &name)
#define DOT_CALL(name) DotCall(#name, &name)

static R_CallMethodDef callEntries[]  = {
    DOT_CALL(rcpp_error_recorder),
    
    {NULL, NULL, 0}
}; 

static Rstreambuf<true>*  Rcout_buf = nullptr ;
static Rstreambuf<false>* Rcerr_buf = nullptr ;
static std::streambuf* cout_buf = nullptr ;
static std::streambuf* cerr_buf = nullptr ;

void init_Rcpp11_routines(DllInfo *info){
    Rostream<true>  Rcout;
    Rostream<false> Rcerr;
    Rcout_buf = new Rstreambuf<true> ;
    Rcerr_buf = new Rstreambuf<false> ;     
    cout_buf  = std::cout.rdbuf() ;           
    cerr_buf  = std::cerr.rdbuf() ;           
    
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );

    R_registerRoutines(info, 
        NULL /* .C*/, 
        callEntries /*.Call*/,
        NULL /* .Fortran */,
        NULL /*.External*/
    );
    
    #define REGISTER(__FUN__) R_RegisterCCallable( "Rcpp11", #__FUN__ , (DL_FUNC)__FUN__ );
    
    REGISTER(Rcpp_eval)
    REGISTER(forward_exception_to_r)
    REGISTER(exception_to_try_error)
    REGISTER(string_to_try_error)
    REGISTER(stack_trace)
    
    REGISTER(enterRNGScope)
    REGISTER(exitRNGScope)
    REGISTER(get_rcpp_cache)
}
        
extern "C" void R_unload_Rcpp11(DllInfo *info) {
    std::cout.rdbuf( Rcout_buf );
    std::cerr.rdbuf( Rcerr_buf );
    delete Rcout_buf ; Rcout_buf = nullptr ;
    delete Rcerr_buf ; Rcerr_buf = nullptr ;
}

static SEXP init_Rcpp11_cache(){ 
    RCPP_DEBUG( "init_Rcpp11_cache()\n" )
    
    SEXP getNamespaceSym = Rf_install("getNamespace"); 
    SEXP RCPP    = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
    SEXP cache   = PROTECT( Rf_allocVector( VECSXP, 7 ) ) ;
    
    // the Rcpp11 namespace
    RCPP_SET_VECTOR_ELT( cache, 0, RCPP ) ;
    SEXP error_occured = PROTECT(Rf_allocVector(LGLSXP, 1)) ;
    LOGICAL(error_occured)[0] = FALSE ;
    RCPP_SET_VECTOR_ELT( cache, 1, error_occured ) ; 
    UNPROTECT(1); 
    
    RCPP_SET_VECTOR_ELT( cache, 2, R_NilValue) ;
    RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ; // stack trace
    Rf_defineVar( Rf_install(".rcpp_cache"), cache, RCPP );
    
    UNPROTECT(2) ;
    return cache ;
}

SEXP rcpp_error_recorder(SEXP e){ 
    SEXP cache = Rcpp::get_rcpp_cache() ;
    Rcpp::error_occured() = true ;
    Rcpp::rcpp_current_error() = e ;
    return R_NilValue ;
}

extern "C" void R_init_Rcpp11( DllInfo* info){
	// init the cache
	init_Rcpp11_cache() ;
	
	// init routines
	init_Rcpp11_routines(info) ;
}

