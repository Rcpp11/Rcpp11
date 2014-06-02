#ifndef Rcpp__sugar__ifelse_h
#define Rcpp__sugar__ifelse_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct ifelse_op {
            inline T operator()(Rboolean cond, T lhs, T rhs ){
                switch( cond ){ 
                    TRUE: return lhs ;
                    FALSE: return rhs ;
                    NA_VALUE: return NA ;
                } ;
            }
        } ;
           
    }
    
    template <typename Cond, typename Expr1, typename Expr2>
    typename std::enable_if<
        std::is_same<typename Cond::value_type, Rboolean>, 
        typename Mapply< 
            sugar::ifelse_op<typename sugar::mapply_input_type<Expr1>::type>, 
            Cond, Expr1, Expr2
        > 
    >::type 
    ifelse( const SugarVectorExpression<Cond>& cond, const Expr1& expr1, const Expr2& expr2 ){
        typedef sugar::ifelse_op< typename sugar::mapply_input_type<Expr1>::type > op ; 
        return mapply( op(), cond, expr1, expr2) ;
    }
    
} // Rcpp

#endif
