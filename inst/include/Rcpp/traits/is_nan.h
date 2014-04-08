#ifndef Rcpp__traits_is_nan_h
#define Rcpp__traits_is_nan_h

namespace Rcpp{
namespace traits{

    // default for most types 
    template <int RTYPE> 
    bool is_nan( typename storage_type<RTYPE>::type){
        return false ;    
    }

    template <> 
    inline bool is_nan<REALSXP>( double x ){
        return Rcpp::internal::is_NaN(x) ;
    }

    template <> 
    inline bool is_nan<CPLXSXP>( Rcomplex x ){
        return Rcpp::internal::is_NaN(x.r) || Rcpp::internal::is_NaN(x.i) ;
    }

}
}

#endif
