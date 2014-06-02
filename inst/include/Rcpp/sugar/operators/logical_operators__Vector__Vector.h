#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::less<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator<( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::less<typename Expr1::value_type>(), lhs, rhs ) ;
}

/* Vector > Vector */
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::greater<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator>( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::greater<typename Expr1::value_type>(), lhs, rhs ) ;
}

/* Vector <= Vector */
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::less_equal<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator<=( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::less_equal<typename Expr1::value_type>(), lhs, rhs ) ;
}


/* Vector >= Vector */
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::greater_equal<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator>=( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::greater_equal<typename Expr1::value_type>(), lhs, rhs ) ;
}


/* Vector == Vector */
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::equal_to<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator==( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::equal_to<typename Expr1::value_type>(), lhs, rhs ) ;
}

/* Vector != Vector */
template <typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::not_equal_to<typename Expr2::value_type>, Expr1, Expr2 >
>::type
operator!=( const Rcpp::SugarVectorExpression<Expr1>& lhs , const Rcpp::SugarVectorExpression<Expr2>& rhs ){
    return mapply( std::not_equal_to<typename Expr1::value_type>(), lhs, rhs ) ;
}


#endif
