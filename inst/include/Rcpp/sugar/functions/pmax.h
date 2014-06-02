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
        ( traits::is_primitive<T1>::value || traits::is_vector_expression<T1>::value ) &&
        ( traits::is_primitive<T2>::value || traits::is_vector_expression<T2>::value ) &&
        std::is_same< typename sugar::mapply_input_type<T1>::type, typename sugar::mapply_input_type<T2>::type >::value, 
        Mapply< sugar::pmax_op<typename sugar::mapply_input_type<T1>::type>, T1, T2 >
    >
    pmax( const T1& lhs, const T2& rhs ){
        return mapply( sugar::pmax_op<typename sugar::mapply_input_type<T1>::type>(), lhs, rhs ) ;  
    }
    
    template <typename T1, typename T2>
    inline typename std::enable_if<
        ( traits::is_primitive<T1>::value || traits::is_vector_expression<T1>::value ) &&
        ( traits::is_primitive<T2>::value || traits::is_vector_expression<T2>::value ) &&
        std::is_same< typename sugar::mapply_input_type<T1>::type, typename sugar::mapply_input_type<T2>::type >::value, 
        Mapply< sugar::pmax_op<typename sugar::mapply_input_type<T1>::type>, T1, T2 >
    >
    pmin( const T1& lhs, const T2& rhs ){
        return mapply( sugar::pmin_op<typename sugar::mapply_input_type<T1>::type>(), lhs, rhs ) ;  
    }
    
    
} // Rcpp

#endif
