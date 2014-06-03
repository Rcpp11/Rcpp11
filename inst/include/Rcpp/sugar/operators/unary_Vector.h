#ifndef Rcpp__sugar__unary_Vector_h
#define Rcpp__sugar__unary_Vector_h

template <typename eT, typename Expr>
inline auto operator-( const Rcpp::SugarVectorExpression<eT, Expr>& x ) -> decltype( sapply(x, std::negate<eT>() ) ) {
    return sapply(x, std::negate<eT>() ); 
}

template <typename eT, typename Expr>
inline auto operator!( const Rcpp::SugarVectorExpression<eT, Expr>& x ) -> decltype( sapply(x, std::logical_not<eT>() ) ) {
    return sapply(x, std::logical_not<eT>() ); 
}


#endif
