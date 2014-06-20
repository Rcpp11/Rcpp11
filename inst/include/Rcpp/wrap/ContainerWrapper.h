#ifndef Rcpp_wrap_ContainerWrapper_h
#define Rcpp_wrap_ContainerWrapper_h
 
namespace Rcpp{
  
    template <typename T> struct ContainerWrapper {
        static inline SEXP wrap(const T& object) {
            // return Vector< traits::r_sexptype_traits<typename T::value_type>::rtype >( import( object.begin(), object.end() ) ) ;
            return internal::range_wrap( object.begin(), object.end() ) ;    
        }
    } ;
    
}

#endif
