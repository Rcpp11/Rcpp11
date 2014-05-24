#ifndef Rcpp__sugar__r_arith_op_h
#define Rcpp__sugar__r_arith_op_h

namespace Rcpp{
    namespace internal{  
        
        template <typename T, typename Op>
        struct arith_op_check_lhs {
            Op op ;
            
            inline auto operator()(T x, T y) const -> decltype( op(x,y) )  {
                if ( x == NA ) return NA ; 
                return op(x,y) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct arith_op_check_rhs {
            Op op ;
            
            inline auto operator()(T x, T y) const -> decltype( op(x,y) )  {
                if( y == NA ) return NA ;
                return op(x,y) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct arith_op_check_both {
            Op op ;
            
            inline auto operator()(T x, T y) const -> decltype( op(x,y) )  {
                if( y == NA || x == NA ) return NA ;
                return op(x,y) ;    
            }
            
        } ;
    }
    
    template <int RTYPE, bool LHS_NA, bool RHS_NA, template <class> class op >
    struct arith_op_type {
        typedef typename Rcpp::traits::storage_type<RTYPE>::type T ;
        typedef op<T> Op ;
          
        typedef typename std::conditional<
            RTYPE == REALSXP,
            Op,
            typename std::conditional<
                LHS_NA,
                typename std::conditional<
                    RHS_NA, 
                    internal::arith_op_check_both<T,Op>, 
                    internal::arith_op_check_lhs<T,Op>
                >::type, 
                typename std::conditional<
                    RHS_NA, 
                    internal::arith_op_check_rhs<T,Op>, 
                    Op
                >::type
            >::type
        >::type type ;
    } ;
    
} // Rcpp

#endif
