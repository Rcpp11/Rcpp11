#ifndef Rcpp_Module_CppFunction_h
#define Rcpp_Module_CppFunction_h

#include <utility>

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
        virtual ~CppFunction(){}
        
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
                
            inline SEXP operator()(SEXP* args) override {
                return FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
            }
    
            inline int nargs() override{ return sizeof...(Args); }
            inline void signature(std::string& s, const char* name) override{ ::Rcpp::signature<OUT, Args...>(s, name) ; }
            
        private:
            Fun ptr_fun ;
    } ;

    template <typename OUT, typename... Args>
    class CppFunction_WithFormals_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            CppFunction_WithFormals_Impl(Fun fun, List formals_,  const char* docstring = 0 ) : 
                CppFunction(docstring), formals(std::move(formals_)), ptr_fun(fun){}
            
            inline SEXP operator()(SEXP* args) override {
                return FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
            }
    
            inline int nargs() override{ return sizeof...(Args) ; }
            inline void signature(std::string& s, const char* name) override{ ::Rcpp::signature<OUT,Args...>(s, name) ; }
            inline SEXP get_formals() override{ return formals; }
        
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
                
            inline SEXP operator()(SEXP* args) override {
                debug_function<Debug_CppFunction_Impl>( *this, name ) ;
                SEXP res = FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
                Rprintf( "\n" ) ;
                return res ;
            }
    
            inline int nargs() override{ return sizeof...(Args); }
            inline void signature(std::string& s, const char* name_) override{ ::Rcpp::signature<OUT, Args...>(s, name_) ; }
            
        private:
            Fun ptr_fun ;
            std::string name ;
    } ;

    template <typename OUT, typename... Args>
    class Debug_CppFunction_WithFormals_Impl : public CppFunction {
        public:
            typedef OUT (*Fun)(Args...) ;
        
            Debug_CppFunction_WithFormals_Impl(Fun fun, List formals_, const char* name_, const char* docstring = 0 ) : 
                CppFunction(docstring), formals(std::move(formals_)), ptr_fun(fun), name(name_) {}
            
            inline SEXP operator()(SEXP* args) override {
                debug_function<Debug_CppFunction_WithFormals_Impl>( *this, name ) ;
                SEXP res = FunctionInvoker<OUT,Args...>( ptr_fun, args ).invoke() ;
                Rprintf( "\n" ) ;
                return res ;
            }
    
            inline int nargs() override{ return sizeof...(Args) ; }
            inline void signature(std::string& s, const char* name_) override{ ::Rcpp::signature<OUT,Args...>(s, name_) ; }
            inline SEXP get_formals() override{ return formals; }
        
        private:
            List formals ;
            Fun ptr_fun ;
            std::string name ;
    } ;

}    
#endif
