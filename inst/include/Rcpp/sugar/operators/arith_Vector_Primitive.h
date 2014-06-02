#ifndef Rcpp__sugar__Arith_Vector_Primitive_h
#define Rcpp__sugar__Arith_Vector_Primitive_h

template <typename Expr>
inline auto
operator+( 
    const Rcpp::SugarVectorExpression<Expr>& lhs,
    typename Expr::value_type rhs
) -> decltype( mapply( std::plus<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::plus<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator-( 
    const Rcpp::SugarVectorExpression<Expr>& lhs,
    typename Expr::value_type rhs
) -> decltype( mapply( std::minus<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::minus<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator*( 
    const Rcpp::SugarVectorExpression<Expr>& lhs,
    typename Expr::value_type rhs
) -> decltype( mapply( std::multiplies<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::multiplies<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator/( 
    const Rcpp::SugarVectorExpression<Expr>& lhs,
    typename Expr::value_type rhs
) -> decltype( mapply( std::divides<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::divides<typename Expr::value_type>(), lhs, rhs ) ;
}

#endif
