#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <typename eT, typename Expr1, typename Expr2>
inline auto operator<( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) ->
    decltype(mapply( std::less<eT>(), lhs, rhs )) 
{
    return mapply( std::less<eT>(), lhs, rhs ) ;
}

/* Vector > Vector */
template <typename eT, typename Expr1, typename Expr2>
inline auto operator>( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) -> 
    decltype(mapply( std::greater<eT>(), lhs, rhs ))
{
    return mapply( std::greater<eT>(), lhs, rhs ) ;
}

/* Vector <= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline auto operator<=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) ->
    decltype(mapply( std::less_equal<eT>(), lhs, rhs ))
{
    return mapply( std::less_equal<eT>(), lhs, rhs ) ;
}


/* Vector >= Vector */
template <typename eT, typename Expr1, typename Expr2>
inline auto operator>=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) ->
    decltype(mapply( std::greater_equal<eT>(), lhs, rhs )) 
{
    return mapply( std::greater_equal<eT>(), lhs, rhs ) ;
}


/* Vector == Vector */
template <typename eT, typename Expr1, typename Expr2>
inline auto operator==( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) ->
    decltype(mapply( std::equal_to<eT>(), lhs, rhs )) 
{
    return mapply( std::equal_to<eT>(), lhs, rhs ) ;
}

/* Vector != Vector */
template <typename eT, typename Expr1, typename Expr2>
inline auto operator!=( const Rcpp::SugarVectorExpression<eT,Expr1>& lhs , const Rcpp::SugarVectorExpression<eT,Expr2>& rhs ) -> 
    decltype(mapply( std::not_equal_to<eT>(), lhs, rhs )) 
{
    return mapply( std::not_equal_to<eT>(), lhs, rhs ) ;
}


#endif
