#ifndef Rcpp__sugar__logical_operators__Vector__primitive_h
#define Rcpp__sugar__logical_operators__Vector__primitive_h

/* Vector < primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::less<RTYPE>, 
    NA, 
    T
    > 
operator<( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::less<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::less<RTYPE>, 
    NA, 
    T
    > 
operator>( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::less<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}



/* Vector > primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::greater<RTYPE>, 
    NA, 
    T
    > 
operator>( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::greater<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::greater<RTYPE>, 
    NA, 
    T
    > 
operator<( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::greater<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}



/* Vector <= primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::less_or_equal<RTYPE>, 
    NA, 
    T
    > 
operator<=( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::less_or_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::less_or_equal<RTYPE>, 
    NA, 
    T
    > 
operator>=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs 
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::less_or_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}




/* Vector >= primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::greater_or_equal<RTYPE>, 
    NA, 
    T
    > 
operator>=( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::greater_or_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::greater_or_equal<RTYPE>, 
    NA, 
    T
    > 
operator<=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::greater_or_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}



/* Vector == primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::equal<RTYPE>, 
    NA, 
    T
    > 
operator==( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::equal<RTYPE>, 
    NA, 
    T
    > 
operator==( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}



/* Vector != primitive */
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::not_equal<RTYPE>, 
    NA, 
    T
    > 
operator!=( 
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::not_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}
template <int RTYPE, bool NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<
    RTYPE , 
    Rcpp::sugar::not_equal<RTYPE>, 
    NA, 
    T
    > 
operator!=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,NA,T>& lhs 
    ){
    return Rcpp::sugar::Comparator_With_One_Value<
        RTYPE, 
        Rcpp::sugar::not_equal<RTYPE>, 
        NA,
        T 
        >( 
            lhs, rhs
        ) ;
}


#endif
