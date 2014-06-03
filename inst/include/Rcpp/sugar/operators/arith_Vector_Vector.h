#ifndef Rcpp__sugar__Arith_Vector_Vector_h
#define Rcpp__sugar__Arith_Vector_Vector_h

template <typename eT, typename Expr1, typename Expr2>
inline auto    
operator+( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) -> decltype( Rcpp::mapply( std::plus<eT>(), lhs.get_ref(), rhs.get_ref() ) ) {
    return Rcpp::mapply( std::plus<eT>(), lhs.get_ref(), rhs.get_ref() ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline auto    
operator-( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) -> decltype( Rcpp::mapply( std::minus<eT>(), lhs.get_ref(), rhs.get_ref() ) ){
    return Rcpp::mapply( std::minus<eT>(), lhs.get_ref(), rhs.get_ref() ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline auto    
operator*( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) -> decltype( Rcpp::mapply( std::multiplies<eT>(), lhs.get_ref(), rhs.get_ref() ) ){
    return Rcpp::mapply( std::multiplies<eT>(), lhs.get_ref(), rhs.get_ref() ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline auto
operator/( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) -> decltype( Rcpp::mapply( std::divides<eT>(), lhs.get_ref(), rhs.get_ref() ) ){
    return Rcpp::mapply( std::divides<eT>(), lhs.get_ref(), rhs.get_ref() ) ;
}

#endif
