#ifndef Rcpp__sugar__Arith_Vector_Vector_h
#define Rcpp__sugar__Arith_Vector_Vector_h

template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Rcpp::sugar::Mapply< std::plus<typename Expr1::value>, Expr1, Expr2 >    
>::type
operator+( 
    const Rcpp::SugarVectorExpression<Expr1>& lhs,
    const Rcpp::SugarVectorExpression<Expr2>& rhs
) {
    return mapply( std::plus< typename Expr1::value >(), lhs, rhs ) ;
}

template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Rcpp::sugar::Mapply< std::minus<typename Expr1::value>, Expr1, Expr2 >    
>::type
operator-( 
    const Rcpp::SugarVectorExpression<Expr1>& lhs,
    const Rcpp::SugarVectorExpression<Expr2>& rhs
) {
    return mapply( std::minus< typename Expr1::value >(), lhs, rhs ) ;
}

template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Rcpp::sugar::Mapply< std::multiplies<typename Expr1::value>, Expr1, Expr2 >    
>::type
operator*( 
    const Rcpp::SugarVectorExpression<Expr1>& lhs,
    const Rcpp::SugarVectorExpression<Expr2>& rhs
) {
    return mapply( std::multiplies< typename Expr1::value >(), lhs, rhs ) ;
}

template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Rcpp::sugar::Mapply< std::divides<typename Expr1::value>, Expr1, Expr2 >    
>::type
operator/( 
    const Rcpp::SugarVectorExpression<Expr1>& lhs,
    const Rcpp::SugarVectorExpression<Expr2>& rhs
) {
    return mapply( std::divides< typename Expr1::value >(), lhs, rhs ) ;
}

#endif
