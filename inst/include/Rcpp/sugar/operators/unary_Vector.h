#ifndef Rcpp__sugar__unary_Vector_h
#define Rcpp__sugar__unary_Vector_h

template <typename Expr>
inline auto operator-( const Rcpp::SugarVectorExpression<Expr>& x ) -> decltype( sapply(x, std::negate<typename Expr::value_type>() ) ) {
    return sapply(x, std::negate<typename Expr::value_type>() ); 
}

template <typename Expr>
inline auto operator!( const Rcpp::SugarVectorExpression<Expr>& x ) -> decltype( sapply(x, std::logical_not<typename Expr::value_type>() ) ) {
    return sapply(x, std::logical_not<typename Expr::value_type>() ); 
}


#endif
