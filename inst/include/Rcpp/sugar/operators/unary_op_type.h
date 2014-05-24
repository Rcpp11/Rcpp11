#ifndef Rcpp__sugar__unary_op_type_h
#define Rcpp__sugar__unary_op_type_h

namespace Rcpp{
    namespace internal{  
        
        template <typename T, typename Op>
        struct unary_op_no_check {
            Op op ;
            
            inline auto operator()(T x) const -> decltype( op(x) ) {
                return op(x) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct unary_op_check {
            Op op ;
            
            inline auto operator()(T x) const -> decltype( op(x) )  {
                if ( x == NA ) return NA ; 
                return op(x) ;    
            }
            
        } ;
        
    }
    
    template <int RTYPE, bool LHS_NA, template <class> class op >
    struct unary_op_type {
        typedef typename Rcpp::traits::storage_type<RTYPE>::type T ;
        typedef op<T> Op ;
          
        typedef typename std::conditional<LHS_NA,
            internal::unary_op_check<T,Op>,
            internal::unary_op_no_check<T,Op>
        >::type type ; 
        
    } ;
    
} // Rcpp

#endif
