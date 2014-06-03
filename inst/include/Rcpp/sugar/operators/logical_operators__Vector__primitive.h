#ifndef Rcpp__sugar__logical_operators__Vector__primitive_h
#define Rcpp__sugar__logical_operators__Vector__primitive_h

/* Vector < primitive */
template <typename eT, typename Expr>
inline auto operator<( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::less<eT>(), lhs, rhs ) ) {
    return mapply( std::less<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator>( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::less<eT>(), lhs, rhs ) ) {{
    return mapply( std::less<eT>(), lhs, rhs ) ;
}


/* Vector > primitive */
template <typename eT, typename Expr>
inline auto operator>( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::greater<eT>(), lhs, rhs ) ) {
    return mapply( std::greater<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator<( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::greater<eT>(), lhs, rhs ) ) {{
    return mapply( std::greater<eT>(), lhs, rhs ) ;
}




/* Vector <= primitive */
template <typename eT, typename Expr>
inline auto operator<=( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::less_equal<eT>(), lhs, rhs ) ) {
    return mapply( std::less_equal<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator>=( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::less_equal<eT>(), lhs, rhs ) ) {{
    return mapply( std::less_equal<eT>(), lhs, rhs ) ;
}

/* Vector >= primitive */
template <typename eT, typename Expr>
inline auto operator>=( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::greater_equal<eT>(), lhs, rhs ) ) {
    return mapply( std::greater_equal<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator<=( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::greater_equal<eT>(), lhs, rhs ) ) {{
    return mapply( std::greater_equal<eT>(), lhs, rhs ) ;
}

/* Vector == primitive */
template <typename eT, typename Expr>
inline auto operator==( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::equal_to<eT>(), lhs, rhs ) ) {
    return mapply( std::equal_to<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator==( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::equal_to<eT>(), lhs, rhs ) ) {{
    return mapply( std::equal_to<eT>(), lhs, rhs ) ;
}

/* Vector != primitive */
template <typename eT, typename Expr>
inline auto operator!=( 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs , 
    eT rhs
) -> decltype( mapply( std::not_equal_to<eT>(), lhs, rhs ) ) {
    return mapply( std::not_equal_to<eT>(), lhs, rhs ) ;
}
template <typename eT, typename Expr>
inline auto operator!=( 
    eT rhs, 
    const Rcpp::SugarVectorExpression<eT,Expr>& lhs 
) -> decltype( mapply( std::not_equal_to<eT>(), lhs, rhs ) ) {{
    return mapply( std::not_equal_to<eT>(), lhs, rhs ) ;
}


#endif
