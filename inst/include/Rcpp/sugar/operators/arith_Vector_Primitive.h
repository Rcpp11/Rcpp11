#ifndef Rcpp__sugar__Arith_Vector_Primitive_h
#define Rcpp__sugar__Arith_Vector_Primitive_h

template <int RTYPE,bool LHS_NA, typename LHS_T>
inline Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::plus >
operator+( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
) {
    return Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::plus >( lhs, rhs ) ;
}

template <int RTYPE,bool LHS_NA, typename LHS_T>
inline Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::minus >
operator-( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
) {
    return Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::minus >( lhs, rhs ) ;
}

template <int RTYPE,bool LHS_NA, typename LHS_T>
inline Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::multiplies >
operator*( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
) {
    return Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::multiplies >( lhs, rhs ) ;
}

template <int RTYPE,bool LHS_NA, typename LHS_T>
inline Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::divides >
operator/( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
) {
    return Rcpp::sugar::Arith_Vector_Primitive<RTYPE,LHS_NA,LHS_T, std::divides >( lhs, rhs ) ;
}

#endif
