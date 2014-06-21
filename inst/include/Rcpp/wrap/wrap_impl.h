#ifndef Rcpp_wrap_wrap_impl_h
#define Rcpp_wrap_wrap_impl_h
 
namespace Rcpp{

    // this also handles char[] 
    inline SEXP wrap(const char* const v ){ 
        return (v == nullptr) ? R_NilValue : Rf_mkString(v) ;
    }
    
} // Rcpp

#endif
