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

#ifndef Rcpp_Module_CppMethod_h
#define Rcpp_Module_CppMethod_h

    template <typename Class, typename MemberFunctionType, bool method_is_const, typename OUT, typename... Args> 
	class CppMethod_Impl : public CppMethod<Class> {
	public:
		typedef CppMethod<Class> method_class ;
		
		CppMethod_Impl( MemberFunctionType m) : method_class(), met(m){} 
		SEXP operator()( Class* object, SEXP* args){
		    return MethodInvoker<Class,OUT,MemberFunctionType,Args...>(met, object, args).invoke() ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return std::is_void<OUT>::value ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
		
	private:
		MemberFunctionType met ;
	} ;


	template <typename Class, typename MemberFunctionType, bool method_is_const, typename OUT, typename... Args> 
	class Debug_CppMethod_Impl : public CppMethod<Class> {
	public:
		typedef CppMethod<Class> method_class ;
		
		Debug_CppMethod_Impl( MemberFunctionType m, const char* name_) : method_class(), met(m), name(name_){} 
		SEXP operator()( Class* object, SEXP* args){
		    debug_method<Class,Debug_CppMethod_Impl>(*this, name, object) ;  
		    SEXP res = MethodInvoker<Class,OUT,MemberFunctionType,Args...>(met, object, args).invoke() ;
		    Rprintf( "\n") ;
		    return res ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return std::is_void<OUT>::value ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
		
	private:
		MemberFunctionType met ;
		std::string name ;
	} ;
	
#endif
