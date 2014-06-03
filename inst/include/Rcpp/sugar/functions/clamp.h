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

    template <typename eT, typename Expr>
    inline auto clamp( eT lhs, const Rcpp::SugarVectorExpression<eT,Expr>& vec, eT rhs) -> 
        decltype( sapply( vec, sugar::clamp_operator<eT>(lhs, rhs) ) ) 
    {
        return sapply( vec, sugar::clamp_operator<eT>(lhs, rhs) ) ;
    }


} // Rcpp

#endif
