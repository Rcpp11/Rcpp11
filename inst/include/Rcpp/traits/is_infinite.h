#ifndef Rcpp__traits_is_infinite_h
#define Rcpp__traits_is_infinite_h

namespace Rcpp{
namespace traits{

    // default for all but REALSXP and CPLXSXP
    template <int RTYPE> 
    bool is_infinite( typename storage_type<RTYPE>::type){
        return false ;    
    }

    template <> 
    inline bool is_infinite<REALSXP>( double x ){
        return !( ISNAN(x) || R_FINITE(x) ) ;
    }

    template <> 
    inline bool is_infinite<CPLXSXP>( Rcomplex x ){
        return is_infinite<REALSXP>(x.r) || is_infinite<REALSXP>(x.i) ;
    }

}
}

#endif
