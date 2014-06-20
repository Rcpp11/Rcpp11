#ifndef Rcpp__sugar__materialize_h
#define Rcpp__sugar__materialize_h

namespace Rcpp{
    
    template <typename eT, typename Expr>
    inline SEXP materialize( const SugarVectorExpression<eT, Expr>& expr ){
        return Vector< traits::r_sexptype_traits<eT>::rtype >(expr) ;
    }

    template <typename eT, typename Expr>
    inline SEXP materialize( const SugarMatrixExpression<eT, Expr>& expr ){
        return Matrix< traits::r_sexptype_traits<eT>::rtype >(expr) ;
    }


} // Rcpp
#endif

