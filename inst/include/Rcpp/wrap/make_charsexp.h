// Copyright (C) 2013  Romain Francois
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

#ifndef Rcpp_wrap_make_charsexp_h
#define Rcpp_wrap_make_charsexp_h
 
namespace Rcpp{
namespace internal{
	
	char* get_string_buffer() ;
	
	inline SEXP make_charsexp__impl__wstring( const wchar_t* data ){
		char* buffer = get_string_buffer() ;
		wcstombs( buffer, data, MAXELTSIZE ) ;
		return Rf_mkChar(buffer) ;
	}
	inline SEXP make_charsexp__impl__wstring( wchar_t data ){
		wchar_t x[2] ; x[0] = data ; x[1] = '\0' ;
		char* buffer = get_string_buffer() ;
		wcstombs( buffer, x, MAXELTSIZE ) ;
		return Rf_mkChar(buffer) ;
	}
	inline SEXP make_charsexp__impl__wstring( const std::wstring& st ){
		return make_charsexp__impl__wstring( st.data()) ;	
	}
	inline SEXP make_charsexp__impl__cstring( const char* data ){
		RCPP_DEBUG( "make_charsexp__impl__cstring( const char* = '%s' )", data )
		return Rf_mkChar( data ) ;
	}
	inline SEXP make_charsexp__impl__cstring( char data ){
		char x[2]; x[0] = data ; x[1] = '\0' ;
		return Rf_mkChar( x ) ;
	}
	
	inline SEXP make_charsexp__impl__cstring( const std::string& st ){
		RCPP_DEBUG( "make_charsexp__impl__cstring( const std::string& )" )
		return make_charsexp__impl__cstring( st.c_str() ) ;
	}
	
	template <typename T>
	inline SEXP make_charsexp__impl( const T& s, std::true_type ){
		RCPP_DEBUG( "make_charsexp__impl<%s>(., is_wide_string = true)", DEMANGLE(T) )
		return make_charsexp__impl__wstring(s) ;
	}
	
	template <typename T>
	inline SEXP make_charsexp__impl( const T& s, std::false_type ){
		RCPP_DEBUG( "make_charsexp__impl<%s>(., is_wide_string = false)", DEMANGLE(T) )
		return make_charsexp__impl__cstring(s) ;
	}
	
	template <typename T> 
	inline SEXP make_charsexp( const T& s) {
		RCPP_DEBUG( "make_charsexp<%s>(.)", DEMANGLE(T) )
		return make_charsexp__impl<T>( s, typename Rcpp::traits::is_wide_string<T>::type() ) ;
	}
	template <>
	inline SEXP make_charsexp<Rcpp::String>( const Rcpp::String& );

}
}

#endif
