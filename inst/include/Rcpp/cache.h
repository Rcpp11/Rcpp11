#ifndef RCPP_CACHE_H
#define RCPP_CACHE_H

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

#endif
