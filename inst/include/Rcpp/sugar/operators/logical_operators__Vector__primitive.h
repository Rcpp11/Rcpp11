#ifndef Rcpp__sugar__logical_operators__Vector__primitive_h
#define Rcpp__sugar__logical_operators__Vector__primitive_h

/* Vector < primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less> 
operator<( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less> 
operator>( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less>(lhs, rhs) ;
}


/* Vector > primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater> 
operator>( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater> 
operator<( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater>(lhs, rhs) ;
}


/* Vector <= primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less_equal>
operator<=( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less_equal>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less_equal>
operator>=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs 
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::less_equal>(lhs, rhs) ;
}


/* Vector >= primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater_equal>
operator>=( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater_equal>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater_equal> 
operator<=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::greater_equal>(lhs, rhs) ;
}

/* Vector == primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::equal_to>
operator==( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::equal_to>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::equal_to>
operator==( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::equal_to>(lhs, rhs) ;
}

/* Vector != primitive */
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::not_equal_to> 
operator!=( 
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs , 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::not_equal_to>(lhs, rhs) ;
}
template <int RTYPE, bool HAS_NA, typename T>
inline Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::not_equal_to>
operator!=( 
    typename Rcpp::traits::storage_type<RTYPE>::type rhs,
    const Rcpp::SugarVectorExpression<RTYPE,HAS_NA,T>& lhs 
    ){
    return Rcpp::sugar::Comparator_With_One_Value<RTYPE,HAS_NA,T,std::not_equal_to>(lhs, rhs) ;
}


#endif
