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
  
  inline SEXP& current_error(){
    return VECTOR_ELT( get_rcpp_cache(), 2 ) ;  
  }
     
  inline int& reset_current_error(){
    current_error() = R_NilValue ;
    stack_trace() = R_NilValue ;
    return error_occured() = false ; 
  }
  
}
#endif
