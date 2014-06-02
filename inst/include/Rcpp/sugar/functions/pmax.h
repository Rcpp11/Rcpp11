#ifndef Rcpp__sugar__pmax_h
#define Rcpp__sugar__pmax_h

namespace Rcpp{
    namespace sugar{
    
        template <typename T>
        struct pmax_op {
            inline T operator()( T lhs, T rhs ){
                return std::max( lhs, rhs ) ;    
            }
        } ;
    
        template <typename T>
        struct pmin_op {
            inline T operator()( T lhs, T rhs ){
                return std::min( lhs, rhs ) ;    
            }
        } ;
    
    } // sugar
    
    
    template <typename T1, typename T2>
    inline typename std::enable_if<
        traits::is_mapply_compatible<T1>::value &&
        traits::is_mapply_compatible<T2>::value &&
        traits::same_mapply_scalar_type<T1,T2>::value && 
        Mapply< sugar::pmax_op<typename sugar::mapply_scalar_type<T1>::type>, T1, T2 >
    >
    pmax( const T1& lhs, const T2& rhs ){
        return mapply( sugar::pmax_op<typename sugar::mapply_scalar_type<T1>::type>(), lhs, rhs ) ;  
    }
    
    template <typename T1, typename T2>
    inline typename std::enable_if<
        traits::is_mapply_compatible<T1>::value &&
        traits::is_mapply_compatible<T2>::value &&
        traits::same_mapply_scalar_type<T1,T2>::value && 
        Mapply< sugar::pmax_op<typename sugar::mapply_scalar_type<T1>::type>, T1, T2 >
    >
    pmin( const T1& lhs, const T2& rhs ){
        return mapply( sugar::pmin_op<typename sugar::mapply_scalar_type<T1>::type>(), lhs, rhs ) ;  
    }
    
    
} // Rcpp

#endif
