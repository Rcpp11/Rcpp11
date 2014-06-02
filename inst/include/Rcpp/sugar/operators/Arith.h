#ifndef Rcpp__sugar__Arith_h
#define Rcpp__sugar__Arith_h

namespace Rcpp{
    namespace sugar{
        
        template <int RTYPE, bool RHS_NA, typename RHS_T, template <class> class Op >
        class Arith_Primitive_Vector : 
            public SugarVectorExpression<RTYPE, true , Arith_Primitive_Vector<RTYPE,RHS_NA,RHS_T, Op> >, 
            public custom_sugar_vector_expression
            {
        public:
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            typedef typename Rcpp::SugarVectorExpression<RTYPE,RHS_NA,RHS_T> RHS_TYPE ;
            typedef typename Rcpp::arith_op_type<RTYPE,true,RHS_NA,Op>::type Operator ;
        
            Arith_Primitive_Vector( STORAGE lhs_, const RHS_TYPE& rhs_ ) : 
                lhs(lhs_), rhs(rhs_) {}
        
            inline STORAGE operator[]( R_xlen_t i ) const {
                return op(lhs, rhs[i]) ;
            }
        
            inline R_xlen_t size() const { return rhs.size() ; }
              
            template <typename Target>
            inline void apply( Target& target ) const {
                if( lhs == NA ) {
                    std::fill( target.begin(), target.end(), lhs ) ;
                } else {
                    std::transform( sugar_begin(rhs), sugar_end(rhs), target.begin(), [this]( STORAGE x){
                        return typename Rcpp::arith_op_type<RTYPE,false,RHS_NA,Op>::type()( lhs, x ) ;            
                    }) ;    
                }
                       
            }
        private:     
            
            STORAGE lhs ;
            const RHS_TYPE& rhs ;
            Operator op ;
        } ;
        
        
    }
}

#endif
