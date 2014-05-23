#ifndef Rcpp__sugar__Arith_Vector_Vector_h
#define Rcpp__sugar__Arith_Vector_Vector_h

template <int RTYPE,bool LHS_NA, typename LHS_T, bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Arith_Vector_Vector<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T, std::plus >
operator+( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs,
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
) {
    return Rcpp::sugar::Arith_Vector_Vector<RTYPE,LHS_NA,LHS_T,RHS_NA,RHS_T, std::plus >( lhs, rhs ) ;
}


#endif
