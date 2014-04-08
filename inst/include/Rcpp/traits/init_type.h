#ifndef Rcpp__traits__init_type_h
#define Rcpp__traits__init_type_h

namespace Rcpp {
namespace traits {

	template<int RTYPE> struct init_type {
		typedef typename storage_type<RTYPE>::type type ;
	} ;
	template<> struct init_type<STRSXP>{
		typedef const char* type ;
	} ;
	template<> struct init_type<LGLSXP>{
		typedef bool type ;
	} ;

}
}

#endif
