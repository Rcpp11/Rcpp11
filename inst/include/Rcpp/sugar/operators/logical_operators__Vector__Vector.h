#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::less<eT>, Expr1, Expr2 >
operator<( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::less<eT>(), lhs, rhs ) ;
}

/* Vector > Vector */
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::greater<eT>, Expr1, Expr2 >
operator>( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::greater<eT>(), lhs, rhs ) ;
}

/* Vector <= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::less_equal<eT>, Expr1, Expr2 >
operator<=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::less_equal<eT>(), lhs, rhs ) ;
}


/* Vector >= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::greater_equal<eT>, Expr1, Expr2 >
operator>=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::greater_equal<eT>(), lhs, rhs ) ;
}


/* Vector == Vector */
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::equal_to<eT>, Expr1, Expr2 >
operator==( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::equal_to<eT>(), lhs, rhs ) ;
}

/* Vector != Vector */
template <typename eT, typename Expr1, typename Expr2>
inline Rcpp::sugar::Mapply< std::not_equal_to<eT>, Expr1, Expr2 >
operator!=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ){
    return mapply( std::not_equal_to<eT>(), lhs, rhs ) ;
}


#endif
