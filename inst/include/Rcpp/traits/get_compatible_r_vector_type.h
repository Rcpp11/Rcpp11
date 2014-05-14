#ifndef Rcpp__traits__get_compatible_r_vector_type__h
#define Rcpp__traits__get_compatible_r_vector_type__h

namespace Rcpp{
    namespace traits{

        // not a primitive
        template <typename T, bool prim>
        struct get_compatible_r_vector_type__dispatch {
            enum { 
                rtype = r_sexptype_traits<typename T::stored_type>::rtype 
            } ; 
        } ;
        
        // a primitive
        template <typename T>
        struct get_compatible_r_vector_type__dispatch<T,true> {
            enum { 
                rtype = r_sexptype_traits<T>::rtype 
            } ; 
        } ;
        
        template <typename T>
        struct get_compatible_r_vector_type {
            enum{
               rtype = get_compatible_r_vector_type__dispatch<T, is_primitive<T>::value >::rtype  
            } ;
        } ;

    }
}

#endif
