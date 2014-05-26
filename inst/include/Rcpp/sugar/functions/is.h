#ifndef Rcpp__sugar__is_h
#define Rcpp__sugar__is_h

namespace Rcpp{
    
    template <int RTYPE, bool NA, typename T>
    inline auto is_finite( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t) -> decltype( sapply(t, Rcpp::traits::is_finite<RTYPE> ) ) {
        return sapply(t, Rcpp::traits::is_finite<RTYPE> ) ;
    }

    template <int RTYPE, bool NA, typename T>
    inline auto is_infinite( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t) -> decltype( sapply(t, Rcpp::traits::is_infinite<RTYPE> ) ) {
        return sapply(t, Rcpp::traits::is_infinite<RTYPE> ) ;
    }

    template <int RTYPE, bool NA, typename T>
    inline auto is_na( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t) -> decltype( sapply(t, Rcpp::traits::is_na<RTYPE> ) ) {
        return sapply(t, Rcpp::traits::is_na<RTYPE> ) ;
    }

    template <int RTYPE, bool NA, typename T>
    inline auto is_nan( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& t) -> decltype( sapply(t, Rcpp::traits::is_nan<RTYPE> ) ) {
        return sapply(t, Rcpp::traits::is_nan<RTYPE> ) ;
    }

    
} // Rcpp
#endif

