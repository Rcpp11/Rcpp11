#ifndef Rcpp__vector_concat_h
#define Rcpp__vector_concat_h

namespace Rcpp{
    
    template <typename T>
    inline int get_size_one( const T&, std::true_type ){
        return 1 ; 
    }
    template <typename T>
    inline int get_size_one( const T& obj, std::false_type ){
        return obj.size() ; 
    }
    
    template <typename First>
    int get_size( const First& first){
        return get_size_one<First>(first, typename traits::is_primitive<First>::type() ) ;   
    }
    
    template <typename First, typename... Rest>
    int get_size( const First& first, Rest... rest ){
        return get_size_one<First>(first, typename traits::is_primitive<First>::type() ) + get_size(rest...) ;   
    }
    
    
}

#endif
