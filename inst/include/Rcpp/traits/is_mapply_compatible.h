#ifndef Rcpp__traits__is_mapply_compatible__h
#define Rcpp__traits__is_mapply_compatible__h

namespace Rcpp{
    namespace traits{
    
        template <typename T> struct is_mapply_compatible : public std::integral_constant<bool, 
            is_primitive<T>::value || is_vector_expression<T>::value
        >{} ;
    
    } // traits
} // Rcpp

#endif
