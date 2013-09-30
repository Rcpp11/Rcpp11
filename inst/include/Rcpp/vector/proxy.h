// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013 Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

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
		typedef typename storage_type<RTYPE>::type* const type ;
	};
	template <int RTYPE> struct const_proxy_based_iterator{
		typedef ::Rcpp::internal::const_Proxy_Iterator< typename r_vector_const_proxy<RTYPE>::type > type ;
	} ;
	template<> struct r_vector_const_iterator<VECSXP>  : const_proxy_based_iterator<VECSXP>{} ;
	template<> struct r_vector_const_iterator<EXPRSXP> : const_proxy_based_iterator<EXPRSXP>{} ;
	template<> struct r_vector_const_iterator<STRSXP>  : const_proxy_based_iterator<STRSXP>{} ;
    
	
}  // traits
}

#endif
