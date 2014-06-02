#ifndef Rcpp__sugar__na_omit_h
#define Rcpp__sugar__na_omit_h

namespace Rcpp{
    
    namespace sugar {
        struct not_na_op {
            template <typename T>
            bool operator()( T x ){
                return ! ( x == NA ) ;    
            }
        } ;
    }
    
    template <typename Expr>
    inline auto na_omit( const SugarVectorExpression<Expr>& t) -> decltype( filter( sugar::not_na_op(), t) ) {
        return filter( sugar::not_na_op(), t) ; 
    }

} // Rcpp
#endif

