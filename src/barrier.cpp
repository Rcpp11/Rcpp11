#define COMPILING_RCPP11
#define USE_RINTERNALS

#include <Rinternals.h>
#include "internal.h"
#include <algorithm>
#include <Rcpp/macros/debug.h>
#include <Rcpp/cache.h>

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 

SEXP& rcpp_get_current_module(){
    return VECTOR_ELT( Rcpp::get_rcpp_cache(), 6 ) ;
}

SEXP init_Rcpp11_cache(){ 
    RCPP_DEBUG( "init_Rcpp11_cache()\n" )
    
    SEXP getNamespaceSym = Rf_install("getNamespace"); 
    SEXP RCPP    = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
    SEXP cache   = PROTECT( Rf_allocVector( VECSXP, 7 ) ) ;
    
    // the Rcpp namespace
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

