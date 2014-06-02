#ifndef Rcpp__sugar__logical_operators__Vector__primitive_h
#define Rcpp__sugar__logical_operators__Vector__primitive_h

/* Vector < primitive */
template <typename Expr>
inline auto operator<( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::less<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::less<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator>( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::less<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::less<typename Expr::value_type>(), lhs, rhs ) ;
}


/* Vector > primitive */
template <typename Expr>
inline auto operator>( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::greater<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::greater<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator<( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::greater<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::greater<typename Expr::value_type>(), lhs, rhs ) ;
}




/* Vector <= primitive */
template <typename Expr>
inline auto operator<=( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::less_equal<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::less_equal<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator>=( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::less_equal<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::less_equal<typename Expr::value_type>(), lhs, rhs ) ;
}

/* Vector >= primitive */
template <typename Expr>
inline auto operator>=( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::greater_equal<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::greater_equal<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator<=( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::greater_equal<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::greater_equal<typename Expr::value_type>(), lhs, rhs ) ;
}

/* Vector == primitive */
template <typename Expr>
inline auto operator==( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::equal_to<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::equal_to<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator==( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::equal_to<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::equal_to<typename Expr::value_type>(), lhs, rhs ) ;
}

/* Vector != primitive */
template <typename Expr>
inline auto operator!=( 
    const Rcpp::SugarVectorExpression<Expr>& lhs , 
    typename Expr::value_type rhs
) -> decltype( mapply( std::not_equal_to<typename Expr::value_type>(), lhs, rhs ) ) {
    return mapply( std::not_equal_to<typename Expr::value_type>(), lhs, rhs ) ;
}
template <typename Expr>
inline auto operator!=( 
    typename Expr::value_type rhs, 
    const Rcpp::SugarVectorExpression<Expr>& lhs 
) -> decltype( mapply( std::not_equal_to<typename Expr::value_type>(), lhs, rhs ) ) {{
    return mapply( std::not_equal_to<typename Expr::value_type>(), lhs, rhs ) ;
}


#endif
