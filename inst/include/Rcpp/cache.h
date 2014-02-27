#ifndef RCPP_CACHE_H
#define RCPP_CACHE_H

namespace Rcpp {
  
  inline SEXP get_Rcpp11_namespace(){ 
    return VECTOR_ELT( get_rcpp_cache() , 0 ) ;
  }
  
  inline SEXP& rcpp_stack_trace(){
    return VECTOR_ELT( get_rcpp_cache(), 3 ) ;  
  }
  
}
#endif
