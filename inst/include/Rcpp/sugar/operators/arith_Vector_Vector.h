#ifndef Rcpp__sugar__Arith_Vector_Vector_h
#define Rcpp__sugar__Arith_Vector_Vector_h

template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::plus<eT>, Expr1, Expr2 >    
operator+( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) {
    return Rcpp::mapply( std::plus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::minus<eT>, Expr1, Expr2 >    
operator-( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) {
    return Rcpp::mapply( std::minus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::multiplies<eT>, Expr1, Expr2 >    
operator*( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) {
    return Rcpp::mapply( std::multiplies<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::divides<eT>, Expr1, Expr2 >
operator/( 
    const Rcpp::SugarVectorExpression<eT, Expr1>& lhs,
    const Rcpp::SugarVectorExpression<eT, Expr2>& rhs
) {
    return Rcpp::mapply( std::divides<eT>(), lhs, rhs ) ;
}

#endif
