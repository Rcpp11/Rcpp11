#ifndef Rcpp__traits__is_trivial_h
#define Rcpp__traits__is_trivial_h

namespace Rcpp{
namespace traits{

	template <int RTYPE> struct is_trivial  : public std::true_type{} ;
	template <> struct is_trivial<VECSXP>   : public std::false_type{} ;
	template <> struct is_trivial<EXPRSXP>  : public std::false_type{} ;

} // traits
} // Rcpp
	
#endif
