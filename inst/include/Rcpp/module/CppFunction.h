//
// CppFunction.h:  C++ exposed function
//
// Copyright (C) 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Module_CppFunction_h
#define Rcpp_Module_CppFunction_h

namespace Rcpp{
    
    /** 
     * base class of all exported C++ functions. Template deduction in the
     * Module_generated_function.h file creates an instance of a class that 
     * derives CppFunction
     */
    class CppFunction {
    public:
        CppFunction(const char* doc = 0) : docstring( doc == 0 ? "" : doc) {}
        
        /**
         * modules call the function with this interface. input: an array of SEXP
         * output: a SEXP. 
         */
        virtual SEXP operator()(SEXP*) { 
            return R_NilValue ;
        }
        virtual ~CppFunction(){} ;
        
        /**
         * The number of arguments of the function
         */
        virtual int nargs(){ return 0 ; }
        
        /**
         * voidness
         */
        virtual bool is_void(){ return false ; }
        
        /**
         * Human readable function signature (demangled if possible)
         */
        virtual void signature(std::string&, const char* ){}
        
        /**
         * formal arguments
         */
        virtual SEXP get_formals(){ return R_NilValue; }
        
        /**
         * description of the function
         */
        std::string docstring ;
    };

    template <typename OUT, typename... Args>
    class CppFunction_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            CppFunction_Impl(Fun fun, const char* docstring = 0 ) : 
                CppFunction(docstring), ptr_fun(fun){}
                
            inline SEXP operator()(SEXP* args) {
                return FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
            }
    
            inline int nargs(){ return sizeof...(Args); }
            inline void signature(std::string& s, const char* name){ ::Rcpp::signature<OUT, Args...>(s, name) ; }
            
        private:
            Fun ptr_fun ;
    } ;

    template <typename OUT, typename... Args>
    class CppFunction_WithFormals_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            CppFunction_WithFormals_Impl(Fun fun, List formals_,  const char* docstring = 0 ) : 
                CppFunction(docstring), formals(formals_), ptr_fun(fun){}
            
            inline SEXP operator()(SEXP* args) {
                return FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
            }
    
            inline int nargs(){ return sizeof...(Args) ; }
            inline void signature(std::string& s, const char* name){ ::Rcpp::signature<OUT,Args...>(s, name) ; }
            inline SEXP get_formals(){ return formals; }
        
        private:
            List formals ;
            Fun ptr_fun ;
    } ;
    
    template <typename OUT, typename... Args>
    class Debug_CppFunction_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            Debug_CppFunction_Impl(Fun fun, const char* name_, const char* docstring = 0 ) : 
                CppFunction(docstring), ptr_fun(fun), name(name_) {}
                
            inline SEXP operator()(SEXP* args) {
                debug_function<Debug_CppFunction_Impl>( *this, name ) ;
                SEXP res = FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
                Rprintf( "\n" ) ;
                return res ;
            }
    
            inline int nargs(){ return sizeof...(Args); }
            inline void signature(std::string& s, const char* name){ ::Rcpp::signature<OUT, Args...>(s, name) ; }
            
        private:
            Fun ptr_fun ;
            std::string name ;
    } ;

    template <typename OUT, typename... Args>
    class Debug_CppFunction_WithFormals_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            Debug_CppFunction_WithFormals_Impl(Fun fun, List formals_, const char* name_, const char* docstring = 0 ) : 
                CppFunction(docstring), formals(formals_), ptr_fun(fun), name(name_) {}
            
            inline SEXP operator()(SEXP* args) {
                debug_function<Debug_CppFunction_WithFormals_Impl>( *this, name ) ;
                SEXP res = FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
                Rprintf( "\n" ) ;
                return res ;
            }
    
            inline int nargs(){ return sizeof...(Args) ; }
            inline void signature(std::string& s, const char* name){ ::Rcpp::signature<OUT,Args...>(s, name) ; }
            inline SEXP get_formals(){ return formals; }
        
        private:
            List formals ;
            Fun ptr_fun ;
            std::string name ;
    } ;

}    
#endif
