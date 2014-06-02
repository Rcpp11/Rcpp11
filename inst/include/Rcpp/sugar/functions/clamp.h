#ifndef Rcpp__sugar__clamp_h
#define Rcpp__sugar__clamp_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct clamp_operator{
            clamp_operator(T lhs_, T rhs_ ) : lhs(lhs_), rhs(rhs_){}
            
            inline T operator()(T x) const {
                return x < lhs ? lhs : (x > rhs ? rhs : x ) ;
            }
            T lhs, rhs ;    
        } ;

    } // sugar

    template <typename Expr>
    inline auto clamp( 
        typename Expr::value_type lhs,
        const Rcpp::SugarVectorExpression<Expr>& vec,  
        typename Expr::value_type rhs
    ) -> decltype( sapply( vec, sugar::clamp_operator<typename Expr::value_type>(lhs, rhs) ) ) {
        return sapply( vec, sugar::clamp_operator<typename Expr::value_type>(lhs, rhs) ) ;
    }


} // Rcpp

#endif
