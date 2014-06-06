#ifndef Rcpp__sugar__var_h
#define Rcpp__sugar__var_h

namespace Rcpp{

    template <typename eT, typename Expr>
    inline double var( const SugarVectorExpression<eT, Expr>& object){
        double ssq  = sum( pow(object-mean(object),2.0) ) ;
        return ssq / (object.size() - 1 ) ;
    }

    template <typename eT, typename Expr>
    inline double sd( const SugarVectorExpression<eT, Expr>& object) {
        return sqrt(var(object)) ;
    }

    
} // Rcpp
#endif

