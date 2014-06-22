#ifndef Rcpp_wrap_wrap_impl_h
#define Rcpp_wrap_wrap_impl_h
 
namespace Rcpp{

    template <typename T>
    inline SEXP wrap( std::initializer_list<T> init ){ 
        return wrap_range( init.begin(), init.end() ) ; 
    } 
 
    // this also handles char[] 
    inline SEXP wrap(const char* const v ){ 
        return (v == nullptr) ? R_NilValue : Rf_mkString(v) ;
    }
    
} // Rcpp

#endif
