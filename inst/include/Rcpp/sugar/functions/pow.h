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
    
    template <typename Expr, typename T>
    inline typename std::enable_if<
        is_mapply_compatible<T>::value, 
        Mapply< sugar::pow_op< typename Expr::value_type, typename traits::mapply_scalar_type<T>::type >, Expr, T>
    >::type
    pow( const SugarVectorExpression<Expr>& expr, const T& exponent ){
        return mapply( sugar::pow_op< typename Expr::value_type, typename traits::mapply_scalar_type<T>::type >(), expr, exponent );  
    }
    

} 
#endif

