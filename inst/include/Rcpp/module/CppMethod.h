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
		    return method_invoke<Class,OUT,MemberFunctionType,Args...>(typename traits::number_to_type<sizeof...(Args)>(), met, object ,args);  
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return false ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
		
	private:
		MemberFunctionType met ;
	} ;

	template <typename Class, typename MemberFunctionType, bool method_is_const, typename... Args> 
	class CppMethod_Impl<Class,MemberFunctionType,method_is_const,void,Args...> : public CppMethod<Class> {
	public:
		typedef CppMethod<Class> method_class ;
		
		CppMethod_Impl( MemberFunctionType m) : method_class(), met(m){} 
		SEXP operator()( Class* object, SEXP* args){
		    void_method_invoke<Class,MemberFunctionType,Args...>(typename traits::number_to_type<sizeof...(Args)>(),met,object,args);
		    return R_NilValue ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return true ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<void,Args...>(s, name) ; }
		
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
		    SEXP res = method_invoke<Class,OUT,MemberFunctionType,Args...>(typename traits::number_to_type<sizeof...(Args)>(), met, object ,args);
		    Rprintf( "\n") ;
		    return res ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return false ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
		
	private:
		MemberFunctionType met ;
		std::string name ;
	} ;

	template <typename Class, typename MemberFunctionType, bool method_is_const, typename... Args> 
	class Debug_CppMethod_Impl<Class,MemberFunctionType, method_is_const,void,Args...> : public CppMethod<Class> {
	public:
		typedef CppMethod<Class> method_class ;
		
		Debug_CppMethod_Impl( MemberFunctionType m, const char* name_) : method_class(), met(m), name(name_){} 
		SEXP operator()( Class* object, SEXP* args){
		    debug_method<Class,Debug_CppMethod_Impl>(*this, name, object) ;  
		    void_method_invoke<Class,MemberFunctionType,Args...>(typename traits::number_to_type<sizeof...(Args)>(),met,object,args);
		    Rprintf( "\n") ;
		    return R_NilValue ;
		}
		inline int nargs(){ return sizeof...(Args) ; }
		inline bool is_void(){ return true ; }
		inline bool is_const(){ return method_is_const ; }
		inline void signature(std::string& s, const char* name){ Rcpp::signature<void,Args...>(s, name) ; }
		
	private:
		MemberFunctionType met ;
		std::string name ;
	} ;

#endif
