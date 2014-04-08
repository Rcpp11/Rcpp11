#ifndef Rcpp__internal__r_coerce__h
#define Rcpp__internal__r_coerce__h

namespace Rcpp{
namespace internal{

template <int FROM, int TO>
typename ::Rcpp::traits::storage_type<TO>::type 
r_coerce( typename ::Rcpp::traits::storage_type<FROM>::type from ){
	// this implementation is never actually called
	return static_cast<typename ::Rcpp::traits::storage_type<TO>::type >(from);
}
template <> int r_coerce<INTSXP,INTSXP>(int from) ;
template <> int r_coerce<LGLSXP,LGLSXP>(int from) ;
template <> double r_coerce<REALSXP,REALSXP>(double from);
template <> Rcomplex r_coerce<CPLXSXP,CPLXSXP>(Rcomplex from);
template <> Rbyte r_coerce<RAWSXP,RAWSXP>(Rbyte from) ;

// -> INTSXP
template <> int r_coerce<LGLSXP,INTSXP>(int from) ;
template <> int r_coerce<REALSXP,INTSXP>(double from);
template <> int r_coerce<CPLXSXP,INTSXP>(Rcomplex from);
template <> int r_coerce<RAWSXP,INTSXP>(Rbyte from) ;

// -> REALSXP
template <> double r_coerce<LGLSXP,REALSXP>(int from) ;
template <> double r_coerce<INTSXP,REALSXP>(int from);
template <> double r_coerce<CPLXSXP,REALSXP>(Rcomplex from);
template <> double r_coerce<RAWSXP,REALSXP>(Rbyte from) ;

// -> LGLSXP
template <> int r_coerce<REALSXP,LGLSXP>(double from) ;
template <> int r_coerce<INTSXP,LGLSXP>(int from);
template <> int r_coerce<CPLXSXP,LGLSXP>(Rcomplex from);
template <> int r_coerce<RAWSXP,LGLSXP>(Rbyte from) ;

// -> RAWSXP
template <> Rbyte r_coerce<REALSXP,RAWSXP>(double from) ;
template <> Rbyte r_coerce<INTSXP,RAWSXP>(int from);
template <> Rbyte r_coerce<CPLXSXP,RAWSXP>(Rcomplex from);
template <> Rbyte r_coerce<LGLSXP,RAWSXP>(int from) ;

// -> CPLXSXP
template <> Rcomplex r_coerce<REALSXP,CPLXSXP>(double from) ;
template <> Rcomplex r_coerce<INTSXP,CPLXSXP>(int from);
template <> Rcomplex r_coerce<RAWSXP,CPLXSXP>(Rbyte from);
template <> Rcomplex r_coerce<LGLSXP,CPLXSXP>(int from) ;

// -> STRSXP
template <int RTYPE> 
const char* coerce_to_string( typename ::Rcpp::traits::storage_type<RTYPE>::type from ) ;
template <> const char* coerce_to_string<CPLXSXP>(Rcomplex from) ;
template <> const char* coerce_to_string<REALSXP>(double from) ; 
template <> const char* coerce_to_string<INTSXP >(int from) ;
template <> const char* coerce_to_string<RAWSXP >(Rbyte from) ;
template <> const char* coerce_to_string<LGLSXP >(int from) ;

template <> inline SEXP r_coerce<STRSXP ,STRSXP>(SEXP from){ return from ; }
template <> inline SEXP r_coerce<CPLXSXP,STRSXP>(Rcomplex from) { return Rcpp::traits::is_na<CPLXSXP>(from) ? NA_STRING : Rf_mkChar( coerce_to_string<CPLXSXP>( from ) ) ; }
template <> inline SEXP r_coerce<REALSXP,STRSXP>(double from){ return Rcpp::traits::is_na<REALSXP>(from) ? NA_STRING :Rf_mkChar( coerce_to_string<REALSXP>( from ) ) ; }
template <> inline SEXP r_coerce<INTSXP ,STRSXP>(int from){ return Rcpp::traits::is_na<INTSXP>(from) ? NA_STRING :Rf_mkChar( coerce_to_string<INTSXP>( from ) ) ; }
template <> inline SEXP r_coerce<RAWSXP ,STRSXP>(Rbyte from){ return Rf_mkChar( coerce_to_string<RAWSXP>(from)); }
template <> inline SEXP r_coerce<LGLSXP ,STRSXP>(int from){ return Rcpp::traits::is_na<LGLSXP>(from) ? NA_STRING :Rf_mkChar( coerce_to_string<LGLSXP>(from)); }

} // internal
} // Rcpp

#include <Rcpp/internal/coerce/coerce_to_string.h>
#include <Rcpp/internal/coerce/true_cast.h>
#include <Rcpp/internal/coerce/r_coerce.h>

#endif
