#ifndef Rcpp_wrap_ContainerWrapper_h
#define Rcpp_wrap_ContainerWrapper_h
 
namespace Rcpp{
namespace internal{
    
    template <typename T>
    inline SEXP wrap_dispatch_unknown_iterable__logical( const T& object, std::true_type){
        RCPP_DEBUG( "wrap_dispatch_unknown_iterable__logical<%s>(., true  )", DEMANGLE(T) )
        size_t size = object.size() ;
        Shield<SEXP> x = Rf_allocVector( LGLSXP, size );
        std::copy( object.begin(), object.end(), LOGICAL(x) ) ; 
        return x ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_unknown_iterable__logical( const T& object, std::false_type){
        RCPP_DEBUG( "wrap_dispatch_unknown_iterable__logical<%s>(., false  )", DEMANGLE(T) )
        return range_wrap( object.begin(), object.end() ) ;
    }
    
}
    
    template <typename T> struct ContainerWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "ContainerWrapper<%s>::wrap() ", DEMANGLE(T) ) 
            return internal::range_wrap( object.begin(), object.end() ) ;    
        }
    } ;
    
}

#endif
