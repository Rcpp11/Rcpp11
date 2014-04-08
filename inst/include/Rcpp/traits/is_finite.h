#ifndef Rcpp__traits_is_finite_h
#define Rcpp__traits_is_finite_h

namespace Rcpp{
namespace traits{

	// default for complex, 
	template <int RTYPE> 
	bool is_finite( typename storage_type<RTYPE>::type) ;

	template <> 
	inline bool is_finite<INTSXP>( int x ){
		return x != NA_INTEGER ;
	}

	template <> 
	inline bool is_finite<REALSXP>( double x ){
		return R_finite(x) ;
	}

	template <> 
	inline bool is_finite<CPLXSXP>( Rcomplex x ){
		return !( !R_finite(x.r) || !R_finite(x.i) );
	}

	template <>
	inline bool is_finite<STRSXP>( SEXP x ){ return x != NA_STRING ; }

	template <>
	inline bool is_finite<LGLSXP>( int x ){ return x != NA_LOGICAL ; }

}
}

#endif
