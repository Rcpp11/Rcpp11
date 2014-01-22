#ifndef Rcpp__vector_concat_h
#define Rcpp__vector_concat_h

namespace Rcpp{
    namespace traits{
            
        template <int RTYPE, typename T>
        struct is_compatible : public std::conditional<
            traits::is_primitive<T>::value, 
            typename std::is_same<T, typename storage_type<RTYPE>::type >::type, 
            typename std::integral_constant<bool, std::is_same<typename T::value_type, typename storage_type<RTYPE>::type >::value >::type
        >::type{} ;
        
        template <int RTYPE, typename... Args>
        struct all_compatible {
           typedef typename and_< typename is_compatible<RTYPE,Args>::type ... >::type type; 
        } ;
    }

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
