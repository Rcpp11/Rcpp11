#ifndef Rcpp__sugar__enumerate_h
#define Rcpp__sugar__enumerate_h

namespace Rcpp{

    template <typename eT, typename Expr, typename Function>
    inline auto enumerate( const SugarVectorExpression<eT,Expr>& expr, Function fun ) -> decltype( mapply( fun, expr, seq(0, expr.size() - 1 ) ) ) {
        return mapply( fun, expr, seq(0, expr.size() - 1 ) ) ;
    }

} // Rcpp

#endif
