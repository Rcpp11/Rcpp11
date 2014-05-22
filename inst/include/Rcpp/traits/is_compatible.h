#ifndef Rcpp__traits__is_compatible__h
#define Rcpp__traits__is_compatible__h

namespace Rcpp{
    namespace traits{

        template <int RTYPE, typename T, bool prim>
        struct is_compatible_type {
            typedef typename std::is_same<typename T::stored_type, typename storage_type<RTYPE>::type >::type type ;
        } ;
        template <int RTYPE, typename T>
        struct is_compatible_type<RTYPE,T,true> {
            typedef typename std::is_same<T, typename storage_type<RTYPE>::type >::type type ;
        } ;

        template <int RTYPE, typename T>
        struct is_compatible {
            typedef typename is_compatible_type<RTYPE,T,traits::is_primitive<typename std::decay<T>::type >::value>::type type ;
        } ;
        
        
    }
}

#endif
