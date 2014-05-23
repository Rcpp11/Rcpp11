#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::less>
operator<( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::less>( lhs, rhs ) ;
}

/* Vector > Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::greater>
operator>( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::greater>( lhs, rhs ) ;
}

/* Vector <= Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::less_equal>
operator<=( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::less_equal>( lhs, rhs ) ;
}


/* Vector >= Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::greater_equal>
operator>=( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::greater_equal>( lhs, rhs ) ;
}


/* Vector == Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::equal_to>
operator==( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::equal_to>( lhs, rhs ) ;
}

/* Vector != Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::not_equal_to>
operator!=( 
    const Rcpp::SugarVectorExpression<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<RTYPE,LHS_NA, LHS_T, RHS_NA, RHS_T,std::not_equal_to>( lhs, rhs ) ;
}


#endif
