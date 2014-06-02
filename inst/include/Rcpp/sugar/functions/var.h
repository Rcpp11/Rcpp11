#ifndef Rcpp__sugar__var_h
#define Rcpp__sugar__var_h

namespace Rcpp{

    template <typename Expr>
    inline double var( const SugarVectorExpression<Expr>& t){
        double ssq  = sum( pow(object-mean(object),2.0) ) ;
        return ssq / (object.size() - 1 ) ;
    }

    template <typename Expr>
    inline double sd( const SugarVectorExpression<Expr>& t) {
        return sqrt(var(t)) ;
    }

    
} // Rcpp
#endif

