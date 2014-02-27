#ifndef RCPP_CACHE_H
#define RCPP_CACHE_H

namespace Rcpp {
  
  inline SEXP get_Rcpp11_namespace(){
      return Rf_findVarInFrame( R_NamespaceRegistry, Rf_install("Rcpp11") ) ;
  }
  
}
#endif
