#ifndef RCPP_CACHE_H
#define RCPP_CACHE_H

namespace Rcpp {
  
  inline SEXP get_rcpp_cache() {
    static SEXP Rcpp_cache = R_NilValue ;
    if( Rcpp_cache == R_NilValue){
        SEXP getNamespaceSym = Rf_install("getNamespace"); 
        SEXP RCPP       = PROTECT( Rf_eval(Rf_lang2( getNamespaceSym, Rf_mkString("Rcpp11") ), R_GlobalEnv) );
        Rcpp_cache      = Rf_findVarInFrame( RCPP, Rf_install(".rcpp_cache") ) ;
        UNPROTECT(1) ;
    }
    return Rcpp_cache ;
  }
  
  inline SEXP get_Rcpp11_namespace(){ 
    return VECTOR_ELT( get_rcpp_cache() , 0 ) ;
  }
  
  inline int& error_occured(){
    SEXP err = VECTOR_ELT( get_rcpp_cache(), 1 ) ;
    return LOGICAL(err)[0] ;
  }  
  
  inline SEXP& rcpp_current_error(){
    return VECTOR_ELT( get_rcpp_cache(), 2 ) ;  
  }
  
  inline SEXP& rcpp_stack_trace(){
    return VECTOR_ELT( get_rcpp_cache(), 3 ) ;  
  }
     
  inline int& reset_current_error(){
    rcpp_current_error() = R_NilValue ;
    rcpp_stack_trace() = R_NilValue ;
    return error_occured() = false ; 
  }
  
  inline SEXP& rcpp11_error_handler(){
    static bool handler_ready = false ;
    if( ! handler_ready ){
      SEXP cache   = get_rcpp_cache() ;
      SEXP RCPP    = VECTOR_ELT(cache, 0) ;
      SEXP handler = Rf_findVarInFrame(RCPP, Rf_install(".rcpp_error_recorder") ) ;
      if( TYPEOF(handler) == PROMSXP){
          handler = Rf_eval(handler, RCPP) ;
      }
      SET_VECTOR_ELT( cache, 5, handler ) ;
      handler_ready = true ;
    }
    return VECTOR_ELT( Rcpp::get_rcpp_cache(), 5) ;
}

  
}
#endif
