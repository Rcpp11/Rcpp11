#ifndef Rcpp__sugar__tail_h
#define Rcpp__sugar__tail_h

namespace Rcpp{

    template <typename eT, typename Expr>
    inline sugar::Import<typename Expr::const_iterator> 
    tail( const SugarVectorExpression<eT, Expr>& t, R_xlen_t n ){
        R_xlen_t offset = (n>0) ? (t.size() - n) : (-n) ;
        return import( sugar_begin(t) + offset , sugar_end(t) ) ;
    }

} // Rcpp
#endif

