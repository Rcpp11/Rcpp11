#ifndef Rcpp__vector__proxy_h
#define Rcpp__vector__proxy_h

namespace Rcpp{
namespace traits {
	
	template <int RTYPE> 
	struct r_vector_name_proxy{
		typedef typename ::Rcpp::internal::simple_name_proxy<RTYPE> type ;
	} ;
	template<> struct r_vector_name_proxy<STRSXP>{
		typedef ::Rcpp::internal::string_name_proxy<STRSXP> type ;
	} ;
	template<> struct r_vector_name_proxy<VECSXP>{
		typedef ::Rcpp::internal::generic_name_proxy<VECSXP> type ;
	} ;
	template<> struct r_vector_name_proxy<EXPRSXP>{
		typedef ::Rcpp::internal::generic_name_proxy<EXPRSXP> type ;
	} ;

	template <int RTYPE> 
	struct r_vector_const_name_proxy{
		typedef ::Rcpp::internal::simple_const_name_proxy<RTYPE> type ;
	} ;
	template<> struct r_vector_const_name_proxy<STRSXP>{
		typedef ::Rcpp::internal::string_const_name_proxy<STRSXP> type ;
	} ;
	template<> struct r_vector_const_name_proxy<VECSXP>{
		typedef ::Rcpp::internal::generic_const_name_proxy<VECSXP> type ;
	} ;
	template<> struct r_vector_const_name_proxy<EXPRSXP>{
		typedef ::Rcpp::internal::generic_const_name_proxy<EXPRSXP> type ;
	} ;

	template <int RTYPE>
	struct r_vector_proxy{
		typedef typename storage_type<RTYPE>::type& type ;
	} ;
	template<> struct r_vector_proxy<STRSXP> {
		typedef ::Rcpp::internal::string_proxy<STRSXP> type ;
	} ;
	template<> struct r_vector_proxy<EXPRSXP> {
		typedef ::Rcpp::internal::generic_proxy<EXPRSXP> type ;
	} ;
	template<> struct r_vector_proxy<VECSXP> {
		typedef ::Rcpp::internal::generic_proxy<VECSXP> type ;
	} ;

	template <int RTYPE>
	struct r_vector_const_proxy{
		typedef const typename storage_type<RTYPE>::type& type ;
	} ;                                            
	template<> struct r_vector_const_proxy<STRSXP> {
	    typedef ::Rcpp::internal::const_string_proxy<STRSXP> type ;
	} ;
	template<> struct r_vector_const_proxy<EXPRSXP> {
		typedef ::Rcpp::internal::const_generic_proxy<EXPRSXP> type ;
	} ;
	template<> struct r_vector_const_proxy<VECSXP> {
		typedef ::Rcpp::internal::const_generic_proxy<VECSXP> type ;
	} ;

	template <int RTYPE>
	struct r_vector_iterator {
		typedef typename storage_type<RTYPE>::type* type ;
	};
	template <int RTYPE> struct proxy_based_iterator{
		typedef ::Rcpp::internal::Proxy_Iterator< typename r_vector_proxy<RTYPE>::type > type ;
	} ;
	template<> struct r_vector_iterator<VECSXP> : proxy_based_iterator<VECSXP>{} ;
	template<> struct r_vector_iterator<EXPRSXP> : proxy_based_iterator<EXPRSXP>{} ;
	template<> struct r_vector_iterator<STRSXP> : proxy_based_iterator<STRSXP>{} ;
    
	
	template <int RTYPE>
	struct r_vector_const_iterator {
	    using type = const typename storage_type<RTYPE>::type* ;
	};
	template <int RTYPE> struct const_proxy_based_iterator{
	    using type = ::Rcpp::internal::const_Proxy_Iterator< typename r_vector_const_proxy<RTYPE>::type > ;
	} ;
	template<> struct r_vector_const_iterator<VECSXP>  : const_proxy_based_iterator<VECSXP>{} ;
	template<> struct r_vector_const_iterator<EXPRSXP> : const_proxy_based_iterator<EXPRSXP>{} ;
	template<> struct r_vector_const_iterator<STRSXP>  : const_proxy_based_iterator<STRSXP>{} ;
    
	
}  // traits
}

#endif
