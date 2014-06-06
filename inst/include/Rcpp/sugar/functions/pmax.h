#ifndef Rcpp__sugar__pmin_h
#define Rcpp__sugar__pmin_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct pmax_op {
            inline T operator()( T lhs, T rhs ) const {
                return std::max( lhs, rhs ) ;    
            }
        } ;
    
        template <typename T>
        struct pmin_op {
            inline T operator()( T lhs, T rhs ) const {
                return std::min( lhs, rhs ) ;
            }
        } ;
    
    } // sugar
    
    
    template <typename eT, typename Expr1, typename Expr2>
    auto pmax( const SugarVectorExpression<eT, Expr1>& x, const SugarVectorExpression<eT,Expr2>& y ) -> decltype(mapply( sugar::pmax_op<eT>(), x, y )) {
        return mapply( sugar::pmax_op<eT>(), x, y ) ;  
    }
    template <typename eT, typename Expr1>
    auto pmax( const SugarVectorExpression<eT, Expr1>& x, eT y ) -> decltype(mapply( sugar::pmax_op<eT>(), x, y )) {
        return mapply( sugar::pmax_op<eT>(), x, y ) ;  
    }
    template <typename eT, typename Expr2>
    auto pmax( eT x, const SugarVectorExpression<eT, Expr2>& y ) -> decltype(mapply( sugar::pmax_op<eT>(), x, y )) {
        return mapply( sugar::pmax_op<eT>(), x, y ) ;  
    }
    
    
    template <typename eT, typename Expr1, typename Expr2>
    auto pmin( const SugarVectorExpression<eT, Expr1>& x, const SugarVectorExpression<eT,Expr2>& y ) -> decltype(mapply( sugar::pmin_op<eT>(), x, y )) {
        return mapply( sugar::pmin_op<eT>(), x, y ) ;  
    }
    template <typename eT, typename Expr1>
    auto pmin( const SugarVectorExpression<eT, Expr1>& x, eT y ) -> decltype(mapply( sugar::pmin_op<eT>(), x, y )) {
        return mapply( sugar::pmin_op<eT>(), x, y ) ;  
    }
    template <typename eT, typename Expr2>
    auto pmin( eT x, const SugarVectorExpression<eT, Expr2>& y ) -> decltype(mapply( sugar::pmin_op<eT>(), x, y )) {
        return mapply( sugar::pmin_op<eT>(), x, y ) ;  
    }
    
    
} // Rcpp

#endif
