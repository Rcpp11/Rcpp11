#ifndef Rcpp__sugar__ifelse_h
#define Rcpp__sugar__ifelse_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct ifelse_op {
            inline T operator()(Rboolean cond, T lhs, T rhs ){
                switch( cond ){ 
                    case TRUE: return lhs ;
                    case FALSE: return rhs ;
                    case NA_VALUE: return NA ;
                } ;
            }
        } ;
           
    }
    
    template <typename Cond, typename Expr1, typename Expr2>
    inline typename std::enable_if<
        traits::is_mapply_compatible<Expr1>::value &&
        traits::is_mapply_compatible<Expr2>::value &&
        traits::same_mapply_scalar_type<Expr1,Expr2>::value &&
        sugar::Mapply< 
            sugar::ifelse_op<typename traits::mapply_scalar_type<Expr1>::type>, 
            Cond, Expr1, Expr2
        > 
    >::type 
    ifelse( const SugarVectorExpression<Rboolean,Cond>& cond, const Expr1& expr1, const Expr2& expr2 ){
        typedef sugar::ifelse_op< typename traits::mapply_scalar_type<Expr1>::type > op ; 
        return mapply( op(), cond, expr1, expr2) ;
    }
    
} // Rcpp

#endif
