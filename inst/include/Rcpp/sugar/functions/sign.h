#ifndef Rcpp__sugar__sign_h
#define Rcpp__sugar__sign_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct sign_op {
            inline int operator()( T x ){
                return ( x > 0 ? 1 : (x==0 ? 0 : -1) ) ;       
            }
        } ;
        
    } // sugar
    
    template <typename eT, typename Expr>
    inline auto sign( const SugarVectorExpression<eT, Expr>& t) -> decltype( sapply( t, sugar::sign_op<eT>() )){
        return sapply( t, sugar::sign_op<eT>() )  ;
    }


} // Rcpp
#endif

