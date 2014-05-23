#ifndef Rcpp__sugar__Arith_Primitive_Vector_h
#define Rcpp__sugar__Arith_Primitive_Vector_h

template <int RTYPE,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::plus >
operator+( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::plus >( lhs, rhs ) ;
}

template <int RTYPE,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::minus >
operator-( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::minus >( lhs, rhs ) ;
}

template <int RTYPE,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::multiplies >
operator*( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::multiplies >( lhs, rhs ) ;
}

template <int RTYPE,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::divides >
operator/( 
    typename Rcpp::traits::storage_type<RTYPE>::type lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, std::divides >( lhs, rhs ) ;
}
 
#endif
