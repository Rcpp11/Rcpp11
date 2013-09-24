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

#ifndef Rcpp_Module_Pointer_CppMethod_h
#define Rcpp_Module_Pointer_CppMethod_h


	template <typename Class, typename OUT, typename... Args> 
	class Pointer_CppMethod_Impl : public CppMethod<Class> {
	public:
		typedef OUT (*Method)(Class*, Args...) ;
		typedef CppMethod<Class> method_class ;
		Pointer_CppMethod_Impl( Method m) : method_class(), met(m){} 
		SEXP operator()( Class* object, SEXP* args ){
			return pointer_method_invoke<Class,OUT,Args...>(object,met,args); 
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return false ; }
		inline bool is_const(){ return false ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
		
	private:
		Method met ;
	} ;
	
	template <typename Class, typename... Args> 
	class Pointer_CppMethod_Impl<Class,void,Args...> : public CppMethod<Class> {
	public:
		typedef void (*Method)(Class*,Args...) ;
		typedef CppMethod<Class> method_class ;
		Pointer_CppMethod_Impl( Method m) : method_class(), met(m){} 
		SEXP operator()( Class* object, SEXP* args ){
			void_pointer_method_invoke<Class,Args...>(object,met,args);
			return R_NilValue ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return true ; }
		inline bool is_const(){ return false ; }
    
		inline void signature(std::string& s, const char* name){ Rcpp::signature<void, Args...>(s, name) ; }
		
	private:
		Method met ;
	} ;

#endif
