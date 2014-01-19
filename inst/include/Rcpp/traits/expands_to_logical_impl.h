#ifndef Rcpp__traits__expands_to_logical_impl__h
#define Rcpp__traits__expands_to_logical_impl__h

namespace Rcpp{
namespace traits{

	template <int RTYPE>
	struct expands_to_logical__impl{} ;

	template <>
	struct expands_to_logical__impl<LGLSXP> {
		struct r_expands_to_logical{}; 
	} ;

}
}

#endif

