#ifndef Rcpp__sugar__Arith_Primitive_Vector_h
#define Rcpp__sugar__Arith_Primitive_Vector_h

template <typename eT, typename Expr>
inline auto
operator+( eT lhs, const Rcpp::SugarVectorExpression<eT,Expr>& rhs) -> decltype( mapply( std::plus<eT>(), lhs, rhs ) ) {
    return mapply( std::plus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator-( eT lhs, const Rcpp::SugarVectorExpression<eT,Expr>& rhs ) -> decltype( mapply( std::minus<eT>(), lhs, rhs ) ) {
    return mapply( std::minus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator*( eT lhs, const Rcpp::SugarVectorExpression<eT,Expr>& rhs) -> decltype( mapply( std::multiplies<eT>(), lhs, rhs ) ) {
    return mapply( std::multiplies<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator/( eT lhs, const Rcpp::SugarVectorExpression<eT,Expr>& rhs) -> decltype( mapply( std::divides<eT>(), lhs, rhs ) ) {
    return mapply( std::divides<eT>(), lhs, rhs ) ;
}
 
#endif
