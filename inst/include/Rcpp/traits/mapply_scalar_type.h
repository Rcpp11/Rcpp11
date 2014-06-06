#ifndef Rcpp__traits__mapply_scalar_type__h
#define Rcpp__traits__mapply_scalar_type__h

namespace Rcpp{
    namespace traits{
    
        template <typename T, bool>
        struct mapply_scalar_type_dispatch ;
        
        template <typename T>
        struct mapply_scalar_type_dispatch<T, false>{
            typedef typename std::decay<T>::type::value_type type ;       
        } ;
        
        template <typename T>
        struct mapply_scalar_type_dispatch<T, true>{
            typedef typename std::decay<T>::type type ;       
        } ;
        
        template <typename T>
        struct mapply_scalar_type {
            typedef typename mapply_scalar_type_dispatch<T, is_primitive<T>::value >::type type ;
        } ;
            
        
    } // traits
} // Rcpp

#endif
