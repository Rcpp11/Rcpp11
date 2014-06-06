#ifndef Rcpp__sugar__na_omit_h
#define Rcpp__sugar__na_omit_h

namespace Rcpp{
    
    namespace sugar {
        
        template <typename T>
        struct not_na_op {
            bool operator()( T x ){
                return ! ( x == NA ) ;    
            }
        } ;
    }
    
    template <typename eT, typename Expr>
    inline auto na_omit( const SugarVectorExpression<eT,Expr>& t) -> decltype( filter( sugar::not_na_op<eT>(), t) ) {
        return filter( sugar::not_na_op<eT>(), t) ; 
    }

} // Rcpp
#endif

