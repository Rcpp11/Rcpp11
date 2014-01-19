#ifndef Rcpp_Module_debug_function_h
#define Rcpp_Module_debug_function_h
 
namespace Rcpp{
    
    template <typename FunctionClass>
    void debug_function( FunctionClass& fun, std::string& name){ 
        std::string s ; 
        fun.signature( s, name.c_str() ) ;
        Rprintf( "    %70s   ...", s.c_str() ) ;
    }

}
#endif
