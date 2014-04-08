#ifndef Rcpp__sugar__logical_operators__Vector__Vector_h
#define Rcpp__sugar__logical_operators__Vector__Vector_h

/* Vector < Vector */ 
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::less<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator<( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::less<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}
/* Vector > Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::greater<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator>( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::greater<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}
/* Vector <= Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::less_or_equal<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator<=( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::less_or_equal<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}
/* Vector >= Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::greater_or_equal<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator>=( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::greater_or_equal<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}
/* Vector == Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::equal<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator==( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::equal<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}
/* Vector != Vector */
template <int RTYPE,bool LHS_NA,typename LHS_T,bool RHS_NA, typename RHS_T>
inline Rcpp::sugar::Comparator<
    RTYPE , 
    Rcpp::sugar::not_equal<RTYPE>, 
    LHS_NA, LHS_T, 
    RHS_NA, RHS_T
    > 
operator!=( 
    const Rcpp::VectorBase<RTYPE,LHS_NA,LHS_T>& lhs , 
    const Rcpp::VectorBase<RTYPE,RHS_NA,RHS_T>& rhs
    ){
    return Rcpp::sugar::Comparator<
        RTYPE, 
        Rcpp::sugar::not_equal<RTYPE>, 
        LHS_NA, LHS_T, 
        RHS_NA, RHS_T
        >( 
        lhs, rhs
        ) ;
}

#endif
