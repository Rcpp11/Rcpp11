//
// CppFunction.h:  C++ exposed function
//
// Copyright (C) 2012 Dirk Eddelbuettel and Romain Francois
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

    /** 
     * base class of all exported C++ functions. Template deduction in the
     * Module_generated_function.h file creates an instance of a class that 
     * derives CppFunction (see Module_generated_CppFunction.h fr all the 
     * definitions
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
         * The actual function pointer, as a catch all function pointer
         * (see Rdynload.h for definition of DL_FUNC)
         */
        virtual DL_FUNC get_function_ptr() = 0  ;        
        
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
            inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT, Args...>(s, name) ; }
            inline DL_FUNC get_function_ptr(){ return (DL_FUNC)ptr_fun ; }
            
        private:
            Fun ptr_fun ;
    } ;

    template <typename OUT, typename... Args>
    class CppFunction_WithFormals_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            CppFunction_WithFormals_Impl(Fun fun, Rcpp::List formals_,  const char* docstring = 0 ) : 
                CppFunction(docstring), formals(formals_), ptr_fun(fun){}
            
            inline SEXP operator()(SEXP* args) {
                return FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
            }
    
            inline int nargs(){ return sizeof...(Args) ; }
            inline void signature(std::string& s, const char* name){ Rcpp::signature<OUT,Args...>(s, name) ; }
            inline DL_FUNC get_function_ptr(){ return (DL_FUNC)ptr_fun ; }
            inline SEXP get_formals(){ return formals; }
        
        private:
            Rcpp::List formals ;
            Fun ptr_fun ;
    } ;
    
#endif
