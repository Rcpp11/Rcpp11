#ifndef Rcpp_Module_get_return_type_h
#define Rcpp_Module_get_return_type_h

namespace Rcpp{
    
    struct void_type{} ;
    
    template <typename OUT>
    inline std::string get_return_type_dispatch( std::false_type ){
        return Demangler<OUT>::get() ;
    }
    template <typename OUT>
    inline std::string get_return_type_dispatch( std::true_type ){
        typedef typename std::remove_pointer<OUT>::type pointer ;
        std::string res = Demangler<pointer>::get().data() ;
        res += "*" ;
        return res ;
    }
    
    template <typename OUT>
    inline std::string get_return_type(){
        return get_return_type_dispatch<OUT>( typename std::is_pointer<OUT>::type() ) ;
    }
    template <>
    inline std::string get_return_type<void_type>(){
        return "void" ;
    }
    
}
#endif
