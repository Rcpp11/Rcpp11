#ifndef Rcpp__sugar__Unary_h
#define Rcpp__sugar__Unary_h

template <int RTYPE,bool NA, typename T>
inline auto operator-( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& x ) -> decltype( sapply(x, typename Rcpp::unary_op_type<RTYPE,NA,std::negate>::type() ) ) {
    return sapply(x, typename Rcpp::unary_op_type<RTYPE,NA,std::negate>::type() ); 
}

template <int RTYPE,bool NA, typename T>
inline auto operator!( const Rcpp::SugarVectorExpression<RTYPE,NA,T>& x ) -> decltype( sapply(x, typename Rcpp::unary_op_type<RTYPE,NA,std::negate>::type() ) ) {
    return sapply(x, typename Rcpp::unary_op_type<RTYPE,NA,std::logical_not>::type() ); 
}


#endif
