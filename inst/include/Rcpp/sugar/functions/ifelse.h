#ifndef Rcpp__sugar__ifelse_h
#define Rcpp__sugar__ifelse_h

namespace Rcpp{
    namespace sugar{

        struct ifelse_op {

            template <typename T>
            inline T operator()(Rboolean cond, T lhs, T rhs ) const {
                switch( cond ){
                    case TRUE: return lhs ;
                    case FALSE: return rhs ;
                    default: break ;
                } ;
                return NA ;
            }

            template <typename T>
            inline T operator()(bool cond, T lhs, T rhs ) const {
                return cond ? lhs : rhs ;
            }
        } ;

    }

    template <typename Cond, typename Expr1, typename Expr2>
    inline auto ifelse( const Cond& cond, const Expr1& expr1, const Expr2& expr2 ) -> decltype(mapply( sugar::ifelse_op(), cond, expr1, expr2)) {
        return mapply( sugar::ifelse_op(), cond, expr1, expr2) ;
    }

} // Rcpp

#endif
