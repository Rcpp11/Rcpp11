#ifndef Rcpp__sugar__pow_h
#define Rcpp__sugar__pow_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T, typename E>
        struct pow_op {
            inline auto operator()(T x, E e) -> decltype(::pow(x,e)){
                return ::pow(x, e) ;    
            }
        } ;
        
    }
    
    template <typename eT, typename Expr, typename T>
    auto pow( const SugarVectorExpression<eT, Expr>& expr, const T& exponent ) -> 
        decltype( mapply( sugar::pow_op<eT, typename traits::mapply_scalar_type<T>::type >(), expr, exponent ) )
    {
        return mapply( sugar::pow_op<eT, typename traits::mapply_scalar_type<T>::type >(), expr, exponent );  
    }
    

} 
#endif

