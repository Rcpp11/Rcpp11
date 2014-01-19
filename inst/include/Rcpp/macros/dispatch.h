#ifndef Rcpp__macros__dispatch_h
#define Rcpp__macros__dispatch_h

#define ___RCPP_HANDLE_CASE___( ___RTYPE___ , ___FUN___ , ___OBJECT___ , ___RCPPTYPE___ )	\
	case ___RTYPE___ :																	\
		return ___FUN___( ::Rcpp::___RCPPTYPE___< ___RTYPE___ >( ___OBJECT___ ) ) ;	
		         
#define ___RCPP_RETURN___( __FUN__, __SEXP__ , __RCPPTYPE__ )						\
	SEXP __TMP__ = __SEXP__ ;															\
	switch( TYPEOF( __TMP__ ) ){										 				\
		___RCPP_HANDLE_CASE___( INTSXP  , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( REALSXP , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( RAWSXP  , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( LGLSXP  , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( CPLXSXP , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( STRSXP  , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( VECSXP  , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
		___RCPP_HANDLE_CASE___( EXPRSXP , __FUN__ , __TMP__ , __RCPPTYPE__ )			\
	default:																			\
		throw std::range_error( "not a vector" ) ;									\
	}

#define RCPP_RETURN_VECTOR( _FUN_, _SEXP_ )  ___RCPP_RETURN___( _FUN_, _SEXP_ , Vector ) 
#define RCPP_RETURN_MATRIX( _FUN_, _SEXP_ )  ___RCPP_RETURN___( _FUN_, _SEXP_ , Matrix )


#endif
