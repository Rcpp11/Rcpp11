#ifndef Rcpp__traits__get_na__h
#define Rcpp__traits__get_na__h

namespace Rcpp{
namespace traits{

template<int RTYPE> 
typename storage_type<RTYPE>::type get_na() ;

template<>
inline int get_na<INTSXP>(){ return NA_INTEGER ; }

template<>
inline int get_na<LGLSXP>(){ return NA_LOGICAL ; }

template<>
inline double get_na<REALSXP>(){ return NA_REAL ; }

template<>
inline Rcomplex get_na<CPLXSXP>(){ 
	Rcomplex x ;
	x.r = NA_REAL ;
	x.i = NA_REAL ;
	return x ;
}

template<>
inline SEXP get_na<STRSXP>(){ return NA_STRING ; }

}
}

#endif
