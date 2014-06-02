#ifndef Rcpp__sugar__is_h
#define Rcpp__sugar__is_h

namespace Rcpp{
    
    template <typename Expr>
    inline auto is_finite( const SugarVectorExpression<Expr>& t) -> decltype( sapply(t, traits::is_finite<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ) {
        return sapply(t, traits::is_finite<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ;
    }

    template <typename Expr>
    inline auto is_infinite( const SugarVectorExpression<Expr>& t) -> decltype( sapply(t, traits::is_infinite<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ) {
        return sapply(t, traits::is_infinite<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ;
    }

    template <typename Expr>
    inline auto is_na( const SugarVectorExpression<Expr>& t) -> decltype( sapply(t, traits::is_na<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ) {
        return sapply(t, traits::is_na<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ;
    }

    template <typename Expr>
    inline auto is_nan( const SugarVectorExpression<Expr>& t) -> decltype( sapply(t, traits::is_nan<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ) {
        return sapply(t, traits::is_nan<trait::r_sexptype_traits<typename Expr::value_type>::rtype> ) ;
    }

    
} // Rcpp
#endif

