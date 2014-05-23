#ifndef Rcpp__sugar__r_binary_op_h
#define Rcpp__sugar__r_binary_op_h

namespace Rcpp{
    
        template <typename T, typename Op>
        struct comp_op_no_check {
            Op op ;
            
            inline int operator()(T x, T y) const {
                return op(x,y) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct comp_op_check_lhs {
            Op op ;
            
            inline int operator()(T x, T y) const {
                if ( x == NA ) return NA ; 
                return op(x,y) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct comp_op_check_rhs {
            Op op ;
            
            inline int operator()(T x, T y) const {
                if( y == NA ) return NA ;
                return op(x,y) ;    
            }
            
        } ;
        
        template <typename T, typename Op>
        struct comp_op_check_both {
            Op op ;
            
            inline int operator()(T x, T y) const {
                if( y == NA || x == NA ) return NA ;
                return op(x,y) ;    
            }
            
        } ;
                      
        template <int RTYPE, bool LHS_NA, bool RHS_NA, template <class> class op >
        struct comp_op_type {
            typedef typename Rcpp::traits::storage_type<RTYPE>::type T ;
            typedef op<T> Op ;
            
            typedef typename std::conditional<
                LHS_NA,
                typename std::conditional<
                    RHS_NA, 
                    comp_op_check_both<T,Op>, 
                    comp_op_check_lhs<T,Op>
                >::type, 
                typename std::conditional<
                    RHS_NA, 
                    comp_op_check_rhs<T,Op>, 
                    comp_op_no_check<T,Op>
                >::type
            >::type type ;
        } ;
        
    namespace sugar {
        
        #undef RCPP_OP
        #define RCPP_OP(NAME,OP)                                            \
        template <int RTYPE>                                                \
        class NAME {                                                        \
        public:                                                             \
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;    \
            inline int operator()( STORAGE lhs, STORAGE rhs) const {       \
                return lhs OP rhs ;                                         \
            }                                                               \
        } ;
        RCPP_OP(less,<)
        RCPP_OP(greater,>)
        RCPP_OP(less_or_equal,<=)
        RCPP_OP(greater_or_equal,>=)
        RCPP_OP(equal,==)
        RCPP_OP(not_equal,!=)
        #undef RCPP_OP
    
    
    } // sugar
} // Rcpp

#endif
