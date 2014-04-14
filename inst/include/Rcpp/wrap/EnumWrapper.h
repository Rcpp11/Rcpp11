#ifndef Rcpp_wrap_EnumWrapper_h
#define Rcpp_wrap_EnumWrapper_h
 
namespace Rcpp{

    template <typename T> struct EnumWrapper {
        static inline SEXP wrap(const T& object) { 
            #if defined(RCPP_HAS_UNDERLYING_TYPE)
            return internal::primitive_wrap( typename std::underlying_type<T>::type( object ) ) ;
            #else 
            return internal::primitive_wrap( static_cast<int>( object ) ) ;
            #endif
        }
    } ;
    
}

#endif
