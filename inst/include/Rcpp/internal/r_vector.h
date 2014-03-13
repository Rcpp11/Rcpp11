#ifndef Rcpp__internal__r_vector_h
#define Rcpp__internal__r_vector_h

namespace Rcpp{
namespace internal{

template<int RTYPE> 
typename Rcpp::traits::storage_type<RTYPE>::type* r_vector_start(SEXP x){ 
    return VECTOR_PTR(x) ;
}

template<> inline int* r_vector_start<INTSXP>(SEXP x){ 
    return INTEGER(x) ; 
}
template<> inline int* r_vector_start<LGLSXP>(SEXP x){ 
    return LOGICAL(x) ;
}
template<> inline double* r_vector_start<REALSXP>(SEXP x){ 
    return REAL(x) ;
}
template<> inline Rbyte* r_vector_start<RAWSXP>(SEXP x){ 
    return RAW(x) ;
}
template<> inline Rcomplex* r_vector_start<CPLXSXP>(SEXP x){ 
    return COMPLEX(x) ;
}

} // internal
} // Rcpp

#endif
