#ifndef Rcpp__sugar__Comparator_h
#define Rcpp__sugar__Comparator_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool LHS_NA, typename T, template <class> class Op>
        class Comparator_With_One_Value : 
            public SugarVectorExpression< LGLSXP, true, Comparator_With_One_Value<RTYPE,LHS_NA,T,Op> >, 
            public custom_sugar_vector_expression 
        {
        public:
            typedef typename Rcpp::SugarVectorExpression<RTYPE,LHS_NA,T> VEC_TYPE ;
            typedef typename traits::storage_type<RTYPE>::type STORAGE ;
            
            typedef typename Rcpp::comp_op_type<RTYPE,LHS_NA,true,Op>::type Operator ;
            
            Comparator_With_One_Value( const VEC_TYPE& lhs_, STORAGE rhs_ ) : lhs(lhs_), rhs(rhs_){}
        
            inline Rboolean operator[]( R_xlen_t i ) const {
                return op( lhs[i], rhs ) ;
            }
        
            inline R_xlen_t size() const { return lhs.size() ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                if( rhs == NA ) {
                    std::fill( target.begin(), target.end(), NA_VALUE ) ;
                } else {
                    std::transform( sugar_begin(lhs), sugar_end(lhs), target.begin(), [this]( STORAGE x){
                        return typename Rcpp::arith_op_type<RTYPE,LHS_NA,false,Op>::type()( x, rhs ) ? TRUE : FALSE ;            
                    }) ; 
                }
            }
            
        private:
            const VEC_TYPE& lhs ;
            STORAGE rhs ;
            Operator op ;
        
        } ;

        
        
    }
}


#endif
