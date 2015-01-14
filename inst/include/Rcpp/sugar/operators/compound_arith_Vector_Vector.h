#ifndef Rcpp__sugar__compound_Arith_Vector_Vector_h
#define Rcpp__sugar__compound_Arith_Vector_Vector_h

template <typename eT, typename Expr1, typename Expr2>
inline Expr1& operator+=( Expr1& lhs, const Rcpp::SugarVectorExpression<eT, Expr2>& rhs ){
    lhs = lhs + rhs ;
    return lhs ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Expr1& operator-=( Expr1& lhs, const Rcpp::SugarVectorExpression<eT, Expr2>& rhs ){
    lhs = lhs - rhs ;
    return lhs ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Expr1& operator*=( Expr1& lhs, const Rcpp::SugarVectorExpression<eT, Expr2>& rhs ){
    lhs = lhs * rhs ;
    return lhs ;
}

template <typename eT, typename Expr1, typename Expr2>
inline Expr1& operator/=( Expr1& lhs, const Rcpp::SugarVectorExpression<eT, Expr2>& rhs ){
    lhs = lhs / rhs ;
    return lhs ;
}


#endif
