#ifndef Rcpp_Module_debug_constructor_h
#define Rcpp_Module_debug_constructor_h

namespace Rcpp{
    
    template <typename Class, typename ConstructorImpl, typename... Args>
    void debug_constructor(ConstructorImpl& ctor){ 
        std::string s ; 
        std::string ctor_name = DEMANGLE(Class) ;
        ctor_name += "::"  ;
        ctor_name += DEMANGLE(Class) ;
        ctor.signature( s, ctor_name.c_str() ) ;
        Rprintf( "    %70s   ...", s.c_str() ) ;
    }

}
#endif
