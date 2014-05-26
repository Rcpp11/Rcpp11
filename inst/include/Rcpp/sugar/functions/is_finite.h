#ifndef Rcpp__sugar__is_finite_h
#define Rcpp__sugar__is_finite_h

namespace Rcpp{
    
    template <int RTYPE, bool NA, typename T>
    inline auto is_finite( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t) -> decltype( sapply(t, Rcpp::traits::is_finite<RTYPE> ) ) {
        return sapply(t, Rcpp::traits::is_finite<RTYPE> ) ;
    }

} // Rcpp
#endif

