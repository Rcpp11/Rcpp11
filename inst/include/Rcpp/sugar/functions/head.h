#ifndef Rcpp__sugar__head_h
#define Rcpp__sugar__head_h

namespace Rcpp{
    
    template <typename eT, typename Expr>
    inline sugar::Import<typename Expr::const_iterator>
    head( const SugarVectorExpression<eT,Expr>& t, R_xlen_t n ) {
        R_xlen_t offset = (n<0) ? ( t.size() + n ) : n ;
        return import_n( sugar_begin(t), offset ) ;
    }

} // Rcpp
#endif

