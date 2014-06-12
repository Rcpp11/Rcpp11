#ifndef Rcpp__traits__is_primitive__h
#define Rcpp__traits__is_primitive__h

namespace Rcpp{
    namespace traits{
    
        template <typename T> struct is_primitive : public std::is_same<
            typename r_type_traits<typename std::decay<T>::type >::r_category , 
            r_type_primitive_tag
        >{} ;
        
        template <typename T> struct is_not_primitive : public std::integral_constant<bool,!is_primitive<T>::value>{};
    
    }
}

#endif
