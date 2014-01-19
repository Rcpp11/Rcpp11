#ifndef Rcpp_wrap_EnumWrapper_h
#define Rcpp_wrap_EnumWrapper_h
 
namespace Rcpp{

    template <typename T> struct EnumWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "EnumWrapper<%s>::wrap() ", DEMANGLE(T) ) 
            return internal::primitive_wrap( typename std::underlying_type<T>::type( object ) ) ;    
        }
    } ;
    
    template <> struct EnumWrapper<Rboolean> {
        static inline SEXP wrap(const Rboolean& object) { 
            RCPP_DEBUG( "EnumWrapper<Rboolean>::wrap() " ) 
            return Rf_ScalarLogical(object) ; ;    
        }
    } ;
    
}

#endif
