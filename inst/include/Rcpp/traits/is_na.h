#ifndef Rcpp__traits_is_na_h
#define Rcpp__traits_is_na_h

namespace Rcpp{
namespace traits{

	// default to always false, applies to VECSXP, EXPRSXP and RAWSXP
	template <int RTYPE> 
	bool is_na( typename storage_type<RTYPE>::type ){
	    return false ;    
	}

	template <> 
	inline bool is_na<INTSXP>( int x ){
		return x == NA_INTEGER ;
	}

	template <> 
	inline bool is_na<REALSXP>( double x ){
		return Rcpp::internal::is_NA(x);
	}

	template <> 
	inline bool is_na<CPLXSXP>( Rcomplex x ){
		return Rcpp::internal::is_NA(x.r) || Rcpp::internal::is_NA(x.i) ;
	}

	template <>
	inline bool is_na<STRSXP>( SEXP x ){ return x == NA_STRING ; }

	template <>
	inline bool is_na<LGLSXP>( int x ){ return x == NA_LOGICAL ; }

}
}

#endif
