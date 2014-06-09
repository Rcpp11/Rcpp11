#ifndef Rcpp__sugar__enumerate_h
#define Rcpp__sugar__enumerate_h

namespace Rcpp{

    template <typename eT, typename Expr, typename Function, typename... Args>
    inline auto enumerate( Function fun, const SugarVectorExpression<eT,Expr>& expr, Args&&... args ) -> 
        decltype( mapply( fun, seq(0, expr.size() - 1 ), expr, std::forward<Args>(args)... ) )
    {
        return mapply( fun, seq(0, expr.size() - 1 ), expr, std::forward<Args>(args)... ) ;
    }

} // Rcpp

#endif
