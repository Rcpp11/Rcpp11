#define COMPILING_RCPP11
#define USE_RINTERNALS

#include <Rinternals.h>
#include "internal.h"
#include <algorithm>
#include <Rcpp/macros/debug.h>

#define RCPP_SET_VECTOR_ELT SET_VECTOR_ELT 

// [[Rcpp::register]]
void* dataptr(SEXP x){ return DATAPTR(x); }

static bool Rcpp_cache_know = false ;
static bool handler_ready = false ;
static SEXP Rcpp_cache = R_NilValue ;

#define RCPP_HASH_CACHE_INDEX 4
#define RCPP_CACHE_SIZE 6

#ifndef RCPP_HASH_CACHE_INITIAL_SIZE
#define RCPP_HASH_CACHE_INITIAL_SIZE 1024
#endif 

// only used for debugging
SEXP get_rcpp_cache() {
    RCPP_DEBUG( "get_rcpp_cache (known = %s)", (Rcpp_cache_know ? "true" : "false" ) )
    if( ! Rcpp_cache_know ){
        SEXP getNamespaceSym = Rf_install("getNamespace"); 
        SEXP RCPP       = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
        Rcpp_cache      = Rf_findVarInFrame( RCPP, Rf_install(".rcpp_cache") ) ;
        Rcpp_cache_know = true ;
        UNPROTECT(1) ;
    }
    RCPP_DEBUG( "  [get_rcpp_cache] Rcpp_cache = <%p>", Rcpp_cache )
        
    return Rcpp_cache ;
}

namespace Rcpp {
    SEXP get_Rcpp11_namespace(){ 
        return VECTOR_ELT( get_rcpp_cache() , 0 ) ;
	  }
}

static int& set_error_occured(SEXP cache, bool occured){
    RCPP_DEBUG( "set_error_occured( <%p>, %s, %s )", cache, PRETTY_BOOL(occured), PRETTY_BOOL(cache==R_NilValue) )
    RCPP_DEBUG( "R_NilValue = <%p>", R_NilValue )
    SEXP err = VECTOR_ELT(cache, 1); 
    int& ref = LOGICAL(err)[0] ;
    ref = occured ;
    return ref ;
}

void set_current_error(SEXP cache, SEXP e){ 
    RCPP_DEBUG( "set_current_error( <%p>, <%p> )", cache, e ) ;
    RCPP_SET_VECTOR_ELT( cache, 2, e ) ;
}

SEXP rcpp_set_stack_trace(SEXP e){
    RCPP_SET_VECTOR_ELT( get_rcpp_cache(), 3, e ) ;
    return R_NilValue ;
}

SEXP rcpp_get_stack_trace(){
    return VECTOR_ELT( get_rcpp_cache(), 3 ) ;
}

// [[Rcpp::register]]
SEXP rcpp11_error_handler(){
    if( ! handler_ready ){
      SEXP cache   = get_rcpp_cache() ;
      SEXP RCPP    = VECTOR_ELT(cache, 0) ;
      SEXP handler = Rf_findVarInFrame(RCPP, Rf_install(".rcpp_error_recorder") ) ;
      if( TYPEOF(handler) == PROMSXP){
          handler = Rf_eval(handler, RCPP) ;
      }
      RCPP_SET_VECTOR_ELT( cache, 5, handler ) ;
      handler_ready = true ;
    }
    return VECTOR_ELT( get_rcpp_cache(), 5) ;
}

SEXP init_Rcpp11_cache(){ 
  RCPP_DEBUG( "init_Rcpp11_cache()\n" )
	
  SEXP getNamespaceSym = Rf_install("getNamespace"); 
  SEXP RCPP    = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
  SEXP cache   = PROTECT( Rf_allocVector( VECSXP, RCPP_CACHE_SIZE ) ) ;
  
  // the Rcpp namespace
	RCPP_SET_VECTOR_ELT( cache, 0, RCPP ) ;
	SEXP error_occured = PROTECT(Rf_allocVector(LGLSXP, 1)) ;
	LOGICAL(error_occured)[0] = FALSE ;
	RCPP_SET_VECTOR_ELT( cache, 1, error_occured ) ; 
	UNPROTECT(1); 
	
	set_current_error( cache, R_NilValue ) ;
	RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ; // stack trace
	RCPP_SET_VECTOR_ELT( cache, 4, Rf_allocVector(INTSXP, RCPP_HASH_CACHE_INITIAL_SIZE) ) ;
	Rf_defineVar( Rf_install(".rcpp_cache"), cache, RCPP );
    
	UNPROTECT(2) ;
	return cache ;
}

// [[Rcpp::register]]
int& reset_current_error(){
    RCPP_DEBUG("reset_current_error")
    SEXP cache = get_rcpp_cache() ;
    
    // current error
    set_current_error( cache, R_NilValue ) ;
	
    // stack trace
    RCPP_SET_VECTOR_ELT( cache, 3, R_NilValue ) ;
    
    // error occured
    return set_error_occured( cache, false ) ;
	
}

// [[Rcpp::register]]
int error_occured(){
    SEXP err = VECTOR_ELT( get_rcpp_cache(), 1 ) ;
    return LOGICAL(err)[0] ;
}

SEXP rcpp_error_recorder(SEXP e){ 
    SEXP cache = get_rcpp_cache() ;
    
    // error occured
    
    RCPP_DEBUG( "rcpp_error_recorder()\n" )
    set_error_occured( cache, true ) ;
	
    // current error
    set_current_error(cache, e ) ;
    
    return R_NilValue ;
}

// [[Rcpp::register]]
SEXP rcpp_get_current_error(){
    return VECTOR_ELT( get_rcpp_cache(), 2 ) ;
}

namespace Rcpp{
    
    // [[Rcpp::register]]
    int* get_cache(int m){
        SEXP cache = get_rcpp_cache() ;
        SEXP hash_cache = VECTOR_ELT( cache, RCPP_HASH_CACHE_INDEX) ;
        int n = Rf_length(hash_cache) ;
        if( m > n ){
            SEXP hash_cache_ = PROTECT(Rf_allocVector( INTSXP, m)) ;
            RCPP_SET_VECTOR_ELT(cache,RCPP_HASH_CACHE_INDEX, hash_cache_); 
            hash_cache = hash_cache_ ;
            UNPROTECT(1) ;
        }
        int *res = INTEGER(hash_cache) ;
        std::fill(res, res+m, 0 ) ;
        return res ;
    }

}
