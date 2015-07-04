#ifndef Rcpp__sugar__compound_Arith_Vector_primitive_h
#define Rcpp__sugar__compound_Arith_Vector_primitive_h

template <int RTYPE, typename Storage, typename eT>
inline Rcpp::Vector<RTYPE,Storage>& operator+=( Rcpp::Vector<RTYPE,Storage>& lhs, eT rhs ){
    lhs = lhs + rhs ;
    return lhs ;    
}

template <int RTYPE, typename Storage, typename eT>
inline Rcpp::Vector<RTYPE,Storage>& operator-=( Rcpp::Vector<RTYPE,Storage>& lhs, eT rhs ){
    lhs = lhs - rhs ;
    return lhs ;    
}

template <int RTYPE, typename Storage, typename eT>
inline Rcpp::Vector<RTYPE,Storage>& operator*=( Rcpp::Vector<RTYPE,Storage>& lhs, eT rhs ){
    lhs = lhs * rhs ;
    return lhs ;    
}

template <int RTYPE, typename Storage, typename eT>
inline Rcpp::Vector<RTYPE,Storage>& operator/=( Rcpp::Vector<RTYPE,Storage>& lhs, eT rhs ){
    lhs = lhs / rhs ;
    return lhs ;    
}

#endif
