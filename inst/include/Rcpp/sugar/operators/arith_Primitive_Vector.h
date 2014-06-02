#ifndef Rcpp__sugar__Arith_Primitive_Vector_h
#define Rcpp__sugar__Arith_Primitive_Vector_h

template <typename Expr>
inline auto
operator+( 
    typename Expr::value_type lhs, 
    const Rcpp::SugarVectorExpression<Expr>& rhs
) -> decltype( mapply( std::plus<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::plus<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator-( 
    typename Expr::value_type lhs, 
    const Rcpp::SugarVectorExpression<Expr>& rhs
) -> decltype( mapply( std::minus<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::minus<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator*( 
    typename Expr::value_type lhs, 
    const Rcpp::SugarVectorExpression<Expr>& rhs
) -> decltype( mapply( std::multiplies<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::multiplies<typename Expr::value_type>(), lhs, rhs ) ;
}

template <typename Expr>
inline auto
operator/( 
    typename Expr::value_type lhs, 
    const Rcpp::SugarVectorExpression<Expr>& rhs
) -> decltype( mapply( std::divides<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::divides<typename Expr::value_type>(), lhs, rhs ) ;
}
 
#endif
