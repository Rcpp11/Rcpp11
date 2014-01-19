#ifndef Rcpp_Module_debug_method_h
#define Rcpp_Module_debug_method_h

namespace Rcpp{
    
    template <typename Class, typename MethodClass>
    void debug_method( MethodClass& method, std::string& name, Class* object){ 
        std::string s ; 
        std::string method_name = DEMANGLE(Class) ;
        method_name += "::"  ;
        method_name += name ;
        method.signature( s, method_name.c_str() ) ;
        Rprintf( "    %70s   [object = <%p>] ...", s.c_str(), object) ;
    }

}
#endif
