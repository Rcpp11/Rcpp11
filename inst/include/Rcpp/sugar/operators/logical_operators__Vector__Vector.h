#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::less<eT>, Expr1, Expr2 >
>::type
operator<( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::less<eT>(), lhs, rhs ) ;
}

/* Vector > Vector */
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::greater<eT>, Expr1, Expr2 >
>::type
operator>( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::greater<eT>(), lhs, rhs ) ;
}

/* Vector <= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::less_equal<eT>, Expr1, Expr2 >
>::type
operator<=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::less_equal<eT>(), lhs, rhs ) ;
}


/* Vector >= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::greater_equal<eT>, Expr1, Expr2 >
>::type
operator>=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::greater_equal<eT>(), lhs, rhs ) ;
}


/* Vector == Vector */
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::equal_to<eT>, Expr1, Expr2 >
>::type
operator==( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::equal_to<eT>(), lhs, rhs ) ;
}

/* Vector != Vector */
template <typename eT, typename Expr1, typename Expr2>
inline typename std::enable_if<
    Rcpp::traits::same_mapply_scalar_type<Expr1,Expr2>::value, 
    Mapply< std::not_equal_to<eT>, Expr1, Expr2 >
>::type
operator!=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::not_equal_to<eT>(), lhs, rhs ) ;
}


#endif
