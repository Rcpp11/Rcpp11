#ifndef Rcpp_Module_get_signature_h
#define Rcpp_Module_get_signature_h

namespace Rcpp{
    
    template <typename... Args>
    struct SignatureBody ;
    
    template <typename First, typename... Args>
    struct SignatureBody<First, Args...> {
        static void process( std::string& s ){
            s += get_return_type<First>() ;
            s += ", " ;
            SignatureBody<Args...>::process(s) ;
        }
    } ;
    
    template <typename First>
    struct SignatureBody<First>{
        static void process( std::string& s ){
            s += get_return_type<First>() ;
        }
    } ;
    
    template <>
    struct SignatureBody<>{
        static void process( std::string& ){}
    } ;
    
    template <typename OUT, typename... Args>
    inline void signature(std::string& s, const char* name ){
        s.clear() ;
        s += get_return_type<OUT>() ;
        s += " " ;
        s += name ;
        s += "(" ;
        SignatureBody<Args...>::process( s ) ;
        s += ")" ;
    }
    
    template <typename... Args>
    inline void ctor_signature( std::string& s, const std::string& classname ){
        s.assign(classname) ;
        s += "(" ; 
        SignatureBody<Args...>::process( s ) ;
        s += ")" ;
    }

}
#endif
