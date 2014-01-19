#ifndef Rcpp_wrap_SugarExpressionWrapper_h
#define Rcpp_wrap_SugarExpressionWrapper_h
 
namespace Rcpp{

    namespace internal{
        template <typename T>
        inline SEXP wrap_range_sugar_expression( const T& object );
    }
    
    template <typename T> struct SugarExpressionWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "SugarExpressionWrapper<%s>::wrap() ", DEMANGLE(T) ) 
            return internal::wrap_range_sugar_expression( object );    
        }
    } ;
    
}

#endif
