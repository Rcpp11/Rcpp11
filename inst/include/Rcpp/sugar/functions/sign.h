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
    
    template <typename Expr>
    inline auto sign( const SugarVectorExpression<Expr>& t) -> decltype( sapply( t, sugar::sign_op<typename Expr::value_type>() )){
        return sapply( t, sugar::sign_op<typename Expr::value_type>() )  ;
    }


} // Rcpp
#endif

