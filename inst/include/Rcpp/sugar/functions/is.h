#ifndef Rcpp__sugar__is_h
#define Rcpp__sugar__is_h

namespace Rcpp{
    
    template <typename eT, typename Expr>
    inline auto is_finite( const SugarVectorExpression<eT,Expr>& t) -> decltype( sapply(t, traits::is_finite< traits::r_sexptype_traits<eT>::rtype > ) ) {
        return sapply(t, traits::is_finite< traits::r_sexptype_traits<eT>::rtype > ) ;
    }

    template <typename eT, typename Expr>
    inline auto is_infinite( const SugarVectorExpression<eT,Expr>& t) -> decltype( sapply(t, traits::is_infinite< traits::r_sexptype_traits<eT>::rtype > ) ) {
        return sapply(t, traits::is_infinite< traits::r_sexptype_traits<eT>::rtype > ) ;
    }

    template <typename eT, typename Expr>
    inline auto is_na( const SugarVectorExpression<eT,Expr>& t) -> decltype( sapply(t, traits::is_na< traits::r_sexptype_traits<eT>::rtype > ) ) {
        return sapply(t, traits::is_na< traits::r_sexptype_traits<eT>::rtype > ) ;
    }

    template <typename eT, typename Expr>
    inline auto is_nan( const SugarVectorExpression<eT,Expr>& t) -> decltype( sapply(t, traits::is_nan< traits::r_sexptype_traits<eT>::rtype > ) ) {
        return sapply(t, traits::is_nan< traits::r_sexptype_traits<eT>::rtype > ) ;
    }

    
} // Rcpp
#endif

