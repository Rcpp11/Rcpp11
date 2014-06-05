#ifndef Rcpp__sugar__Arith_Vector_Primitive_h
#define Rcpp__sugar__Arith_Vector_Primitive_h

template <typename eT, typename Expr>
inline auto
operator+(const Rcpp::SugarVectorExpression<eT,Expr>& lhs, eT rhs) -> decltype( mapply( std::plus<eT>(), lhs, rhs ) ) {
    return mapply( std::plus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator-( const Rcpp::SugarVectorExpression<eT,Expr>& lhs, eT rhs) -> decltype( mapply( std::minus<eT>(), lhs, rhs ) ) {
    RCPP_DEBUG( "%s - %s (%d)\n", DEMANGLE(Expr), DEMANGLE(eT), rhs )
    return mapply( std::minus<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator*( const Rcpp::SugarVectorExpression<eT,Expr>& lhs, eT rhs) -> decltype( mapply( std::multiplies<eT>(), lhs, rhs ) ) {
    return mapply( std::multiplies<eT>(), lhs, rhs ) ;
}

template <typename eT, typename Expr>
inline auto
operator/( const Rcpp::SugarVectorExpression<eT,Expr>& lhs, eT rhs) -> decltype( mapply( std::divides<eT>(), lhs, rhs ) ) {
    return mapply( std::divides<eT>(), lhs, rhs ) ;
}

#endif
